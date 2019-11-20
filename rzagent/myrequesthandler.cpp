#include "myrequesthandler.h"
#include <QtCore>
#include <QString>
#include <QStringList>
#include <iostream>
#include "Poco/Net/HTTPResponse.h"
#include "Poco/URI.h"
#include "Poco/Path.h"
#include "Poco/Base64Encoder.h"
#include "Poco/Base64Decoder.h"
#include "umxCommonLib/cjson/cJSONpp.h"
//
#include <vector>
#include "runtime.h"
#include "umxDBLib/umxDBGlobal.h"
#include "umxCommonLib/umxCommonGlobal.h"
#include "umxDBLib/umxDB.h"
#include "algoutils.h"
#include "utilshelper.h"
#include <QByteArray>
using namespace std;
using namespace Poco;
using namespace Net;
using namespace cjsonpp;

#include "runtime.h"
#include "Poco/Logger.h"
#include "Poco/FileChannel.h"
#include "Poco/AutoPtr.h"
#include "Poco/PatternFormatter.h"
#include "Poco/FormattingChannel.h"
using Poco::DirectoryIterator;
using Poco::Path;
using Poco::File;
using Poco::Logger;
using Poco::FileChannel;
using Poco::AutoPtr;
using Poco::PatternFormatter;
using Poco::FormattingChannel;


MyRequestHandler::MyRequestHandler()
{

}

void MyRequestHandler::handleRequest(HTTPServerRequest &request, HTTPServerResponse &response)
{
    Poco::URI uri(request.getURI());
    QStringList path=QString::fromStdString(uri.getPath()).split("/");
    std::cout << uri.getPath() <<endl;
    std::cout << uri.getQuery() <<endl;
    std::cout <<qPrintable(path.at(1))<<endl;
    //std::cout <<qPrintable(path.at(2))<<endl;
    qDebug()<<path.count();
    //post /uploadimage

    Logger& m_logger = dzrun.initLog("webrequest");
    poco_information_f1(m_logger,"web request: %s",uri.getPathAndQuery());

    qDebug()<<"web request:"<< QString::fromStdString( uri.getPathAndQuery());

    if(path.value(1)=="uploadimage" && request.getMethod()=="POST"){
        api_UploadImages(request,response);
        return;
    }
    if(path.value(1)=="reboot" && request.getMethod()=="POST")
    {
        poco_information(logger_handle,"api:reboot");
        system("reboot");
    }


    //get /personscount
    if(path.value(1)=="personscount" && request.getMethod()=="GET"){
        api_GetPersonsCount(request,response);
        return;
    }

    //get /persons
    if(path.value(1) =="persons" && request.getMethod()=="GET"){
            api_GetPersons(request,response);
        return;
    }
    //post /persons
    if(path.value(1) =="persons" && request.getMethod()=="POST"){
            api_PostPersons(request,response);
        return;
    }

    if(path.value(1) =="deletepersons" && request.getMethod()=="POST"){
            api_DeletePersons(request,response);
        return;
    }

    if(path.value(1) =="persons" && request.getMethod()=="PUT"){
            api_Persons(request,response);
        return;
    }
    //get logs
    if(uri.getPath()=="/logs")
    {
        api_GetLogs(request,response);
        return;
    }
    //get logs
    if(uri.getPath()=="/deletelogs")
    {
        api_DeleteLogs(request,response);
        return;
    }
    //获取模板
    if(uri.getPath()=="/getiristemplate" && request.getMethod()=="PUT")
    {
        api_GetTemplates(request,response);
        return;
    }
    //login
    if(uri.getPath()=="/login" && request.getMethod()=="POST")
    {
        api_Login(request,response);
        return;
    }
    response.setContentType("application/json");
    response.redirect(request.getURI(),HTTPResponse::HTTPStatus::HTTP_NOT_IMPLEMENTED);
}

