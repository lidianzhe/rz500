#ifndef SERVERAUTHATAHANDLER_H
#define SERVERAUTHATAHANDLER_H
#include <umxNetLib/umxNetGlobal.h>
//#include "ServerPushDataCollectionResponse.h"

//class ReturnData
//{
//public:
//    ReturnData(){}
//    ReturnData(const int retCode, const std::string retMsg) : _retCode(retCode), _retMsg(retMsg)
//    {

//    }

//    int _retCode;
//    std::string _retMsg;

//    template<class T>
//    static bool HasValue(cjsonpp::JSONObject& obj, const std::string& name);
//    static ReturnData Parse(const std::string jsonString);

//};

class RestNet;
class ServerAuthDataHandler
{
public:
    ServerAuthDataHandler(RestNet* parent);

    void initialize();
    void setPropertiesServerInfo(int usePush, std::string addr, int port, std::string serverAuthUri);
    int send(int type, UMXNetwork::ServerAuthData* data, bool manageLogId);
    int sendData(int restSendCountForBackup);
    bool getOnlineFlag(){return _online;}
    bool getForceRetryFlag(){return _forceRetry;}
    int getUseServer(){return _serverUse;}

    enum {
        SERVER_AUTH_URI_TYPE,
        MAX_URI_TYPE
    };

private:
    static Poco::Mutex _mutex;
    static Poco::Mutex _fileMutex;
    RestNet* _restNet;
    bool _online;
    bool _forceRetry;
    std::string _serverAddr;
    int _serverUse;
    int _serverPort;
    std::string _serverAuthUri;
    std::string _serverIpBak = "0.0.0.0";

    std::string replaceString(std::string subject, const std::string &search, const std::string &replace);
    std::string getUri(int type);
   // std::string getCurrentTime();
    std::string getCurrentTime();
    UMXNetwork::CommuteData createServerAuthData(UMXCommon::LogEntry* logEntry);
    int createHttpRequest(std::string sendUri, std::string sendReq, std::string* retResponse, std::string sendJson);
    bool checkIpv4(std::string val);
};

#endif // SERVERAUTHATAHANDLER_H
