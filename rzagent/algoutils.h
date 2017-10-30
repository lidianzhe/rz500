#ifndef ALGOUTILS_H
#define ALGOUTILS_H
#include "Poco/Logger.h"
#include "Poco/DirectoryIterator.h"
#include <iostream>
#include <vector>

#include "umxAlgoLib/umxAlgoGlobal.h"
using namespace std;
using Poco::Logger;
class AlgoUtils
{
public:
    AlgoUtils();
    AlgoUtils(UMXALGO_HANDLE handle);
    int getTemplates(UMXALGO_HANDLE handle,std::string& id);
    int getTemplates(std::string& id);
    int getEnrollTemplate(UMXALGO_HANDLE handle,std::string& imagepath,UMXALGO_IRIS_GET_ENROL_TEMPLATE_OUTPUT* output);
    void splitEyes(std::string &filename);
    void clearEnrollIrisTemplate(UMXALGO_IRIS_GET_ENROL_TEMPLATE_OUTPUT* enrollIrisTemplate);
    void saveSmallImage(string imagePath,string destPath,UMXALGO_IRIS_GET_ENROL_TEMPLATE_OUTPUT* output);

    void setHandle(UMXALGO_HANDLE handle){this->algoHandle=handle;}
    double leftscore;
    double rightscore;
private:
    UMXALGO_HANDLE algoHandle;
    Poco::Logger& m_logger;

};

#endif // ALGOUTILS_H
