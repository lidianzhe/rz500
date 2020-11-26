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
#include <stdio.h>
#include <QByteArray>
#include <QTimer>
#include <QDateTime>
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

#include "umxPeriDev.h"

/*
insert into camera_configuration (id,serialNumber,Mode) values(
1,'HC0709A000303','Recog')
*/
StatusForm::StatusForm(QStackedWidget *pQStackedWidget,QWidget *parent) :
    QDialog(parent),
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


    m_config = new Poco::Util::PropertyFileConfiguration("/usr/local/bin/umxLauncher.properties");

    //读取配置
    m_DeviceSN=m_config->getString("umx.device.serialnumber","HC0000000000");
    if(m_DeviceSN.empty()){
        m_config->setString("umx.device.serialnumber","HC0000000000");
        m_config->save("/usr/local/bin/umxLauncher.properties");
    }

    std::cout<<m_DeviceSN<<std::endl;
    poco_information_f1(logger_handle,"service start runing,deivce's SN is %s",m_DeviceSN);
    m_client = new Client();
    //封装需要读取的内容
    readConfig();

    // umxAlgoLib
    int ret=  umxAlgo_create(&_gUmxAlgoHandle, m_config, UMXALGO_IRIS_DELTAID_ACTIVEIRIS_USA, UMXALGO_FACE_OPENCV, UMXALGO_FACE_NORMAL);

    //int ret = umxAlgo_create(&_gUmxAlgoHandle, m_config, UMXALGO_IRIS_DELTAID_ACTIVEIRIS_USA, UMXALGO_FACE_OPENCV);

    //int ret = umxAlgo_create(&_gUmxAlgoHandle, _logger.get("umxAlgoLib"), m_config, UMXALGO_IRIS_DELTAID_ACTIVEIRIS_USA, UMXALGO_FACE_OPENCV);
    //int ret = umxAlgo_create(&_gUmxAlgoHandle, _logger.get("umxAlgoLib"), m_config, UMXALGO_IRIS_DELTAID_ACTIVEIRIS_USA, UMXALGO_FACE_NEUROTECH_VERILOOK_LITHUANIA);
    //int ret = umxAlgo_create(&_gUmxAlgoHandle, _logger.get("umxAlgoLib"), m_config, UMXALGO_IRIS_DELTAID_ACTIVEIRIS_USA, UMXALGO_FACE_NEC_NEOFACE_JAPAN);

    std::cout<<"ret="<<ret<<std::endl;
    // umxDBLib
    int retDB = umxDB_create(&_umxDBHandle, logger_handle, m_config);
    poco_information(logger_handle,"open database");
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

    m_utilsHelper = new utilsHelper();
    _rs232 = new CDeviceRs232();
    umxPeriDev_setupRs232(9600);

    //rs232Write("123",0);
    _rs485 = new CDeviceRs485();
    umxPeriDev_setupRs485(9600);
    //rs485Write("123",0);

    //test
    //m_utils->algotest();
    //m_utils->algotest2("/home/root/right_vista.bmp","4","algovista");
    //------


    m_serverThread = new ServerThread(this);
    m_serverThread->start();

    m_timeTimer = new QTimer(this);
    connect(m_timeTimer,SIGNAL(timeout()),this,SLOT(syncTime()));
    m_timeTimer->setInterval(1000*60);
    m_timeTimer->start();

    m_syncTimer = new QTimer(this);
    connect(m_syncTimer,SIGNAL(timeout()),this,SLOT(syncToServer()));
    m_syncTimer->setInterval(1000*((m_checkAvailable || m_rs232 || m_rs485 || m_dynamicWg)==1?1:3));
    m_syncTimer->start();
    //
    syncTime();

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


