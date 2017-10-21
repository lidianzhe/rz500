/**************************************************************************************************\

	Author:		Ralph
	Created:	11.07.2014

---------------------------------------------------------------------------------------------------

	Copyright (c) 2014 Smartsensors Ltd.

\**************************************************************************************************/

#ifndef __HTTP_REQUEST_VERB_HANDLER_H__
#define __HTTP_REQUEST_VERB_HANDLER_H__

#include <algorithm>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

#include <Poco/Any.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;

class HTTPRequestVerbHandler : public HTTPRequestHandler
{
public:
    HTTPRequestVerbHandler(){};
    HTTPRequestVerbHandler(const std::vector<std::string>& pathSegments)
        : _pathSegments(pathSegments){};
    virtual ~HTTPRequestVerbHandler(){};

	virtual void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
    {
        if (request.getMethod() == HTTPServerRequest::HTTP_GET)
        {
            handleGetRequest( request, response );
        }
        else if (request.getMethod() == HTTPServerRequest::HTTP_POST)
        {
            handlePostRequest( request, response );
        }
        else if (request.getMethod() == HTTPServerRequest::HTTP_DELETE)
        {
            handleDeleteRequest( request, response );
        }
        else if (request.getMethod() == HTTPServerRequest::HTTP_PUT)
        {
            handlePutRequest( request, response );
        }
        else
        {
            response.setStatusAndReason( HTTPServerResponse::HTTP_METHOD_NOT_ALLOWED );
            response.send();
        }
    };

protected:
    virtual void handleGetRequest(HTTPServerRequest& request, HTTPServerResponse& response)
    {
        response.setStatusAndReason( HTTPServerResponse::HTTP_METHOD_NOT_ALLOWED );
        response.send();
    };

    virtual void handlePostRequest(HTTPServerRequest& request, HTTPServerResponse& response)
    {
        response.setStatusAndReason( HTTPServerResponse::HTTP_METHOD_NOT_ALLOWED );
        response.send();
    };

    virtual void handleDeleteRequest(HTTPServerRequest& request, HTTPServerResponse& response)
    {
        response.setStatusAndReason( HTTPServerResponse::HTTP_METHOD_NOT_ALLOWED );
        response.send();
    };

    virtual void handlePutRequest(HTTPServerRequest& request, HTTPServerResponse& response)
    {
        response.setStatusAndReason( HTTPServerResponse::HTTP_METHOD_NOT_ALLOWED );
        response.send();
    };

    bool getQueryValue(const std::string& query, const std::string& queryName, std::string& value)
    {
        bool bSuccess = false;
        std::string searchQuery = queryName + "=";
        auto beg = query.find(searchQuery);
        if (beg != std::string::npos)
        {
            beg += searchQuery.length();
            auto end = query.find("&", beg + 1);
            value = query.substr(beg, end - beg);
            bSuccess = true;
        }
        return bSuccess;
    };

    bool getBoolValue(const std::string& query, const std::string& queryName, const bool defaultValue)
    {
        std::string value;
        if (getQueryValue(query, queryName, value))
        {
            return toBool(value);
        }
        return defaultValue;
    };

    int getIntValue(const std::string& query, const std::string& queryName, const int defaultValue)
    {
        std::string value;
        if (getQueryValue(query, queryName, value))
        {
            try
            {
                return std::stoi(value);
            }
            catch(const std::invalid_argument&)
            {
            }
        }
        return defaultValue;
    };

    std::string getStringValue(const std::string& query, const std::string& queryName, const std::string& defaultValue)
    {
        std::string value;
        if (getQueryValue(query, queryName, value))
        {
            return value;
        }
        return defaultValue;
    };
protected:
    const std::vector<std::string> _pathSegments;
private:
    bool toBool(std::string& value)
    {
        std::transform(value.begin(), value.end(), value.begin(), ::tolower);
        std::istringstream is(value);
        bool b;
        is >> std::boolalpha >> b;
        return b;
    };
private:
	HTTPRequestVerbHandler(const HTTPRequestVerbHandler&);
	HTTPRequestVerbHandler& operator = (const HTTPRequestVerbHandler&);
};

#endif // __HTTP_REQUEST_VERB_HANDLER_H__
