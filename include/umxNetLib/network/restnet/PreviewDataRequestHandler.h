/**************************************************************************************************\

	Author:		Ralph
	Created:	25.04.2014

---------------------------------------------------------------------------------------------------

	Copyright (c) 2014 Smartsensors Ltd.

\**************************************************************************************************/

#ifndef __PREVIEW_DATA_REQUEST_HANDLER_H__
#define __PREVIEW_DATA_REQUEST_HANDLER_H__

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;

#include "HTTPRequestVerbHandler.h"
#if 1 //EF-45(unklee88)-57 : netglobal.h includes iNetworkmanager.h vvv
#include "umxNetLib/umxNetGlobal.h"
#else
#include "iNetworkManager.h"
#endif //EF-45(unklee88)-57 : netglobal.h includes iNetworkmanager.h ^^^

#if 1 //EF-45(unklee88)-62 : made Namespace UMXNetwork vvv
using namespace UMXNetwork;
#endif //EF-45(unklee88)-62 : made Namespace UMXNetwork ^^^

class PreviewDataRequestHandler : public HTTPRequestVerbHandler
{
public:
    PreviewDataRequestHandler(INetworkManager *iNetworkManager, const std::vector<std::string>& pathSegments);
    ~PreviewDataRequestHandler(void);
protected:
    void handleGetRequest(HTTPServerRequest& request, HTTPServerResponse& response);
    void handleDeleteRequest(HTTPServerRequest& request, HTTPServerResponse& response);
private:
	PreviewDataRequestHandler(const PreviewDataRequestHandler&);
	PreviewDataRequestHandler& operator = (const PreviewDataRequestHandler&);
private:
    INetworkManager* _iNetworkManager;
};

class PreviewDataRequestHandler_usb : public PreviewDataRequestHandler
{
public:
    PreviewDataRequestHandler_usb(INetworkManager *iNetworkManager, const std::vector<std::string>& pathSegments);
    std::string getResponse() {return responseAsJSONString;};
public:
    void handleGetRequest(Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response);
    void handleDeleteRequest(Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response);
private:
    PreviewDataRequestHandler_usb(const PreviewDataRequestHandler_usb&);
    PreviewDataRequestHandler_usb& operator = (const PreviewDataRequestHandler_usb&);
private:
    INetworkManager* _iNetworkManager;
    std::string responseAsJSONString = "";
};

#endif // __PREVIEW_DATA_REQUEST_HANDLER_H__
