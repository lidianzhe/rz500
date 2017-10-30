#ifndef MYREQUESTHANDLER_H
#define MYREQUESTHANDLER_H
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/HTTPRequest.h"
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include "entities.h"
using namespace Poco;
using namespace Net;

class MyRequestHandler : public Poco::Net::HTTPRequestHandler
{
public:
    MyRequestHandler();
    void handleRequest(HTTPServerRequest& request, HTTPServerResponse &response);
private:
    void api_Persons(HTTPServerRequest& request, HTTPServerResponse &response);

};

#endif // MYREQUESTHANDLER_H
