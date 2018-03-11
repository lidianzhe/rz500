#ifndef MYREQUESTHANDLER_H
#define MYREQUESTHANDLER_H
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/HTTPRequest.h"
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include "entities.h"
#include <QString>
using namespace Poco;
using namespace Net;

class MyRequestHandler : public Poco::Net::HTTPRequestHandler
{
public:
    MyRequestHandler();
    void handleRequest(HTTPServerRequest& request, HTTPServerResponse &response);
private:
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
};

#endif // MYREQUESTHANDLER_H