void MyRequestHandler::api_Persons(HTTPServerRequest &request, HTTPServerResponse &response)
{
    try{

        if(request.getMethod()=="GET")
        {

        }
        else if(request.getMethod()=="POST")
        {
            //TODO
        }else if(request.getMethod()=="PUT")
        {
            //std::string id= QString::fromStdString(request.getURI()).split("/").at(2).toStdString();
            AlgoUtils *algo = new AlgoUtils(dzrun.umxalgo_Handle);

            std::istream &i = request.stream();
            int len = request.getContentLength();
            char* buffer = new char[len];
            i.read(buffer, len);
            std::cout<<buffer<<std::endl;
            QString s=QString(buffer);
            cjsonpp::JSONObject obj=cjsonpp::parse(s.toStdString());
            Person person;
            try {
                person.Id = obj.get<JSONObject>("Id").as<string>();
                person.Name =obj.get<string>("Name");
                person.Card = obj.get<string>("Card");
                person.WiegandCode = obj.get<int>("WiegandCode");
            } catch (const cjsonpp::JSONError& e) {
                std::cerr << e.what() << '\n';
            }

            int ret=algo->getTemplates(person);
            if(ret>=0)
            {
                //response.redirect(request.getURI(),HTTPResponse::HTTPStatus::HTTP_OK);
                response.setChunkedTransferEncoding(true);
                response.setContentType("application/json");
                std::ostream& ostr = response.send();
                JSONObject obj;
                obj.set("Id",person.Id);
                obj.set("Name",person.Name);
                obj.set("Card",person.Card);
                obj.set("WeigandCode",person.WiegandCode);
                obj.set("LeftEyeScore",algo->leftscore);
                obj.set("RightEyeScore",algo->rightscore);
                ostr<<obj.print();
                response.setStatusAndReason(HTTPResponse::HTTPStatus::HTTP_OK);
            }
            else
                response.setStatusAndReason(HTTPResponse::HTTPStatus::HTTP_NOT_FOUND);

        }
    }catch(Exception)
    {
        response.setStatusAndReason(HTTPResponse::HTTPStatus::HTTP_BAD_REQUEST);
    }
    response.send();
}

void MyRequestHandler::api_GetPersonsCount(HTTPServerRequest &request, HTTPServerResponse &response)
{
    response.setChunkedTransferEncoding(true);
    response.setContentType("application/json");
    int count;
    int ret=umxDB_countSubject(dzrun.umxdb_Handle,&count);
    int suc_flag=1;
    if(ret==UMXDB_SUCCESS)
        suc_flag=0;

    std::ostream& ostr = response.send();
    JSONObject obj;
    obj.set("suc_flag",suc_flag);
    obj.set("error_msg","");
    obj.set("staff_count",count);
    ostr<<obj.print();

    response.setStatusAndReason(HTTPResponse::HTTPStatus::HTTP_OK);
}

