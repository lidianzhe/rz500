/**************************************************************************************************\

    Author:		Unkyoung Lee
    Created:	2016.05.02

---------------------------------------------------------------------------------------------------

    Copyright (c) 2014 CMI-Tech Ltd.

\**************************************************************************************************/

#ifndef __CONFIGURATION_REQUEST_HANDLER_H__
#define __CONFIGURATION_REQUEST_HANDLER_H__

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

class ConfigurationRequestHandler : public HTTPRequestVerbHandler
{
public:
    ConfigurationRequestHandler(INetworkManager *iNetworkManager, const std::vector<std::string>& pathSegments);
    ~ConfigurationRequestHandler(void);
protected:
    void handleGetRequest(HTTPServerRequest& request, HTTPServerResponse& response);
    void handlePostRequest(HTTPServerRequest& request, HTTPServerResponse& response);
    void handlePutRequest(HTTPServerRequest& request, HTTPServerResponse& response);
private:
    ConfigurationRequestHandler(const ConfigurationRequestHandler&);
    ConfigurationRequestHandler& operator = (const ConfigurationRequestHandler&);
//private:
protected:
    const bool isConfigurationRequest() const;
    const bool isControlRequest() const;
    const bool isStartControlRequest() const;
    const bool isStopControlRequest() const;
    void handleGetConfigurationRequest(HTTPServerRequest& request, HTTPServerResponse& response);
    void handlePutConfigurationRequest(HTTPServerRequest& request, HTTPServerResponse& response);
    void handleGetControlRequest(HTTPServerRequest& request, HTTPServerResponse& response);
    void handlePostControlRequest(HTTPServerRequest& request, HTTPServerResponse& response);
    INetworkManager* _iNetworkManager;

    std::string getConfigByTitle(const std::string& title, const std::string& type, HTTPServerResponse& response);
    std::string getConfig(HTTPServerResponse& response);

    template<class T>
    static bool HasValue(cjsonpp::JSONObject& obj, const std::string& name);

    int ParseAndSetIntProperties(int val, int* ival, double* dval, bool* bval);
    bool ParseAndSetStringProperties(std::string val);
    bool SetDeviceInfo(std::string val);
    std::string GetDeviceInfo(std::string val);

};

//- usb com //////////////////////////////////////////////////////////////////////////////////////////
class ConfigurationRequestHandler_usb : public ConfigurationRequestHandler
{
public:
    ConfigurationRequestHandler_usb(INetworkManager *iNetworkManager, const std::vector<std::string>& pathSegments, std::string strSendJson);
    ~ConfigurationRequestHandler_usb(void);
    std::string getResponse() {return responseAsJSONString;};
public:
    void handleGetRequest(Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response);
    void handlePostRequest(Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response);
    void handlePutRequest(Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response);
private:
    ConfigurationRequestHandler_usb(const ConfigurationRequestHandler_usb&);
    ConfigurationRequestHandler_usb& operator = (const ConfigurationRequestHandler_usb&);
private:
    const bool isConfigurationRequest() const;
    const bool isControlRequest() const;
    const bool isStartControlRequest() const;
    const bool isStopControlRequest() const;
    void handleGetConfigurationRequest(Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response);
    void handlePutConfigurationRequest(Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response);
    void handleGetControlRequest(Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response);
    void handlePostControlRequest(Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response);
    INetworkManager* _iNetworkManager;

    std::string getConfigByTitle(const std::string& title, const std::string& type, Poco::Net::HTTPResponse& response);
    std::string getConfig(Poco::Net::HTTPResponse& response);

    template<class T>
    static bool HasValue(cjsonpp::JSONObject& obj, const std::string& name);

    int ParseAndSetIntProperties(int val, int* ival, double* dval, bool* bval);
    bool ParseAndSetStringProperties(std::string val);
    bool SetDeviceInfo(std::string val);
    std::string GetDeviceInfo(std::string val);

    std::string sendJson = "";
    std::string responseAsJSONString = "";
};

#endif // __CONFIGURATION_REQUEST_HANDLER_H__
