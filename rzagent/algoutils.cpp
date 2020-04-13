#include "algoutils.h"
#include <iostream>
#include <string>
#include <QImage>
#include <QByteArray>
#include <QPainter>
#include "Poco/Logger.h"
#include "Poco/FileChannel.h"
#include "Poco/AutoPtr.h"
#include "Poco/PatternFormatter.h"
#include "Poco/FormattingChannel.h"
using Poco::DirectoryIterator;
using Poco::Path;
using Poco::File;
using Poco::Logger;
using Poco::FileChannel;
using Poco::AutoPtr;
using Poco::PatternFormatter;
using Poco::FormattingChannel;
#include "umxAlgoLib/umxAlgo.h"
#include "umxDBLib/umxDBGlobal.h"
#include "umxCommonLib/umxCommonGlobal.h"
#include "umxDBLib/umxDB.h"
#include "runtime.h"
#include "utilshelper.h"
#include <QBuffer>
using namespace std;
using namespace UMXCommon;
AlgoUtils::AlgoUtils(): m_logger(Logger::get("algo"))
{

}

AlgoUtils::AlgoUtils(UMXALGO_HANDLE handle):
    m_logger(Logger::get("algo"))
{
    algoHandle = handle;

    AutoPtr<FileChannel> pChannel(new FileChannel);
    pChannel->setProperty("path", "/home/root/algoutils.log");
    pChannel->setProperty("rotation", "2 K");
    pChannel->setProperty("archive", "timestamp");
//    m_logger.setChannel(pChannel);

    AutoPtr<PatternFormatter> pPF(new PatternFormatter);
    pPF->setProperty("pattern", "%m-%d %H:%M:%S %s: [%p] %t"); // local time
    AutoPtr<FormattingChannel> pFC(new FormattingChannel(pPF, pChannel));
    m_logger.setChannel(pFC);

}

