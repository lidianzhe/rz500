#include "myserver.h"
#include "myrequesthandlerfactory.h"
#include "Poco/Util/ServerApplication.h"
#include <QObject>
MyServer::MyServer()
{


}

void MyServer::StartServer()
{
    Poco::UInt16 port = 9999;
    HTTPServerParams* pParams = new HTTPServerParams;
    pParams->setMaxQueued(100);
    pParams->setMaxThreads(16);
    ServerSocket svs(port); // set-up a server socket
    MyRequestHandlerFactory* reqFactor = new MyRequestHandlerFactory();

    HTTPServer m_server(reqFactor, svs, pParams);
    m_server.start();
    waitForTerminationRequest();
}

void MyServer::StopServer()
{
    release();
}



