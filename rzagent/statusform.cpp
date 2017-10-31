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
#include <vector>
#include "stdlib.h"

#include "umxAlgoLib/umxAlgo.h"
#include "umxDBLib/umxDB.h"
#include "umxCommonLib/umxCommonGlobal.h"

#include "httpclient.h"
#include "Poco/Base64Encoder.h"
#include "algoutils.h"
#include "runtime.h"
/*
insert into camera_configuration (id,serialNumber,Mode) values(
1,'HC0709A000303','Recog')
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
    //读取配置
    m_DeviceSN=m_config->getString("umx.device.serialnumber","HC0709A000303");
    if(m_DeviceSN.empty()){
        m_config->setString("umx.device.serialnumber","HC0709A000303");
        m_config->save("/usr/local/bin/umxLauncher.properties");
    }

    std::cout<<m_DeviceSN<<std::endl;

    m_client = new Client();
    //封装需要读取的内容
    readConfig();

    initlog();

    // umxAlgoLib
    int ret = umxAlgo_create(&_gUmxAlgoHandle, _logger.get("umxAlgoLib"), m_config, UMXALGO_IRIS_DELTAID_ACTIVEIRIS_USA, UMXALGO_FACE_OPENCV);
    //int ret = umxAlgo_create(&_gUmxAlgoHandle, _logger.get("umxAlgoLib"), m_config, UMXALGO_IRIS_DELTAID_ACTIVEIRIS_USA, UMXALGO_FACE_NEUROTECH_VERILOOK_LITHUANIA);
    //int ret = umxAlgo_create(&_gUmxAlgoHandle, _logger.get("umxAlgoLib"), m_config, UMXALGO_IRIS_DELTAID_ACTIVEIRIS_USA, UMXALGO_FACE_NEC_NEOFACE_JAPAN);

    std::cout<<"ret="<<ret<<std::endl;
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
    //test image

    //--


    dzrun.umxalgo_Handle = _gUmxAlgoHandle;
    dzrun.umxdb_Handle = _umxDBHandle;
    //test
    m_utils->algotest();
    //------


    m_serverThread = new ServerThread(this);
    m_serverThread->start();
    if(m_useServer)
    {
        m_timeTimer = new QTimer(this);
        connect(m_timeTimer,SIGNAL(timeout()),this,SLOT(syncTime()));
        m_timeTimer->setInterval(1000*30);
        m_timeTimer->start();

        m_timer = new QTimer(this);
        connect(m_timer,SIGNAL(timeout()),this,SLOT(syncToServer()));
        m_timer->setInterval(1000*5);
        m_timer->start();
    }

}

StatusForm::~StatusForm()
{
    // umxDBLib
    umxDB_destroy(_umxDBHandle);
    // umxAlgoLib
    umxAlgo_destroy(_gUmxAlgoHandle);

    delete ui;
}


//
void StatusForm::initlog()
{

    AutoPtr<FileChannel> pChannel(new FileChannel);
    pChannel->setProperty("path", "/home/root/rzagent.log");
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

void StatusForm::readConfig()
{
    //读取最新的配置文件
    m_config->load("/usr/local/bin/umxLauncher.properties");
    m_debugMode = m_config->getInt("launcher.device.hidden.debug",0);
    m_useServer=m_config->getInt("launcher.network.server.useserver");
    m_configRequestImage = m_config->getInt("rzagent.json.requestimage",0);
    //std::cout<<"write serialnumber:"<<m_config->getString("umx.device.serialnumber")<<std::endl;
    m_client->setServer(m_config->getString("launcher.network.server.serverip","118.31.22.44")+":"+m_config->getString("launcher.network.server.port","8080"));
    m_client->setPath(m_config->getString("launcher.network.server.syncuri","/api/"));
}

void StatusForm::clearEnrollIrisTemplate(UMXALGO_IRIS_GET_ENROL_TEMPLATE_OUTPUT *enrollIrisTemplate)
{

}

void StatusForm::clearIrisInfo(IRIS_INFO *irisInfo)
{
    irisInfo->uuid = "";
    if(irisInfo->image != NULL) {
        delete irisInfo->image;
    }
    irisInfo->image = NULL;
    irisInfo->imagePath = "";
    irisInfo->width = 0;
    irisInfo->height = 0;
    irisInfo->centerX = 0;
    irisInfo->centerY = 0;
    irisInfo->radius = 0;
}

void StatusForm::syncToServer()
{
    m_timer->stop();

    if(m_useServer!=1 )
    {

        return;
    }
    std::string strJson;
    std::vector<LogEntry> logs;
    logs.clear();
    int ret=-1;
    try{
        ret = umxDB_selectLogEntryByPage(_umxDBHandle,1,3,"asc",&logs);
    }
    catch(Poco::Exception &e){
        poco_warning(_logger,"selectlog fail:"+e.message());
    }
    if (ret == UMXDB_SUCCESS)
    {
        for(LogEntry log:logs){
            Poco::Data::BLOB i(log.GetImageData());
            std::cout<<"blob size="<<i.size()<<std::endl;
            Poco::Data::BLOBInputStream bis(i);
            std::ostringstream os;
            Poco::Base64Encoder encoder(os);
            std::string s(i.rawContent(),i.size());
            //std::vector<char> c = log.GetImageData().content();
            //s.insert(s.begin(),c.begin(),c.end());
            encoder<<s;
            encoder.close();
            //std::cout<<"asbase64: "<<os.str()<<std::endl;

            std::stringstream ss;
            ss.clear();
            ss<<"{\"pId\":"<<1<<",\"deviceSN\":"<<"\""<<m_DeviceSN<<"\",\"id\":"<<log.GetId()<<",";
            ss<<"\"eventType\":\""<<log.GetEventType()<<"\",\"timeStamp\":\""<<log.GetTimestamp()<<"\",\"userUID\":\""<<log.GetUserUUID()<<"\",";
            ss<<"\"info\":\""<<log.GetInfo()<<"\",\"additionalData\":\""<<log.GetAdditionalData()<<"\",\"imageData\":";
            if(m_configRequestImage == 0 || os.str()=="")
                ss<<"null";
            else
                ss<<"\""<<os.str()<<"\"";
            ss<<"}";
            strJson=ss.str();
            //strJson =log.AsJSONString();
            std::cout<<"josn: "<<strJson<<std::endl;
            std::cout<<"begin post"<<std::endl;
            if (m_client->Post(strJson)==HTTPResponse::HTTPStatus::HTTP_CREATED)
            {
                ui->infoText->setText(QString("upload log Id=%1").arg(log.GetId()));
                try{
                    std::cout<<"upload log Id="<<log.GetId()<<std::endl;
                    bool isimage=true;
                    ret = umxDB_deleteLogEntryById(_umxDBHandle, log.GetId(),&isimage);
                }
                catch(Poco::Exception &e){
                    poco_warning(_logger,"delete log fail:"+e.message());
                }

            }
            else
            {
                std::cout<<"返回，待syncTime调用后，再次尝试连接。"<<std::endl;
                ui->infoText->setText("bad request or not found....");
                //返回，待syncTime调用后，再次尝试连接
                m_timer->start();
                return;
            }
        }
    }

    m_timer->start();

}

void StatusForm::syncTime()
{
    m_timeTimer->stop();
    if(m_useServer!=1 )
    {
        m_timeTimer->start();
        return;
    }
    m_config->load("/usr/local/bin/umxLauncher.properties");
    readConfig();

    std::string strTime= m_client->getDatetime();
    if(strTime!="")
    {
        strTime = "date -s "+strTime;
        system(strTime.c_str());
    }
    m_timeTimer->start();
}
