#include "algoutils.h"
#include <iostream>
#include <string>
#include <QImage>
#include <QByteArray>
#include <QPainter>

using Poco::DirectoryIterator;
using Poco::Path;
using Poco::File;
#include "umxAlgoLib/umxAlgo.h"
using namespace std;
AlgoUtils::AlgoUtils()
{

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

    DirectoryIterator it(path);
    DirectoryIterator end;
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
                bestRightEyeImage = lefteyefile;
            }
        }
        ++it;
    }
    cout<<"best leftimage: "<<bestLeftEyeImage<< "  high score: "<<bestLeftTemplate.usableIrisArea<<endl;
    cout<<"best rightimage: "<<bestRightEyeImage<< "  high score: "<<bestRightTemplate.usableIrisArea<<endl;
    //save eye images
    //string smallpath="/usr/local/share/CMITECH/Images/"
    saveSmallImage(bestLeftEyeImage,"/usr/local/share/CMITECH/Images/"+id+"_lefteye.jpg",bestLeftTemplate.usableIrisArea);

    return 0;
}

int AlgoUtils::getEnrollTemplate(UMXALGO_HANDLE handle, std::string &imagepath, UMXALGO_IRIS_GET_ENROL_TEMPLATE_OUTPUT *output)
{
    std::cout<<"dd"<<std::endl;
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

    //UMXALGO_IRIS_GET_ENROL_TEMPLATE_OUTPUT irisGetEnrolTemplateOutput;
    //clearEnrollIrisTemplate(&irisGetEnrolTemplateOutput);

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
//    QPainter painter(&img); //为这个QImage构造一个QPainter
//    //painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);
//    //设置画刷的组合模式CompositionMode_SourceOut这个模式为目标图像在上。
//    //改变组合模式和上面的填充方式可以画出透明的图片。

//    //改变画笔和字体
////    QPen pen = painter.pen();
////    pen.setColor(Qt::blue);
////    QFont font = painter.font();
////    font.setBold(true);//加粗
////    font.setPixelSize(20);//改变字体大小

////    painter.setPen(pen);
////    painter.setFont(font);

//    //painter.drawText(img.rect(),Qt::AlignCenter,"88");
//    painter.drawText(110,160,QString::number(score));
//    int n = 100;//这个为图片的压缩度。0/100
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