void StatusForm::readConfig()
{
    std::cout<<"call readConfig()"<<std::endl;
    //读取最新的配置文件
    m_config->load("/usr/local/bin/umxLauncher.properties");
    m_debugMode = m_config->getInt("launcher.device.hidden.debug",0);
    m_useServer=m_config->getInt("rzagent.server.useserver",0);
    m_configRequestImage = m_config->getInt("rzagent.json.requestimage",0);
    m_checkAvailable = m_config->getInt("rzagent.setup.checkAvailable",0);

    m_cmdHead=m_config->getString("rzagent.rs.cmdhead","");
    m_cmdEnd=m_config->getString("rzagent.rs.cmdend","");
    m_rsEncode=m_config->getInt("rzagent.rs.encode",0); //0 ascii 1 hex 2 ten
    m_rs232=m_config->getInt("rzagent.rs.rs232",0);
    m_rs485=m_config->getInt("rzagent.rs.rs485",0);
    m_dynamicWg=m_config->getInt("rzagent.wg.dynamic",0);

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
    m_syncTimer->stop();

    Logger& m_logger=dzrun.initLog("sync");
    //std::cout << "----begin call syncToServer----"<<endl;
    //poco_information(m_logger,"----begin call syncToServer----");
    //std::cout << "runing syncToServer Interval = "<<m_syncTimer->interval()<<endl;

    std::string strJson;
    std::vector<LogEntry> logs;
    logs.clear();
    int ret=-1;
    bool isNew=true;
    LogEntry logNew;
    try{
        int count;
        ret = umxDB_countLog(_umxDBHandle,&count);
        //如果记录数大于1条，说明有没上传的数据，取最新一条，判读是否为刚识别的，上传直到完成。
        if(count>1){
            ret = umxDB_selectLogEntryByPage(_umxDBHandle,1,1,"desc",&logs);
            logNew = logs[0];
            QDateTime t1 = QDateTime::fromString(QString::fromStdString(logNew.GetTimestamp()),"yyyy-MM-ddThh:mm:ssZ");
            QDateTime t2 = QDateTime::currentDateTime();
            qint64 msecs = t1.msecsTo(t2);
            if((logNew.GetUserUUID()=="") || (msecs>2000)){
                logs.clear();
                isNew=false;
                ret = umxDB_selectLogEntryByPage(_umxDBHandle,1,20,"asc",&logs);
            }
        }else
        {
            if(count==1){
                ret = umxDB_selectLogEntryByPage(_umxDBHandle,1,1,"desc",&logs);
                logNew = logs[0];
                QDateTime t1 = QDateTime::fromString(QString::fromStdString(logNew.GetTimestamp()),"yyyy-MM-ddThh:mm:ssZ");
                QDateTime t2 = QDateTime::currentDateTime();
                qint64 msecs = t1.msecsTo(t2);
                if(logNew.GetUserUUID()=="" || msecs>2000){
                    isNew=false;
                }
            }else //count==0 返回
            {
                isNew=false;
                m_syncTimer->start();
                return;
            }
        }
    }
    catch(Poco::Exception &e){
        poco_warning(m_logger," selectlog fail:"+e.message());
    }

    bool availbale = true; //default不需要二次验证，是有效的

    //新记录并且识别类型并且不等同最后处理的记录，才执行串口或韦根发送或二次验证，避免多次执行
    int pid=logNew.GetId();
    if(isNew && pid!=m_lastpid && logNew.GetEventType()=="Recognition"){
        //----发送串口指令
        if((m_rs232 || m_rs485)&& isNew){
            if(m_rs232)
                rs232Write(logNew.GetUserUUID(),m_rsEncode);
            if(m_rs485)
                rs485Write(logNew.GetUserUUID(),m_rsEncode);
        }
        //----end rs232

        //--begin 双韦根
        if(m_dynamicWg && isNew){
            //        QString strid=QString::fromStdString(logNew.GetUserUUID());
            //        bool isNumber=false;
            //        int uid= strid.toInt(&isNumber); //先得到用户Id
            int uid = std::stoi(logNew.GetUserUUID());

            if(logNew.GetEventType()=="Recognition"){
                string info=logNew.GetInfo();
                if(info.substr(0,2)=="In")
                    uid=uid+10000;
                if(info.substr(0,3)=="Out")
                    uid=uid+20000;
                wgWrite(uid);
            }

        }
        //--end 双韦根
        //----二次验证
        if(m_checkAvailable && isNew)
        {
            std::cout<<"call getAvailable api"<<std::endl;
            //如果没查到则显示
            LogEntry newlog=logs[0];
            std::cout<<          newlog.GetUserUUID()<<std::endl;
            std::string strAvailable =m_client->getAvailable(newlog.GetUserUUID(),m_DeviceSN);
            std::cout<<"getAvailable="<<strAvailable<<std::endl;
            if(strAvailable=="1")
            {
                std::cout<<"setRelay=1"<<std::endl;
                umxPeriDev_setRelay(1);
                sleep(1);
                umxPeriDev_setRelay(0);
            }
            else
            {
                try{
                    std::cout<<"remove log Id="<<newlog.GetId()<<std::endl;
                    bool isimage=true;
                    ret = umxDB_deleteLogEntryById(_umxDBHandle, newlog.GetId(),&isimage);
                }
                catch(Poco::Exception &e){
                    poco_warning(m_logger,"remove log fail:"+e.message());
                }

                umxPeriDev_setLedIndicatorBrightness(255,0,0);
                ui->infoText->setText(QString("Can't Find Location CARD"));
                sleep(1);
                system("aplay /usr/local/share/CMITECH/sound/cn/unauthorized.wav");
                umxPeriDev_setLedIndicatorBrightness(0,0,0);
                availbale=false;
            }
        }
        //----结束二次验证

        m_lastpid=pid;
    } //end if isnew

    //如果没设置云上传，返回
    if(m_useServer!=1 )
    {
        m_syncTimer->start();
        return;
    }
    //如果上传失败过，等待时间计时器同步后再尝试
    if(!m_allowtryupload){
        m_syncTimer->start();
        return ;
    }
    if (availbale && ret == UMXDB_SUCCESS &&logs.size()>0)
    {
        std::cout << "----begin try upload data...----"<<endl;
        std::stringstream ss;
        ss.clear();
        ss<<"[";
        for(LogEntry log:logs){
            std::string uuid="";
            if(log.GetInfo().find("{")==string::npos && log.GetInfo().find("[")==string::npos && log.GetInfo().find("}")==string::npos && log.GetInfo().find("]")==string::npos)
            {
                uuid=log.GetUserUUID();
            }

            ss<<"\n{\"pId\":"<<0<<",\"deviceSN\":"<<"\""<<m_DeviceSN<<"\",\"id\":"<<log.GetId()<<",";
            ss<<"\"eventType\":\""<<log.GetEventType()<<"\",\"timeStamp\":\""<<log.GetTimestamp()<<"\",\"userUID\":\""<<uuid<<"\",";
            ss<<"\"info\":\""<<log.GetInfo()<<"\",\"additionalData\":\""<<log.GetAdditionalData()<<"\",\"imageData\":";
            if(m_configRequestImage == 0 )
                ss<<"\"\"";
            else{ //解码Image
                Poco::Data::BLOB i(log.GetImageData());
                std::cout<<"blob size="<<i.size()<<std::endl;
                std::ostringstream os;
                Poco::Base64Encoder encoder(os);
                std::string s(i.rawContent(),i.size());
                //std::vector<char> c = log.GetImageData().content();
                //s.insert(s.begin(),c.begin(),c.end());
                encoder<<s;
                encoder.close();
                //std::cout<<"asbase64: "<<os.str()<<std::endl;
                ss<<"\""<<os.str()<<"\"";
            }
            ss<<"},";
        }
        strJson=ss.str();
        strJson.pop_back();
        strJson=strJson+"\n]";
        //strJson =log.AsJSONString();
        std::cout<<"josn: "<<strJson<<std::endl;
        std::cout<<"begin post"<<std::endl;
        if (m_client->SyncToServerPost(strJson)==HTTPResponse::HTTPStatus::HTTP_CREATED)
        {
            //ui->infoText->setText(QString("上传日志 logId=%1").arg(log.GetId()));

            try{
                int b=logs.front().GetId();
                int e=logs.back().GetId();
                int size=logs.size();
                std::cout<<"upload success, logs size="<<logs.size()<<" from "<<b <<" to "<<e <<std::endl;
                poco_information_f3(m_logger,"upload success, logs size= %d from %d  to %d",size,b,e);
                ret = umxDB_deleteLogEntryFromTo(_umxDBHandle,b,e);
                //bool isimage=true;
                //ret = umxDB_deleteLogEntryById(_umxDBHandle, log.GetId(),&isimage);
            }
            catch(Poco::Exception &e){
                poco_warning(logger_handle,"rzagent: delete logs fail:"+e.message());
            }
        }
        else
        {
            std::cout<<"上传失败，待syncTime调用后，再次尝试连接。"<<std::endl;
            //poco_warning(m_logger,"SyncToServer:上传失败，待syncTime调用后，再次尝试连接。");
            ui->infoText->setText("bad request or not found....");
            m_allowtryupload=false;
            m_syncTimer->start();
            return;
        }

    }
    //poco_information(m_logger,"----end call syncToServer----");
    std::cout << "----end call syncToServer"<<endl;
    m_syncTimer->start();
}

