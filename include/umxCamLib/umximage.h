#ifndef UMXIMAGE_H
#define UMXIMAGE_H

#include <cstdint>
#include <queue>
#include <deque>
#include <iostream>

#include "command.h"
#include "stereo.h"

#include <Poco/Logger.h>
#include <Poco/Mutex.h>
#include "Poco/FileChannel.h"
#include "Poco/AutoPtr.h"

#if __GNUC__
#if __x86_64__ || __ppc64__
#define ENV64
#define TO_INT u_int64_t
#else
#define ENV32
#define TO_INT u_int32_t
#endif
#endif

class UMXImage
{
public:
    enum {
        HEADER_SIZE = 32,

        NUM_OF_SAVE_FRAMES = 60,

        //DM_REGION_NUM = 4, // in findDynamicRegion(), number of regions in x and y direction
        // Distance Measure Region Number
        MD_BLOCK_SIZE = 8, // Motion Detection and Object Detection Block size
        // If this is changed, need to change Y45x80 and Y45x80Size
        DIFF_THRESHOLD = 5
    };
    enum {MAGIC_ID = (u_int32_t)(0xCDC3C9C6)};
    //enum {MAGIC_ID = (u_int32_t)(0x809D0000)};

    enum PosOffset {
        MAGIC_NUMBER_OFFSET = 0,
        MAJOR_VERSION_OFFSET = 4,
        MINOR_VERSION_OFFSET = 5,
        FRAME_COUNT_OFFSET = 6,
        STATE_FRAME_COUNT_OFFSET = 8,
        STATE_OFFSET = 10,
        IMAGE_TYPE_OFFSET = 11,
        SENSOR_TYPE_OFFSET = 12,
        IMAGE_RESOL_OFFSET = 13,
        X1_OFFSET = 14,
        Y1_OFFSET = 16,
        WIDTH_OFFSET = 18,
        HEIGHT_OFFSET = 20,
        X2_OFFSET = 22,
        GAIN_OFFSET = 24,
        EXPOSURE_OFFSET = 25,
        LED_KIND_OFFSET = 27,
        DEVICE_TYPE_OFFSET = 28,
        MOTOR_MOVING_OFFSET = 29,
        MOTOR_POS_OFFSET = 30
    };

    enum ImageType {
        NARROW = 0x00,
        WIDE = 0x01
    };

    enum SensorType {
        V024C = 0x00,
        V024M = 0x01,
        M023M = 0x11,
        M024M = 0x21,
        M021M = 0x31,
        P031M = 0x41,  // Narrow Aptina 5M
        P031C = 0x40,
        PO3100K = 0x50 // Wide PixelPlus color
    };

    enum ImageResol {
        BW_FULL = 0x00,
        BW_SUB2 = 0x01,
        BW_SUB4 = 0x02,
        YUV_FULL = 0x10,
        YUV_SUB2 = 0x11,  // omit the YUV line, color
        YUV_SUB4 = 0x12,
        Y_FULL =   0x20,  // Y only out of YUV sensor
        Y_SUB2 =   0x21,
        Y_SUB4 =   0x22
    };

    enum {
        NARROW_EYE_BLOCK = 160,  // 480/4
        NARROW_EYE_BLOCK2 = 80,
        NARROW_EYE_BLOCK_MARGIN = 20,
        WIDE_EYE_BLOCK = 120, // NARROW_EYE_BLOCK/1.5
        WIDE_EYE_BLOCK2 = 60,
        WIDE_EYE_BLOCK_MARGIN = 16,
        EYE_BLOCK_SMALL = 40, // not used
        EYE_BLOCK_SMALL2 = 20 // not used
    };

    // OD: Object Detection, ID: Iris Detection, IC: Iris Capture, MD: Motion Detection
    enum  {
        BW240x180 = 0, // 640x480 => 4/7 reduce for distance measure. OD
        Y160x160 = 1,  // Wide Eye finder image. change EYE_BLOCK above if this is changed
        Y640x360 = 2,  // Sub2, MD, OD
        Y45x80 = 3,
        Y180x320 = 4, // face detection object

        BW640x480 = 5, // Sub4 of Narrow, OD
        Y320x480 = 6, // ID, IC
        BW2560x1920 = 7, // Debug

        YUV720x360 = 8,  // Led off, color, ID, IC
        YUV1280x360 = 9, // Led off, color, OD
        Y720x720 = 10,  // Led on, Y only, ID, IC
        YUV1280x720 = 11, // Debug

        RGB540x480 = 12,  // For display
        RGB720x1280 = 13,  // For debug display
        YUV2560x480 = 14,   // for test

