#ifndef OBJDETECTOR_H
#define OBJDETECTOR_H

#if defined(WIN32)
  #include <windows.h>
#endif

#include <cstdint>
#include <queue>
#include <deque>
#include <iostream>
#include "umximage.h"
#include "stereo.h"

#include <Poco/Logger.h>
#include <Poco/Mutex.h>
#include "Poco/FileChannel.h"
#include "Poco/AutoPtr.h"

class MainProc;

class ObjDetector
{
public:
    ObjDetector(Poco::Logger& logger, STEREO& stereo, MainProc *mainProc);

    bool findObjInWide(int index);

private:
    Poco::Logger& _logger;
    STEREO& _stereo;
    MainProc *_mainProc;

    static Poco::Mutex _mutex;
};

#endif // OBJDETECTOR_H
