#ifndef STEREO_H
#define STEREO_H

#include "umxeeprom.h"
#include "calibplane.h"

#include <Poco/Logger.h>

namespace {
const float AbsRotationSlopeAllowed = 0.0262f; // tan(1.5degree)
const float RelRotationSlopeAllowed = 0.0349f; // tan(2.0degree)
const int DeltaDueToRelRotation = 16; // 640*RelRotationSlopeAllowed/2 + 4
}

class STEREO
{
public:

    enum {
        LEFT_CAM_PIXEL_WIDTH = 2560,
        LEFT_CAM_PIXEL_HEIGHT = 1920,
        RIGHT_CAM_PIXEL_WIDTH = 720,
        RIGHT_CAM_PIXEL_HEIGHT = 1280,
        MIN_DIST = 290, // Fast Recog test
        MAX_DIST = 1000
    };

    enum StereoReturn {
        OK = 0,
        ERROR_OUT_OF_RANGE = 1,
        ERROR_WRONG_CAM = 2,
        ERROR_TOO_MUCH_ROTATION = 3,
        ERROR_WRONG_EEPROM = 4
    };

    enum {
        LEFT_NARROW_CAM = 0,
        RIGHT_WIDE_CAM = 1
    };

public:
    STEREO(Poco::Logger& logger, UMXEeprom *eeprom);
    ~STEREO();

    int initialize();

    int setCalibData( int whichCam, int zmm,
                      float xmm0, float ymm0, float xp0, float yp0,
                      float xmm1, float ymm1, float xp1, float yp1,
                      float xmm2, float ymm2, float xp2, float yp2,
                      float xmm3, float ymm3, float xp3, float yp3);
    int initialCalc();
    int getXCFromZmm(int zmm);
    int getXYmmPos(int whichCam, int zmm, float xp, float yp, float *xmm, float *ymm);
    int getXYPixelPos(int whichCam, int zmm, float xmm, float ymm, float *xp, float *yp);
    int getPixelPerMM(int whichCam, int zmm, float *pixelPerMM);
    void findWidthMM();
    void getLinearFitting(float *Y, float *X, int size, float *a, float *b);
    float getWidthMM(int whichCam, int zmm);
    void findDistanceMM(float rx, float ry, float lx, float ly, float *diff, float *outZmm,
                        float *outXmm, float *outYmm);

    float relSlope() {return _relSlope;}
    float pixelRatio() {return _pixelRatio;}
    int minYInWide() {return _minYInWide;}
    int maxYInWide() {return _maxYInWide;}
    int centerYInWide() {return _centerYInWide;}
    int zmmTableSize() {return _zmmTableSize;}
    int *zmmTable() {return _zmmTable;}
    int zmmTableMinXC() {return _zmmTableMinXC;}
    int zmmTableMaxXC() {return _zmmTableMaxXC;}

    int yNarrowObjWidth() {return _yNarrowObjWidth;}
    int yNarrowObjHeight() {return _yNarrowObjHeight;}
    float narrowInterval() {return _narrowInterval;}
    float motorStepPerWidePixel() {return _motorStepPerWidePixel;}
    float motorStepPerNarrowPixel() {return _motorStepPerNarrowPixel;}

    int _offsetYInObjImage;
    int _offsetXInObjImage;

private:
    Poco::Logger& _logger;
    UMXEeprom *_eeprom;

    int _minZMM, _maxZMM, _numOfZ, _dz;
    int _minYInWide, _maxYInWide, _centerYInWide;
    float _pixelRatio, _narrowSlope, _wideSlope, _relSlope;

    CalibPlane *_leftCalibData, *_rightCalibData;
    float _aLeftWidthMM, _bLeftWidthMM;  // y_widthMM = _aWidthMM*zmm + _bWidthMM
    float _aRightWidthMM, _bRightWidthMM;
    float _aLeftXpZ, _bLeftXpZ; // xpixel = _aLeftXpZ/(_aWidthMM*zmm + _bWidthMM) + _bLeftXpZ
    float *_XX, *_YY, *_ZZ;
    float *_XMM, *_YMM, *_ZMM;
    float *_narrowXCInWide, *_narrowYCInWide;
    float *_narrowXMMCInWide, *_narrowYMMCInWide;
    float *_wideLeftBDXMM, *_wideRightBDXMM;
    float _aWideLeftBD, _bWideLeftBD, _aWideRightBD, _bWideRightBD;
    float _aNarrowCenter, _bNarrowCenter;
    int _zmmTableMaxXC, _zmmTableMinXC, _zmmTableSize, *_zmmTable;

    int _yNarrowObjWidth, _yNarrowObjHeight;
    float _narrowInterval;
    float _motorStepPerWidePixel;
    float _motorStepPerNarrowPixel;
};

#endif // STEREO_H