        BUFFER_ID_SIZE = YUV2560x480+1
    };

    enum BufferIDSize {
        BW240x180Size = 43200,
        Y160x160Size = 25600,
        Y640x360Size = 230400,
        Y45x80Size = 3600,
        Y180x320Size = 57600,

        BW640x480Size = 307200,
        Y320x480Size = 153600,
        BW2560x1920Size = 4915200,

        YUV720x360Size = 518400,
        YUV1280x360Size = 921600,
        Y720x720Size = 518400,
        YUV1280x720Size = 1843200,

        RGB540x480Size = 777600,
        RGB720x1280Size = 2764800,
        YUV2560x480Size = 2457600
    };

    enum LedKind {
        LED_OFF = 0,
        LED_LC7 = (unsigned char)0x01, LED_RC7 = (unsigned char)0x10,
        LED_LC8 = (unsigned char)0x02, LED_RC8 = (unsigned char)0x20,
        LED_BOTH8 = (LED_LC8 | LED_RC8), LED_BOTH7 = (LED_LC7 | LED_RC7),
        LED_LC78 = (LED_LC7 | LED_LC8), LED_RC78 = (LED_RC7 | LED_RC8)
    };

    enum DeviceType {
        DEMX = 0x00,
        BMT = 0x01,
        LGC = 0x02,
        FI = 0x03,
        ULC = 0x04,
        UMX = 0x05
    };

    enum ExposurePara {
        MAX_NARROW_EXPOSURE = 1200,
        MAX_WIDE_EXPOSURE = 719,

        // the diff in a certain exposure should be bigger than 4. =>
        // min exposure allowed for object detection is (maxExp/curExp)*4 = 30
        MIN_NARROW_OBJ_THRESHOLD_IN_FULL_EXP = 40, // at 1000mm
        MIN_NARROW_OBJ_COUNT_PERC = 20,

        MIN_WIDE_OBJ_COUNT_PERC = 3,

        EXPOSURE_AVG_MARGIN = 80,
        MIN_EXPOSURE_AVG = 20
    };

    enum Brightness {
        BRIGHT_DARK = 0,
        BRIGHT_ENOUGH = 1,
        TOO_BRIGHT = 2
    };

    enum ObjInfoImage {
        BRIGHT_PIXEL_IN_OFF_IMAGE = (1<<0),
        BRIGHT_PIXEL_IN_ON_IMAGE = (1<<1),
        BRIGHT_PIXEL = (BRIGHT_PIXEL_IN_OFF_IMAGE | BRIGHT_PIXEL_IN_ON_IMAGE),
        OBJ_PIXEL = (1<<7)
    };

    enum Misc {
        MIN_SPEC_VALUE = 200
    };

public:
    UMXImage();
    UMXImage(Poco::Logger& logger);
    ~UMXImage();
    void init();

    // image loading ...
    bool setBuffer(std::string &filename, unsigned char **pbuf, int *plength, int *pbufferID);
    bool readHeader(unsigned char *buf, int cnt);
    std::string stringHeader(unsigned char *header);
    bool loadBuffer(unsigned char *buf, int cnt, int bufferID);
    void unloadBuffers(bool unloadCapturedImage, bool saveFlag, std::string &baseName);
    bool allocBlockImageBuffer();
    bool allocNarrowIDEyeImageBuffer();
    bool allocNarrowEyeImageBuffer();
    bool allocLargeNarrowEyeImageBuffer();
    bool allocWideEyeImageBuffer();
    bool allocObjImageBuffer();
    bool writeHeader(unsigned char *buf);

    // Motion Detection in MD
    //bool rotateLeftYtoY_forMD_inMD (); // Wide LED_OFF yDistImage in MD

    bool getObjAvg (int x1, int y1, int x2, int y2, int skip, float *avg);
    // Display color and Y image
    bool rotateLeftYUVtoARGB32 (int offsetX1, int offsetY1, unsigned char *toBuffer,
                                int targetW, int targetH);
    bool rotateLeftYUVtoSub2ARGB32 (int offsetX1, int offsetY1, unsigned char *toBuffer,
                                int targetW, int targetH);
    bool rotateLeftFlipCenterYUVtoARGB32Sub2 (int offsetX1, unsigned char *toBuffer, int targetH);
    bool rotateLeftFlipCenterYtoARGB32Sub2 (int offsetX1, unsigned char *toBuffer, int targetH);

