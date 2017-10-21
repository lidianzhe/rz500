#ifndef MIRLINALGO_H
#define MIRLINALGO_H

#include <Poco/Logger.h>
#include "umxAlgoLib/umxAlgoGlobal.h"
#include "irisalgo.h"

class MirlinAlgo : public IrisAlgo
{
public:
    MirlinAlgo(Poco::Logger& logger);
    ~MirlinAlgo();

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
#if 1 //EF-45(unklee88)-1 : umxAlgoLib's define name revised
    void initIrisGetEnrolTemplateOutput(UMXALGO_IRIS_GET_ENROL_TEMPLATE_OUTPUT* output);
    void initIrisGetTemplateOutput(UMXALGO_IRIS_GET_TEMPLATE_OUTPUT* output);
#endif
public:
    Poco::Logger& _logger;
};

#endif // MIRLINALGO_H
