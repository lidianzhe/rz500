#ifndef VERIEYEALGO_H
#define VERIEYEALGO_H

#include <Poco/Logger.h>
#include "umxAlgoLib/umxAlgoGlobal.h"
#include "irisalgo.h"

class VeriEyeAlgo : public IrisAlgo
{
public:
    VeriEyeAlgo(Poco::Logger& logger);
    ~VeriEyeAlgo();

	virtual int initialize();
#if 1 //EF-45(unklee88)-1 : umxAlgoLib's define name revised
    virtual int getEnrollTemplate(UMXALGO_IRIS_GET_TEMPLATE_INPUT* input, UMXALGO_IRIS_GET_ENROL_TEMPLATE_OUTPUT* output);
    virtual int getMatchTemplate(UMXALGO_IRIS_GET_TEMPLATE_INPUT* input, UMXALGO_IRIS_GET_TEMPLATE_OUTPUT* output);
    virtual int compareTemplate (UMXALGO_IRIS_COMPARE_TEMPLATE_INPUT* input, UMXALGO_IRIS_COMPARE_TEMPLATE_OUTPUT* output);
    virtual int checkCompareResult(UMXALGO_IRIS_COMPARE_TEMPLATE_OUTPUT outputResult, double matchThreshlod, double coOcclusionThreshold);
    virtual int getTmplateSize(int type);
    virtual double convMatchingScore(double score);
    virtual int compareMaxHammingDistance(double src, double dst);
    virtual int convertDeserializeTemplate(const char* serializeData, const int serializeSize, char* retDeserialize, int deserializeBufferSize);
#endif

private:
    float _faceScore;
    Poco::Logger& _logger;
};

#endif // VERIEYEALGO_H
