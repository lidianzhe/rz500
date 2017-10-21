#ifndef VERILOOKALGO_H
#define VERILOOKALGO_H

#include <Poco/Logger.h>
#include "facealgo.h"
#include "umxAlgoLib/umxAlgoGlobal.h"
#include <NCore.h>
#include <NBiometricClient.h>
#include <NBiometrics.h>
#include <NMedia.h>
#include <NLicensing.h>

#define LICENSE_SERVER "/local"
#define LICENSE_PORT "5000"

class VeriLookAlgo : public FaceAlgo
{
public:
    VeriLookAlgo(Poco::Logger& logger);
    ~VeriLookAlgo();

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
    virtual int getFaceScore(float* faceScore);
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
    void initFaceFindOutput(UMXALGO_FACE_FIND_OUTPUT* faceFindOutput);
    int initIdentifyVariable();
#endif

    NResult CreateSubjectFromTemplate(HNSubject hSubject, const unsigned char * featureData);
    NResult PrintErrorMsgWithLastError(NChar * szErrorMessage, NResult result);
    NResult PrintErrorMsgWithError(NChar * szErrorMessage, HNError hError);
    NResult PrintErrorMsg(NChar * szErrorMessage, NResult result);
    NResult PrintErrorWithError(NResult result, HNError hError);
    NResult RetrieveErrorCode(NResult result, HNError hError);
    NResult PrintError(NResult result);

private:
    static Poco::Mutex _mutex;
    HNBiometricEngine _nbE;

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

    HNSubject _hProbeSubject = NULL;
    //HNSubject _hGallerySubject = NULL;
    HNBiometricClient _hBiometricClient = NULL;
    HNBiometricTask _hBiometricTask = NULL;
};

#endif // VERILOOKALGO_H