void MyRequestHandler::api_GetPersons(HTTPServerRequest &request, HTTPServerResponse &response)
{
    Logger &m_logger = dzrun.initLog("webrequest");

    Poco::URI uri(request.getURI());
    QStringList path=QString::fromStdString(uri.getPath()).split("/");
    QStringList query=QString::fromStdString(uri.getQuery()).split("&");
    int page_no=1;
    int page_count=10;
    try{
        for(int i=0;i<query.count();i++){
            QStringList kv=query[i].split("=");
            if(kv.at(0)=="page_no")
                page_no=kv.at(1).toInt();
            if(kv.at(0)=="page_count")
                page_count=kv.at(1).toInt();
        }
    }
    catch(Exception)
    {

    }

    response.setChunkedTransferEncoding(true);
    response.setContentType("application/json");

    std::vector<SubjectData> result;
    int ret=umxDB_selectIrisesByPage(dzrun.umxdb_Handle,page_no,page_count,&result);
    //std::vector<UserInfoData> userinfoResult;
    //umxDB_selectUserInfoByPage(dzrun.umxdb_Handle,1,20,&userinfoResult);
    int suc_flag=1;
    if(ret==UMXDB_SUCCESS)
        suc_flag=0;
    int count=result.size();
    std::ostream& ostr = response.send();
    JSONObject obj;
    obj.set("suc_flag",suc_flag);
    obj.set("error_msg","");
    obj.set("page",page_no);
    obj.set("pagesize",page_count);
    obj.set("count",count);
    JSONObject r=cjsonpp::arrayObject();
    for(int i=0;i<result.size();i++){
        JSONObject item ;
        SubjectData sd=result[i];
        UserInfoData ui;
        umxDB_selectUserInfoByUUID(dzrun.umxdb_Handle,sd._userUUID,&ui);
        JSONObject sdObj = sd.AsJSONObject();

        item.set("staff_no",sd._userUUID);
        item.set("name",sd._lastName);
        item.set("card_no",ui._card);
        item.set("password",ui._pin);
        //
        std::vector<FaceData> allface;
        FaceData faroff;
        FaceData faron;
        umxDB_selectFacesByUUID(dzrun.umxdb_Handle,sd._userUUID,&allface);
        if(allface.size()>=2){
            faroff=allface[0];
            faron=allface[1];
            item.set("face_faroff",faroff.AsJSONString());
            item.set("face_faron",faron.AsJSONString());
        }else
        {
            item.set("face_faroff","");
            item.set("face_faron","");
        }
        //
        item.set("left_feature",sdObj.get("left_eye_template").as<string>());
        item.set("right_feature",sdObj.get("right_eye_template").as<string>());
        item.set("is_admin",ui._admin);
        item.set("enable_flag",1);
        item.set("create_time",sd._insertTime);
        item.set("expired_time","");
        item.set("verify_type",ui._indivisual);
        item.set("bypasscard",ui._byPassCard);
        item.set("wiegandcode",sd._wiegandCode);
        r.add(item);
    }
    obj.set("staff_list",r);
    ostr<<obj.print();

    response.setStatusAndReason(HTTPResponse::HTTPStatus::HTTP_OK);

}

void MyRequestHandler::api_PostPersons(HTTPServerRequest &request, HTTPServerResponse &response)
{
    response.setChunkedTransferEncoding(true);
    response.setContentType("application/json");
    int suc_flag=0;
    //read json
    std::istream &i = request.stream();
    int len = request.getContentLength();
    char* buffer = new char[len];
    i.read(buffer, len);
    //std::cout<<buffer<<std::endl;
    QString s=QString(buffer);
    cjsonpp::JSONObject jobj=cjsonpp::parse(s.toStdString());
    //std::cout<<jobj.get<int>("count")<<std::endl;
    std::vector<JSONObject> stafflist= jobj.get("staff_list").asArray<JSONObject>();
    std::cout<<"size:"<<stafflist.size()<<std::endl;
    utilsHelper *util = new utilsHelper();
    JSONObject objlist=cjsonpp::arrayObject();
    //poco_information(dzrun._logger,QString("api:开始下发 %0 人到设备").arg(stafflist.size()).toStdString());
    for(int i=0;i<stafflist.size();i++){
        JSONObject objstaff= stafflist[i];
        //std::cout<<objstaff.get<string>("staff_no")<<std::endl;
        Staff ys;
        ys.staff_no=objstaff.get<string>("staff_no");
        ys.name = objstaff.get<string>("name");
        ys.card_no = objstaff.get<string>("card_no");
        ys.password=objstaff.get<string>("password");
        ys.left_feature=util->fromBase64(objstaff.get<string>("left_feature"));
        ys.right_feature=util->fromBase64(objstaff.get<string>("right_feature"));
        ys.is_admin=objstaff.get<int>("is_admin");
        ys.enable_flag=objstaff.get<int>("enable_flag");
        ys.create_time=objstaff.get<string>("create_time");
        ys.expired_time=objstaff.get<string>("expired_time");
        ys.verify_type=objstaff.get<int>("verify_type");
        ys.bypasscard=objstaff.get<int>("bypasscard");
        try{

            ys.face_faroff=objstaff.get<string>("face_faroff");
            ys.face_faron=objstaff.get<string>("face_faron");
        }
        catch (const JSONError& e) {
            //std::cerr << e.what() << '\n';
            ys.face_faroff="";
            ys.face_faron="";
        }
        try{
            ys.wiegandcode = objstaff.get<int>("wiegandcode");
        }catch (const JSONError& e) {
            //std::cerr << e.what() << '\n';
            ys.wiegandcode=-1;
        }

        //
        int ret=saveStaff(ys);
        if(ret!=0){
            stringstream stream;
            stream<<ret;
            string string_ret=stream.str();

            JSONObject objerr;
            objerr.set("staff_no",ys.staff_no);
            objerr.set("error_msg",string_ret);
            objlist.add(objerr);
        }
        //
    }
    delete util;

    //write json
    std::ostream& ostr = response.send();
    JSONObject obj;
    obj.set("suc_flag",suc_flag);
    obj.set("error_msg","");
    obj.set("error_staff_list",objlist);
    ostr<<obj.print();
    //poco_information(dzrun._logger,QString("api:成功下发 %0 人到设备").arg(stafflist.size()).toStdString());
    response.setStatusAndReason(HTTPResponse::HTTPStatus::HTTP_CREATED);
}

