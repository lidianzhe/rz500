#ifndef NEOFACEALGO_H
#define NEOFACEALGO_H

#include <Poco/Logger.h>
#include "../external/NeoFace.hpp"
#include "facealgo.h"
#include "umxAlgoLib/umxAlgoGlobal.h"

class NeoFaceAlgo : public FaceAlgo
{
public:
    enum NeoFaceReturn {
        NEOFACE_FACE_FOUND = 0,
        NEOFACE_FACE_NOT_FOUND = 1,
        NEOFACE_ERROR_NOT_INITIALIZE = 2,
        NEOFACE_ERROR_UNKNOWN = 3
    };

    NeoFaceAlgo(Poco::Logger& logger);
    ~NeoFaceAlgo();

    virtual int initialize();
    virtual int terminate();
    virtual int setParamEyesMinWidth(int width);
    virtual int setParamEyesMaxWidth(int width);
    virtual int setParamEyesMaxRoll(unsigned short roll);
    virtual int setParamEyesMaxPan(unsigned short pan);
    virtual int setParamEyesMaxTilt(unsigned short tilt);
#if 1 //EF-45(unklee88)-1 : umxAlgoLib's define name revised
    virtual int findFace(UMXALGO_FACE_FIND_INPUT* faceFindInput, UMXALGO_FACE_FIND_OUTPUT* faceFindOutput);
    virtual int getLEyePosition(UMXALGO_POINT_XY* leye);
    virtual int getREyePosition(UMXALGO_POINT_XY* reye);
#endif
    virtual int getFaceScore(float* faceScore);
#if 1 //EF-45(unklee88)-1 : umxAlgoLib's define name revised
    virtual int getFaceTemplate(UMXALGO_FACE_FIND_INPUT* faceFindInput, UMXALGO_FACE_FIND_OUTPUT* faceFindOutput, UMXALGO_FACE_GET_TEMPLATE_OUTPUT* faceGetTemplateOutput);
#endif
    // EF-45(bkko)-3 : added face recognition function for neurotech vvv
    //virtual int compareFaceTemplate(const unsigned char* liveFeature, const unsigned char* enrolFeature, float* retScore);
    virtual int compareFaceTemplate(const unsigned char* liveFeature, const int liveFeatureSize, const unsigned char* enrolFeature, const int enrolFeatureSize, const int faceThreshold, float* retScore);
    // EF-45(bkko)-3 : added face recognition function for neurotech ^^^

    // EF-45(bkko)-28 : modify face recognition mathod of neurotech algorihtm for matching speed vvv
    virtual int setSourceTemplate(const unsigned char* feature, const int featureSize);
    virtual int setDestinationTemplate(const unsigned char* feature, const int featureSize, const unsigned char* uuid);
    virtual int identifyTemplate(const int faceThreshold, float* retScore, unsigned char* retUuid);
    // EF-45(bkko)-28 : modify face recognition mathod of neurotech algorihtm for matching speed ^^^

private:
#if 1 //EF-45(unklee88)-1 : umxAlgoLib's define name revised
    int faceFind(NeoFaceM::CFaceInfo* faceInfo, UMXALGO_FACE_FIND_INPUT* faceFindInput, UMXALGO_FACE_FIND_OUTPUT* faceFindOutput);
    void initFaceFindOutput(UMXALGO_FACE_FIND_OUTPUT* faceFindOutput);
#endif
    int checkFaceInfo(NeoFaceM::CFaceInfo* faceInfo);
#if 1 //EF-45(unklee88)-1 : umxAlgoLib's define name revised
    void setFaceInfo(NeoFaceM::CFaceInfo* faceInfo, UMXALGO_FACE_FIND_OUTPUT* faceFindOutput);
#endif

private:
    static Poco::Mutex _mutex;

    POINT _ptLEye;
    POINT _ptREye;
    int _paramEyesRoll;
    int _paramEyesMaxWidth;
    int _paramEyesMinWidth;
    float _paramReliability;
    float _faceScore;
    float _paramEyesPan;
    float _paramEyesTilt;

    Poco::Logger& _logger;

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

#endif // NEOFACEALGO_H
