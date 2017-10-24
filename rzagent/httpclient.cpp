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
#include "Poco/Net/NetException.h"
//#include "Poco/JSON/Parser.h"
#include <stdio.h>
#include <iostream>
#include <sstream>

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

Client::Client()
{

}

bool Client::doRequest(Poco::Net::HTTPClientSession &session, Poco::Net::HTTPRequest &request, Poco::Net::HTTPResponse &response,std::string &body)
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
    URI uri("http://"+m_Server+m_Path+m_LogsUri);
    std::string path=uri.getPathAndQuery();
    if (path.empty()) path="/";
    HTTPClientSession session(uri.getHost(),uri.getPort());
    try{
        HTTPRequest request(HTTPRequest::HTTP_GET,path,HTTPRequest::HTTP_1_1);
        session.setTimeout(Poco::Timespan(2,0));
        HTTPResponse response;

        session.sendRequest(request);
        std::istream &isres =session.receiveResponse(response);
        std::cout << response.getStatus() <<" "<< response.getReason() << std::endl;
        StreamCopier::copyStream(isres,std::cout);
        std::cout<<std::endl;
    }
    catch(Poco::Exception &exc)
    {
        std::cout << "get request: "<<exc.displayText() <<std::endl;
    }
    catch(...)
    {
        std::cout <<"get request : other error"<<std::endl;
    }
}

HTTPResponse::HTTPStatus Client::Post(std::string &body)
{

    URI uri("http://"+m_Server+m_Path+m_LogsUri);
    HTTPClientSession session(uri.getHost(),uri.getPort());
    HTTPRequest request(HTTPRequest::HTTP_POST,uri.getPath(),HTTPRequest::HTTP_1_1);
    session.setTimeout(Poco::Timespan(2,0));
    request.setContentLength((int)body.length());
    request.setContentType("application/json");
    try{
        session.sendRequest(request)<<body;
        HTTPResponse response;
        std::istream &isres = session.receiveResponse(response);
        std::cout << response.getStatus() << " " << response.getReason() << std::endl;

        return response.getStatus();
    }
    catch(Poco::Exception &exc){
        session.reset();
        std::cout << "post request:"<<exc.displayText() <<std::endl;
        return HTTPResponse::HTTPStatus::HTTP_NOT_FOUND;
    }
    catch(...){
        std::cout << "post request: no handle error"<<std::endl;
        return HTTPResponse::HTTPStatus::HTTP_EXPECTATION_FAILED;
    }

}

std::string Client::getDatetime()
{
    try{
        URI uri("http://"+m_Server+m_Path+"echo/datetime");
        std::string path=uri.getPathAndQuery();
        if (path.empty()) path="/";

        HTTPClientSession session(uri.getHost(),uri.getPort());

        HTTPRequest request(HTTPRequest::HTTP_GET,path,HTTPRequest::HTTP_1_1);
        session.setTimeout(Poco::Timespan(2,0));
        HTTPResponse response;

        session.sendRequest(request);
        std::istream &isres =session.receiveResponse(response);
        std::cout << response.getStatus() <<" "<< response.getReason() << std::endl;
        std::stringstream ss;
        StreamCopier::copyStream(isres,ss);
        std::cout<<"set datetime="<<ss.str()<<std::endl;
        return ss.str();
    }
    catch(Poco::Exception &exc)
    {
        std::cout <<"getTime request:" <<exc.displayText() <<std::endl;
        return "";
    }
    catch(...)
    {
        std::cout <<"get request : other error"<<std::endl;
        return "";
    }

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

bool Client::DeleteLog(long id)
{

}