void MyRequestHandler::api_DeletePersons(HTTPServerRequest &request, HTTPServerResponse &response)
{
    response.setChunkedTransferEncoding(true);
    response.setContentType("application/json");
    int suc_flag=0;
    //read json
    std::istream &i = request.stream();
    int len = request.getContentLength();
    char* buffer = new char[len];
    i.read(buffer, len);
    std::cout<<buffer<<std::endl;
    QString s=QString(buffer);
    cjsonpp::JSONObject jobj=cjsonpp::parse(s.toStdString());
    //std::cout<<jobj.get<int>("count")<<std::endl;
    std::vector<JSONObject> stafflist= jobj.get("staff_list").asArray<JSONObject>();
    std::cout<<"size:"<<stafflist.size()<<std::endl;
    utilsHelper *util = new utilsHelper();

    JSONObject objlist=cjsonpp::arrayObject();
    for(int i=0;i<stafflist.size();i++){
        JSONObject objstaff= stafflist[i];
        std::cout<<objstaff.get<string>("staff_no")<<std::endl;
        string staff_no=objstaff.get<string>("staff_no");
        //umxDB_deleteUserInfoByUUID
        int ret=umxDB_deleteUserByUUID(dzrun.umxdb_Handle,staff_no);
        if(ret==-741){
            ret=umxDB_deleteUserInfoByUUID(dzrun.umxdb_Handle,staff_no);
            ret=umxDB_deleteFacesByUUID(dzrun.umxdb_Handle,staff_no);
        }
        if(ret!=0 && ret!=-401){
            stringstream stream;
            stream<<ret;
            string string_ret=stream.str();
            if(ret==-201)
                string_ret="STAFF_UUID_NO_EXIST";

            JSONObject objerr;
            objerr.set("staff_no",staff_no);
            objerr.set("error_msg",string_ret);
            objlist.add(objerr);
        }
        //
    }
    delete util;

    //write json
    std::ostream& ostr = response.send();
    JSONObject obj;
    obj.set("suc_flag",suc_flag);
    obj.set("error_msg","");
    obj.set("error_staff_list",objlist);
    ostr<<obj.print();

    response.setStatusAndReason(HTTPResponse::HTTPStatus::HTTP_OK);
}

