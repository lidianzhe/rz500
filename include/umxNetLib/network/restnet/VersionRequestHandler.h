/**************************************************************************************************\

	Author:		Ralph
	Created:	27.02.2014

---------------------------------------------------------------------------------------------------

	Copyright (c) 2014 Smartsensors Ltd.

\**************************************************************************************************/

#ifndef __VERSION_REQUEST_HANDLER_H__
#define __VERSION_REQUEST_HANDLER_H__

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;

#if 0 //EF-45(unklee88)-65 : netglobal.h includes DataTypes/VersionConverter.h vvv
#include <DataTypes/VersionConverter.h>
#endif //EF-45(unklee88)-65 : netglobal.h includes DataTypes/VersionConverter.h ^^^
#include "HTTPRequestVerbHandler.h"
#include "umxNetLib/umxNetGlobal.h"

using namespace UMXNetwork;

class VersionRequestHandler : public HTTPRequestVerbHandler
{
public:
    VersionRequestHandler(INetworkManager *iNetworkManager);
    ~VersionRequestHandler(void);
protected:
    void handleGetRequest(HTTPServerRequest& request, HTTPServerResponse& response);
private:
	VersionRequestHandler(const VersionRequestHandler&);
	VersionRequestHandler& operator = (const VersionRequestHandler&);

private:
    INetworkManager* _pINetworkManager;
};

class VersionRequestHandler_usb : public VersionRequestHandler
{
public:
    VersionRequestHandler_usb(INetworkManager *iNetworkManager);
    std::string getResponse() {return responseAsJSONString;};
public:
    void handleGetRequest(Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response);
private:
    VersionRequestHandler_usb(const VersionRequestHandler_usb&);
    VersionRequestHandler_usb& operator = (const VersionRequestHandler_usb&);

private:
    INetworkManager* _pINetworkManager;
    std::string responseAsJSONString = "";
};

#endif // __VERSION_REQUEST_HANDLER_H__
