#include "CDeviceRs485.h"

#include "umxPeriDev.h"


static CDeviceRs485* __pDeviceRs485 = NULL;

CDeviceRs485::CDeviceRs485(QObject *parent) : QObject(parent)
{
    __pDeviceRs485 = this;
    m_bQuit = true;
}

CDeviceRs485::~CDeviceRs485()
{

}

int CDeviceRs485::start()
{
    qDebug("CDeviceRs485::%s() ENTER, m_bQuit=%d, pid=%d", __func__, m_bQuit,  m_thredId);
    if (m_bQuit) {
        m_bQuit = false;
        pthread_create(&m_thredId, NULL, run, this);
        if (m_thredId < 0) {
            m_bQuit = true;
            return -errno;
        }
    }
    //pthread_detach(m_thredId);
    qDebug("CDeviceRs485::%s() EXIT, m_bQuit=%d, pid=%d", __func__, m_bQuit,  m_thredId);
    return 0;
}

int CDeviceRs485::stop()
{
    qDebug("CDeviceRs485::%s() ENTER, m_bQuit=%d, pid=%d", __func__, m_bQuit,  m_thredId);
    if (!m_bQuit) {
        int status;
        m_bQuit = true;
        if (pthread_join(m_thredId, (void **)&status)) {
            return -errno;
        }
    }
    qDebug("CDeviceRs485::%s() EXIT, m_bQuit=%d, pid=%d", __func__, m_bQuit,  m_thredId);
    return 0;
}

int CDeviceRs485::write(QByteArray data)
{
    int write_size;
    int err = umxPeriDev_writeRs485(data.constData(), data.size(), &write_size);
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

void CDeviceRs485::cbDataReceived(char* buffer, const int buffer_size, int err)
{
    qDebug("%s(), buffer=%p, size=%d, err=%d", __func__, buffer, buffer_size, err);
    if (__pDeviceRs485) {
        QByteArray data;
        if (buffer != NULL && err == 0) {
            data.append(buffer, buffer_size);
            __status = buffer_size;
            if (buffer[0] == 'h' && buffer[1] == 'e' && buffer[2] == 'l' && buffer[3] == 'l' && buffer[4] == 'o') {
                __pDeviceRs485->emit dataReceived(data, 2, 0);
                __pDeviceRs485->emit dataReceived(NULL, 0, 0);
                __status = 0;
            }
            else
                __pDeviceRs485->emit dataReceived(data, 2, -1);
        }
        else {
            __status = -1;
            __pDeviceRs485->emit dataReceived(NULL, 2, (err != 0) ? err : -1);
        }
    }
}

#define DATA "hello"

void *CDeviceRs485::run(void *data)
{
    CDeviceRs485 *pOwn = (CDeviceRs485*)data;
    int err, i;
    int timeout = 5;
    int success = 0;
    QByteArray baBuf;

    __status = -1;

    err = umxPeriDev_setRs232RecvCB(cbDataReceived);
    if (err != 0) {
        qDebug("Failed umxPeriDev_setRs232RecvCB, errno=%d\n", err);
    }

    int write_size;
    err = umxPeriDev_writeRs485(DATA, strlen(DATA), &write_size);
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
    qDebug("rs232 data receive time-out, status=%d", __status);
    if (__status < 0) {
        pOwn->emit dataReceived(NULL, 0, 1001/*timeout*/);
        goto FAIL;
    }

    //pOwn->emit dataReceived(NULL, 0, 0); // Success
    //success = 1;

FAIL:
    err = umxPeriDev_setRs232RecvCB(NULL);
    if (err != 0) {
        qDebug("Failed umxPeriDev_setRs232RecvCB(NULL), errno=%d\n", err);
    }

    return NULL;
}
