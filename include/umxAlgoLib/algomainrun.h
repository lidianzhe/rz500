#ifndef ALGOMAINRUN_H
#define ALGOMAINRUN_H
#include <Poco/Logger.h>
#include <Poco/Mutex.h>
#include <Poco/Condition.h>
#include <Poco/Runnable.h>
#include <Poco/Thread.h>
#include "algosubrun.h"
#include "umxAlgoGlobal.h"

class AlgoMainRun : public Poco::Runnable
{
public:
    AlgoMainRun(Poco::Logger& logger, void*, long numOfProcess);
    ~AlgoMainRun();

    void run();
    void abort();
    void start(long numOfProcess);
    void stop();
    int pauseAllThreads(bool flag);
    int getIrisTemplate(UMXALGO_IRIS_GET_TEMPLATE* left, UMXALGO_IRIS_GET_TEMPLATE* right);
    int requestIrisMatch(int timer, UMXALGO_IRIS_IDENTIFY_INFO* info);

private:
    Poco::Logger& _logger;
    bool _start;
    void* _parent;
    bool _abort;
    long _numOfProcess;

    Poco::Thread _subThread[ALGO_SUB_THREADS_MAX];
    AlgoSubRun* _subRun[ALGO_SUB_THREADS_MAX];

    Poco::Mutex* _irisMutex;
    //Poco::Mutex _mutexRequestBuffer;
};

#endif // ALGOMAINRUN_H