int AlgoUtils::getTemplates(UMXALGO_HANDLE handle, Person &person)
{
    string homePath = Path::home();
    std::string path(homePath+person.Id);

    //---
    UMXALGO_IRIS_GET_ENROL_TEMPLATE_OUTPUT bestLeftTemplate;
    clearEnrollIrisTemplate(&bestLeftTemplate);
    UMXALGO_IRIS_GET_ENROL_TEMPLATE_OUTPUT bestRightTemplate;
    clearEnrollIrisTemplate(&bestRightTemplate);

    string bestLeftEyeImage;
    string bestRightEyeImage;

    File f(path);
    if(!f.exists())
        return -1;
    DirectoryIterator it(path);
    DirectoryIterator end;
    if(it==end)
        return -1;
    UMXALGO_IRIS_GET_ENROL_TEMPLATE_OUTPUT irisLeftOutput;
    UMXALGO_IRIS_GET_ENROL_TEMPLATE_OUTPUT irisRightOutput;
    while (it!=end) {
        if(it->isFile()){
            std::cout<< it.name()<<std::endl;
            //
            string fullname=path+"/"+it.name();
            this->splitEyes(fullname);
            //
            //
            clearEnrollIrisTemplate(&irisLeftOutput);
            string lefteyefile = homePath+"lefteye_"+it.name();
            //string lefteyefile="/home/root/79_lefteye.bmp";

            this->getEnrollTemplate(handle,lefteyefile,irisLeftOutput);
            if(bestLeftTemplate.usableIrisArea<irisLeftOutput.usableIrisArea)
            {
                bestLeftTemplate = irisLeftOutput;
                memcpy(bestLeftTemplate.temPlate,irisLeftOutput.temPlate,irisLeftOutput.size);
                bestLeftEyeImage = lefteyefile;
            }
            //

            clearEnrollIrisTemplate(&irisRightOutput);
            string righteyefile = homePath+"righteye_"+it.name();
            //string righteyefile="/home/root/79_righteye.bmp";
            this->getEnrollTemplate(handle,righteyefile,irisRightOutput);
            if(bestRightTemplate.usableIrisArea<irisRightOutput.usableIrisArea)
            {
                bestRightTemplate = irisRightOutput;
                memcpy(bestRightTemplate.temPlate,irisRightOutput.temPlate,irisRightOutput.size);
                bestRightEyeImage = righteyefile;
            }
        }
        ++it;
    }
    cout<<"best leftimage: "<<bestLeftEyeImage<< "  high score: "<<bestLeftTemplate.usableIrisArea<<endl;
    cout<<"best rightimage: "<<bestRightEyeImage<< "  high score: "<<bestRightTemplate.usableIrisArea<<endl;
    //save eye images

    QString leftname =QString::fromStdString(Path(bestLeftEyeImage).getFileName());
    QString rightname=QString::fromStdString(Path(bestRightEyeImage).getFileName());
    QString logtext=QString("id=%0,best %1, score=%2,best %3,score=%4")
            .arg(QString::fromStdString(person.Id),leftname,
                 QString::number(bestLeftTemplate.usableIrisArea),rightname,
                 QString::number(bestRightTemplate.usableIrisArea));
    if(bestLeftTemplate.usableIrisArea<70 || bestRightTemplate.usableIrisArea<70)
        m_logger.warning(logtext.toStdString());
    else
        m_logger.information(logtext.toStdString());

    string smallleft="/usr/local/share/CMITECH/Images/"+person.Id+"_lefteye.jpg";
    string smallright="/usr/local/share/CMITECH/Images/"+person.Id+"_righteye.jpg";
    saveSmallImage(bestLeftEyeImage,smallleft,&bestLeftTemplate);
    saveSmallImage(bestRightEyeImage,smallright,&bestRightTemplate);
    //
    leftscore = bestLeftTemplate.usableIrisArea;
    rightscore = bestRightTemplate.usableIrisArea;
    //
    SubjectData subjectData;
    subjectData._recordVersion = 8976;
    subjectData._userUUID = person.Id;
    subjectData._lastName = person.Name;
    subjectData._wiegandCode = person.WiegandCode;
    subjectData._leftTemplate=Poco::Data::BLOB((char *)bestLeftTemplate.temPlate,UMXALGO_IRIS_MAX_TEMPLATE_SIZE);
    subjectData._rightTemplate=Poco::Data::BLOB((char *)bestRightTemplate.temPlate,UMXALGO_IRIS_MAX_TEMPLATE_SIZE);
    subjectData._leftImagePath=smallleft;
    subjectData._rightImagePath=smallright;
    UserInfoData retUserinfo;

    umxDB_selectUserInfoByUUID(dzrun.umxdb_Handle,person.Id,&retUserinfo);
    if(retUserinfo._userUUID=="")
    {
        std::cout << "insert "<<person.Id<<" name="<<subjectData._lastName<<std::endl;
        subjectData._recordVersion = 8976;
        subjectData._firstName = "";
        subjectData._accessAllowed = true;
        subjectData._matchUntil ="";
        subjectData._wiegandFacility = -1;
        subjectData._wiegandSite = -1;
        subjectData._wiegandCode = person.WiegandCode;
        subjectData._wiegandCustom = "";
        umxDB_insertSubject(dzrun.umxdb_Handle,subjectData);
        umxDB_insertUserInfo(dzrun.umxdb_Handle,person.Id,person.Card,"",0,0,0,0,0,0,0,0,0,"");
    }else
    {
        std::cout << "update "<<person.Id <<" name="<<person.Name<<endl;

        int ret=    umxDB_updateSubject(dzrun.umxdb_Handle,subjectData);
        if (ret<0)
        {
            umxDB_deleteUserByUUID(dzrun.umxdb_Handle,person.Id);
            umxDB_deleteUserInfoByUUID(dzrun.umxdb_Handle,person.Id);
            std::cout << "insert "<<person.Id<<" name="<<subjectData._lastName<<std::endl;
            subjectData._recordVersion = 8976;
            subjectData._firstName = "";
            subjectData._accessAllowed = true;
            subjectData._matchUntil ="";
            subjectData._wiegandFacility = -1;
            subjectData._wiegandSite = -1;
            subjectData._wiegandCode = person.WiegandCode;
            subjectData._wiegandCustom = "";
            umxDB_insertSubject(dzrun.umxdb_Handle,subjectData);
            umxDB_insertUserInfo(dzrun.umxdb_Handle,person.Id,person.Card,"",0,0,0,0,0,0,0,0,0,"");
        }
    }
    return 0;
}