    bool rotateLeftFlipCenterYUVtoARGB32 (int offsetX1, int offsetY1, unsigned char *toBuffer,
                                          int outWidth, int targetW, int targetH, bool isEF45Module);
    bool rotateLeftFlipCenterYtoARGB32 (int offsetX1, int offsetY1, unsigned char *toBuffer,
                                          int outWidth, int targetW, int targetH, bool isEF45Module);

    bool rotateLeftFlipYUVtoARGB32 (int offsetX1, int offsetY1, unsigned char *toBuffer,
                                    int targetW, int targetH);
    bool rotateLeftYUVtoBMP24 (int offsetX1, int offsetY1, unsigned char *toBuffer,
                               int targetW, int targetH);
    //bool makeEyeImage (int offsetX1, int offsetY1);
    //bool getObjAvg (int x1, int y1, int x2, int y2, int skip, float *avg);
    bool rotateLeftYtoY (int offsetX1, int offsetY1, unsigned char *toBuffer,
                         int targetW, int targetH);
    bool rotateLeftYtoSub2Y (int offsetX1, int offsetY1, unsigned char *toBuffer,
                         int targetW, int targetH);
    // ChangDG  160721
    bool rotateMirrorYtoY (int offsetX1, int offsetY1, unsigned char *toBuffer,
                                   int targetW, int targetH);

    // Distance Measure in OD
    //bool rotateLeftYUVtoY_forDM_inOD (int offsetX1); // // Wide LED_OFF yDistImage
    //bool rotateLeftYUVtoFullY_forOD_inOD ();
    bool rotateLeftYUVtoSub4Y_FaceDetection (bool flip);
    bool rotateLeftYtoSub4YDiff_ObjDetection (UMXImage &wideBoth, bool flip);
    bool rotateLeftYtoSub4Y_FaceDetection (UMXImage &wideBoth, bool flip);
    bool rotateLeftYtoSub4Y_FakeFace (bool flip); // Both image
    bool rotateLeftYtoSub4YDiff_FakeFace (UMXImage &wideOff, bool flip); // diff image
    bool rotateLeftYUVtoSub2Y_forOD_inOD (STEREO& stereo);
    //bool rotateLeftYtoY_forDM_inOD (int offsetX1, UMXImage &wideOff); // Wide LED_BOTH8 yDistImage
    bool rotateLeftYtoFullY_forOD_inOD (UMXImage &wideOff);
    bool rotateLeftYtoFullY_forBMP8 (UMXImage &wideOff, int offsetX1, int offsetY1,
                                     unsigned char *toBuffer, int targetW, int targetH);
    bool rotateLeftYtoFullY_forEyeFinder (int offsetX1, int offsetY1,
                                          unsigned char *toBuffer, int targetW, int targetH);
    bool rotateLeftYtoSub2Y_forOD_inOD (STEREO& stereo, UMXImage &wideOff);
    bool subFractionBW_forEye_inOD(STEREO& stereo, UMXImage &narrowOff, int sx, int sy);
    bool subFractionBW_forDMOD_inOD(STEREO& stereo, UMXImage &narrowOff); // Narrow yDistImage
    //bool findDynamicRegion ();
    bool findNarrowObjRegion ();
    bool findWideObjRegion (int initY);
    void findNarrowSelectedAvg(UMXImage& narrowBoth8);

    // Object Detection, Motion Detection in OD
    bool rotateLeftSub2YUVtoY_forODMD_inOD (); // Wide LED_Off yObjImage
    bool rotateLeftSub2YtoY_forOD_inOD (); // Wide LED_BOTH8 yObjImage

    // Narrow sub4 eyefinder
    bool cropImage (int offsetX1, int offsetY1, unsigned char *toBuffer,
                    int targetW, int targetH);
    bool cropSmoothImage (int offsetX1, int offsetY1, unsigned char *toBuffer,
                          int targetW, int targetH);

    // Iris Capture
    bool seperateLeftRight ();

    // getter and setter
    bool isValid() {return _isValid;}
    void setValid(bool isValid) {_isValid = isValid;}

    int brightness() {return _brightness;}
    unsigned short frameCount() {return _frameCount;}
    unsigned short stateFrameCount() {return _stateFrameCount;}
    unsigned short x1() {return _x1;}
    unsigned short y1() {return _y1;}
    unsigned short x2() {return _x2;}
    unsigned short width() {return _width;}
    unsigned short height() {return _height;}
    unsigned short exposure() {return _exposure;}
    unsigned short motorPos() {return _motorPos;}

    unsigned char sensorType() {return _sensorType;}
    unsigned char imageType() {return _imageType;}
    unsigned char imageResol() {return _imageResol;}
    unsigned char deviceType() {return _deviceType;}
    unsigned char state() {return _state;}
    unsigned char gain() {return _gain;}
    unsigned char ledKind() {return _ledKind;}
    unsigned char motorMoving() {return _motorMoving;}

