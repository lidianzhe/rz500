/**************************************************************************************************\

	Author:		Ralph
	Created:	29.04.2014

---------------------------------------------------------------------------------------------------

	Copyright (c) 2014 Smartsensors Ltd.

\**************************************************************************************************/

#ifndef __LOCK_REQUEST_HANDLER_H__
#define __LOCK_REQUEST_HANDLER_H__

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;

#include "Locker.h"
#include "HTTPRequestVerbHandler.h"

class LockRequestHandler : public HTTPRequestVerbHandler
{
public:
    LockRequestHandler(Locker* locker, const std::vector<std::string>& pathSegments);
    ~LockRequestHandler(void);
protected:
    void handlePostRequest(HTTPServerRequest& request, HTTPServerResponse& response);
    void handlePutRequest(HTTPServerRequest& request, HTTPServerResponse& response);
    void handleDeleteRequest(HTTPServerRequest& request, HTTPServerResponse& response);
private:
	LockRequestHandler(const LockRequestHandler&);
	LockRequestHandler& operator = (const LockRequestHandler&);
private:
    Locker* _locker;
};

class LockRequestHandler_usb : public LockRequestHandler
{
public:
    LockRequestHandler_usb(Locker* locker, const std::vector<std::string>& pathSegments);
    std::string getResponse() {return responseAsJSONString;};
public:
    void handlePostRequest(Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response);
    void handlePutRequest(Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response);
    void handleDeleteRequest(Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response);
private:
    LockRequestHandler_usb(const LockRequestHandler_usb&);
    LockRequestHandler_usb& operator = (const LockRequestHandler_usb&);
private:
    Locker* _locker;
    std::string responseAsJSONString = "";
};

#endif // __LOCK_REQUEST_HANDLER_H__
