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
    //ostr << "{";
    ostr << "\"version\":\"19.10.26\",\n";
    ostr << "\"20180309\":\"add convertimage\",\n";
    ostr << "\"20180730\":\"fix four question\"\n";
    ostr << "\"20190131\":\"upgrade to 0.5.3 LLSDK\"\n";
    ostr << "\"20190415\":\"add check available function.\"\n";
    ostr << "\"20190820\":\"support rz to ef convert.\"\n";
    ostr << "\"20191001\":\"add extend properties.\"\n";
    ostr << "\"20191026\":\"修正时间没有写到固件的问题.\"\n";
    ostr << "\"20191120\":\"upgrade to 0.5.12 LLSDK,添加详细的日志功能\"\n";
    ostr << "\"20200110\":\"批量上传功能\"\n";
    ostr << "\"20200207\":\"修正UID乱码上传的问题\"\n";
    //ostr <<"}";
    ostr<<endl;

}
