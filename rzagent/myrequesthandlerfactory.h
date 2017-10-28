#ifndef MYREQUESTHANDLERFACTORY_H
#define MYREQUESTHANDLERFACTORY_H
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include <Poco/Net/HTTPRequestHandler.h>
using namespace Poco;
using namespace Net;

class MyRequestHandlerFactory:public HTTPRequestHandlerFactory
{
public:
    MyRequestHandlerFactory();
    HTTPRequestHandler* createRequestHandler(const HTTPServerRequest& request) ;
};

#endif // MYREQUESTHANDLERFACTORY_H
