#include "myrequesthandler.h"
#include <QtCore>
#include <QString>
#include <QStringList>
#include <iostream>
#include "Poco/Net/HTTPResponse.h"
#include "Poco/URI.h"
#include "Poco/Path.h"
#include <vector>
#include "runtime.h"

#include "algoutils.h"
using namespace std;
using namespace Poco;
using namespace Net;
MyRequestHandler::MyRequestHandler()
{

}

void MyRequestHandler::handleRequest(HTTPServerRequest &request, HTTPServerResponse &response)
{
    Poco::URI uri(request.getURI());
    QStringList path=QString::fromStdString(uri.getPath()).split("/");
//    std::cout << qPrintable(path.first()) <<endl;
//    std::cout <<qPrintable(path.at(1))<<endl;
//    std::cout <<qPrintable(path.at(2))<<endl;
    if(path.value(1) =="templates"){
        api_Templates(request,response);
        return;
    }

// read...
//    std::istream &i = request.stream();
//    int len = request.getContentLength();
//    char* buffer = new char[len];
//    i.read(buffer, len);
//    std::cout<<buffer<<std::endl;

    response.setContentType("application/json");
    response.redirect(request.getURI(),HTTPResponse::HTTPStatus::HTTP_CREATED);
}

void MyRequestHandler::api_Templates(HTTPServerRequest &request, HTTPServerResponse &response)
{
    try{

        if(request.getMethod()=="GET")
        {
            //todo
        }
        else if(request.getMethod()=="POST")
        {
            //TODO
        }else if(request.getMethod()=="PUT")
        {
            std::string id= QString::fromStdString(request.getURI()).split("/").at(2).toStdString();
            AlgoUtils *algo = new AlgoUtils(dzrun.umxalgo_Handle);
            int ret=algo->getTemplates(id);
            if(ret>=0)
                response.redirect(request.getURI(),HTTPResponse::HTTPStatus::HTTP_OK);
            else
                response.setStatusAndReason(HTTPResponse::HTTPStatus::HTTP_NOT_FOUND);

        }
    }catch(Exception)
    {
        response.setStatusAndReason(HTTPResponse::HTTPStatus::HTTP_BAD_REQUEST);
    }
    response.send();
}
