#ifndef MAINIMAGERUN_H
#define MAINIMAGERUN_H

#include <cstdint>
#include <queue>
#include <deque>
#include <iostream>
#include "umximage.h"
#include "stereo.h"
#include "distestimator.h"
#include "eyefinder.h"

#include <Poco/Logger.h>
#include <Poco/Mutex.h>
#include <Poco/Condition.h>
#include <Poco/Runnable.h>
#include "Poco/FileChannel.h"
#include "Poco/AutoPtr.h"
#include "umxCamGlobal.h"
//// EF-45(unklee88)-28 : added umxCamLib in umxLauncherWithLib.pro ////
#include "umxAlgoLib/umxAlgoGlobal.h"
/////////////////////////////////////////////////////////////////////
class MainProc;

class MainImageRun : public Poco::Runnable
{
public:
    enum Actions {
        ACTION_WAIT = 0,
        ACTION_NO_MOVE_CAPTURE = 1,
        ACTION_MOVE_CAPTURE = 2
    };

    enum Direction {
        LEFT = 0x01,
        BOTTOM = 0x02,
        RIGHT = 0x04,
        TOP = 0x08
    };

//    enum MaxMovement {
//        MAX_DELTA_DIST_MM = 10, // 40mm/sec
//        MAX_DELTA_X = 26, // 10mm/sec
//        MAX_DELTA_Y = 26  // 10mm/sec
//    };


    MainImageRun(Poco::Logger& logger, MainProc *mainProc, STEREO& stereo, int openMode);
    ~MainImageRun();

    void run();

    void abort();

    bool getIrisTemplate(UMXImage *narrow, int *usableIrisArea);

    void checkRestoreMotorPos();

    bool isGoodImageAfterAlgoRun(UMXImage *narrow, int enrolRecogMode);
    bool isGoodImageBeforeAlgoRun(UMXImage *narrow, int enrolRecogMode);

    void handleIrisDetectImages();

    void handleObjectDetectImages();

    void checkAndGotoIrisDetect();
    int yFromZmm(int zmm);
    int zmmFromY(int y);

    float getEyeDiff2(unsigned char *refImage, unsigned char *tgtImage,
                      int blackPixel, int maxPixel, float expRatio,
                      int width, int height,
                      int dw, int dh, int x1, int y1,
                      int offsetX0, int offsetY0);

    bool findEyeShift(UMXImage *ref, UMXImage *target, int cx, int cy,
                      int boxSize, int maxShift, int *shiftX, int *shiftY);

    bool findNarrowEyeInIrisDetect(UMXImage *narrow, int whichEye);
    //bool findWideEyeFromNarrow(int index, int offIndex, int refIndex, int whichEye);
    bool findEye(int index, int refIndex, int whichEye);

    void traceReyeInWide_0_from_2();
    void traceLeyeInWide_0_from_3();

    void processODImagesLED_LC8();
    bool processODImagesLED_RC8();
    void processODImagesLED_BOTH8();
    float getDiff2(unsigned char *aimage, unsigned char *bimage, int width,
                   int height, float expRatio);

    bool eventIrisSelected(UMXImage* narrowLC78, UMXImage* narrowRC78);

    void eventWidePreview();

    void eventNarrowPreview();

    // ChangDG  160721
    void eventNarrowPreviewForAging();

    void eventWideNormalFaceCapturePreview(int index);

    void eventWideNormalIrisCapturePreview(int index);

    void overlayImage(int *base, int *add, int count);

    void displayNarrowInWide(int index, int wideDisplayOffsetX1, int wideDisplayOffsetY1,
                             unsigned char *faceImageARGB32, int width, int height);

private:
    Poco::Logger& _logger;

public:
    MainProc *_mainProc;
    STEREO& _stereo;
    int _frameCount, _latestFrameCount, _frameDiff, _stateFrameCount;
    int _ledKind, _state, _exposure, _index, _index1;
    int _mdStartFrameCount;

    UMXImage *_narrowLC78, *_narrowRC78, *_narrowRC78Reye;
    UMXImage *_narrowID[6];
    int _curDistMMForDisplay;
    unsigned char *_faceDisplayBuffer; // 480*480*4
    int _animationCount;
    int _lc78ReceiveCnt, _rc78ReceiveCnt;
    int _wideopenMessageCnt;
    int _maxLedInterval;
    int _whichLed;

private:
    bool _abort;
    int _openMode;
    DistEstimator *_distEstimator;
};

#endif // MAINIMAGETHREAD_H
