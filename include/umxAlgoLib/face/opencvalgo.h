#ifndef OPENCV_H
#define OPENCV_H

#include <Poco/Logger.h>
#include "facealgo.h"
#include "umxAlgoLib/umxAlgoGlobal.h"

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

class OpenCvAlgo : public FaceAlgo
{
public:
    OpenCvAlgo(Poco::Logger& logger);
    ~OpenCvAlgo();

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
    static Poco::Mutex _mutex;
    cv::Mat *_cvFaceImage;
    cv::CascadeClassifier _cvFaceCascade;
    cv::CascadeClassifier _cvEyeCascade;

    POINT _ptLEye;
    POINT _ptREye;
    int _paramEyesMaxWidth;
    int _paramEyesMinWidth;

    float _faceScore;
    Poco::Logger& _logger;
};

#endif // OPENCV_H