int AlgoUtils::getTemplates(Person &person)
{
    this->getTemplates(this->algoHandle,person);
}

int AlgoUtils::getEnrollTemplate(UMXALGO_HANDLE handle, std::string &imagepath, UMXALGO_IRIS_GET_ENROL_TEMPLATE_OUTPUT &output)
{

    QImage image;
    image.load(QString::fromStdString(imagepath));
    this->getEnrollTemplate(&image,output);
}

int AlgoUtils::getEnrollTemplate(QImage *image, UMXALGO_IRIS_GET_ENROL_TEMPLATE_OUTPUT &output)
{
    int tempSize = umxAlgo_iris_template_size(algoHandle, UMXALGO_IRIS_TYPE_ENROL_TEMPLATE);
    UMXALGO_IRIS_GET_TEMPLATE_INPUT irisGetTemplateInput;
    irisGetTemplateInput.cbSize = sizeof(UMXALGO_IRIS_GET_TEMPLATE_INPUT);

    irisGetTemplateInput.image = image->bits();
    irisGetTemplateInput.width = image->width();
    irisGetTemplateInput.height = image->height();
    irisGetTemplateInput.centerX = 0;
    irisGetTemplateInput.centerY = 0;
    irisGetTemplateInput.radius = 0;
    irisGetTemplateInput.templateSize = tempSize;
    irisGetTemplateInput.showSegmentation = UMXALGO_IRIS_MIR_DO_NOT_SHOW_SEGMENTATION;

    int retGetEnroll= umxAlgo_iris_getEnrollTemplate(algoHandle, &irisGetTemplateInput, &output);

    if(retGetEnroll != UMXALGO_SUCCESS)
    {
        std::cout << "Fail to get enroll template: ret " << retGetEnroll << std::endl;
        return -1;
    }
    if(output.usableIrisArea < 50.0)
    {
        std::cout << "Enroll iris small usable area: " << output.usableIrisArea << "/50.0" << std::endl;
        return -1;
    }
    return UMXALGO_SUCCESS;
}

int AlgoUtils::getTemplateString(const string &base64Input, string &base64Output, int &irisarea)
{
    //初始化
    QImage img;
    QString strContent=QString::fromStdString(base64Input);
    QByteArray qa64 = strContent.toLatin1();
    QByteArray qa = QByteArray::fromBase64(qa64);
    img.loadFromData(qa);
    img.save("/home/root/test.bmp");
    //int retGetEnroll = algo->getEnrollTemplate(&img2, irisGetEnrolTemplateOutput);

    UMXALGO_IRIS_GET_ENROL_TEMPLATE_OUTPUT irisTemplateOutput;
    clearEnrollIrisTemplate(&irisTemplateOutput);
    int ret =getEnrollTemplate(&img,irisTemplateOutput);
    if(ret != UMXALGO_SUCCESS)
    {
        std::cout << "Fail to get enroll template: ret " << ret << std::endl;
        return -1;
    }

    QByteArray qbaout((char*)irisTemplateOutput.temPlate,UMXALGO_IRIS_MAX_TEMPLATE_SIZE);
    QString qstringout = QString(qbaout.toBase64());
    base64Output= qstringout.toStdString();
    irisarea = irisTemplateOutput.usableIrisArea;
    return UMXALGO_SUCCESS;
}



void AlgoUtils::splitEyes(std::string &filename)
{
    string homepath=Path::home();
    QImage dauleye;
    dauleye.load((char*) filename.c_str());
    QImage righteye;
    if(dauleye.width()==1920 && dauleye.height()==1080)
        righteye = dauleye.copy(0,220,960,720).scaled(640,480);
    else if(dauleye.width()==2560 && dauleye.height()==720)
        righteye = dauleye.copy(160,0,960,720).scaled(640,480);
    else
        righteye = dauleye.scaled(640,480);
    righteye.save(QString::fromStdString(homepath+"righteye_"+Path(filename).getFileName()));
    QImage lefteye;
    if(dauleye.width()==1920 && dauleye.height()==1080)
        lefteye = dauleye.copy(960,220,960,720).scaled(640,480);
    else if(dauleye.width()==2560 && dauleye.height()==720)
        lefteye = dauleye.copy(1440,0,960,720).scaled(640,480);
    else
        lefteye = dauleye.scaled(640,480);

    //QImage lefteye = dauleye.copy(920+100,220,768,576).scaled(640,480);
    lefteye.save(QString::fromStdString(homepath+"lefteye_"+Path(filename).getFileName()));
}

