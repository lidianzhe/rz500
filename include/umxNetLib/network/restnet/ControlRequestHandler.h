#ifndef __CONTROL_REQUEST_HANDLER_H__
#define __CONTROL_REQUEST_HANDLER_H__

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

class ControlRequestHandler : public HTTPRequestVerbHandler
{
public:
    ControlRequestHandler(INetworkManager* pINetworkManager, const std::vector<std::string>& pathSegments);
    ~ControlRequestHandler(void);
protected:
    void handleGetRequest(HTTPServerRequest& request, HTTPServerResponse& response);
    void handlePostRequest(HTTPServerRequest& request, HTTPServerResponse& response);
    void handleDeleteRequest(HTTPServerRequest& request, HTTPServerResponse& response);
    void handlePutRequest(HTTPServerRequest& request, HTTPServerResponse& response);
private:
    ControlRequestHandler(const ControlRequestHandler&);
    ControlRequestHandler& operator = (const ControlRequestHandler&);
private:
    const bool isControlRequest() const;
private:
    void handlePostControlRequest(HTTPServerRequest& request, HTTPServerResponse& response);
    INetworkManager* _pINetworkManager;
};

//- usb com //////////////////////////////////////////////////////////////////////////////////////////
class ControlRequestHandler_usb : public ControlRequestHandler
{
public:
    ControlRequestHandler_usb(INetworkManager* pINetworkManager, const std::vector<std::string>& pathSegments, std::string strSendJson);
    std::string getResponse() {return responseAsJSONString;};
public:
    void handleGetRequest(Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response);
    void handlePostRequest(Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response);
    void handleDeleteRequest(Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response);
    void handlePutRequest(Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response);
private:
    ControlRequestHandler_usb(const ControlRequestHandler_usb&);
    ControlRequestHandler_usb& operator = (const ControlRequestHandler_usb&);
private:
    const bool isControlRequest() const;
private:
    void handlePostControlRequest(Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response);
    INetworkManager* _pINetworkManager;
    std::string sendJson;
    std::string responseAsJSONString = "";
};

#endif // __CONTROL_REQUEST_HANDLER_H__
