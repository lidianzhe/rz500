#include "serverthread.h"


ServerThread::ServerThread(QObject *parent):QThread(parent)
{
    m_server = new MyServer();
}

ServerThread::~ServerThread()
{
    m_server->StopServer();
    delete m_server;
}

void ServerThread::run()
{
    m_server->StartServer();
}
