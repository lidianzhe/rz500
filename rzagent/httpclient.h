#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include <Poco/Net/HTTPCredentials.h>
#include "Poco/StreamCopier.h"
#include "Poco/NullStream.h"
#include "Poco/Path.h"
#include "Poco/URI.h"
#include "Poco/Exception.h"
#include <stdio.h>
#include <iostream>
#include <istream>

#include <QString>


#include "umxCamLib/umxCamGlobal.h"
#include "algoutils.h"
using Poco::Net::HTTPClientSession;
using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPMessage;
using Poco::StreamCopier;
using Poco::Path;
using Poco::URI;
using Poco::Exception;

class Client
{
public:
    Client();
    Client(std::string server){m_Server= server;}
    //body
    bool doRequest(HTTPClientSession &session, HTTPRequest &request, HTTPResponse &response, std::string &body);
    std::string Get();
    HTTPResponse::HTTPStatus SyncToServerPost(std::string &body);
    std::string getDatetime();
    void setLogsUri(std::string uri){m_LogsUri=uri;}
    void setServer(std::string server){m_Server=server;}
    void setPath(std::string path){m_Path=path;}
//
    HTTPResponse::HTTPStatus Request(const std::string &method, const string &path, const std::string &body, string &data);

    std::string getAvailable(std::string uuid);
    std::string getAvailable(std::string uuid,std::string sn);
private:
    std::string m_Server="120.27.233.3:80";
    std::string m_Path="/irisapi/api/";
    std::string m_LogsUri="logs";
    //algo
    AlgoUtils *m_utils;

    bool DeleteLog(long id);



};

#endif // HTTPCLIENT_H
