#include "myrequesthandler.h"
#include <QtCore>
#include <QString>
#include <QStringList>
#include <iostream>
#include "Poco/Net/HTTPResponse.h"
#include "Poco/URI.h"
#include "Poco/Path.h"
#include "umxCommonLib/cjson/cJSONpp.h"
//
#include <vector>
#include "runtime.h"
#include "umxDBLib/umxDBGlobal.h"
#include "umxCommonLib/umxCommonGlobal.h"
#include "umxDBLib/umxDB.h"
#include "algoutils.h"
#include <QByteArray>
using namespace std;
using namespace Poco;
using namespace Net;
using namespace cjsonpp;

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

    if(path.value(1) =="persons" && request.getMethod()=="PUT"){
            api_Persons(request,response);
        return;
    }

    response.setContentType("application/json");
    response.redirect(request.getURI(),HTTPResponse::HTTPStatus::HTTP_OK);
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
                obj.set("LeftEyeScore",algo->leftscore);
                obj.set("RightEyeScore",algo->rightscore);
                ostr<<obj.print();
//                ostr << "{";
//                ostr << "\"Id\":\""<<id<<"\",";
//                ostr << "\"LeftEyeScore\":\""<<algo->leftscore<<"\",";
//                ostr << "\"RightEyeScore\":\""<<algo->rightscore<<"\"";
//                ostr <<"}";
//                ostr<<endl;
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
        item.set("password","");
        item.set("face_feature","");
        //std::cout<<sdObj.get("left_eye_template").as<string>()<<std::endl;
        item.set("left_feature",sdObj.get("left_eye_template").as<string>());
        item.set("right_feature",sdObj.get("right_eye_template").as<string>());
        item.set("is_admin",ui._admin);
        item.set("enable_flag",1);
        item.set("create_time",sd._insertTime);
        item.set("expired_time","");
        item.set("verify_type",ui._indivisual);
        item.set("bypasscard",ui._byPassCard);
        r.add(item);
    }
    obj.set("sfaff_list",r);
    ostr<<obj.print();

    response.setStatusAndReason(HTTPResponse::HTTPStatus::HTTP_OK);

}
