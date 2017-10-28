#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H
#include <QThread>
#include "myserver.h"

class ServerThread : public QThread
{
public:
    explicit ServerThread(QObject *parent = 0);
    ~ServerThread();
protected:
    void run() ;
private:
    MyServer* m_server;
};

#endif // SERVERTHREAD_H
