#ifndef FACEALGO_H
#define FACEALGO_H

#include "umxAlgoLib/umxAlgoGlobal.h"
#include "../external/NeoFace.hpp"
#include <iostream>

class FaceAlgo
{
public:
    FaceAlgo() : _cmsFaceDetect(""), _cmsFaceMatch("")
    {
        FILE *pipe_fp = NULL;
        if (( pipe_fp = popen("cmsenv get facedetectalgo", "r")) == NULL)
        {
            //error
        }
        else
        {
            char buffer[256] = {0,};
            fgets(buffer, 256, pipe_fp);

            _cmsFaceDetect = buffer;
            std::cout << "facedetectalgo site:" << _cmsFaceDetect << std::endl;
        }

        if(pipe_fp != NULL)
        {
            pclose(pipe_fp);
        }

        FILE *pipe_fp2 = NULL;
        if (( pipe_fp2 = popen("cmsenv get facematchalgo", "r")) == NULL)
        {
            //error
        }
        else
        {
            char buffer[256] = {0,};
            fgets(buffer, 256, pipe_fp2);

            _cmsFaceMatch = buffer;
            std::cout << "facematchalgo site:" << _cmsFaceMatch << std::endl;
        }

        if(pipe_fp2 != NULL)
        {
            pclose(pipe_fp2);
        }
    }
    std::string _cmsFaceDetect;
    std::string _cmsFaceMatch;
public:
    virtual int initialize() = 0;
    virtual int terminate() = 0;
    virtual int setParamEyesMinWidth(int width) = 0;
    virtual int setParamEyesMaxWidth(int width) = 0;
    virtual int setParamEyesMaxRoll(unsigned short roll) = 0;
    virtual int setParamEyesMaxPan(unsigned short pan) = 0;
    virtual int setParamEyesMaxTilt(unsigned short tilt) = 0;
#if 1 //EF-45(unklee88)-1 : umxAlgoLib's define name revised
    virtual int findFace(UMXALGO_FACE_FIND_INPUT* faceFindInput, UMXALGO_FACE_FIND_OUTPUT* faceFindOutput) = 0;
    virtual int getLEyePosition(UMXALGO_POINT_XY* leye) = 0;
    virtual int getREyePosition(UMXALGO_POINT_XY* reye) = 0;
#endif
    virtual int getFaceScore(float* faceScore) = 0;
#if 1 //EF-45(unklee88)-1 : umxAlgoLib's define name revised
    virtual int getFaceTemplate(UMXALGO_FACE_FIND_INPUT* faceFindInput, UMXALGO_FACE_FIND_OUTPUT* faceFindOutput, UMXALGO_FACE_GET_TEMPLATE_OUTPUT* faceGetTemplateOutput) = 0;
#endif
    // EF-45(bkko)-3 : added face recognition function for neurotech vvv
    //virtual int compareFaceTemplate(const unsigned char* liveFeature, const unsigned char* enrolFeature, float* retScore) = 0;
    virtual int compareFaceTemplate(const unsigned char* liveFeature, const int liveFeatureSize, const unsigned char* enrolFeature, const int enrolFeatureSize, const int faceThreshold, float* retScore) = 0;
    // EF-45(bkko)-3 : added face recognition function for neurotech ^^^

    // EF-45(bkko)-28 : modify face recognition mathod of neurotech algorihtm for matching speed vvv
    virtual int setSourceTemplate(const unsigned char* feature, const int featureSize) = 0;
    virtual int setDestinationTemplate(const unsigned char* feature, const int featureSize, const unsigned char* uuid) = 0;
    virtual int identifyTemplate(const int faceThreshold, float* retScore, unsigned char* retUuid) = 0;
    // EF-45(bkko)-28 : modify face recognition mathod of neurotech algorihtm for matching speed ^^^
};

#endif // FACEALGO_H
