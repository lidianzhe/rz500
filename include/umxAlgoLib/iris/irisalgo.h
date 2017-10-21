#ifndef IRISALGO_H
#define IRISALGO_H

#include "umxAlgoLib/umxAlgoGlobal.h"

class IrisAlgo
{
public:
    enum {MAGIC_ID = (u_int32_t)(0xCDC3C9C6)};

    IrisAlgo(){};

public:
	virtual int initialize()=0;
    virtual int getEnrollTemplate(UMXALGO_IRIS_GET_TEMPLATE_INPUT* input, UMXALGO_IRIS_GET_ENROL_TEMPLATE_OUTPUT* output)=0;
    virtual int getMatchTemplate(UMXALGO_IRIS_GET_TEMPLATE_INPUT* input, UMXALGO_IRIS_GET_TEMPLATE_OUTPUT* output)=0;
    virtual int compareTemplate (UMXALGO_IRIS_COMPARE_TEMPLATE_INPUT* input, UMXALGO_IRIS_COMPARE_TEMPLATE_OUTPUT* output)=0;
    virtual int checkCompareResult(UMXALGO_IRIS_COMPARE_TEMPLATE_OUTPUT outputResult, double matchThreshlod, double coOcclusionThreshold)=0;
    virtual int getTmplateSize(int type)=0;
    virtual double convMatchingScore(double) = 0; // EF-45(bkko)-21 : Added Asymetric function for iris recognition mode
    virtual int compareMaxHammingDistance(double src, double dst) = 0; // EF-45(bkko)-21 : Added Asymetric function for iris recognition mode
    virtual int convertDeserializeTemplate(const char* serializeData, const int serializeSize, char* retDeserialize, int deserializeBufferSize) = 0;
};

#endif // IRISALGO_H
