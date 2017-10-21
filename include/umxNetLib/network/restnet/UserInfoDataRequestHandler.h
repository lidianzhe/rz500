/**************************************************************************************************\

    Author:		UK
    Created:	2016.10.14

---------------------------------------------------------------------------------------------------

    Copyright (c) 2015 CMITech Ltd.

\**************************************************************************************************/

#ifndef __USERINFO_DATA_REQUEST_HANDLER_H__
#define __USERINFO_DATA_REQUEST_HANDLER_H__

#include <string>
#include <vector>

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;

#include "HTTPRequestVerbHandler.h"
#include "umxNetLib/umxNetGlobal.h"

using namespace UMXNetwork;

class UserInfoDataRequestHandler : public HTTPRequestVerbHandler
{
public:
    UserInfoDataRequestHandler(INetworkManager* pINetworkManager, const std::vector<std::string>& pathSegments);
    ~UserInfoDataRequestHandler(void);
protected:
    void handleGetRequest(HTTPServerRequest& request, HTTPServerResponse& response);
    void handlePostRequest(HTTPServerRequest& request, HTTPServerResponse& response);
    void handleDeleteRequest(HTTPServerRequest& request, HTTPServerResponse& response);
    void handlePutRequest(HTTPServerRequest& request, HTTPServerResponse& response);
private:
    UserInfoDataRequestHandler(const UserInfoDataRequestHandler&);
    UserInfoDataRequestHandler& operator = (const UserInfoDataRequestHandler&);
private:
    std::string getUserInfoByUUID(const std::string& id, HTTPServerResponse& response);
    std::string getUserInfoByCard(const std::string& card, HTTPServerResponse& response);
    std::string getAllUserInfo(HTTPServerResponse& response, const int page, const int pageSize);
private:
    INetworkManager* _pINetworkManager;
};


class UserInfoDataRequestHandler_usb : public UserInfoDataRequestHandler
{
public:
    UserInfoDataRequestHandler_usb(INetworkManager* pINetworkManager, const std::vector<std::string>& pathSegments, std::string strSendJson);
    std::string getResponse() {return responseAsJSONString;};
public:
    void handleGetRequest(Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response);
    void handlePostRequest(Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response);
    void handlePutRequest(Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response);
    void handleDeleteRequest(Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response);
private:
    UserInfoDataRequestHandler_usb(const UserInfoDataRequestHandler_usb&);
    UserInfoDataRequestHandler_usb& operator = (const UserInfoDataRequestHandler_usb&);
private:
    std::string getUserInfoByUUID(const std::string& id, Poco::Net::HTTPResponse& response);
    std::string getUserInfoByCard(const std::string& card, Poco::Net::HTTPResponse& response);
    std::string getAllUserInfo(Poco::Net::HTTPResponse& response, const int page, const int pageSize);
private:
    INetworkManager* _pINetworkManager;
    std::string sendJson = "";
    std::string responseAsJSONString = "";
};

#endif // __USERINFO_DATA_REQUEST_HANDLER_H__