    unsigned char *image() {return _image;}
    int imageSize() {return _imageSize;}
    int imageBufferID() {return _imageBufferID;}

    unsigned char *rgbImage() {return _rgbImage;}
    int rgbImageBufferID() {return _rgbImageBufferID;}
    int distMM() {return _distMM;}
    void setDistMM (int distMM) {_distMM = distMM;}

    int minIPD() {return _minIPD;}
    void setMinIPD (int minIPD) {_minIPD = minIPD;}
    int maxIPD() {return _maxIPD;}
    void setMaxIPD (int maxIPD) {_maxIPD = maxIPD;}

    /*
    unsigned char *yDistImage() {return _yDistImage;}
    int yDistImageBufferID() {return _yDistImageBufferID;}
    unsigned char *yDistSubtractedImage() {return _yDistSubtractedImage;}
    int yDistSubtractedImageBufferID() {return _yDistSubtractedImageBufferID;}
    int yDistWidth() {return _yDistWidth;}
    int yDistHeight() {return _yDistHeight;}
    int yDistOffsetY() {return _yDistOffsetY;}
    */
    int yObjSelectedX1() {return _yObjSelectedX1;}
    int yObjSelectedY1() {return _yObjSelectedY1;}
    int yObjSelectedWidth() {return _yObjSelectedWidth;}
    int yObjSelectedHeight() {return _yObjSelectedHeight;}
    int yObjSelectedAvg() {return _yObjSelectedAvg;}

    int yObjEyesX1() {return _yObjEyesX1;}
    int yObjEyesY1() {return _yObjEyesY1;}
    int yObjEyesWidth() {return _yObjEyesWidth;}
    int yObjEyesHeight() {return _yObjEyesHeight;}

    unsigned char *yObjInfoImage() {return _yObjInfoImage;}
    int yObjInfoImageBufferID() {return _yObjInfoImageBufferID;}

    unsigned char *yObjImage() {return _yObjImage;}
    int yObjImageBufferID() {return _yObjImageBufferID;}
    int yObjWidth() {return _yObjWidth;}
    int yObjHeight() {return _yObjHeight;}

    unsigned char *yBlockImage() {return _yBlockImage;}
    int yBlockImageBufferID() {return _yBlockImageBufferID;}
    int yBlockWidth() {return _yBlockWidth;}
    int yBlockHeight() {return _yBlockHeight;}

    unsigned char *yEyeImage() {return _yEyeImage;}
    unsigned char *yEyeSpecImage() {return _yEyeSpecImage;}
    int yEyeImageBufferID() {return _yEyeImageBufferID;}
    int yEyeWidth() {return _yEyeWidth;}
    int yEyeHeight() {return _yEyeHeight;}

    unsigned char *leftImage() {return _leftImage;}
    int leftImageBufferID() {return _leftImageBufferID;}

    unsigned char *rightImage() {return _rightImage;}
    int rightImageBufferID() {return _rightImageBufferID;}

    // static functions
    static bool writeUMXImage(std::string &filename, unsigned char *buf, int cnt);
    static int readUMXImage(std::string &filename, unsigned char *buf, int cnt);
    static int readStateFromFile(std::string &filename);

    // Internal buffers
    static void prepareBuffers();
    static void cleanBuffers();
    static unsigned char *getBuffer(int bufferID);
    static void collectBuffer(unsigned char *buf, int bufferID);
#if defined(UMX_LIB_CAPTURE_MEMORY_LEAK_RESOLVE)
    static void collectBuffer(bool flag);
    static void collectBuffer(unsigned char *buf, int bufferID, bool flag);
#endif

    //
    static void setCurFrameCount(int curFrameCount);
    static int curFrameCount();
    static void setCurState(int curState);
    static int curState();
    static unsigned short getFrameCountFromBuffer(unsigned char *buffer);
    static unsigned char getStateFromBuffer(unsigned char *buffer);

private:

    bool allocImageBuffer(unsigned char **image, int *imageBufferID, int bufferID);

public:
    bool _isValid;
    bool _isSkipped;
    bool _isMotionDetected;
    int _motionDetectedY;
    int _frameCountDiffInMD;
    unsigned char *_image;   // NULL: invalid, otherwise valid
    int _imageBufferID;
    int _imageSize;