void AlgoUtils::clearEnrollIrisTemplate(UMXALGO_IRIS_GET_ENROL_TEMPLATE_OUTPUT* enrollIrisTemplate)
{
    enrollIrisTemplate->cbSize = sizeof(UMXALGO_IRIS_GET_ENROL_TEMPLATE_OUTPUT);
    memset(enrollIrisTemplate->temPlate, 0x00, UMXALGO_IRIS_MIR_ENROL_TEMPLATE_SIZE);
    enrollIrisTemplate->size = 0;
    enrollIrisTemplate->usableIrisArea = 0.0;
    enrollIrisTemplate->qualityOk = false;
    enrollIrisTemplate->qualityScore = 0.0;
}

void AlgoUtils::saveSmallImage(string imagePath, string destPath, UMXALGO_IRIS_GET_ENROL_TEMPLATE_OUTPUT *output, bool center)
{

    QImage image(QString::fromStdString(imagePath));
    QImage img;
    if(center)
        img=image.copy(output->irisCenterX-160,output->irisCenterY-120,320,240).scaled(160,120);
    else
        img=image.scaled(320,240);
    img.save(QString::fromStdString(destPath));
}

void AlgoUtils::algotest()
{

    AlgoUtils *algo = new AlgoUtils(dzrun.umxalgo_Handle);

    UMXALGO_IRIS_GET_ENROL_TEMPLATE_OUTPUT irisGetEnrolTemplateOutput;
    clearEnrollIrisTemplate(&irisGetEnrolTemplateOutput);

    string righteyefile="/home/root/79_righteye.bmp";
    //int retGetEnroll=algo->getEnrollTemplate(dzrun.umxalgo_Handle,righteyefile,irisGetEnrolTemplateOutput);

        QImage img;
        img.load(QString::fromStdString(righteyefile));
        //Image转为QByteArray
        QByteArray ba;
        QBuffer buffer(&ba);
        buffer.open(QIODevice::WriteOnly);
        img.save(&buffer,"BMP");

        QString qstring(ba.toBase64());
        string stringBase64=qstring.toStdString();
        //base64 string转为Image
        QImage img2;
        QString strContent=QString::fromStdString(stringBase64);
        QByteArray qa64 = strContent.toLatin1();
        QByteArray qa = QByteArray::fromBase64(qa64);
        img2.loadFromData(qa);
        int retGetEnroll = algo->getEnrollTemplate(&img2, irisGetEnrolTemplateOutput);
        //测试
        string base64out;
        int score;
        retGetEnroll=algo->getTemplateString(stringBase64,base64out,score);
        std::cout<<base64out<<std::endl;
        //
        if(retGetEnroll != UMXALGO_SUCCESS)
        {
            std::cout << "Fail to get enroll template: ret " << retGetEnroll << std::endl;
            return;
        }
        if(irisGetEnrolTemplateOutput.usableIrisArea < 70.0)
        {
            std::cout << "Enroll iris small usable area: " << irisGetEnrolTemplateOutput.usableIrisArea << "/70.0" << std::endl;
            return;
        }
        SubjectData subjectData;
        //subjectData._userUUID = _enrolIris.uuid;
        subjectData._recordVersion = 8976;
        subjectData._firstName = "";
        //subjectData._lastName = "uk";
        subjectData._accessAllowed = true;
        subjectData._matchUntil ="";
        subjectData._wiegandFacility = -1;
        subjectData._wiegandSite = -1;
        subjectData._wiegandCode = -1;
        subjectData._wiegandCustom = "";
        subjectData._leftTemplate=Poco::Data::BLOB((char *)irisGetEnrolTemplateOutput.temPlate,UMXALGO_IRIS_MAX_TEMPLATE_SIZE);
        subjectData._rightTemplate=Poco::Data::BLOB((char *)irisGetEnrolTemplateOutput.temPlate,UMXALGO_IRIS_MAX_TEMPLATE_SIZE);
        subjectData._userUUID="3";
        subjectData._lastName="lhjalgo";
        umxDB_insertSubject(dzrun.umxdb_Handle,subjectData);
        umxDB_insertUserInfo(dzrun.umxdb_Handle,"3","","",0,0,0,0,0,0,0,0,0,"");

    //-------------



}

