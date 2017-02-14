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



#include "umxCamLib/umxCamGlobal.h"

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
    bool doRequest(HTTPClientSession &session,HTTPRequest &request,HTTPResponse &response);
    std::string Get();
    bool Post(std::string &body);
    std::string BuildJSON();
private:
    std::string m_strUri;
};

#endif // HTTPCLIENT_H
