#ifndef DISTESTIMATOR_H
#define DISTESTIMATOR_H

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

class DistEstimator
{
public:
    enum ImageAlgoReturn {
        OK = 0,
        INVALID_IMAGE = 1,
        INVALID_STATE = 2,
        ARRAY_TOO_SMALL = 3
    };

    // distMM*distMM*narrow._yObjAvgInMaxExposure = 35000000
    enum DistParameter {
        MAX_DIST_CONVSERION_FACTOR = 171428571, // 50000000*1200/350,
        MIN_DIST_CONVERSION_FACTOR = 68571428 // 20000000*1200/350
    };

    DistEstimator(Poco::Logger& logger, STEREO& stereo, MainProc *mainProc);

    bool getRegionDistance(UMXImage &wideBoth8, UMXImage &wideOff,
                           UMXImage &narrowBoth8, UMXImage &narrowOff,
                           int initXC, float *distMM);

    bool getEyeDistance(UMXImage &wideBoth8, UMXImage &narrowBoth8,
                        int wideOffsetX, int wideOffsetY, int *shifti, int *shiftj, float *distMM);

    bool findEyeDistance(UMXImage &wideImage, UMXImage &narrowImage,
                          int wideX1Sub2, int wideY1Sub2,
                          int wideWidthSub2, int wideHeightSub2, float *distMM);

    bool getEyeShift(UMXImage &wideBoth8, UMXImage &narrowBoth8,
                     int wideOffsetX, int wideOffsetY, int *shifti, int *shiftj);

private:
    bool compareAndFindDistance(UMXImage &wideImage, UMXImage &narrowImage,
                                              int initXC, float *distMM);

    float findDiff2(unsigned char *nImage, int nWidth, unsigned char *nInfoImage,
                     unsigned char *wImage, int wWidth, unsigned char *wInfoImage,
                     int nX1, int nY1, int wX1, int wY1, int dW, int dH, int thres,
                     float *newNarrowMulti = NULL);

    float findEyeDiff2(unsigned char *nImage, int nWidth, unsigned char *nInfoImage,
                       unsigned char *wImage, int wWidth, unsigned char *wInfoImage,
                       int nX1, int nY1, int wX1, int wY1, int dW, int dH, int thres);

    void findEyeStdDev(unsigned char *nImage, int nWidth,
                     unsigned char *wImage, int wWidth, int nX1, int nY1,
                     int wScanX1, int wScanY1, int wScanX2, int wScanY2);

    void findEyeMinArea(unsigned char *nImage, int nWidth,
                                 unsigned char *wImage, int wWidth, int nX1, int nY1,
                                 int wScanX1, int wScanY1, int wScanX2, int wScanY2,
                                 int *shifti, int *shiftj);
public:
    int _yShift;

private:
    Poco::Logger& _logger;
    STEREO& _stereo;
    MainProc *_mainProc;

    float _narrowMulti;
    int _curXCFull;
    float _maxDiff2;
    int _findDiffCnt;
    float _wideVar, _wideStdDev, _narrowVar, _narrowStdDev;
    int _nAccum[UMXImage::EYE_BLOCK_SMALL*UMXImage::EYE_BLOCK_SMALL];
    int _wAccum[UMXImage::EYE_BLOCK_SMALL*UMXImage::EYE_BLOCK_SMALL];

    static Poco::Mutex _mutex;
};

#endif // DISTESTIMATOR_H
