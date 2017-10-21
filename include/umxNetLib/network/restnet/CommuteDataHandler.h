#ifndef COMMUTEDATAHANDLER_H
#define COMMUTEDATAHANDLER_H
#include <umxNetLib/umxNetGlobal.h>
#include "CommuteDataCollectionResponse.h"

class RestNet;
class CommuteDataHandler
{
public:
    CommuteDataHandler(RestNet* parent);

    void initialize();
    void setPropertiesServerInfo(int usePush, std::string addr, int port, std::string commuteUri, std::string syncUri, std::string acceptableUri);
    int send(int type, UMXNetwork::CommuteData* data, bool manageLogId);
    int sendSync(int type, CommuteDataCollectionResponse<UMXNetwork::CommuteData>* data);
    int sendData(int restSendCountForBackup);
    bool getOnlineFlag(){return _online;}
    bool getForceRetryFlag(){return _forceRetry;}
    int getUseServer(){return _serverUse;}

    enum {
        COMMUTE_URI_TYPE,
        SYNC_URI_TYPE,
        ACCEPTABLE_URI_TYPE,
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
    std::string _commuteUri;
    std::string _syncUri;
    std::string _acceptableUri;
    std::string _serverIpBak = "0.0.0.0";

    std::string getUri(int type);
    bool acceptableSendData();
    void getNotTransmissionLogId(std::vector<int>* retLogId);
   // std::string getCurrentTime();
    void setNotTransmissionLogId(int logId);
    void deleteNotTransmissionLogId(int logId);
    std::string getCurrentTime();
    UMXNetwork::CommuteData createCommuteData(UMXCommon::LogEntry* logEntry);
    int createHttpRequest(std::string sendUri, std::string sendReq, std::string* retResponse, std::string sendJson);
    bool checkIpv4(std::string val);
    std::string replaceString(std::string subject, const std::string &search, const std::string &replace);
};

#endif // COMMUTEDATAHANDLER_H
