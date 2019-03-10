#ifndef ALGOUTILS_H
#define ALGOUTILS_H
#include "Poco/Logger.h"
#include "Poco/DirectoryIterator.h"
#include <iostream>
#include <vector>
#include "entities.h"
#include "umxAlgoLib/umxAlgoGlobal.h"
#include <QString>
#include <QImage>
using namespace std;
using Poco::Logger;
class AlgoUtils
{
public:
    AlgoUtils();
    AlgoUtils(UMXALGO_HANDLE handle);
    int getTemplates(UMXALGO_HANDLE handle,Person &person);
    int getTemplates(Person &person);
    int getEnrollTemplate(UMXALGO_HANDLE handle,std::string& imagepath,UMXALGO_IRIS_GET_ENROL_TEMPLATE_OUTPUT& output);
    int getEnrollTemplate(QImage* image ,UMXALGO_IRIS_GET_ENROL_TEMPLATE_OUTPUT& output);
    //从图像生成模板，传入传出为base64编码字符串，便于在webapi中传递
    int getTemplateString(const string& base64Input , string& base64Output,int& irisarea);
    void splitEyes(std::string &filename);
    void clearEnrollIrisTemplate(UMXALGO_IRIS_GET_ENROL_TEMPLATE_OUTPUT* enrollIrisTemplate);
    void saveSmallImage(string imagePath,string destPath,UMXALGO_IRIS_GET_ENROL_TEMPLATE_OUTPUT* output,bool center=true);

    void setHandle(UMXALGO_HANDLE handle){this->algoHandle=handle;}
    double leftscore;
    double rightscore;
    void algotest();
    void algotest2(QString filepath, string uuid, string name);

    void savetofile(string personid,int n,string content);

private:
    UMXALGO_HANDLE algoHandle;
    Poco::Logger& m_logger;

};

#endif // ALGOUTILS_H