int MyRequestHandler::saveStaff(Staff &staff)
{
    SubjectData sd;
    sd._recordVersion = 17952;//8976;
    sd._accessAllowed = true;
    sd._wiegandFacility = -1;
    sd._wiegandSite = -1;
    sd._wiegandCode = (uint)staff.wiegandcode;
    sd._wiegandCustom = "";
    sd._userUUID = staff.staff_no;
    sd._lastName = staff.name;
    sd._leftTemplate=Poco::Data::BLOB(staff.left_feature);
    sd._rightTemplate=Poco::Data::BLOB(staff.right_feature);
    sd._leftImagePath="/usr/local/share/CMITECH/Images/"+sd._userUUID+"_lefteye.jpg";
    sd._rightImagePath="/usr/local/share/CMITECH/Images/"+sd._userUUID+"_righteye.jpg";

    FaceData faroff;
    FaceData faron;
    if(staff.face_faroff!="")
    {
        faroff=FaceData::Parse(staff.face_faroff);
        faron=FaceData::Parse(staff.face_faron);
        faroff._imagePath = "/usr/local/share/CMITECH/Images/"+faroff._userUUID+"_faroff.jpg";
        faron._imagePath = "/usr/local/share/CMITECH/Images/"+faron._userUUID+"_faron.jpg";
    }
    UserInfoData userinfo
            ;
    umxDB_selectUserInfoByUUID(dzrun.umxdb_Handle,sd._userUUID,&userinfo);
    int ret;
    try{

        if(userinfo._userUUID=="")
        {
            sd._firstName = "";
            sd._matchUntil ="";
            ret=umxDB_insertSubject(dzrun.umxdb_Handle,sd);
            ret=umxDB_insertUserInfo(dzrun.umxdb_Handle,sd._userUUID,staff.card_no,staff.password,staff.is_admin,0,staff.bypasscard,staff.verify_type,0,0,0,0,0,"");
            /*
            HTTPResponse::HTTPStatus status= AddSubject(sd);
            userinfo._userUUID=sd._userUUID;
            userinfo._card = staff.card_no;
            userinfo._pin = staff.password;
            userinfo._admin = staff.is_admin;
            userinfo._byPassCard=staff.bypasscard;
            userinfo._indivisual=staff.verify_type;
            userinfo._card=staff.card_no;
            status=AddUserInfo(userinfo);
            */
            if(staff.card_no!=""){
                UMXCommon::CardInfoData cid = UMXCommon::CardInfoData(sd._userUUID,0,staff.card_no,"");
                umxDB_insertCard(dzrun.umxdb_Handle,cid);
            }
            if(staff.face_faroff!="")
                umxDB_insertFace2(dzrun.umxdb_Handle,&faroff);
                //AddFace(faroff);
            if(staff.face_faron!="")
                umxDB_insertFace2(dzrun.umxdb_Handle,&faron);
                //AddFace(faron);
        }else
        {
            std::cout << "update "<<sd._userUUID <<" name="<<sd._lastName<<endl;
            ret=umxDB_updateSubject(dzrun.umxdb_Handle,sd);
            ret=umxDB_updateUserInfoByUUID(dzrun.umxdb_Handle,sd._userUUID,staff.card_no,staff.password,staff.is_admin,0,staff.bypasscard,staff.verify_type,0,0,0,0,0,"");
            umxDB_deleteCardInfoByUUID(dzrun.umxdb_Handle,sd._userUUID);
            if(staff.card_no!=""){
                UMXCommon::CardInfoData cid = UMXCommon::CardInfoData(sd._userUUID,0,staff.card_no,"");
                umxDB_insertCard(dzrun.umxdb_Handle,cid);
            }
            umxDB_deleteFacesByUUID(dzrun.umxdb_Handle,sd._userUUID);
            if(staff.face_faroff!="")
                umxDB_insertFace2(dzrun.umxdb_Handle,&faroff);
            if(staff.face_faron!="")
                umxDB_insertFace2(dzrun.umxdb_Handle,&faron);
        }
    }
    catch(Exception e)
    {
        std::cout<<"saveStaff error:"<<e.message()<<std::endl;
    }
    return ret;
}

void MyRequestHandler::api_Logs(HTTPServerRequest &request, HTTPServerResponse &response)
{
    if(request.getMethod()=="GET")
        api_GetLogs(request,response);

    //if(request.getMethod()=="POST") //delete

}

