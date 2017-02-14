#include "httpclient.h"

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
#include <sstream>
#include <QString>
#include "umxCamLib/umxCamGlobal.h"

using Poco::Net::HTTPClientSession;
using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPMessage;
using Poco::StreamCopier;
using Poco::Path;
using Poco::URI;
using Poco::Exception;
Client::Client()
{
    m_strUri = "http://192.168.0.6:80/irisapi/api/ServiceLog";

}

bool Client::doRequest(Poco::Net::HTTPClientSession &session, Poco::Net::HTTPRequest &request, Poco::Net::HTTPResponse &response)
{
    //std::ostream &osreq =
    std::cout<<"sendReques:path="<<request.getURI()<<"|"<< session.getHost() <<std::endl;
    session.sendRequest(request);
    std::cout<<"reiveResponse"<<std::endl;
    std::istream &isres =session.receiveResponse(response);
    std::cout << response.getStatus() << " " << response.getReason() << std::endl;
    StreamCopier::copyStream(isres,std::cout);
    return true;
}

std::string Client::Get()
{
    URI uri(m_strUri);
    std::string path=uri.getPathAndQuery();
    if (path.empty()) path="/";
    HTTPClientSession session(uri.getHost(),uri.getPort());
    HTTPRequest request(HTTPRequest::HTTP_GET,path,HTTPRequest::HTTP_1_1);
    HTTPResponse response;

    session.sendRequest(request);

    std::istream &isres =session.receiveResponse(response);
    std::cout << response.getStatus() << response.getReason() << std::endl;
    StreamCopier::copyStream(isres,std::cout);
    std::cout<<std::endl;
}

bool Client::Post(std::string &body)
{

    URI uri(m_strUri);
    HTTPClientSession session(uri.getHost(),uri.getPort());
    HTTPRequest request(HTTPRequest::HTTP_POST,uri.getPath(),HTTPRequest::HTTP_1_1);
    request.setContentLength((int)body.length());
    request.setContentType("application/json");
    session.sendRequest(request)<<body;
    HTTPResponse response;
    std::istream &isres = session.receiveResponse(response);
    std::cout << response.getStatus() << " " << response.getReason() << std::endl;

    return true;
}

std::string Client::BuildJSON()
{
    /*
   Poco::JSON::Object jsnObj;
   jsnObj.set("Id",3);
   jsnObj.set("UUId",3);
   jsnObj.set("Info","IrisOk");
   std::stringstream ss;
   jsnObj.stringify(ss,3);
   return ss.str();
   */
   return "{\"Id\":3,\"UUId\":2,\"Info\":\"IrisOk\"}";
}