void StatusForm::syncTime()
{
    m_timeTimer->stop();
    readConfig();
    if(m_useServer!=1 )
    {
        m_timeTimer->start();
        return;
    }

    std::string strTime= m_client->getDatetime();
    if(strTime!="")
    {
        //"yyyy-mm-dd hh:mm:ss"
        QString t=QString::fromStdString(strTime);
        QString nt=QString("%1-%2-%3 %4").arg(t.mid(6,4), t.left(2),t.mid(3,2),t.right(8));
        string strcmd="date -s \""+nt.toStdString()+"\"";
        std::cout << "date2:"<<strcmd<< endl;
        system(strcmd.c_str());
        //"mm/dd/yyyy hh:mm:ss"
        strTime = "date -s \""+strTime+"\"";
        std::cout << "date:"<<strTime<< endl;
        system(strTime.c_str());

        system("hwclock -w");
    }
    //重新激活上传尝试
    if(m_allowtryupload==false){
        m_allowtryupload=true;
    }
    m_timeTimer->start();
    std::cout<<"call syncTime end"<<std::endl;
}

void StatusForm::rs232Write(string uuid,int rsEncode)
{
    QString cmdHead=QString::fromStdString(m_cmdHead);
    QString cmdEnd=QString::fromStdString(m_cmdEnd);
    int formattype=10 ;
    bool hexencode=0 ;
    switch (rsEncode) {
    case 1: //hex
        formattype=16;
        hexencode=1; //原样传出
        break;
    case 2: //10进制 hex传
        formattype=10;
        hexencode=1; //原样传出
    default: //0 10进制 ascii传
        formattype=10;
        hexencode=0;
        break;
    }
    //int id= std::stoi(uuid,nullptr,10);

    QString strId=QString::fromStdString(uuid);
    strId = QString::number(strId.toLong(),formattype);
    std::cout << "write to rs232: "<<strId.toStdString()<<std::endl;

    QByteArray baHead= QByteArray::fromHex(cmdHead.toLatin1());
    QByteArray baEnd= QByteArray::fromHex(cmdEnd.toLatin1());
    QByteArray baId;
    if(hexencode){
        baId= QByteArray::fromHex(strId.toLatin1());
    }else
    {
        baId= strId.toLatin1();
    }
    QByteArray cmd;
    cmd.append(baHead);
    cmd.append(baId);
    cmd.append(baEnd);
    _rs232->write(cmd);
}
void StatusForm::rs485Write(string uuid,int rsEncode)
{
    QString cmdHead=QString::fromStdString(m_cmdHead);
    QString cmdEnd=QString::fromStdString(m_cmdEnd);
    int formattype=10 ;
    bool hexencode=0 ;
    switch (rsEncode) {
    case 1: //hex
        formattype=16;
        hexencode=1; //原样传出
        break;
    case 2: //10进制 hex传
        formattype=10;
        hexencode=1; //原样传出
    default: //0 10进制 ascii传
        formattype=10;
        hexencode=0;
        break;
    }
    //int id= std::stoi(uuid,nullptr,10);

    QString strId=QString::fromStdString(uuid);
    strId = QString::number(strId.toLong(),formattype);
    std::cout << "write to rs485: "<<strId.toStdString()<<std::endl;

    QByteArray baHead= QByteArray::fromHex(cmdHead.toLatin1());
    QByteArray baEnd= QByteArray::fromHex(cmdEnd.toLatin1());
    QByteArray baId;
    if(hexencode){
        baId= QByteArray::fromHex(strId.toLatin1());
    }else
    {
        baId= strId.toLatin1();
    }
    QByteArray cmd;
    cmd.append(baHead);
    cmd.append(baId);
    cmd.append(baEnd);
    _rs485->write(cmd);
}

