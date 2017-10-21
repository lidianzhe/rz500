#ifndef MAINPROC_H
#define MAINPROC_H

#if defined(WIN32)
  #include <windows.h>
#endif

#include <cstdint>
#include <queue>
#include <deque>
#include <iostream>
#include <string>
#include "umxCamGlobal.h"
#include "umximage.h"
#include "umxeeprom.h"
#include "stereo.h"
#include "narrowcamera.h"
#include "widecamera.h"
#include "faceeyerun.h"
#include "mainimagerun.h"
#include "capturerun.h"
#include "motionobjdetector.h"

#include <Poco/Logger.h>
#include <Poco/Thread.h>
#include <Poco/Mutex.h>
#include <Poco/Condition.h>
#include "Poco/FileChannel.h"
#include "Poco/AutoPtr.h"

//// EF-45(unklee88)-28 : added umxCamLib in umxLauncherWithLib.pro ////
#include "umxAlgoLib/umxAlgo.h"
/////////////////////////////////////////////////////////////////////

// Utility functions
// convert float to string with precision
#include <sstream>
#include <iomanip>

template <typename T>
std::string toString(const T a_value, const int n = 4)
{
    std::ostringstream out;
    out << std::setprecision(n) << a_value;
    return out.str();
}

#define MES1(a) _message += a; _message += "\n"
#define MES2(a, b) _message += a + toString(b) + "\n"
#define MES3(a, b, c) _message += a; _message += " "; _message += b + toString(c) + "\n"
#define MES4(a, b, c, d) _message += a + toString(b) + " "; _message += c + toString(d) + "\n"
#define MES6(a, b, c, d, e, f) _message += a + toString(b) + " "; _message += c + toString(d) + " ";\
    _message += e + toString(f) + "\n"
#define MES8(a, b, c, d, e, f, g, h) _message += a + toString(b) + " "; _message += c + toString(d) + " ";\
    _message += e + toString(f) + " "; _message += g + toString(h) + "\n"


// after debugging
//#define MES1(a)
//#define MES2(a, b)
//#define MES3(a, b, c)
//#define MES4(a, b, c, d)
//#define MES8(a, b, c, d, e, f, g, h)

class EyeFinder;

class MainProc
{
public:
    enum {
        ARRAY_SIZE = UMXImage::NUM_OF_SAVE_FRAMES,

        NUM_OF_PREVIEW_FRAMES = 16,
        NUM_OF_FACE_SELECTED_FRAMES = 10,
        PREVIEW_SIZE = 720*480*4,
        IRIS_SIZE = 640*480,
        FULL_PREVIEW_YUV_SIZE = 720*1280*4,
        FULL_PREVIEW_Y_SIZE = 720*1280,
        FULL_NARROW_SIZE = 2560*1920,
        MAX_NORMAL_NARROW_SIZE = 1280*520,
        MAX_FACE_SELECTED_SIZE = 720*960*3
    };

    enum OpenMode {
        OPEN_NORMAL = 1,
        OPEN_CALIB = 1<<1,
        OPEN_SIMULATE = 1<<2,
        OPEN_AGING = 1<<3,  // ChangDG  160721
        OPEN_DEBUG = 1<<7
    };

    enum ReturnValue {
        OK = 0,
        ERROR_CAMERA_OPEN = 1
    };

    MainProc();
#if 0
    MainProc(Poco::Logger& logger);
#endif
    ~MainProc();

    void init();

    int readEvent(UMXCAM_EVENT *event, long timeout);
    int clearEventQueue();
    int cancelPendingReadEvent();

    bool initialize();

    void getOperatingRange(int *minOperatingRangeMM, int *maxOperatingRangeMM);
    bool setOperatingRange(int minOperatingRangeMM, int maxOperatingRangeMM);

    int openAlgo();
    int open(int mode, std::string &dirName);
    int getBufferSize();
    int gotoState(int state, bool retryFlag = false, int ledOnInMD = 0);
    int isStartCapture();
    bool switchCaptureMode(int *faceCaptureEnabled);
    bool isFaceCaptureMode();

    void readFakeFaceInfo();
    void writeFakeFaceInfo();
    int start(int bufferSize, unsigned char *buffer, UMXCAM_START_PARA *startPara);
        // startPara->minUsableIrisArea only works for Enroll mode

    bool eventWideViewImage();
    int captureWideViewImage();
    int stop();
    int closeAlgo();
    int close();
    int releasePreviewBuffer(unsigned char *buffer);
    int releaseFaceBuffer(unsigned char *buffer);

    int processMotionDetectState (int index);
    int processBothMotionDetectState (int index);
    int processMotionDetectInODState (int index);
    int processBothMotionDetectInODState (int index);
    void initImageInfo(UMXCAM_IMAGE_INFO *imageInfo);