    unsigned char _sensorType, _imageType, _imageResol, _deviceType;
    unsigned char _state, _gain, _ledKind, _motorMoving;
    unsigned short _frameCount, _stateFrameCount, _x1, _y1, _x2;
    unsigned short _width, _height, _exposure, _motorPos;
    bool _objFoundInNarrow;
    bool _objFoundInWide;
    bool _findFaceTriedInWide;
    bool _faceFoundInWide;
    int _leyeXFullInWide, _leyeYFullInWide, _reyeXFullInWide, _reyeYFullInWide;
    int _narrowX1FullInWide, _narrowY1FullInWide, _narrowX2FullInWide, _narrowY2FullInWide;
    bool _reyeInsideNarrow, _leyeInsideNarrow;
    int _eyePosXFull, _eyePosYFull; // JJC 20161120
    int _curXCSub2InWide, _curYCSub2InWide; // matched with narrow image
    int _narrowInitX1Sub2, _narrowInitY1Sub2;
    //int _leftNarrowInitX1Sub2, _leftNarrowInitY1Sub2;
    //int _rightNarrowInitX1Sub2, _rightNarrowInitY1Sub2;
    int _reyeXSub4InNarrow, _reyeYSub4InNarrow, _leyeXSub4InNarrow, _leyeYSub4InNarrow;
    int _ipdMM, _ipdPixels;
    int _brightness;
    int _distMM, _reyeDistMM, _leyeDistMM;
    int _minIPD, _maxIPD;
    int _expAvg;
    bool _exposureOK;
    int _narrowShifti, _narrowShiftj;
    int _yObjAvgInMaxExposure;

    int _curObjThresholdInFullExp; // proportional to 1/r^2

    int _yObjSelectedX1, _yObjSelectedY1;
    int _yObjSelectedWidth, _yObjSelectedHeight;
    int _yObjSelectedAvg;

    int _yPixelsMovedInNarrow, _yPixelsMovedInWide;
    int _irisCenterX, _irisCenterY, _irisRadius;
    int _pupilCenterX, _pupilCenterY, _pupilRadius;
    int _specCenterX, _specCenterY;

    int _algoIrisCenterX, _algoIrisCenterY, _algoIrisRadius;
    int _algoPupilCenterX, _algoPupilCenterY, _algoPupilRadius;

    unsigned char _gamma[256];
    unsigned char _invGamma[256];

    int _irisPartR, _irisPartL;

    static int s_bufferSize[BUFFER_ID_SIZE];
    static const float s_convertNarrowToWideThreshold;
    static const int s_minWideExposureBrightEnough, s_minNarrowExposureBrightEnough;

    static float s_yIrisRatio;
    static float s_yFaceRatio;
    static bool s_wasIrisPreviewColor;
    static bool s_wasFacePreviewColor;
#if defined(UMX_LIB_CAPTURE_MEMORY_LEAK_RESOLVE)
#else
    static std::deque<unsigned char *> s_bufferDeque[BUFFER_ID_SIZE];
#endif

#if defined(UMX_LIB_MEMORY_LEAK_TEST_JJ)
    static int s_bufferDequeCnt[BUFFER_ID_SIZE];
#endif

#if defined(UMX_LIB_CAPTURE_MEMORY_LEAK_RESOLVE)
    //test
    static std::deque<unsigned char *> s_getBufferDeque[BUFFER_ID_SIZE];
    static std::deque<unsigned char *> s_bufferDeque[BUFFER_ID_SIZE];
#endif

private:
    unsigned char *_rgbImage;
    int _rgbImageBufferID;

    // Obj: sub2

    int _yObjEyesX1, _yObjEyesY1;
    int _yObjEyesWidth, _yObjEyesHeight;

    unsigned char *_yObjImage;
    int _yObjImageBufferID;
    unsigned char *_yObjInfoImage;
    int _yObjInfoImageBufferID;
    int _yObjWidth, _yObjHeight;

    unsigned char *_yBlockImage;
    int _yBlockImageBufferID;
    int _yBlockWidth, _yBlockHeight;

    unsigned char *_yEyeImage, *_yEyeSpecImage;
    int _yEyeImageBufferID;
    int _yEyeWidth, _yEyeHeight;

    unsigned char *_leftImage;
    int _leftImageBufferID;
    int _leftWidth, _leftHeight;

    unsigned char *_rightImage;
    int _rightImageBufferID;
    int _rightWidth, _rightHeight;

    Poco::Logger& _logger;

    // static varables
    static Poco::Mutex s_mutex;

    static int s_initNumBuffers[BUFFER_ID_SIZE];
    static int s_curFrameCount;
    static int s_curState;



};

#endif // UMXIMAGE_H
