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
// umxAlgoLib
#include "umxAlgoLib/umxAlgoGlobal.h"
typedef struct _IRIS_INFO {
    std::string uuid;
    unsigned char* image;
    std::string imagePath;
    int width;
    int height;
    int centerX;
    int centerY;
    int radius;
}IRIS_INFO;

namespace Ui {
class StatusForm;
}

class StatusForm : public QDialog
{
    Q_OBJECT

public:
    explicit StatusForm(QStackedWidget *pQStackedWidget,QWidget *parent = 0);
    ~StatusForm();
    //返回设备是否为调试模式
    int getDebugMode(){return m_debugMode;}
private slots:
    void syncToServer();
    void syncTime();
private:
    Ui::StatusForm *ui;

    QStackedWidget *_pQStackedWidget;
    // umxAlgoLib, umxDBLib, umxNetLib
    Poco::Logger& _logger;
    Poco::AutoPtr<Poco::Util::PropertyFileConfiguration> m_config;

    // umxAlgoLib
    UMXALGO_HANDLE _gUmxAlgoHandle;
    // umxDBLib
    UMXDB_HANDLE _umxDBHandle;
    UMXCAM_HANDLE _umxCAMHandle;

    //
    std::string m_DeviceSN;
    Client *m_client;
    QTimer *m_timer;
    QTimer *m_timeTimer;
    int m_useServer;
    int m_debugMode;
    int m_configRequestImage;

    void initlog();
    void readConfig();
    // umxAlgoLib
    void clearEnrollIrisTemplate(UMXALGO_IRIS_GET_ENROL_TEMPLATE_OUTPUT* enrollIrisTemplate);
    void clearIrisInfo(IRIS_INFO* irisInfo);
    void setIrisInfo(IRIS_INFO* toIrisInfo, UMXCAM_EVENT* fromUmxCamEvent, std::string uuid, std::string imagePath);

};

#endif // STATUSFORM_H
