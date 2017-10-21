/**************************************************************************************************\

	Author:		Ralph
	Created:	28.04.2014

---------------------------------------------------------------------------------------------------

	Copyright (c) 2014 Smartsensors Ltd.

\**************************************************************************************************/

#ifndef __SUBJECT_DATA_REQUEST_HANDLER_H__
#define __SUBJECT_DATA_REQUEST_HANDLER_H__

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

class SubjectDataRequestHandler : public HTTPRequestVerbHandler
{
public:
    SubjectDataRequestHandler(INetworkManager* pINetworkManager, const std::vector<std::string>& pathSegments);
    ~SubjectDataRequestHandler(void);
protected:
    void handleGetRequest(HTTPServerRequest& request, HTTPServerResponse& response);
    void handlePostRequest(HTTPServerRequest& request, HTTPServerResponse& response);
    void handleDeleteRequest(HTTPServerRequest& request, HTTPServerResponse& response);
    void handlePutRequest(HTTPServerRequest& request, HTTPServerResponse& response);
private:
	SubjectDataRequestHandler(const SubjectDataRequestHandler&);
	SubjectDataRequestHandler& operator = (const SubjectDataRequestHandler&);
private:
#if 1 //EF-45(unklee88)-7 : removed DataAccess in umxNetLib
    std::string getSubjectById(const std::string& id, HTTPServerResponse& response);
    std::string getSubjects(HTTPServerResponse& response, const int page, const int pageSize);
#endif
    std::string getUserList(HTTPServerResponse& response, const int page, const int pageSize);
private:
    INetworkManager* _pINetworkManager;
};

class SubjectDataRequestHandler_usb : public SubjectDataRequestHandler
{
public:
    SubjectDataRequestHandler_usb(INetworkManager* pINetworkManager, const std::vector<std::string>& pathSegments, std::string strSendJson);
    std::string getResponse() {return responseAsJSONString;};
public:
    void handleGetRequest(Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response);
    void handlePostRequest(Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response);
    void handleDeleteRequest(Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response);
    void handlePutRequest(Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response);
private:
    SubjectDataRequestHandler_usb(const SubjectDataRequestHandler_usb&);
    SubjectDataRequestHandler_usb& operator = (const SubjectDataRequestHandler_usb&);
private:
#if 1 //EF-45(unklee88)-7 : removed DataAccess in umxNetLib
    std::string getSubjectById(const std::string& id, Poco::Net::HTTPResponse& response);
    std::string getSubjects(Poco::Net::HTTPResponse& response, const int page, const int pageSize);
#endif
    std::string getUserList(Poco::Net::HTTPResponse& response, const int page, const int pageSize);
private:
    INetworkManager* _pINetworkManager;
    std::string sendJson = "";
    std::string responseAsJSONString = "";
};

#endif // __SUBJECT_DATA_REQUEST_HANDLER_H__