void AlgoUtils::algotest2(QString filepath, string uuid, string name)
{
    int tempSize = umxAlgo_iris_template_size(dzrun.umxalgo_Handle, UMXALGO_IRIS_TYPE_ENROL_TEMPLATE);

    UMXALGO_IRIS_GET_TEMPLATE_INPUT irisGetTemplateInput;
    irisGetTemplateInput.cbSize = sizeof(UMXALGO_IRIS_GET_TEMPLATE_INPUT);

//        QImage lefto;
//        lefto.load("/usr/local/share/CMITECH/Images/matched_rightIris_0.bmp");
//        QImage left=lefto.mirrored(false,true);

    QImage left;
    left.load(filepath);
    irisGetTemplateInput.image = left.bits();
    irisGetTemplateInput.width = left.width();
    irisGetTemplateInput.height = left.height();
    irisGetTemplateInput.centerX = 0;
    irisGetTemplateInput.centerY = 0;
    irisGetTemplateInput.radius = 0;
    irisGetTemplateInput.templateSize = tempSize;
    irisGetTemplateInput.showSegmentation = UMXALGO_IRIS_MIR_DO_NOT_SHOW_SEGMENTATION;

    UMXALGO_IRIS_GET_ENROL_TEMPLATE_OUTPUT irisGetEnrolTemplateOutput;
    clearEnrollIrisTemplate(&irisGetEnrolTemplateOutput);

    int retGetEnroll = umxAlgo_iris_getEnrollTemplate(dzrun.umxalgo_Handle, &irisGetTemplateInput, &irisGetEnrolTemplateOutput);
    if(retGetEnroll != UMXALGO_SUCCESS)
    {
        std::cout << "Fail to get enroll template: ret " << retGetEnroll << std::endl;
        return;
    }
    if(irisGetEnrolTemplateOutput.usableIrisArea < 70.0)
    {
        std::cout << "Enroll iris small usable area: " << irisGetEnrolTemplateOutput.usableIrisArea << "/70.0" << std::endl;
        return;
    }
    SubjectData subjectData;
    //subjectData._userUUID = _enrolIris.uuid;
    subjectData._recordVersion = 8976;
    subjectData._firstName = "";
    //subjectData._lastName = "uk";
    subjectData._accessAllowed = true;
    subjectData._matchUntil ="";
    subjectData._wiegandFacility = -1;
    subjectData._wiegandSite = -1;
    subjectData._wiegandCode = -1;
    subjectData._wiegandCustom = "";
    subjectData._leftTemplate=Poco::Data::BLOB((char *)irisGetEnrolTemplateOutput.temPlate,UMXALGO_IRIS_MAX_TEMPLATE_SIZE);
    subjectData._rightTemplate=Poco::Data::BLOB((char *)irisGetEnrolTemplateOutput.temPlate,UMXALGO_IRIS_MAX_TEMPLATE_SIZE);
    subjectData._userUUID=uuid;
    subjectData._lastName=name;
    umxDB_insertSubject(dzrun.umxdb_Handle,subjectData);
    umxDB_insertUserInfo(dzrun.umxdb_Handle,uuid,"","",0,0,0,0,0,0,0,0,0,"");


}

void AlgoUtils::savetofile(string personid, int n, string content)
{
    QImage img;
    QString strContent=QString::fromStdString(content);
    QByteArray qa64 = strContent.toLatin1();
    QByteArray qa = QByteArray::fromBase64(qa64);
    img.loadFromData(qa);
    Path p=Path::home()+personid;
    File f(Path::home()+personid);
    f.createDirectory();
    //QString filename=QString::fromStdString(p.toString())+"/"+QString::number(n)+".png";
    //std::cout << filename.toStdString() <<std::endl;
    img.save(QString::fromStdString(p.toString())+"/"+QString::number(n)+".png");


}



