#ifndef ALGOUTILS_H
#define ALGOUTILS_H
#include "Poco/DirectoryIterator.h"
#include <iostream>
#include <vector>

#include "umxAlgoLib/umxAlgoGlobal.h"
using namespace std;
class AlgoUtils
{
public:
    AlgoUtils();
    int getTemplates(UMXALGO_HANDLE handle,std::string& id);
    int getEnrollTemplate(UMXALGO_HANDLE handle,std::string& imagepath,UMXALGO_IRIS_GET_ENROL_TEMPLATE_OUTPUT* output);
    void splitEyes(std::string &filename);
    void clearEnrollIrisTemplate(UMXALGO_IRIS_GET_ENROL_TEMPLATE_OUTPUT* enrollIrisTemplate);
    void saveSmallImage(string imagePath,string destPath,double score);
private:

};

#endif // ALGOUTILS_H
