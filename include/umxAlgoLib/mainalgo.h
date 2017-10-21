#ifndef MAINALGO_H
#define MAINALGO_H

#include <Poco/Logger.h>
#include <Poco/AutoPtr.h>
#include <Poco/Util/AbstractConfiguration.h>

#include "iris/irisalgo.h"
#include "face/facealgo.h"

#include "algomainrun.h"

class MainAlgo
{
public:
    MainAlgo(Poco::Logger& logger, Poco::AutoPtr<Poco::Util::AbstractConfiguration> config, int irisType, int faceType);
    ~MainAlgo();

    bool initialize();

    // iris
//EF-45(unklee88)-1 : umxAlgoLib's define name revised
    int getIrisEnrollTemplate(UMXALGO_IRIS_GET_TEMPLATE_INPUT* input, UMXALGO_IRIS_GET_ENROL_TEMPLATE_OUTPUT* output);
    int getIrisMatchTemplate(UMXALGO_IRIS_GET_TEMPLATE_INPUT* input, UMXALGO_IRIS_GET_TEMPLATE_OUTPUT* output);
    int compareEnrollIrisTemplate(UMXALGO_IRIS_COMPARE_TEMPLATE_INPUT* input, UMXALGO_IRIS_COMPARE_TEMPLATE_OUTPUT* output);
    int convDeserializeIrisTemplate(const char* serializeData, const int serializeSize, char* retDeserialize, int deserializeBufferSize);
    int getIrisTemplate(UMXALGO_IRIS_GET_TEMPLATE_INPUT* left_input, UMXALGO_IRIS_GET_TEMPLATE_OUTPUT* left_output,
                        UMXALGO_IRIS_GET_TEMPLATE_INPUT* right_input, UMXALGO_IRIS_GET_TEMPLATE_OUTPUT* right_output);
    int requestIrisMatch(int timer, UMXALGO_IRIS_IDENTIFY_INFO* info);


    // EF-45(bkko)-19 : Added Iris recognition engine for DeltaID vvv
    int getIrisTemplateSize(int type);
    int getIrisType() { return _irisType; }
    void setIrisType(int irisType) { _irisType = irisType; }
    int getFaceType() { return _faceType; }
    void setFaceType(int faceType) { _faceType = faceType; }
    int checkIrisCompareResult(UMXALGO_IRIS_COMPARE_TEMPLATE_OUTPUT outputResult, double matchThreshlod, double coOcclusionThreshold);
    double convIrisMatchingScore(double score);
    int compareIrisMaxHammingDistance(double src, double dst);
    // EF-45(bkko)-19 : Added Iris recognition engine for DeltaID ^^^

    // face
    int setParamEyesMinWidth(int minWidth);
    int setParamEyesMaxWidth(int maxWidth);
#if 1 //EF-45(unklee88)-1 : umxAlgoLib's define name revised
    int findFace(UMXALGO_FACE_FIND_INPUT* faceFindInput, UMXALGO_FACE_FIND_OUTPUT* faceFindOutput);
    int getLEyePosition(UMXALGO_POINT_XY* leye);
    int getREyePosition(UMXALGO_POINT_XY* reye);
    int getFaceScore(float* faceScore);
    int getFaceTemplate(UMXALGO_FACE_FIND_INPUT* faceFindInput, UMXALGO_FACE_FIND_OUTPUT* faceFindOutput, UMXALGO_FACE_GET_TEMPLATE_OUTPUT* faceGetTemplateOutput);
#endif
    // EF-45(bkko)-3 : added face recognition function for neurotech vvv
    //int compareFaceTemplate(const unsigned char* liveFeature, const unsigned char* enrolFeature, float* retScore);
    int compareFaceTemplate(const unsigned char* liveFeature, const int liveFeatureSize, const unsigned char* enrolFeature, const int enrolFeatureSize, const int faceThreshold, float* retScore);
    // EF-45(bkko)-3 : added face recognition function for neurotech ^^^

    // EF-45(bkko)-28 : modify face recognition mathod of neurotech algorihtm for matching speed vvv
    int setFaceSourceTemplate(const unsigned char* liveFeature, const int liveFeatureSize);
    int setFaceDestinationTemplate(const unsigned char* enrolFeature, const int enrolFeatureSize, const unsigned char* uuid);
    int identifyFaceTemplate(const int faceThreshold, float* retScore, unsigned char* retUuid);
    // EF-45(bkko)-28 : modify face recognition mathod of neurotech algorihtm for matching speed ^^^

    u_int32_t magicID() {return _magicID;}

    int setIAlgoManager(UMXAlgorithm::IAlgorithm* ptr) {_iAlgoManager = ptr;}
    UMXAlgorithm::IAlgorithm* getIAlgoManager(){return _iAlgoManager;}
public:
    IrisAlgo* _irisAlgo;
    FaceAlgo* _faceAlgo;

private:
    u_int32_t _magicID;

    Poco::Logger& _logger;
    const Poco::AutoPtr<Poco::Util::AbstractConfiguration> _config;

    int _irisType;
    int _faceType;

    long _numOfThreads;
    long _maxNumOfUsers;
    Poco::Thread _mainThread;
    long _dbCount;
    AlgoMainRun* _mainRun;

    UMXAlgorithm::IAlgorithm* _iAlgoManager;
};

#endif // MAINALGO_H
