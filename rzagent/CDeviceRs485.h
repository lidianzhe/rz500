#ifndef CDEVICERS485_H
#define CDEVICERS485_H

#include <unistd.h> // sleep
#include <pthread.h>
#include <errno.h>
#include <fcntl.h>

#include <QObject>

class CDeviceRs485 : public QObject
{
    Q_OBJECT
public:
    explicit CDeviceRs485(QObject *parent = 0);
    ~CDeviceRs485();

signals:
    void dataReceived(QByteArray data, int status, int err);

public slots:

private:
    pthread_t   m_thredId;
    bool    m_bQuit;

public:
    int start();
    int stop();
    int write(QByteArray data);

private:
    static void* run(void *data);
    static void cbDataReceived(char* buffer, const int buffer_size, int err);
};

#endif // CDEVICERS485_H