void StatusForm::wgWrite(int uid)
{
    //uid=2;
    //set wiegand 26
    umxPeriDev_setWiegandConfig(26, 80, 500,26, 80, 500);
    // Below is direct sending 26bits including decimal 10 from total 4bytes (32bits) but if parity bits are necessary
    //p0000000 00000000 00000101 0p000000
    //00000000 00000000 00000010 10000000
    unsigned char buf[4], writeData[4];
    bool isOdd=false;
    int n=uid/2;
    isOdd=(uid&1);
    if(isOdd)
    {
        n=(uid-1)/2;
    }else
    {
        n=uid/2;
    }

    QString strHexId= QString::number(n,16);
    QByteArray baId_hex=QByteArray::fromHex(strHexId.toLatin1());

//    std::cout << "hexid= "<<strHexId.toStdString()<<std::endl;
//    cout << "balen= "<<baId_hex.length()<<endl;

    buf[0] = 0x00;
    buf[1] = 0x00;
    buf[2] = 0x00;
    buf[3] = 0x80;

    int len=baId_hex.length()-1;
    for(int i=2;i>0;i--){
        buf[i]=len>=0?baId_hex.at(len--):0x00;
    }
    buf[3]=isOdd?0x80:0x00; //对应教验位，x80时 值加1

    // Wiegand bits swap,反转存储example: 10000101->10100001
    for(int i=0; i<4; i++)
    {
        writeData[i] = 0;
        writeData[i] |= ((buf[i] & 0x01) ? 0x1 : 0x0) << 7;
        writeData[i] |= ((buf[i] & 0x02) ? 0x1 : 0x0) << 6;
        writeData[i] |= ((buf[i] & 0x04) ? 0x1 : 0x0) << 5;
        writeData[i] |= ((buf[i] & 0x08) ? 0x1 : 0x0) << 4;
        writeData[i] |= ((buf[i] & 0x10) ? 0x1 : 0x0) << 3;
        writeData[i] |= ((buf[i] & 0x20) ? 0x1 : 0x0) << 2;
        writeData[i] |= ((buf[i] & 0x40) ? 0x1 : 0x0) << 1;
        writeData[i] |= ((buf[i] & 0x80) ? 0x1 : 0x0) << 0;
    }

    umxPeriDev_writeWiegandData((const char *)writeData, 4);

}