    u_int32_t magicID() {return _magicID;}
    bool isOpen() {return s_isOpen;}
    bool isStart() {return s_isStart;}
    void setWideExposure(int exp) {_wideExposure = exp;}
    void setNarrowExposure(int exp) {_narrowExposure = exp;}
    void setWideEventOn(bool on) {_wideEventOn = on;}
    void setNarrowEventOn(bool on) {_narrowEventOn = on;}
    void setWideEventPeriod(int wideEventPeriod) {_wideEventPeriod = wideEventPeriod;}
    void setNarrowEventPeriod(int narrowEventPeriod) {_narrowEventPeriod = narrowEventPeriod;}

    bool saveAllImages(const std::string &dirName);
    void findExpAvg(UMXImage& umxImage);

    void simulWait();
    void simulBroadcast(int steps);
    void processWait(int eventID, void *ptRun, int action, int step=0);
    void processBroadcast(int steps);

    // EF-45(bkko)-24 : Change mode for algorithm, use the cmsenv vvv
    bool getPopen(const char* command, unsigned char* value, int maxSize);
    // EF-45(bkko)-24 : Change mode for algorithm, use the cmsenv ^^^

    UMXCAM_EVENT * createUmxEvent(int umxEventType);
    bool destroyUmxEvent(UMXCAM_EVENT *umxEvent, bool releaseApplFlag);

#if defined(UMXCAM_USE_WHITE_LED)
    void turnOnWhiteLED(bool on, bool forceFlag = false);
#endif

    static std::string s_returnString[];

    // application buffers
    static bool setupApplBuffers(unsigned char *applBuffer, int applBufferSize);
    static unsigned char *getApplPreviewBuffer();
    static unsigned char *getApplFaceBuffer();
    static bool releaseApplPreviewBuffer(unsigned char *buffer);
    static bool releaseApplFaceBuffer(unsigned char *buffer);
    static unsigned char *getApplNarrowBuffer();
    static bool releaseApplNarrowBuffer(unsigned char *buffer);

public:
    Poco::Logger& _logger;
    bool _isWhiteLEDOn;

    // image buffers
    UMXImage _narrowUmxImages[ARRAY_SIZE];
    UMXImage _wideUmxImages[ARRAY_SIZE];
    UMXImage *_backgroundUMXImage;

    // event
    Poco::Mutex _eventMutex;
    std::deque<UMXCAM_EVENT *> _eventDeque;
    Poco::Condition _eventDequeNotEmpty;

    // EEPROM & STEREO
    UMXEeprom *_eeprom;
    STEREO *_stereo;

    // image capture
    NarrowCamera _narrowCamera;
    WideCamera _wideCamera;

    // captureRun
    CaptureRun *_captureRun;
    Poco::Thread _captureThread;
    Poco::Mutex _captureMutex;
    std::deque<int> _wideCaptureDeque;
    std::deque<int> _narrowCaptureDeque;
    Poco::Condition _captureDequeNotEmpty;

    // faceEyeRun
    FaceEyeRun *_faceEyeRun;
    Poco::Thread _faceEyeThread;
    Poco::Mutex _faceEyeMutex;
    std::deque<int> _faceEyeDeque;
    Poco::Condition _faceEyeDequeNotEmpty;

    // _mainImageRun
    MainImageRun *_mainImageRun;
    Poco::Thread _mainImageThread;

    // _mainImageRun & faceEyeRun
    int _waitFrameCount;
    Poco::Mutex _waitFrameCountMutex;

    // save the wideview image when timeout
    Poco::Mutex _wideviewSaveMutex;
    int _wideviewIpdPixel;
    bool _wideviewSaveFlag; // if true, save
    bool _wideviewFaceSaved; // to s_bmp24FaceBuffer
    int _wideviewLastIndex;


    // state variables
    Poco::Mutex _stateChangeMutex;
    int _curState, _curWideWidth, _curWideHeight, _curWideSize;
    int _curNarrowWidth, _curNarrowHeight, _curNarrowSize;
    int _curWideBufferID, _curNarrowBufferID;
    bool _wideCameraStarted, _narrowCameraStarted;
    Poco::Mutex _faceCaptureEnabledChangeMutex;
    bool _faceCaptureEnabled;

    int _prevWideFrameCount, _curWideFrameCount;
    int _prevNarrowFrameCount, _curNarrowFrameCount;

    // Motion Detector
    MotionObjDetector *_mdMotionObjDetector;
    MotionObjDetector *_odMotionObjDetector;

