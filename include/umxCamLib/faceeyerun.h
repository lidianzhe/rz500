#ifndef FACEEYERUN_H
#define FACEEYERUN_H

#include <cstdint>
#include <queue>
#include <deque>
#include <iostream>
#include <string>
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

class FaceEyeRun : public Poco::Runnable
{
public:
    enum Actions {
        ACTION_WAIT = 0,
        ACTION_NO_MOVE_CAPTURE = 1,
        ACTION_MOVE_CAPTURE = 2
    };

    enum OperaringRange {
        ENROL_MIN_DIST_MM = 350,
        ENROL_MAX_DIST_MM = 450,
        RECOG_MIN_DIST_MM = 300, // Fast Recog test
        RECOG_MAX_DIST_MM = 450,
        TOTAL_MAX_DIST_MM = RECOG_MAX_DIST_MM
    };

    enum {
        EYE_MARGIN = 30 // in wide ~ 192 pixels from the center to boundary in narrow
    };

    enum Direction {
        LEFT = 0x01,
        BOTTOM = 0x02,
        RIGHT = 0x04,
        TOP = 0x08
    };

    enum MaxMovement {
        RECOG_MAX_DELTA_DIST_MM = 20, // 20x6 = 120mm/sec
        RECOG_MAX_DELTA_X = 40, // 40x6 = 240 pixels => 15~12mm/sec
        RECOG_MAX_DELTA_Y = 40,  // 40x6 = 240 pixels => 15~12mm/sec

        // Fast Recog test
        FAST_RECOG_MAX_DELTA_DIST_MM = 40, // 40x6 = 240mm/sec
        FAST_RECOG_MAX_DELTA_X = 80, // 80x6 = 480 pixels => 30~24mm/sec
        FAST_RECOG_MAX_DELTA_Y = 80,  // 80x6 = 480 pixels => 30~24mm/sec

        ENROL_MAX_DELTA_DIST_MM = 8, // 48mm/sec
        ENROL_MAX_DELTA_X = 18, // 18x6 = 108 pixels => 7~5mm/sec
        ENROL_MAX_DELTA_Y = 18,  // 18x6 = 108 pixels => 7~5mm/sec
    };


    FaceEyeRun(Poco::Logger& logger, MainProc *mainProc, STEREO& stereo, int openMode);
    ~FaceEyeRun();

    void run();

    void abort();

    void processODImages();

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
    bool findNarrowEyeInOD(int index, int refIndex, int distMM, int whichEye);
    bool findLargeNarrowEyeInOD(int index, int refIndex, int bothIndex, int distMM, int whichEye);

    //bool findWideEyeFromNarrow(int index, int offIndex, int refIndex, int whichEye);
    //bool findEye(int index, int refIndex, int whichEye);

    //void traceReyeInWide_0_from_2();
    //void traceLeyeInWide_0_from_3();

    void processODImagesLED_LC8();
    bool processODImagesLED_RC8();
    void processODImagesLED_OFF_FaceDetect();

//    bool eventPreviewInfo(UMXImage *wideBOTH8);
//    bool eventPreviewInfo(UMXImage *wideLC8, UMXImage *wideRC8);

    bool eventWideSelected(UMXImage& wideOn, UMXImage& wideOff);

    void simplestColorBalanceARGB32(unsigned char *argb32, int width, int height);
    void correctFaceColorBMP24(unsigned char *bmp24, int width, int height,
                          int faceX1, int faceY1, int faceWidth, int faceHeight);
//    bool storeWideSelected(UMXImage& wideOff, float faceScore);

private:
    //bool isFakeFace(UMXImage &wideOn, UMXImage &wideOff, int offsetX1, int offsetY1, unsigned char* diffFace, int diffFaceWidth, int diffFaceHeight);
    //bool isFakeFace2(UMXImage &wideOn, UMXImage &wideOff);
    void findFakeFaceInfo(UMXImage &wideOn, UMXImage &wideOff);
public:
    MainProc *_mainProc;
    STEREO& _stereo;
    bool _faceFound;
    int _frameCount, _latestFrameCount, _frameDiff, _stateFrameCount;
    int _ledKind, _state, _exposure, _index, _index1;
    int _faceSelectedFrameCount;

    UMXImage *_wide[12], *_narrow[12];

    float _curDistMM;
    int _curIrisRadius;
    int _whichEyeWillBeUsed;
    int _whichReyeWillBeUsed;

    int _enrollFaceMaxCnt; // JJC 20161120
    int _prevEyePosXFull, _prevEyePosYFull;
    int _prevFrameCount;

    int _faceDetectedX1;
    int _faceDetectedY1;
    int _faceDetectedWidth;
    int _faceDetectedHeight;

    bool _isFindFaceInBothFailed;
    int _wideOffExposure;
    bool _isFakeFace;

    int _fakeFaceX1;
    int _fakeFaceY1;
    int _fakeFaceWidth;
    int _fakeFaceHeight;

    std::string _message;

    int _diffHist[256], _diffHistCnt;
    //int _onHist[512];
    int _onDiffHist[512];
    //int _offHist[512];
    int _histCnt;
    int _preExpAvg, _preQuarter, _preExpAvgCnt;
    int _preExpAvgMin, _preQuarterMin;
    int _preExpAvgMax, _preQuarterMax;
    int _expAvgSum, _expAvg, _quarterSum, _quarter, _expAvgCnt;

private:
    Poco::Logger& _logger;
    bool _abort;
    int _openMode;
    DistEstimator *_distEstimator;


    static Poco::Mutex _mutex;
};

#endif // FACEEYERUN_H
