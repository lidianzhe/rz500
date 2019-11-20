#include "myrequesthandlerfactory.h"
#include "roothandler.h"
#include "myrequesthandler.h"
MyRequestHandlerFactory::MyRequestHandlerFactory()
{

}

HTTPRequestHandler *MyRequestHandlerFactory::createRequestHandler(const HTTPServerRequest &request)
{

    if(request.getURI()=="/")
        return new RootHandler();
    else
    {
        return new MyRequestHandler();
    }
}