    // EyeFinder
    EyeFinder *_eyeFinderWide;
    EyeFinder *_eyeFinderNarrowOD;
    EyeFinder *_eyeFinderLargeNarrowOD;
    EyeFinder *_eyeFinderNarrowID;
    int _displayCenterYInWide;

    // application buffer allocation
    unsigned char *_applBuffer;
    int _applBufferSize;

    // Simulation
    std::deque<std::string> _wideSimulFilenames;
    std::deque<std::string> _narrowSimulFilenames;
    std::string _eepromSimulFilename;
    std::string _simulDirname;

    Poco::Mutex _simulMutex;
    std::deque<int> _simulDeque;
    Poco::Condition _simulDequeNotEmpty;

    Poco::Mutex _processMutex;
    std::deque<int> _processDeque;
    Poco::Condition _processDequeNotEmpty;
    bool _processDebug;
    bool _processNowWait;
    int _curProcessIndex;

    int _whichEye;
    int _enrolRecogMode;
    bool _wideEventOn, _narrowEventOn;
    int _wideEventPeriod, _narrowEventPeriod;
    int _narrowIRIntensity; // for red color correction due to IR
                            // Max is around 1200

    // Options
    int _maxFrameDiffinEitherEyeMode;
    int _minOperatingRangeMM;
    int _maxOperatingRangeMM;

    // Brightness
    bool _narrowTooBright; // not used
    bool _wideTooBright;

    // goto state variables. Use left in Object Detect State
    unsigned short _narrowExpX1, _narrowExpY1, _narrowExpWidth, _narrowExpHeight;
    unsigned char _narrowLedOnTarget, _narrowLedOffTarget;
    unsigned short _narrowLeftExpX1, _narrowLeftExpY1, _narrowLeftExpWidth, _narrowLeftExpHeight;
    unsigned char _narrowLeftLedOnTarget, _narrowLeftLedOffTarget;
    unsigned short _narrowRightExpX1, _narrowRightExpY1, _narrowRightExpWidth, _narrowRightExpHeight;
    unsigned short _narrowLeftExposure, _narrowRightExposure;
    unsigned char _narrowRightLedOnTarget, _narrowRightLedOffTarget;
    unsigned short _wideExpX1, _wideExpY1, _wideExpWidth, _wideExpHeight;
    unsigned char _wideLedOnTarget, _wideLedOffTarget;
    unsigned char _motorDir;
    unsigned short _motorSteps;
    unsigned short _additionalGain;
    int _simulFirstID;
    float _leftScleraIntensity, _rightScleraIntensity;
    int _recentNarrowExp;

    static bool s_isOpen, s_isStart;
    static int s_openMode;
    static int s_initState;

    static unsigned char *s_leftIrisBuffer;
    static unsigned char *s_rightIrisBuffer;
    static unsigned char *s_bmp8FaceBuffer;
    static unsigned char *s_bmp24FaceBuffer;

    UMXALGO_HANDLE _algoHandle;
//    UMXCAM_EVENT *_faceUmxEvent;
    int _faceSub2OffsetY;

    Poco::Mutex _moveUpDownMutex;
    bool _userShouldMoveDown, _userShouldMoveUp;
    int _motorPosHigh, _motorPosLow;

    int _faceModeReyeCenterX, _faceModeReyeCenterY;
    int _faceModeLeyeCenterX, _faceModeLeyeCenterY;

    int _irisModeReyeCenterX, _irisModeReyeCenterY;
    int _irisModeLeyeCenterX, _irisModeLeyeCenterY;

    int _curMessage;
    int _minUsableIrisArea;
    int _faceFullResolution;
    int _faceImageInterval;
    int _checkFakeFace;
    int _faceColorCorrection;
    int _coverGlassTrans;
    bool _isMotionObjectDetectState;
    bool _isEF45Module;

    // for face image in irisSelected event
    UMXImage *_wideBothSelected, *_wideOffSelected;

    UMXImage *_mdLastWide;

#if defined(UMX_LIB_MEMORY_LEAK_TEST_JJ)
    static std::deque<UMXCAM_EVENT *> s_umxEventDeque;
#endif

private:

    u_int32_t _magicID;
    int _wideExposure, _narrowExposure;

    static Poco::Mutex s_mutex;
    static Poco::Mutex s_applMutex;
    static Poco::Mutex s_motionDetectMutex;

    // buffers allocated in application for UMX_IMAGE event
    static std::deque<unsigned char *> s_applPreviewDeque;
    static std::deque<unsigned char *> s_curApplPreviewDeque;

    static std::deque<unsigned char *> s_applFaceDeque;
    static std::deque<unsigned char *> s_curApplFaceDeque;

    static std::deque<unsigned char *> s_applNarrowDeque;
    static std::deque<unsigned char *> s_curApplNarrowDeque;
};

#endif // MAINPROC_H
