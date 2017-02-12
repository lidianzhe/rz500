#ifndef STATUSFORM_H
#define STATUSFORM_H

#include <QDialog>
#include <QStackedWidget>

//umxAlgoLib, umxDBLib, umxNetLib
#include "Poco/Logger.h"
#include "Poco/AutoPtr.h"
#include "Poco/Util/PropertyFileConfiguration.h"
//umxDBLib
#include "umxDBLib/umxDBGlobal.h"
//umxCam
#include "umxCamLib/umxCam.h"
#include "umxCamLib/umxCamGlobal.h"

namespace Ui {
class StatusForm;
}

class StatusForm : public QDialog
{
    Q_OBJECT

public:
    explicit StatusForm(QStackedWidget *pQStackedWidget,QWidget *parent = 0);
    ~StatusForm();

private:
    Ui::StatusForm *ui;

    QStackedWidget *_pQStackedWidget;
    // umxAlgoLib, umxDBLib, umxNetLib
    Poco::Logger& _logger;
    Poco::AutoPtr<Poco::Util::PropertyFileConfiguration> _config;

    // umxDBLib
    UMXDB_HANDLE _gUmxDBHandle;

    UMXCAM_HANDLE _gUmxHandle;

    void initlog();
};

#endif // STATUSFORM_H
