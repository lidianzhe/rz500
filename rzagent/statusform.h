#ifndef STATUSFORM_H
#define STATUSFORM_H

#include <QDialog>
#include <QStackedWidget>
#include <QTimer>
//umxAlgoLib, umxDBLib, umxNetLib
#include "Poco/Logger.h"
#include "Poco/AutoPtr.h"
#include "Poco/Util/PropertyFileConfiguration.h"
//umxDBLib
#include "umxDBLib/umxDBGlobal.h"
//umxCam
#include "umxCamLib/umxCam.h"
#include "umxCamLib/umxCamGlobal.h"
#include "stdlib.h"
#include "httpclient.h"
namespace Ui {
class StatusForm;
}

class StatusForm : public QDialog
{
    Q_OBJECT

public:
    explicit StatusForm(QStackedWidget *pQStackedWidget,QWidget *parent = 0);
    ~StatusForm();
private slots:
    void syncToServer();
    void syncTime();
private:
    Ui::StatusForm *ui;

    QStackedWidget *_pQStackedWidget;
    // umxAlgoLib, umxDBLib, umxNetLib
    Poco::Logger& _logger;
    Poco::AutoPtr<Poco::Util::PropertyFileConfiguration> m_config;

    // umxDBLib
    UMXDB_HANDLE _umxDBHandle;
    UMXCAM_HANDLE _umxCAMHandle;

    //
    std::string m_DeviceSN;
    Client *m_client;
    QTimer *m_timer;
    QTimer *m_timeTimer;
    int m_useServer;
    void initlog();

};

#endif // STATUSFORM_H
