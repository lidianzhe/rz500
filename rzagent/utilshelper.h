#ifndef UTILSHELPER_H
#define UTILSHELPER_H

//#include "Poco/JSON/Parser.h"
//#include "Poco/JSON/ParseHandler.h"
//#include "Poco/JSON/Object.h"
//#include "Poco/JSON/JSONException.h"
#include "Poco/Environment.h"
#include "Poco/Path.h"
#include "Poco/File.h"
#include "Poco/FileStream.h"
#include "Poco/StreamCopier.h"
#include "Poco/Stopwatch.h"
#include <iostream>
#include <iomanip>
#include "algoutils.h"
class utilsHelper
{
public:
    utilsHelper();
    std::string BuildJSON();
    //static AlgoUtils* m_agloUtils;
    std::string toBase64 (const std::string &source);
    std::string fromBase64 (const std::string &source);
    QByteArray QString2Hex(QString str);
private:
    char ConvertHexChar(char ch);
};

#endif // UTILSHELPER_H