void MyRequestHandler::api_GetLogs(HTTPServerRequest &request, HTTPServerResponse &response)
{
    Poco::URI uri(request.getURI());
    QStringList path=QString::fromStdString(uri.getPath()).split("/");
    QStringList query=QString::fromStdString(uri.getQuery()).split("&");
    int page_no=1;
    int page_count=10;
    try{
        for(int i=0;i<query.count();i++){
            QStringList kv=query[i].split("=");
            if(kv.at(0)=="page_no")
                page_no=kv.at(1).toInt();
            if(kv.at(0)=="page_count")
                page_count=kv.at(1).toInt();
        }
    }
    catch(Exception)
    {

    }

    response.setChunkedTransferEncoding(true);
    response.setContentType("application/json");


            std::vector<LogEntry> result;
            int ret= umxDB_selectLogEntryByPage(dzrun.umxdb_Handle,page_no,page_count,"asc",&result);
            int suc_flag=1;
            if(ret==UMXDB_SUCCESS)
                suc_flag=0;
            int count=result.size();

            JSONObject obj;
            obj.set("suc_flag",suc_flag);
            obj.set("error_msg","");
            obj.set("page",page_no);
            obj.set("pagesize",page_count);
            obj.set("count",count);
            JSONObject r=cjsonpp::arrayObject();
            for(int i=0;i<result.size();i++){
                JSONObject item ;
                LogEntry log=result[i];

                //
                item.set("staff_no",log.GetUserUUID());
                item.set("swing_card_time",log.GetTimestamp());
                item.set("verify_type",log.GetEventType());
                item.set("additional",log.GetAdditionalData());
                item.set("info",log.GetInfo());
                item.set("id",log.GetId());
                //
                r.add(item);
            }
            obj.set("staff_list",r);
            response.setStatusAndReason(HTTPResponse::HTTPStatus::HTTP_OK);
            std::ostream& ostr = response.send();
            ostr<<obj.print();
}

void MyRequestHandler::api_DeleteLogs(HTTPServerRequest &request, HTTPServerResponse &response)
{
    response.setChunkedTransferEncoding(true);
    response.setContentType("application/json");
    int suc_flag=0;
    //read json
    std::istream &i = request.stream();
    int len = request.getContentLength();
    char* buffer = new char[len];
    i.read(buffer, len);
    std::cout<<buffer<<std::endl;
    QString s=QString(buffer);
    cjsonpp::JSONObject jobj=cjsonpp::parse(s.toStdString());
    std::vector<JSONObject> stafflist= jobj.get("staff_list").asArray<JSONObject>();
    std::cout<<"size:"<<stafflist.size()<<std::endl;
    utilsHelper *util = new utilsHelper();

    JSONObject objlist=cjsonpp::arrayObject();
    for(int i=0;i<stafflist.size();i++){
        JSONObject objstaff= stafflist[i];
        std::cout<<objstaff.get<int>("id")<<std::endl;
        int id=objstaff.get<int>("id");
        //
        bool isImage=true;
        int ret=umxDB_deleteLogEntryById(dzrun.umxdb_Handle,id,&isImage);
        if(ret!=0 && ret!=-401){
            stringstream stream;
            stream<<ret;
            string string_ret=stream.str();
            if(ret=-201)
                string_ret="ID_NO_EXIST";

            JSONObject objerr;
            objerr.set("id",id);
            objerr.set("error_msg",string_ret);
            objlist.add(objerr);
        }
        //
    }
    delete util;

    //write json
    response.setStatusAndReason(HTTPResponse::HTTPStatus::HTTP_OK);
    JSONObject obj;
    obj.set("suc_flag",suc_flag);
    obj.set("error_msg","");
    obj.set("error_staff_list",objlist);
    std::ostream& ostr = response.send();
    ostr<<obj.print();


}

