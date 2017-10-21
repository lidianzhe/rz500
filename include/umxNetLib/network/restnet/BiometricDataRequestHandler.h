/**************************************************************************************************\

	Author:		Ralph
	Created:	22.04.2014

---------------------------------------------------------------------------------------------------

	Copyright (c) 2014 Smartsensors Ltd.

\**************************************************************************************************/

#ifndef __BIOMETRIC_DATA_REQUEST_HANDLER_H__
#define __BIOMETRIC_DATA_REQUEST_HANDLER_H__

#include <memory>
#include <string>
#include <vector>

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;

#include "HTTPRequestVerbHandler.h"
#if 1 //EF-45(unklee88)-59 : netglobal.h includes BiometricDataCache.h vvv
#include "umxNetLib/umxNetGlobal.h"
#else
#include <DataAccess/BiometricDataCache.h>
#endif //EF-45(unklee88)-59 : netglobal.h includes BiometricDataCache.h ^^^

#if 1 //EF-45(unklee88)-62 : made Namespace UMXNetwork vvv
using namespace UMXNetwork;
#endif //EF-45(unklee88)-62 : made Namespace UMXNetwork ^^^

class BiometricDataRequestHandler : public HTTPRequestVerbHandler
{
public:
    BiometricDataRequestHandler(INetworkManager* pINetworkManager, std::shared_ptr<BiometricDataCache> biometricDataCache,
                                const std::vector<std::string>& pathSegments);
    ~BiometricDataRequestHandler(void);
protected:
    void handleGetRequest(HTTPServerRequest& request, HTTPServerResponse& response);
    void handleDeleteRequest(HTTPServerRequest& request, HTTPServerResponse& response);
    void handlePutRequest(HTTPServerRequest& request, HTTPServerResponse& response);
private:
	BiometricDataRequestHandler(const BiometricDataRequestHandler&);
	BiometricDataRequestHandler& operator = (const BiometricDataRequestHandler&);
private:
    const std::string getBiometricData(HTTPServerResponse& response);
    std::string createFilename(int index);
private:
    std::shared_ptr<BiometricDataCache> _biometricDataCache;
    INetworkManager* _pINetworkManager;
};

//- usb com //////////////////////////////////////////////////////////////////////////////////////////
class BiometricDataRequestHandler_usb : public BiometricDataRequestHandler
{
public:
    BiometricDataRequestHandler_usb(INetworkManager* pINetworkManager, std::shared_ptr<BiometricDataCache> biometricDataCache,
                                const std::vector<std::string>& pathSegments, std::string strSendJson);
    std::string getResponse() {return responseAsJSONString;};
public:
    void handleGetRequest(Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response);
    void handleDeleteRequest(Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response);
    void handlePutRequest(Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response);
private:
    BiometricDataRequestHandler_usb(const BiometricDataRequestHandler_usb&);
    BiometricDataRequestHandler_usb& operator = (const BiometricDataRequestHandler_usb&);
private:
    std::string createFilename(int index);
    const std::string getBiometricData(Poco::Net::HTTPResponse& response);
private:
    std::shared_ptr<BiometricDataCache> _biometricDataCache;
    INetworkManager* _pINetworkManager;
    std::string sendJson = "";
    std::string responseAsJSONString = "";
};

#endif // __BIOMETRIC_DATA_REQUEST_HANDLER_H__
