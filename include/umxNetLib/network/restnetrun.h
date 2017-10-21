#ifndef RESTNETRUN_H
#define RESTNETRUN_H
#include <Poco/Logger.h>
#include <Poco/Mutex.h>
#include <Poco/Condition.h>
#include <Poco/Runnable.h>
#include "restnet/CommuteDataHandler.h"
#include "restnet/ServerAuthDataHandler.h"
#include "restnet/ServerPushEnrolDataHandler.h"

class RestNet;
class RestNetRun : public Poco::Runnable
{
public:
    RestNetRun(RestNet*);
    ~RestNetRun();

    void run();
    void abort();

private:
    RestNet* _restNet;
    bool _abort;
    bool _onTimer;
    int _bakHour;

    CommuteDataHandler* _commuteHandler;
    ServerAuthDataHandler* _spushHandler;
    ServerPushEnrolDataHandler* _spushEnrolHandler;

    void setProperties(Poco::AutoPtr<Poco::Util::PropertyFileConfiguration> config);
    bool checkUpdate();
};

#endif // RESTNETRUN_H
