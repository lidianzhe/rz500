/**************************************************************************************************\

	Author:		Ralph
	Created:	23.04.2014

---------------------------------------------------------------------------------------------------

	Copyright (c) 2014 Smartsensors Ltd.

\**************************************************************************************************/

#ifndef __CAMERA_CONFIGURATION_REQUEST_HANDLER_H__
#define __CAMERA_CONFIGURATION_REQUEST_HANDLER_H__

#include <string>
#include <vector>

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

class CameraConfigurationRequestHandler : public HTTPRequestVerbHandler
{
public:
    CameraConfigurationRequestHandler(INetworkManager *iNetworkManager, const std::vector<std::string>& pathSegments);
    ~CameraConfigurationRequestHandler(void);
protected:
    void handleGetRequest(HTTPServerRequest& request, HTTPServerResponse& response);
    void handlePostRequest(HTTPServerRequest& request, HTTPServerResponse& response);
    void handlePutRequest(HTTPServerRequest& request, HTTPServerResponse& response);
//private:
protected:
	CameraConfigurationRequestHandler(const CameraConfigurationRequestHandler&);
	CameraConfigurationRequestHandler& operator = (const CameraConfigurationRequestHandler&);
//private:
protected:
    const bool isConfigurationRequest() const;
    const bool isControlRequest() const;
    const bool isStartControlRequest() const;
    const bool isStopControlRequest() const;
    const bool isCaptureWideViewControlRequest() const;
    const bool isPoweroffControlRequest() const;
    const bool isRebootControlRequest() const;
    const bool isSetDeviceTimeControlRequest() const;
    void handleGetConfigurationRequest(HTTPServerRequest& request, HTTPServerResponse& response);
    void handlePutConfigurationRequest(HTTPServerRequest& request, HTTPServerResponse& response);
    void handlePostConfigurationRequest(HTTPServerRequest& request, HTTPServerResponse& response);
    void handleGetControlRequest(HTTPServerRequest& request, HTTPServerResponse& response);
    void handlePostControlRequest(HTTPServerRequest& request, HTTPServerResponse& response);
    INetworkManager* _iNetworkManager;
};

class CameraConfigurationRequestHandler_usb : public CameraConfigurationRequestHandler
{
public:
    CameraConfigurationRequestHandler_usb(INetworkManager *iNetworkManager, const std::vector<std::string>& pathSegments, std::string strSendJson);
    std::string getResponse() {return responseAsJSONString;};
public:
    void handleGetRequest(Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response);
    void handlePostRequest(Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response);
    void handlePutRequest(Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response);
private:
    CameraConfigurationRequestHandler_usb(const CameraConfigurationRequestHandler_usb&);
    CameraConfigurationRequestHandler_usb& operator = (const CameraConfigurationRequestHandler_usb&);
private:    
    void handleGetConfigurationRequest(Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response);
    void handlePutConfigurationRequest(Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response);
    void handlePostConfigurationRequest(Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response);
    void handleGetControlRequest(Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response);
    void handlePostControlRequest(Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response);

    INetworkManager* _iNetworkManager;
    std::string sendJson = "";
public:
    std::string responseAsJSONString = "";
};

#endif // __CAMERA_CONFIGURATION_REQUEST_HANDLER_H__

