/**************************************************************************************************\

    Author:		UK
    Created:	2016.05.04

---------------------------------------------------------------------------------------------------

    Copyright (c) 2015 CMITech Ltd.

\**************************************************************************************************/

#ifndef __FACE_DATA_REQUEST_HANDLER_H__
#define __FACE_DATA_REQUEST_HANDLER_H__

#include <string>
#include <vector>

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
using Poco::Net::HTTPRequestHandler;
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

class FaceDataRequestHandler : public HTTPRequestVerbHandler
{
public:
    FaceDataRequestHandler(INetworkManager* pINetworkManager, const std::vector<std::string>& pathSegments);
    ~FaceDataRequestHandler(void);
protected:
    void handleGetRequest(HTTPServerRequest& request, HTTPServerResponse& response);
    void handlePostRequest(HTTPServerRequest& request, HTTPServerResponse& response);
    void handleDeleteRequest(HTTPServerRequest& request, HTTPServerResponse& response);
    void handlePutRequest(HTTPServerRequest& request, HTTPServerResponse& response);
private:
    FaceDataRequestHandler(const FaceDataRequestHandler&);
    FaceDataRequestHandler& operator = (const FaceDataRequestHandler&);
private:
#if 1 //EF-45(unklee88)-7 : removed DataAccess in umxNetLib
    std::string getFaceBySubId(const std::string& id, const int subId, HTTPServerResponse& response);
    std::string getFacesByUUId(const std::string& id, HTTPServerResponse& response);
    std::string getFaces(HTTPServerResponse& response, const int page, const int pageSize);
#endif
private:
    INetworkManager* _pINetworkManager;
};

class FaceDataRequestHandler_usb : public FaceDataRequestHandler
{
public:
    FaceDataRequestHandler_usb(INetworkManager* pINetworkManager, const std::vector<std::string>& pathSegments, std::string strSendJson);
    std::string getResponse() {return responseAsJSONString;};
public:
    void handleGetRequest(Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response);
    void handlePostRequest(Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response);
    void handlePutRequest(Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response);
    void handleDeleteRequest(Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response);
private:
    FaceDataRequestHandler_usb(const FaceDataRequestHandler_usb&);
    FaceDataRequestHandler_usb& operator = (const FaceDataRequestHandler_usb&);
private:
    std::string getFaceBySubId(const std::string& id, const int subId, Poco::Net::HTTPResponse& response);
    std::string getFacesByUUId(const std::string& id, Poco::Net::HTTPResponse& response);
    std::string getFaces(Poco::Net::HTTPResponse& response, const int page, const int pageSize);
private:
    INetworkManager* _pINetworkManager;
    std::string sendJson = "";
    std::string responseAsJSONString = "";
};

#endif // __FACE_DATA_REQUEST_HANDLER_H__
