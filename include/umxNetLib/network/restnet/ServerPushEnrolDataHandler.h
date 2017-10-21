#ifndef SERVERPUSHENROLDATAHANDLER_H
#define SERVERPUSHENROLDATAHANDLER_H
#include <umxNetLib/umxNetGlobal.h>

class RestNet;
class ServerPushEnrolDataHandler
{
public:
    ServerPushEnrolDataHandler(RestNet* parent);

    void initialize();
    void setPropertiesServerInfo(int usePush, std::string addr, int port, std::string serverAuthUri);
    int send(UMXNetwork::ServerAuthData* data);
    bool getOnlineFlag(){return _online;}
    int getUseServer(){return _serverUse;}
    int send(UMXNetwork::ServerEnrolData* data);

private:
    static Poco::Mutex _mutex;
    bool _online;
    std::string _serverAddr;
    int _serverUse;
    int _serverPort;
    std::string _serverUri;
    RestNet* _restNet;
    std::string _serverIpBak = "0.0.0.0";

    int createHttpRequest(std::string sendUri, std::string sendReq, std::string* retResponse, std::string sendJson);
    bool checkIpv4(std::string val);
    std::string replaceString(std::string subject, const std::string &search, const std::string &replace);
};

#endif // SERVERPUSHENROLDATAHANDLER_H