void MyRequestHandler::api_UploadImages(HTTPServerRequest &request, HTTPServerResponse &response)
{
    response.setChunkedTransferEncoding(true);
    response.setContentType("application/json");
    int suc_flag=0;
    //read json
    std::istream &i = request.stream();
    int len = request.getContentLength();
    char* buffer = new char[len];
    i.read(buffer, len);
    QString s=QString(buffer);
    cjsonpp::JSONObject obj=cjsonpp::parse(s.toStdString());
    Person person;
    try {
        person.Id = obj.get<JSONObject>("staff_no").as<string>();
        person.Name =obj.get<string>("name");
        person.Card = obj.get<string>("card_no");
        person.WiegandCode = obj.get<int>("wiegandcode");
    } catch (const cjsonpp::JSONError& e) {
        std::cerr << e.what() << '\n';
    }

    //----
    std::vector<JSONObject> stafflist= obj.get("image_list").asArray<JSONObject>();
    std::cout<<"size:"<<stafflist.size()<<std::endl;
    //utilsHelper *util = new utilsHelper();
    AlgoUtils *algo = new AlgoUtils(dzrun.umxalgo_Handle);
    JSONObject objlist=cjsonpp::arrayObject();
    for(int i=0;i<stafflist.size();i++){
        JSONObject objstaff= stafflist[i];
        //string image=util->fromBase64(objstaff.get<string>("image"));
        algo->savetofile(person.Id, i,objstaff.get<string>("image"));
    }
    //delete util;

    //write json
    response.setChunkedTransferEncoding(true);
    response.setContentType("application/json");

    JSONObject robj;

    //----
    int ret=algo->getTemplates(person);
    if(ret>=0)
    {
        suc_flag=0;
        response.setStatusAndReason(HTTPResponse::HTTPStatus::HTTP_OK);
    }
    else
    {
        suc_flag=-1;
        response.setStatusAndReason(HTTPResponse::HTTPStatus::HTTP_NOT_FOUND);
    }
    robj.set("suc_flag",suc_flag);
    robj.set("error_msg","");
    robj.set("error_staff_list",objlist);
    robj.set("staff_no",person.Id);
    robj.set("lefteyescore",algo->leftscore);
    robj.set("righteyescore",algo->rightscore);

    std::ostream& ostr = response.send();
    ostr<<robj.print();

    system(QString("rm -rf %0").arg(QString::fromStdString( Path::home()+person.Id)).toStdString().c_str());
    delete algo;

}

void MyRequestHandler::api_Login(HTTPServerRequest &request, HTTPServerResponse &response)
{
    //获取lock_uid
    checkConnetct();
    response.setChunkedTransferEncoding(true);
    response.setContentType("application/json");
    response.setStatusAndReason(HTTPResponse::HTTPStatus::HTTP_OK);
    JSONObject robj;
    robj.set("lock_uid",dzrun.lock_uid);
    std::ostream& ostr = response.send();
    ostr<<robj.print();

}
//-----------------------------------------------------------------------------------------------------------
void MyRequestHandler::api_GetTemplates(HTTPServerRequest &request, HTTPServerResponse &response)
{
    response.setChunkedTransferEncoding(true);
    response.setContentType("application/json");
    int suc_flag=0;
    //read json
    std::istream &i = request.stream();
    int len = request.getContentLength();
    char* buffer = new char[len];
    i.read(buffer, len);
    QString s=QString(buffer);
    cjsonpp::JSONObject obj=cjsonpp::parse(s.toStdString());
    string leftimage,rightimage;
    try {
        leftimage = obj.get<string>("lefteye_image");
        rightimage =obj.get<string>("righteye_image");
    } catch (const cjsonpp::JSONError& e) {
        std::cerr << e.what() << '\n';
        return;
    }

    //加载算法
    string leftout,rightout;
    int leftirisarea=0,rightirisarea=0;
    AlgoUtils *algo = new AlgoUtils(dzrun.umxalgo_Handle);
    algo->getTemplateString(leftimage,leftout,leftirisarea);
    algo->getTemplateString(rightimage,rightout,rightirisarea);

    response.setChunkedTransferEncoding(true);
    response.setContentType("application/json");

    JSONObject robj;
    response.setStatusAndReason(HTTPResponse::HTTPStatus::HTTP_OK);
    robj.set("lefteye_template",leftout);
    robj.set("lefteye_irisarea",leftirisarea);
    robj.set("righteye_template",rightout);
    robj.set("righteye_irisarea",rightirisarea);
    std::ostream& ostr = response.send();
    ostr<<robj.print();

    delete algo;
}

