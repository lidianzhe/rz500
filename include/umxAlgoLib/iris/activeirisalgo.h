#ifndef ACTIVEIRISALGO_H
#define ACTIVEIRISALGO_H

#include <Poco/Logger.h>
#include "../umxAlgoGlobal.h"
#include "irisalgo.h"
#include <iris_engine_v3.h>

class ActiveIrisAlgo : public IrisAlgo
{
public:
    ActiveIrisAlgo(Poco::Logger& logger);
    ~ActiveIrisAlgo();

	virtual int initialize();
    virtual int getEnrollTemplate(UMXALGO_IRIS_GET_TEMPLATE_INPUT* input, UMXALGO_IRIS_GET_ENROL_TEMPLATE_OUTPUT* output);
    virtual int getMatchTemplate(UMXALGO_IRIS_GET_TEMPLATE_INPUT* input, UMXALGO_IRIS_GET_TEMPLATE_OUTPUT* output);
    virtual int compareTemplate (UMXALGO_IRIS_COMPARE_TEMPLATE_INPUT* input, UMXALGO_IRIS_COMPARE_TEMPLATE_OUTPUT* output);
    virtual int checkCompareResult(UMXALGO_IRIS_COMPARE_TEMPLATE_OUTPUT outputResult, double matchThreshlod, double coOcclusionThreshold);
    virtual int getTmplateSize(int type);
    virtual double convMatchingScore(double score);
    virtual int compareMaxHammingDistance(double src, double dst);
    virtual int convertDeserializeTemplate(const char* serializeData, const int serializeSize, char* retDeserialize, int deserializeBufferSize);
private:
    int _maxScore; // EF-45(bkko)-20 : Change display score for debug mode from DeltaId like a HD
    float _faceScore;
    Poco::Logger& _logger;

    bool cropImage (unsigned char *fromBuffer, int width, int offsetX1, int offsetY1, unsigned char *toBuffer, int targetW, int targetH);
    void initIrisGetEnrolTemplateOutput(UMXALGO_IRIS_GET_ENROL_TEMPLATE_OUTPUT* output);
    void initIrisGetTemplateOutput(UMXALGO_IRIS_GET_TEMPLATE_OUTPUT* output);
    bool saveBMP8Image(char* szPathName, void* lpBits, int w, int h);


    typedef int                 LONG;
    typedef unsigned int        DWORD;
    typedef unsigned char       BYTE;
    typedef unsigned short      WORD;

    typedef struct tagPOINT
    {
        LONG  x;
        LONG  y;
    } POINT;

    typedef struct _RECTL       /* rcl */
    {
        LONG    left;
        LONG    top;
        LONG    right;
        LONG    bottom;
    } RECT;

    typedef struct tagRGBQUAD {
        BYTE    rgbBlue;
        BYTE    rgbGreen;
        BYTE    rgbRed;
        BYTE    rgbReserved;
    } RGBQUAD;

    typedef struct tagBITMAPINFOHEADER{
        DWORD      biSize;
        LONG       biWidth;
        LONG       biHeight;
        WORD       biPlanes;
        WORD       biBitCount;
        DWORD      biCompression;
        DWORD      biSizeImage;
        LONG       biXPelsPerMeter;
        LONG       biYPelsPerMeter;
        DWORD      biClrUsed;
        DWORD      biClrImportant;
    } BITMAPINFOHEADER;

    typedef struct tagBITMAPINFO {
        BITMAPINFOHEADER    bmiHeader;
        RGBQUAD             bmiColors[1];
    } BITMAPINFO;

    typedef struct _BITMAPFILEHEADER {
        WORD    bfType;
        DWORD   bfSize;
        WORD    bfReserved1;
        WORD    bfReserved2;
        DWORD   bfOffBits;
    } BITMAPFILEHEADER;

    typedef struct _BITMAPINFO256 {
        BITMAPINFOHEADER bmiHeader;
        RGBQUAD bmiColors[256];
    }BITMAPINFO256;

    BITMAPINFO _binfo;
    BITMAPINFO256 _binfo256;
};

#endif // ACTIVEIRISALGO_H
