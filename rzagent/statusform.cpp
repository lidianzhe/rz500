#include "statusform.h"
#include "ui_statusform.h"

#include "Poco/FileChannel.h"
#include "Poco/FormattingChannel.h"
#include "Poco/PatternFormatter.h"
#include "Poco/FileStream.h"
#include "Poco/LogStream.h"
using Poco::FileChannel;
using Poco::FormattingChannel;
using Poco::PatternFormatter;
using Poco::AutoPtr;

#include "umxDBLib/umxDB.h"
#include "umxCommonLib/umxCommonGlobal.h"

StatusForm::StatusForm(QStackedWidget *pQStackedWidget,QWidget *parent) :
    QDialog(parent),_logger(Poco::Logger::get("rzagent")),
    ui(new Ui::StatusForm)
{
    ui->setupUi(this);

    _pQStackedWidget = pQStackedWidget;

    //set backgroud
    ui->textBackground->setStyleSheet("background-color: rgba(36, 41, 55, 255);");
    //this->setStyleSheet("background-color: rgba(36, 36, 36, 255);");
    //this->setStyleSheet("background-color:transparent;");

    ui->infoText->setStyleSheet("QLabel#infoText{color:rgb(136, 136, 133); font-size: 24px;}");
    ui->leftTextbar->setStyleSheet("QWidget#leftTextbar{background-image: url(:/images/textbar_left.png);}");
    ui->centerTextbar->setStyleSheet("QWidget#centerTextbar{border-image: url(:/images/textbar_center.png);}");
    ui->rightTextbar->setStyleSheet("QWidget#rightTextbar{background-image: url(:/images/textbar_right.png);}");


    // config logger
    _config = new Poco::Util::PropertyFileConfiguration("/home/root/rzagent.properties");
    //_config->setString("umx.device.serialnumber","HC0709A000231");
    //_config->save("/home/root/rzagent.properties");
    std::string s=_config->getString("application.logger");
    std::cout<<s<<std::endl;
    std::cout<<"write serialnumber:"<<_config->getString("umx.device.serialnumber")<<std::endl;
    initlog();

    // umxDBLib
    int retDB = umxDB_create(&_gUmxDBHandle, _logger.get("umxDBLib"), _config);
    poco_information(_logger,"open database");
    std::cout << "call umxDB_create" <<std::endl;
    ui->infoText->setText("open database");

    //
    UMXCommon::CameraConfiguration *_cameraConfig = new UMXCommon::CameraConfiguration();
    std::string sn =_cameraConfig->GetSerialNumber();
    std::cout<<"getid" <<_cameraConfig->GetId() <<std::endl;
    std::cout<<"sn: "<<sn<<std::endl;
    //delete _cameraConfig;
    ImageCapture *_imageCapture = new ImageCapture();
    std::cout << "sn=" <<_imageCapture->GetSerialNumber()<<std::endl;

}

StatusForm::~StatusForm()
{

    // umxDBLib
    umxDB_destroy(_gUmxDBHandle);

    delete ui;
}

void StatusForm::initlog()
{
//HC0709A000231
    AutoPtr<FileChannel> pChannel(new FileChannel);
    pChannel->setProperty("path", _config->getString("logging.channels.file.path", "/home/root/rzagent.log"));
    pChannel->setProperty("rotation", _config->getString("logging.channels.file.rotation", "10M"));
    pChannel->setProperty("archive", _config->getString("logging.channels.file.archive", "number"));
    pChannel->setProperty("purgeCount", _config->getString("logging.channels.file.purgeCount", "10"));


    AutoPtr<PatternFormatter> pPF(new PatternFormatter);
    pPF->setProperty("pattern", _config->getString("logging.formatters.standard.pattern", "%L%Y-%m-%d %H:%M:%S %Z %s: [%p] %t")); // local time

    AutoPtr<FormattingChannel> pFC(new FormattingChannel(pPF, pChannel));
    _logger.setChannel(pFC);
    poco_information(_logger,"init rzagent log");

}
