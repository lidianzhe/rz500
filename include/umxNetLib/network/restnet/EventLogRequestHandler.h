/**************************************************************************************************\

	Author:		Ralph
	Created:	28.03.2014

---------------------------------------------------------------------------------------------------

	Copyright (c) 2014 Smartsensors Ltd.

\**************************************************************************************************/

#ifndef __EVENT_LOG_REQUEST_HANDLER_H__
#define __EVENT_LOG_REQUEST_HANDLER_H__

#include <string>
#include <vector>

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;

#if 0 //EF-45(unklee88)-23 : removed not using access class in umxNetLib
#include <DataAccess/EventLogDataAccess.h>
#endif

#include "HTTPRequestVerbHandler.h"

#if 1 //EF-45(unklee88)-57 : netglobal.h includes iNetworkmanager.h vvv
#include "umxNetLib/umxNetGlobal.h"
#else
#include "iNetworkManager.h" //EF-45(unklee88)-23 : removed not using access class in umxNetLib
#endif //EF-45(unklee88)-57 : netglobal.h includes iNetworkmanager.h ^^^

#if 1 //EF-45(unklee88)-62 : made Namespace UMXNetwork vvv
using namespace UMXNetwork;
#endif //EF-45(unklee88)-62 : made Namespace UMXNetwork ^^^

class EventLogRequestHandler : public HTTPRequestVerbHandler
{
public:
    EventLogRequestHandler(INetworkManager *iNetworkManager, const std::vector<std::string>& pathSegments);
    virtual ~EventLogRequestHandler(void);
protected:
    void handleGetRequest(HTTPServerRequest& request, HTTPServerResponse& response);
    void handlePostRequest(HTTPServerRequest& request, HTTPServerResponse& response);
    void handleDeleteRequest(HTTPServerRequest& request, HTTPServerResponse& response);
private:
	EventLogRequestHandler(const EventLogRequestHandler&);
	EventLogRequestHandler& operator = (const EventLogRequestHandler&);
private:
#if 1 //EF-45(unklee88)-23 : removed not using access class in umxNetLib
    std::string getEventLogById(const std::string& id, HTTPServerResponse& response);
    std::string getEventLogs(HTTPServerResponse& response, const int page, const int pageSize, const std::string& order);
#endif
    std::string getEventLogsFromTo(Poco::Net::HTTPResponse& response, const int page, const int pageSize, const int fromId, const int toId);
private:
    //const std::string _databaseConnection; //EF-45(unklee88)-23 : removed not using access class in umxNetLib
    INetworkManager* _iNetworkManager; //EF-45(unklee88)-23 : removed not using access class in umxNetLib

};

class EventLogRequestHandler_usb : public EventLogRequestHandler
{
public:
    EventLogRequestHandler_usb(INetworkManager *iNetworkManager, const std::vector<std::string>& pathSegments);
    std::string getResponse() {return responseAsJSONString;};
public:
    void handleGetRequest(Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response);
    void handlePostRequest(Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response);
    void handleDeleteRequest(Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response);
private:
    EventLogRequestHandler_usb(const EventLogRequestHandler_usb&);
    EventLogRequestHandler_usb& operator = (const EventLogRequestHandler_usb&);
private:
#if 1 //EF-45(unklee88)-23 : removed not using access class in umxNetLib
    std::string getEventLogById(const std::string& id, Poco::Net::HTTPResponse& response);
    std::string getEventLogs(Poco::Net::HTTPResponse& response, const int page, const int pageSize, const std::string& order);
#endif
    std::string getEventLogsFromTo(Poco::Net::HTTPResponse& response, const int page, const int pageSize, const int fromId, const int toId);
private:
    //const std::string _databaseConnection; //EF-45(unklee88)-23 : removed not using access class in umxNetLib
    INetworkManager* _iNetworkManager; //EF-45(unklee88)-23 : removed not using access class in umxNetLib
    std::string responseAsJSONString = "";
};

#endif // __EVENT_LOG_REQUEST_HANDLER_H__
