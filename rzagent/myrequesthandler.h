#ifndef MYREQUESTHANDLER_H
#define MYREQUESTHANDLER_H
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/HTTPRequest.h"
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include "entities.h"
#include <QString>
#include "httpclient.h"
#include "umxDBLib/umxDBGlobal.h"
#include "umxCommonLib/umxCommonGlobal.h"
#include "umxDBLib/umxDB.h"
using namespace Poco;
using namespace Net;

class MyRequestHandler : public Poco::Net::HTTPRequestHandler
{
public:
    MyRequestHandler();
    void handleRequest(HTTPServerRequest& request, HTTPServerResponse &response);
    Client* _client = new Client();
private:

    std::string LOCALHOST="http://127.0.0.1:9980";
    const std::string PATH_LOCK="/1.0/lock";
    const std::string PATH_ADDSUBJECT="/1.0/subjects?lock_uid=%1";
    const std::string PATH_ADDUSERINFO="/1.0/user-info?lock_uid=%1";
    const std::string PATH_ADDFACE="/1.0/faces?lock_uid=%1";

    const std::string PATH_GETSUBJECT="/1.0/subjects/1?lock_uid=%1";

    void api_Persons(HTTPServerRequest& request, HTTPServerResponse &response);
    void api_GetPersonsCount(HTTPServerRequest& request, HTTPServerResponse &response);
    void api_GetPersons(HTTPServerRequest& request, HTTPServerResponse &response);
    void api_PostPersons(HTTPServerRequest& request, HTTPServerResponse &response);
    void api_DeletePersons(HTTPServerRequest& request, HTTPServerResponse &response);
    int saveStaff(Staff &staff);
    void api_Logs(HTTPServerRequest& request, HTTPServerResponse &response);

    void api_GetLogs(HTTPServerRequest& request, HTTPServerResponse &response);
    void api_DeleteLogs(HTTPServerRequest& request, HTTPServerResponse &response);

    void api_UploadImages(HTTPServerRequest& request, HTTPServerResponse &response);
    void api_Login(HTTPServerRequest& request, HTTPServerResponse &response);
    //获取模板数据
    void api_GetTemplates(HTTPServerRequest& request, HTTPServerResponse &response);


    void ConvertStaffToSubject();
    void ConvertStaffToUserinfo();

    bool tryLock();
    bool stealLock();
    void checkConnetct();

    HTTPResponse::HTTPStatus AddSubject(SubjectData &subject);
    HTTPResponse::HTTPStatus AddUserInfo(UserInfoData &userinfo);
    HTTPResponse::HTTPStatus AddFace(FaceData &facedata);
        HTTPResponse::HTTPStatus GetSubject();
    HTTPResponse::HTTPStatus Relay();

};

#endif // MYREQUESTHANDLER_H
