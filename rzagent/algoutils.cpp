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
using namespace std;
AlgoUtils::AlgoUtils(): m_logger(Logger::get("algo"))
{

}

AlgoUtils::AlgoUtils(UMXALGO_HANDLE handle):
    m_logger(Logger::get("algo"))
{
    algoHandle = handle;

    AutoPtr<FileChannel> pChannel(new FileChannel);
    pChannel->setProperty("path", "algoutils.log");
    pChannel->setProperty("rotation", "2 K");
    pChannel->setProperty("archive", "timestamp");
//    m_logger.setChannel(pChannel);

    AutoPtr<PatternFormatter> pPF(new PatternFormatter);
    pPF->setProperty("pattern", "%m-%d %H:%M:%S %s: [%p] %t"); // local time
    AutoPtr<FormattingChannel> pFC(new FormattingChannel(pPF, pChannel));
    m_logger.setChannel(pFC);

}

int AlgoUtils::getTemplates(UMXALGO_HANDLE handle, std::string &id)
{
    string homePath = Path::home();
    std::string path(homePath+id);
    /*test
    Path p(path+"/ee.png");
    Path p1(p.parent().toString());
    p1.pushDirectory("newdir");
    cout<<p1.toString()<<endl;
    File f(p1);
    cout<<f.path()<<endl;
    f.createDirectory();
    cout<<f.path()<<endl;
    cout<<p.toString()<<endl;
    cout<<p.current()<<endl;
    cout<<p.getFileName()<<endl;
    cout<<p.parent().toString()<<endl;
    //cout<<p.popDirectory().toString()<<endl;
    cout<<p.resolve(p).toString()<<endl;
    cout<<p.makeParent().toString()<<endl;
    cout<<p.toString()<<endl;
    */
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
    while (it!=end) {
        if(it->isFile()){
            std::cout<< it.name()<<std::endl;
            //
            string fullname=path+"/"+it.name();
            this->splitEyes(fullname);
            UMXALGO_IRIS_GET_ENROL_TEMPLATE_OUTPUT irisGetEnrolTemplateOutput;
            clearEnrollIrisTemplate(&irisGetEnrolTemplateOutput);
            string lefteyefile = homePath+"lefteye_"+it.name();
            this->getEnrollTemplate(handle,lefteyefile,&irisGetEnrolTemplateOutput);
            if(bestLeftTemplate.usableIrisArea<irisGetEnrolTemplateOutput.usableIrisArea)
            {
                bestLeftTemplate = irisGetEnrolTemplateOutput;
                bestLeftEyeImage = lefteyefile;
            }
            //
            clearEnrollIrisTemplate(&irisGetEnrolTemplateOutput);
            string righteyefile = homePath+"righteye_"+it.name();
            this->getEnrollTemplate(handle,righteyefile,&irisGetEnrolTemplateOutput);
            if(bestRightTemplate.usableIrisArea<irisGetEnrolTemplateOutput.usableIrisArea)
            {
                bestRightTemplate = irisGetEnrolTemplateOutput;
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
            .arg(QString::fromStdString(id),leftname,
                 QString::number(bestLeftTemplate.usableIrisArea),rightname,
                 QString::number(bestRightTemplate.usableIrisArea));
    if(bestLeftTemplate.usableIrisArea<70 || bestRightTemplate.usableIrisArea<70)
        m_logger.warning(logtext.toStdString());
    else
        m_logger.information(logtext.toStdString());

    //string smallpath="/usr/local/share/CMITECH/Images/";
    saveSmallImage(bestLeftEyeImage,"/usr/local/share/CMITECH/Images/"+id+"_lefteye.jpg",bestLeftTemplate.usableIrisArea);
    saveSmallImage(bestRightEyeImage,"/usr/local/share/CMITECH/Images/"+id+"_righteye.jpg",bestRightTemplate.usableIrisArea);
    //
    leftscore = bestLeftTemplate.usableIrisArea;
    rightscore = bestRightTemplate.usableIrisArea;
    return 0;
}

int AlgoUtils::getTemplates(std::string &id)
{
    this->getTemplates(this->algoHandle,id);
}

int AlgoUtils::getEnrollTemplate(UMXALGO_HANDLE handle, std::string &imagepath, UMXALGO_IRIS_GET_ENROL_TEMPLATE_OUTPUT *output)
{

    int tempSize = umxAlgo_iris_template_size(handle, UMXALGO_IRIS_TYPE_ENROL_TEMPLATE);

    UMXALGO_IRIS_GET_TEMPLATE_INPUT irisGetTemplateInput;
    irisGetTemplateInput.cbSize = sizeof(UMXALGO_IRIS_GET_TEMPLATE_INPUT);

    QImage left;
    left.load(QString::fromStdString(imagepath));
    irisGetTemplateInput.image = left.bits();
    irisGetTemplateInput.width = left.width();
    irisGetTemplateInput.height = left.height();
    irisGetTemplateInput.centerX = 0;
    irisGetTemplateInput.centerY = 0;
    irisGetTemplateInput.radius = 0;
    irisGetTemplateInput.templateSize = tempSize;
    irisGetTemplateInput.showSegmentation = UMXALGO_IRIS_MIR_DO_NOT_SHOW_SEGMENTATION;

    int retGetEnroll= umxAlgo_iris_getEnrollTemplate(handle, &irisGetTemplateInput, output);

    if(retGetEnroll != UMXALGO_SUCCESS)
    {
        std::cout << "Fail to get enroll template: ret " << retGetEnroll << std::endl;
        return -1;
    }
    if(output->usableIrisArea < 70.0)
    {
        std::cout << "Enroll iris small usable area: " << output->usableIrisArea << "/70.0" << std::endl;
        return -1;
    }
    return 0;
}

void AlgoUtils::splitEyes(std::string &filename)
{
    string homepath=Path::home();
    QImage dauleye;
    dauleye.load((char*) filename.c_str());
    QImage righteye = dauleye.copy(152,100,768,576).scaled(640,480);
    righteye.save(QString::fromStdString(homepath+"righteye_"+Path(filename).getFileName()));

    QImage lefteye = dauleye.copy(920+100,100,768,576).scaled(640,480);
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

void AlgoUtils::saveSmallImage(string imagePath, string destPath, double score)
{
    QImage image(QString::fromStdString(imagePath));
    QImage img=image.scaled(240,180);
    img.save(QString::fromStdString(destPath));
}



//-------------
//    int tempSize = umxAlgo_iris_template_size(_gUmxAlgoHandle, UMXALGO_IRIS_TYPE_ENROL_TEMPLATE);

//    UMXALGO_IRIS_GET_TEMPLATE_INPUT irisGetTemplateInput;
//    irisGetTemplateInput.cbSize = sizeof(UMXALGO_IRIS_GET_TEMPLATE_INPUT);

//    //QImage lefto;
//    //lefto.load("/usr/local/share/CMITECH/Images/matched_rightIris_0.bmp");
//    //QImage left=lefto.mirrored(false,true);
//    QImage left;
//    left.load("/usr/local/share/CMITECH/Images/left1.png");
//    irisGetTemplateInput.image = left.bits();
//    irisGetTemplateInput.width = left.width();
//    irisGetTemplateInput.height = left.height();
//    irisGetTemplateInput.centerX = 0;
//    irisGetTemplateInput.centerY = 0;
//    irisGetTemplateInput.radius = 0;
//    irisGetTemplateInput.templateSize = tempSize;
//    irisGetTemplateInput.showSegmentation = UMXALGO_IRIS_MIR_DO_NOT_SHOW_SEGMENTATION;

//    UMXALGO_IRIS_GET_ENROL_TEMPLATE_OUTPUT irisGetEnrolTemplateOutput;
//    clearEnrollIrisTemplate(&irisGetEnrolTemplateOutput);

//    int retGetEnroll = umxAlgo_iris_getEnrollTemplate(_gUmxAlgoHandle, &irisGetTemplateInput, &irisGetEnrolTemplateOutput);
//    if(retGetEnroll != UMXALGO_SUCCESS)
//    {
//        std::cout << "Fail to get enroll template: ret " << retGetEnroll << std::endl;
//        return;
//    }
//    if(irisGetEnrolTemplateOutput.usableIrisArea < 70.0)
//    {
//        std::cout << "Enroll iris small usable area: " << irisGetEnrolTemplateOutput.usableIrisArea << "/70.0" << std::endl;
//        return;
//    }
//    subjectData._rightTemplate=Poco::Data::BLOB((char *)irisGetEnrolTemplateOutput.temPlate,UMXALGO_IRIS_MAX_TEMPLATE_SIZE);
//    subjectData._userUUID="1";
//    subjectData._lastName="lhj";
//    umxDB_insertSubject(_gUmxDBHandle,subjectData);
//    umxDB_insertUserInfo(_gUmxDBHandle,"0","","",0,0,0,0,0,0);
//    umxDB_insertUserInfo(_gUmxDBHandle,"1","","",0,0,0,0,0,0);

//-------------


