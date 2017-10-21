#ifndef CALIBPLANE_H
#define CALIBPLANE_H

#if defined(WIN32)
  #include <windows.h>
  #if defined(CMIRISLIB_LIBRARY)
    #define CMIRISLIBINTERNAL_EXPORT __declspec(dllexport)
  #else
    #define CMIRISLIBINTERNAL_EXPORT __declspec(dllimport)
  #endif
#endif

class CalibPlane
{
public:
    enum {
        INIT_VALUE = -100000,
        INIT_VALUE1 = INIT_VALUE+1,
    };

public:
    CalibPlane();
    void setPlaneData(int zmm, float xmm0, float ymm0, float xp0, float yp0,
                                 float xmm1, float ymm1, float xp1, float yp1,
                                 float xmm2, float ymm2, float xp2, float yp2,
                                 float xmm3, float ymm3, float xp3, float yp3,
                                 int pixelWidth, int pixelHeight);
    void getPlaneRegionMM(float *x1mm, float *y1mm, float *x2mm, float *y2mm);
    void getXYmmPos(float xp, float yp, float *xmm, float *ymm);
    void getXYPixelPos(float xmm, float ymm, float *xp, float *yp);
    float getPixelPerMM() {return _pixelPerMM;}
    float getSlope() {return _slope;}

private:
    int _zmm;
    // Left Top = 0, Left Bottom = 1, Right Bottom = 2, Right Top = 3
    float _xmm[4], _ymm[4];
    float _xp[4], _yp[4];
    float _LTHVectorX, _LTHVectorY;
    float _LTVVectorX, _LTVVectorY;
    float _RBHVectorX, _RBHVectorY;
    float _RBVVectorX, _RBVVectorY;
    float _dxmm, _dymm;
    float _pixelPerMM;
    float _totalWidthMM; // 2560 pixels
    float _minXmm, _maxXmm, _minYmm, _maxYmm;
    float _slope;
};

#endif // CALIBPLANE_H
