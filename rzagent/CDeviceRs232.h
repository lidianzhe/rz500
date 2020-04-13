#ifndef CDEVICERS232_H
#define CDEVICERS232_H

#include <unistd.h> // sleep
#include <pthread.h>
#include <errno.h>
#include <fcntl.h>

#include <QObject>

class CDeviceRs232 : public QObject
{
    Q_OBJECT
public:
    explicit CDeviceRs232(QObject *parent = 0);
    ~CDeviceRs232();

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

#endif // CDEVICERS232_H
