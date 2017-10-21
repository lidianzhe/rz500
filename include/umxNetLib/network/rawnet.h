#ifndef RAWNET_H
#define RAWNET_H
#include <Poco/Logger.h>
#include <Poco/Mutex.h>
#include <Poco/Condition.h>
#include <Poco/Runnable.h>

class RestNet;
class RawNet : public Poco::Runnable
{
public:
    RawNet(RestNet*);
    ~RawNet();

    void run();
    void abort();

private:
    RestNet* _restNet;
    bool _abort;
};

#endif // RAWNET_H
