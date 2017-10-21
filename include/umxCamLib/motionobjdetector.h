#ifndef MOTIONOBJDETECTOR_H
#define MOTIONOBJDETECTOR_H

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
#include <Poco/Condition.h>
#include <Poco/Runnable.h>
#include "Poco/FileChannel.h"
#include "Poco/AutoPtr.h"

#ifdef UMXCAM_MOTION_DETECTION_TEST
typedef struct _FLUC_INFO {
    int n;
    int expsum;
    int sum;
    int sum2;
    int min;
    int max;
} FLUC_INFO;
#endif

class MainProc;

class MotionObjDetector
{
public:
    enum {
        MOTION_AREA_THRESHOLD_PERC = 5, // 5% of total area
        RESOL = 1000,                   // 0.1%
        MOTION_THRESHOLD = 40,          // 4% => if pixel = 100, the threshold is 104
        SATURATION = 240
    };

    enum {
        MIN_MOTION_OBJECT_WIDTH = 4
    };

    enum GlobalMotion {
        MOTION_UNKNOWN = 0, // if the image is too bright and exposures are different
        MOTION_DETECTED = 1,
        MOTION_NOT_DETECTED = 2,
        MOTION_OBJECT_DETECTED = 3
    };

    enum MotionObjectPixelInfo {
        // pixel level
        PIXEL_UNKNOWN = 0,
        PIXEL_CHANGED_BY_MOTION = (1<<7),
        PIXEL_NOT_CHANGED_BY_MOTION = (1<<1),
        PIXEL_OBJECT_BY_LED = (1<<2),
        PIXEL_NO_OBJECT_BY_LED = (1<<3)
    };

    enum MotionObjectBlockInfo {
        // block level
        BLOCK_UNKNOWN = 0,
        BLOCK_BACKGROUND_BY_MOTION_TMP = (1<<1),
        BLOCK_BACKGROUND_BY_MOTION = (1<<2),
        BLOCK_POTENTIAL_OBJECT = (1<<3),
        BLOCK_OBLECT_BY_LED = (1<<4),
        BLOCK_NO_OBJECT_BY_LED = (1<<5),
        BLOCK_NO_OBJECT = (1<<0),
        BLOCK_OBJECT = (1<<7)
    };

    MotionObjDetector(Poco::Logger& logger, MainProc *mainProc, int openMode);

    void wideOffMotionDetectPixelBlock(UMXImage &off0, UMXImage &off1, UMXImage &off2);
    void wideOffMotionDetectPixelBlock(UMXImage &off0, UMXImage &off2);
    void wideBothMotionDetectPixelBlock(UMXImage &off, UMXImage &both, UMXImage *mdLast);
    //bool wideOffMotionDetectPixelBlock(UMXImage &widePrevImage, UMXImage &wideCurImage);
    //bool wideBoth8MotionDetectPixelBlock(UMXImage &widePrevImage, UMXImage &wideCurImage);
    //bool objectDetectByLedPixelBlock(UMXImage &wideImageOff, UMXImage &wideImageBoth8);

    int motionX1() {return _motionX1;}
    int motionY1() {return _motionY1;}
    int motionWidth() {return _motionWidth;}
    int motionHeight() {return _motionHeight;}
    int motionDetected() {return _motionDetected;}

public:
    UMXImage *_widePrevImage;
    UMXImage *_wideCurImage;
    UMXImage *_off0, *_off1, *_off2, *_both, *_mdLast;
    int _minH1, _minH2, _mintop1, _minTop2;
    int _minW1, _minW2, _minLeft1, _minLeft2;
    bool _isBlackImage, _isCorruptedImage; //, _isMotionValueChanged;
    int _minBlockY, _maxBlockY;
    int _minBlockX, _maxBlockX;
    int _mini;

    #ifdef UMXCAM_MOTION_DETECTION_TEST
    static FLUC_INFO s_flucInfo[256];
    static int s_flucCnt;
    #endif

private:
    Poco::Logger& _logger;
    MainProc *_mainProc;
    int _openMode;

    int _motionThreshold[256];
    int _objVeritcalCnt[80];
    int _uvThreshold;
    float _minMotionValue;
    int _motionDetected;
    int _motionX1, _motionY1, _motionWidth, _motionHeight; // left rotated full resolution coordinate

    static bool s_isDark;
    static Poco::Mutex _mutex;
    static int s_threshold;
    static int s_startY;
    //static unsigned char s_block[3600];
};

#endif // MOTIONOBJDETECTOR_H
