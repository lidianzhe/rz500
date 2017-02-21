#include "statusform.h"
#include "ui_statusform.h"

#include "Poco/FileChannel.h"
#include "Poco/FormattingChannel.h"
#include "Poco/PatternFormatter.h"
#include "Poco/FileStream.h"
#include "Poco/LogStream.h"
#include "Poco/StreamCopier.h"
#include "Poco/Data/BLOB.h"
#include "Poco/Data/BLOBStream.h"
using Poco::FileChannel;
using Poco::FormattingChannel;
using Poco::PatternFormatter;
using Poco::AutoPtr;
using Poco::Data::BLOBInputStream;
using Poco::StreamCopier;
#include <QByteArray>
#include <QTimer>
#include <QThread>

#include "umxDBLib/umxDB.h"
#include "umxCommonLib/umxCommonGlobal.h"

#include "httpclient.h"

/*
insert into camera_configuration (id,serialNumber,Mode) values(
1,'HC0709A000302','Recog')
*/
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

    //launcher.network.server.port: 80
    //launcher.network.server.serverip: 120.27.233.3
    //launcher.network.server.useserver: 1

    // config logger
    m_config = new Poco::Util::PropertyFileConfiguration("/usr/local/bin/umxLauncher.properties");
    //HC0709A000231
    m_DeviceSN=m_config->getString("umx.device.serialnumber");
    if(m_DeviceSN.empty()){
        m_config->setString("umx.device.serialnumber","HC0709A000302");
        m_config->save("/usr/local/bin/umxLauncher.properties");
    }

    std::cout<<m_DeviceSN<<std::endl;
    //读取最新的配置文件
    m_config->load("/usr/local/bin/umxLauncher.properties");
    std::cout<<"write serialnumber:"<<m_config->getString("umx.device.serialnumber")<<std::endl;
    initlog();


    // umxDBLib
    int retDB = umxDB_create(&_umxDBHandle, _logger.get("umxDBLib"), m_config);
    poco_information(_logger,"open database");
    std::cout << "call umxDB_create" <<std::endl;
    ui->infoText->setText("open database");
    //
    int lastLogId=0;
    retDB = umxDB_selectLastLogID(_umxDBHandle,&lastLogId);
    if(retDB==UMXDB_SUCCESS)
        std::cout<<"last log id: "<<lastLogId<<std::endl;



    //test get
    m_useServer=m_config->getString("launcher.network.server.useserver");

    m_client = new Client();
    m_client->setServer(m_config->getString("launcher.network.server.serverip","120.27.233.3")+":"+m_config->getString("launcher.network.server.port","80"));
    m_timer = new QTimer(this);
    connect(m_timer,SIGNAL(timeout()),this,SLOT(syncToServer()));
    m_timer->start(1000*3);

    //syncToServer(true);
    //test post
    //std::string strJSON =client->BuildJSON();
    //client->Post(strJSON);

    //client->Get();
}

StatusForm::~StatusForm()
{
    // umxDBLib
    umxDB_destroy(_umxDBHandle);

    delete ui;
}


//
void StatusForm::initlog()
{
//HC0709A000231
    AutoPtr<FileChannel> pChannel(new FileChannel);
    pChannel->setProperty("path", "/home/root/rzagent.log");
    //pChannel->setProperty("path", _config->getString("logging.channels.file.path", "/home/root/rzagent.log"));
    pChannel->setProperty("rotation", m_config->getString("logging.channels.file.rotation", "10M"));
    pChannel->setProperty("archive", m_config->getString("logging.channels.file.archive", "number"));
    pChannel->setProperty("purgeCount", m_config->getString("logging.channels.file.purgeCount", "10"));

    AutoPtr<PatternFormatter> pPF(new PatternFormatter);
    pPF->setProperty("pattern", m_config->getString("logging.formatters.standard.pattern", "%L%Y-%m-%d %H:%M:%S %Z %s: [%p] %t")); // local time

    AutoPtr<FormattingChannel> pFC(new FormattingChannel(pPF, pChannel));
    _logger.setChannel(pFC);
    poco_information(_logger,"init rzagent log");
    std::cout << "write log " <<std::endl;
}

void StatusForm::syncToServer()
{
    if(m_useServer!="1" )
    {
        //m_config = new Poco::Util::PropertyFileConfiguration("/usr/local/bin/umxLauncher.properties");
        return;
    }
    std::string strJson;
    std::vector<LogEntry> logs;
    logs.clear();
    int ret = umxDB_selectLogEntryByPage(_umxDBHandle,1,2,"asc",&logs);
    if (ret == UMXDB_SUCCESS)
    {
        for(LogEntry log:logs){
            std::cout<<log.GetId()<<"|"<<log.GetEventType()<<"|"<<log.GetTimestamp()<<"|";
            std::cout<<log.GetInfo()<<"|"<<log.GetInfo()<<"|"<<log.GetAdditionalData()<<"|";
            //Poco::Data::BLOB bb(log.GetImageData());
            //Poco::Data::BLOBInputStream blobis(bb);
            //std::string strBlob;
            //Poco::UInt64 _size =StreamCopier::copyToString64(blobis,strBlob,30000);

            //std::cout << "size="<<_size<< "---->"<<strBlob<<std::endl;

            //StreamCopier::copyStream(blobis,std::cout);
            //std::string str(b);
            //QString str=QString::fromAscii(b);
            std::cout<<std::endl;
            std::stringstream ss;
            ss.clear();
            ss<<"{\"pId\":"<<1<<",\"deviceSN\":"<<"\""<<"HC0709A000302"<<"\",\"id\":"<<log.GetId()<<",";
            ss<<"\"eventType\":\""<<log.GetEventType()<<"\",\"timeStamp\":\""<<log.GetTimestamp()<<"\",\"userUID\":\""<<log.GetUserUUID()<<"\",";
            ss<<"\"info\":\""<<log.GetInfo()<<"\",\"additionalData\":\""<<log.GetAdditionalData()<<"\",\"imageData\":";
            ss<<"null";
            //ss<<"\""<<strBlob<<"\"";
            ss<<"}";
            strJson=ss.str();
            std::cout<<strJson<<std::endl;
            if (m_client->Post(strJson)==HTTPResponse::HTTPStatus::HTTP_CREATED)
            {
                ui->infoText->setText(QString("upload log Id=%1").arg(log.GetId()));
                umxDB_deleteLogEntryById(_umxDBHandle, log.GetId());
            }
            else
            {
                ui->infoText->setText("bad request or not found....");
            }
        }
    }

}
