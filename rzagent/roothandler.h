#ifndef ROOTHANDLER_H
#define ROOTHANDLER_H
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/HTTPRequest.h"
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
using namespace Poco;
using namespace Net;
class RootHandler : public Poco::Net::HTTPRequestHandler
{
public:
    RootHandler();
    void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response);
};

#endif // ROOTHANDLER_H
