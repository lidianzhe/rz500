#include <iostream>
#include "roothandler.h"
#include "Poco/Util/Application.h"
using namespace Poco;
using namespace std;
RootHandler::RootHandler()
{

}

void RootHandler::handleRequest(HTTPServerRequest &request, HTTPServerResponse &response)
{
    Poco::Util::Application& app = Poco::Util::Application::instance();
    app.logger().information("Request from " +
    request.clientAddress().toString());
    response.setChunkedTransferEncoding(true);
    response.setContentType("application/json");
    std::ostream& ostr = response.send();
    ostr << "{";
    ostr << "\"version\":\"1.6.5\",\n";
    ostr << "\"20180309\":\"add convertimage\",\n";
    ostr << "\"20180730\":\"fix four question\"\n";
    ostr << "\"20190131\":\"upgrade to 0.5.3 LLSDK\"\n";
    ostr <<"}";
    ostr<<endl;

}
