/**************************************************************************************************\

    Author:		UK
    Created:	2015.07.21

---------------------------------------------------------------------------------------------------

    Copyright (c) 2015 CMITech Ltd.

\**************************************************************************************************/

#ifndef __SELECTED_DATA_REQUEST_HANDLER_H__
#define __SELECTED_DATA_REQUEST_HANDLER_H__

#include <memory>
#include <string>
#include <vector>

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;

#include "HTTPRequestVerbHandler.h"
#if 1 //EF-45(unklee88)-60 : netglobal.h includes SelectedDataCache.h vvv
#include "umxNetLib/umxNetGlobal.h"
#else
#include "DataAccess/SelectedDataCache.h"
#endif //EF-45(unklee88)-60 : netglobal.h includes SelectedDataCache.h ^^^

#if 1 //EF-45(unklee88)-62 : made Namespace UMXNetwork vvv
using namespace UMXNetwork;
#endif //EF-45(unklee88)-62 : made Namespace UMXNetwork ^^^

class SelectedDataRequestHandler : public HTTPRequestVerbHandler
{
public:
    SelectedDataRequestHandler(std::shared_ptr<SelectedDataCache> selectedDataCache, const std::vector<std::string>& pathSegments);
    ~SelectedDataRequestHandler(void);
protected:
    void handleGetRequest(HTTPServerRequest& request, HTTPServerResponse& response);
    void handleDeleteRequest(HTTPServerRequest& request, HTTPServerResponse& response);
private:
    SelectedDataRequestHandler(const SelectedDataRequestHandler&);
    SelectedDataRequestHandler& operator = (const SelectedDataRequestHandler&);
private:
    const std::string getSelectedData(HTTPServerResponse& response);
private:
    std::shared_ptr<SelectedDataCache> _selectedDataCache;
};

class SelectedDataRequestHandler_usb : public SelectedDataRequestHandler
{
public:
    SelectedDataRequestHandler_usb(std::shared_ptr<SelectedDataCache> selectedDataCache, const std::vector<std::string>& pathSegments);
    std::string getResponse() {return responseAsJSONString;};
public:
    void handleGetRequest(Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response);
    void handleDeleteRequest(Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response);
private:
    SelectedDataRequestHandler_usb(const SelectedDataRequestHandler_usb&);
    SelectedDataRequestHandler_usb& operator = (const SelectedDataRequestHandler_usb&);
private:
    const std::string getSelectedData(Poco::Net::HTTPResponse& response);
private:
    std::shared_ptr<SelectedDataCache> _selectedDataCache;
    std::string responseAsJSONString = "";
};

#endif // __SELECTED_DATA_REQUEST_HANDLER_H__
