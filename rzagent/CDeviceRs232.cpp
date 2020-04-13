#include "CDeviceRs232.h"

#include "umxPeriDev.h"


static CDeviceRs232* __pDeviceRs232 = NULL;

CDeviceRs232::CDeviceRs232(QObject *parent) : QObject(parent)
{
    __pDeviceRs232 = this;
    m_bQuit = true;
}

CDeviceRs232::~CDeviceRs232()
{

}

int CDeviceRs232::start()
{
    qDebug("CDeviceRs232::%s() ENTER, m_bQuit=%d, pid=%d", __func__, m_bQuit,  m_thredId);
    if (m_bQuit) {
        m_bQuit = false;
        pthread_create(&m_thredId, NULL, run, this);
        if (m_thredId < 0) {
            m_bQuit = true;
            return -errno;
        }
    }
    //pthread_detach(m_thredId);
    qDebug("CDeviceRs232::%s() EXIT, m_bQuit=%d, pid=%d", __func__, m_bQuit,  m_thredId);
    return 0;
}

int CDeviceRs232::stop()
{
    qDebug("CDeviceRs232::%s() ENTER, m_bQuit=%d, pid=%d", __func__, m_bQuit,  m_thredId);
    if (!m_bQuit) {
        int status;
        m_bQuit = true;
        if (pthread_join(m_thredId, (void **)&status)) {
            return -errno;
        }
    }
    qDebug("CDeviceRs232::%s() EXIT, m_bQuit=%d, pid=%d", __func__, m_bQuit,  m_thredId);
    return 0;
}

int CDeviceRs232::write(QByteArray data)
{
    int write_size;
    int err = umxPeriDev_writeRs232(data.constData(), data.size(), &write_size);
    if (!err) {
        return write_size;
    }
    else {
        if (err < 0)
            return err;
        return -err;
    }
}

static int __status;

void CDeviceRs232::cbDataReceived(char* buffer, const int buffer_size, int err)
{
    qDebug("%s(), buffer=%p, size=%d, err=%d", __func__, buffer, buffer_size, err);
    if (__pDeviceRs232) {
        QByteArray data;
        if (buffer != NULL && err == 0) {
            data.append(buffer, buffer_size);
            __status = buffer_size;
            if (buffer[0] == 'h' && buffer[1] == 'e' && buffer[2] == 'l' && buffer[3] == 'l' && buffer[4] == 'o') {
                __pDeviceRs232->emit dataReceived(data, 2, 0);
                __pDeviceRs232->emit dataReceived(NULL, 0, 0); // Success
                __status = 0;

            }
            else
                __pDeviceRs232->emit dataReceived(data, 2, -1);
        }
        else {
            __status = -1;
            __pDeviceRs232->emit dataReceived(NULL, 2, (err != 0) ? err : -1);
        }
    }
}

#define DATA "hello"

void *CDeviceRs232::run(void *data)
{
    CDeviceRs232 *pOwn = (CDeviceRs232*)data;
    int err, i;
    int timeout = 5;
    int success = 0;
    QByteArray baBuf;

    __status = -1;

    err = umxPeriDev_setRs485RecvCB(cbDataReceived);
    if (err != 0) {
        qDebug("Failed umxPeriDev_setRs485RecvCB, errno=%d\n", err);
    }

    int write_size;
    err = umxPeriDev_writeRs232(DATA, strlen(DATA), &write_size);
    if (err) {
        qDebug("Failed umxPeriDev_writeRs232(...), errno=%d\n", err);
        pOwn->emit dataReceived(NULL, 1, err);
        goto FAIL;
    }
    qDebug("rs232 write(%d)", write_size);
    pOwn->emit dataReceived(baBuf.append(DATA, strlen(DATA)), 1, err);

    i = timeout;
    while (i) {
        if (pOwn->m_bQuit)
            goto FAIL;
        --i;
        if (__status >= 0)
            break;
        sleep(1);
    }
    qDebug("rs485 data receive time-out, status=%d", __status);
    if (__status < 0) {
        pOwn->emit dataReceived(NULL, 0, 1001/*timeout*/);
        goto FAIL;
    }

    //pOwn->emit dataReceived(NULL, 0, 0); // Success
    //success = 1;

FAIL:
    err = umxPeriDev_setRs485RecvCB(NULL);
    if (err != 0) {
        qDebug("Failed umxPeriDev_setRs485RecvCB(NULL), errno=%d\n", err);
    }

    return NULL;
}