bool MyRequestHandler::tryLock()
{
    string data;
    string path=LOCALHOST+PATH_LOCK;
    string body="";
    HTTPResponse::HTTPStatus status = _client->Request(HTTPRequest::HTTP_POST,path,body,data);
    if (status==HTTPResponse::HTTP_OK){
        cjsonpp::JSONObject obj=cjsonpp::parse(data);
        dzrun.lock_uid = obj.get<string>("lock_uid");
        return true;
    }else
        return false;
}

bool MyRequestHandler::stealLock()
{
    string data;
    string path=LOCALHOST+PATH_LOCK;
    string body="";
    HTTPResponse::HTTPStatus status = _client->Request(HTTPRequest::HTTP_PUT,path,body,data);
    if (status==HTTPResponse::HTTP_OK){
        cjsonpp::JSONObject obj=cjsonpp::parse(data);
        dzrun.lock_uid = obj.get<string>("lock_uid");
        GetSubject();
        return true;
    }else
        return false;
}

void MyRequestHandler::checkConnetct()
{
    if(!tryLock() && dzrun.lock_uid=="")
        stealLock();
}



HTTPResponse::HTTPStatus  MyRequestHandler::AddSubject(SubjectData &subject)
{
    Relay();
    checkConnetct();
    string data;
    QString path=QString::fromStdString(LOCALHOST+PATH_ADDSUBJECT);
    path=path.arg(QString::fromStdString(dzrun.lock_uid));
    string body=subject.AsJSONString();
    //std::cout<<body<<std::endl;
    HTTPResponse::HTTPStatus status = _client->Request(HTTPRequest::HTTP_POST,path.toStdString(),body,data);
    return status;
}

HTTPResponse::HTTPStatus MyRequestHandler::AddUserInfo(UserInfoData &userinfo)
{
    checkConnetct();
    string data;
    QString path=QString::fromStdString(LOCALHOST+PATH_ADDUSERINFO);
    path=path.arg(QString::fromStdString(dzrun.lock_uid));
    HTTPResponse::HTTPStatus status = _client->Request(HTTPRequest::HTTP_POST,path.toStdString(),userinfo.AsJSONString(),data);
    return status;
}

HTTPResponse::HTTPStatus MyRequestHandler::AddFace(FaceData &facedata)
{
    checkConnetct();
    string data;
    QString path=QString::fromStdString(LOCALHOST+PATH_ADDFACE);
    path=path.arg(QString::fromStdString(dzrun.lock_uid));
    HTTPResponse::HTTPStatus status = _client->Request(HTTPRequest::HTTP_POST,path.toStdString(),facedata.AsJSONString(),data);
    return status;
}

HTTPResponse::HTTPStatus MyRequestHandler::GetSubject()
{

    checkConnetct();
    string data;
    QString path=QString::fromStdString(LOCALHOST+PATH_GETSUBJECT);
    path=path.arg(QString::fromStdString(dzrun.lock_uid));
    string body="";
    //std::cout<<body<<std::endl;
    HTTPResponse::HTTPStatus status = _client->Request(HTTPRequest::HTTP_GET,path.toStdString(),body,data);
    std::cout<<data<<std::endl;
    return status;

}

HTTPResponse::HTTPStatus MyRequestHandler::Relay()
{
    checkConnetct();
    string data;
    QString path=QString::fromStdString(LOCALHOST+"/1.0/config/relay?lock_uid=%1");
    path=path.arg(QString::fromStdString(dzrun.lock_uid));
    HTTPResponse::HTTPStatus status = _client->Request(HTTPRequest::HTTP_PUT,path.toStdString(),"",data);
    return status;
}



