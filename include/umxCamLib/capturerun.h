#ifndef CAPTURERUN_H
#define CAPTURERUN_H

#include <cstdint>
#include <queue>
#include <deque>
#include <iostream>
#include "umximage.h"
#include "stereo.h"

#include <Poco/Logger.h>
#include <Poco/Mutex.h>
#include <Poco/Condition.h>
#include <Poco/Runnable.h>
#include "Poco/FileChannel.h"
#include "Poco/AutoPtr.h"

class MainProc;

class CaptureRun : public Poco::Runnable
{
public:
    CaptureRun(Poco::Logger& logger, MainProc *mainProc, int openMode);

    void run();

    void abort();

public:
    int _curID, _wideID;

private:
    Poco::Logger& _logger;
    MainProc *_mainProc;
    bool _abort;
    int _openMode;

    static Poco::Mutex _mutex;
#if defined(UMX_LIB_CAPTURE_MEMORY_LEAK_RESOLVE)
    static Poco::Mutex _abortMutex;
#endif
};

#endif // CAPTURERUN_H
