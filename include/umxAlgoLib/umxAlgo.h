/////////////////////////////////////////////////////////////////////////////////////////
// umxAlgo.h
//
// Version 0.1.3   July 18, 2016
//                 Initial Public Release
//
// Description: umxAlgo.h provide the interface with the iris image capture device
//              UMX-10 (EF-45) developed by CMITECH.
//              Please see umxAlgoGlobal.h for detailed definitions.
//
/////////////////////////////////////////////////////////////////////////////////////////

#ifndef UMXALGO_H
#define UMXALGO_H

#include "umxAlgoGlobal.h"
#include <Poco/Logger.h>
#include <Poco/AutoPtr.h>
#include <Poco/Util/AbstractConfiguration.h>

#if __GNUC__ >= 4
    #define UMXALGO_SHARED_EXPORT __attribute__ ((visibility ("default")))
#else
    #define UMXALGO_SHARED_EXPORT
#endif  // __GNUC_C >= 4
#define _UMXALGO_EXPORT UMXALGO_SHARED_EXPORT

#ifdef __cplusplus
extern "C" {
#endif

    void _UMXALGO_EXPORT umxAlgo_getVersion(unsigned int *major, unsigned int *minor, unsigned int *revision);
    // Get umxAlgo version and revision number for compatibility.
    // Application should check if major version number is consistent.
    //
    // major[out]
    // minor[out]
    // revision[out]

    int _UMXALGO_EXPORT umxAlgo_create(UMXALGO_HANDLE *phandle, Poco::Logger& logger, Poco::AutoPtr<Poco::Util::AbstractConfiguration> config, int irisType = UMXALGO_DISABLE, int faceType = UMXALGO_DISABLE);
    // Create umxAlgo.
    //
    // phandle[out] - UMXALGO_HANDLE value if successful. Otherwise, NULL.
    // logger[in] - Poco logger's pointer
    // config[in] - Poco config's pointer
    // irisType[in] - UMXALGO_DISABLE                                : None
    //                UMXALGO_IRIS_FOTONATION_MIRLIN_UNITEDKINGDOM   : Fotonation Mirlin algorithm
    //                UMXALGO_IRIS_NEUROTECH_VERIEYE_LITHUANIA       : Neurotech Verieye algorithm
    //                UMXALGO_IRIS_DELTAID_ACTIVEIRIS_USA            : DELTAID ActiveIris algorithm
    // faceType[in] - UMXALGO_DISABLE                                : None
    //                UMXALGO_FACE_NEC_NEOFACE_JAPAN                 : NEC Neoface algorithm
    //                UMXALGO_FACE_NEUROTECH_VERILOOK_LITHUANIA      : Neurotech Verilook algorithm
    //                UMXALGO_FACE_OPENCV                            : OpenCV algorithm
    //
    // Return value - UMXALGO_ERROR_CANNOT_ALLOC_MEMORY
    //                UMXALGO_ERROR_IN_ARGUMENTS
    //                UMXALGO_SUCCESS

    int _UMXALGO_EXPORT umxAlgo_destroy(UMXALGO_HANDLE handle);
    // Destroy umxAlgo.
    //
    // handle[in] - UMXALGO_HANDLE value
    //
    // Return value - UMXALGO_ERROR_INVALID_HANDLE
    //                UMXALGO_SUCCESS

    int _UMXALGO_EXPORT umxAlgo_iris_type(UMXALGO_HANDLE handle);
    // Get iris algorithm type.
    //
    // handle[in] - UMXALGO_HANDLE value
    //
    // Return value - UMXALGO_ERROR_INVALID_HANDLE
    //                UMXALGO_DISABLE
    //                UMXALGO_IRIS_FOTONATION_MIRLIN_UNITEDKINGDOM
    //                UXALGO_IRIS_NEUROTECH_VERIEYE_LITHUANIA
    //                UMXALGO_IRIS_DELTAID_ACTIVEIRIS_USA

    int _UMXALGO_EXPORT umxAlgo_iris_checkCompareResult(UMXALGO_HANDLE handle, UMXALGO_IRIS_COMPARE_TEMPLATE_OUTPUT outputResult, double matchThreshlod, double coOcclusionThreshold);
    // Check if score is okay.
    //
    // handle[in] - UMXALGO_HANDLE value
    // outputResult[out] - double hammingDistance : hammingDistance value (iris template compare score)
    //                     double coOcclusion : co-occlusion area (MIRLIN only)
    // matchThreshold[in] - threshold to compare
    // coOcclusionThreshold[in] - threshold about coOcclusion
    //
    // Return value - UMXALGO_ERROR_INVALID_HANDLE
    //                UMXALGO_IRIS_ERROR_COMPARE_RESULT
    //                UMXALGO_SUCCESS

    int _UMXALGO_EXPORT umxAlgo_iris_template_size(UMXALGO_HANDLE handle, int type);
    // Get template size as iris algorithm.
    //
    // handle[in] - UMXALGO_HANDLE value
    // type[in] - UMXALGO_IRIS_TYPE_ENROL_TEMPLATE : Fotonation Mirlin algorithm (MIRLIN only)
    //            UMXALGO_IRIS_TYPE_RECOG_TEMPLATE : Fotonation Mirlin algorithm (MIRLIN only)
    //
    // Return value - UMXALGO_ERROR_INVALID_HANDLE
    //                UMXALGO_IRIS_IRE_TEMPLATE_SIZE : DELTAID ActiveIris algorithm's iris template size
    //                UMXALGO_IRIS_MIR_ENROL_TEMPLATE_SIZE : Fotonation Mirlin algorithm's enrol iris template size
    //                UMXALGO_IRIS_MIR_MATCH_ROT_13_TEMPLATE_SIZE : Fotonation Mirlin algorithm's recog iris template size

    double _UMXALGO_EXPORT umxAlgo_iris_conv_matching_score(UMXALGO_HANDLE handle, double score);
    // Convert a score (ex. active iris score or others algorithm) to hanmming distance score (MIRLIN) notation.
    //
    // handle[in] - UMXALGO_HANDLE value
    // score[in] - iris template compare score to convert
    //
    // Return value - converted iris template compare score

    int _UMXALGO_EXPORT umxAlgo_iris_compare_max_hamming_distance(UMXALGO_HANDLE handle, double src, double dst);
    // Find higher quality iris template.
    //
    // handle[in] - UMXALGO_HANDLE value
    // src[in] - current score
    // dst[in] - old score
    //
    // Return value - UMXALGO_ERROR_INVALID_HANDLE
    //                UMXALGO_TRUE
    //                UMXALGO_FALSE

    int _UMXALGO_EXPORT umxAlgo_iris_getEnrollTemplate(UMXALGO_HANDLE handle, UMXALGO_IRIS_GET_TEMPLATE_INPUT* input, UMXALGO_IRIS_GET_ENROL_TEMPLATE_OUTPUT* output);
    // Get iris enroll-template for enrollment.
    //
    // handle[in] - UMXALGO_HANDLE value
    // input[in] - you should input iris informations (image width, height, image byte array, template size to generate, eye center x, y, radius, etc..)
    //             for getting iris template
    // output[out] - you can get the iris enroll-template for enrollment and informations about it (iris template byte array, template size, iris usable area, information if iris quality is ok, iris quality score)
    //
    // Return value - UMXALGO_ERROR_INVALID_HANDLE
    //                UMXALGO_IRIS_ERROR_WRONG_TEMPLATE_SIZE : wrong template size of "input[in]"
    //                UMXALGO_IRIS_ERROR_NO_INPUT_IMAGE : iris image of "input[in]" are NULL
    //                UMXALGO_IRIS_ERROR_FAIL_TO_GENERATE_TEMPLATE : fail to generate iris template
    //                UMXALGO_SUCCESS

    int _UMXALGO_EXPORT umxAlgo_iris_getMatchTemplate(UMXALGO_HANDLE handle, UMXALGO_IRIS_GET_TEMPLATE_INPUT* input, UMXALGO_IRIS_GET_TEMPLATE_OUTPUT* output);
    // Get iris match-template for recognition.
    //
    // handle[in] - UMXALGO_HANDLE value
    // input[in] - you should input iris informations (image width, height, image byte array, template size to generate, eye center x, y, radius, etc..)
    //             for getting iris template
    // output[out] - you can get the iris match-template for recognition and informations about it (iris template byte array, template size, iris usable area, information if iris quality is ok, iris quality score)
    //
    // Return value - UMXALGO_ERROR_INVALID_HANDLE
    //                UMXALGO_IRIS_ERROR_WRONG_TEMPLATE_SIZE : wrong template size of "input[in]"
    //                UMXALGO_IRIS_ERROR_NO_INPUT_IMAGE : iris image of "input[in]" are NULL
    //                UMXALGO_IRIS_ERROR_FAIL_TO_GENERATE_TEMPLATE : fail to generate iris template
    //                UMXALGO_SUCCESS

    int _UMXALGO_EXPORT umxAlgo_iris_compareTemplate(UMXALGO_HANDLE handle, UMXALGO_IRIS_COMPARE_TEMPLATE_INPUT* input, UMXALGO_IRIS_COMPARE_TEMPLATE_OUTPUT* output);
    // Compare enroll-template with match-template by IRIS Algorithm (MIRLIN, ACTIVEIRIS, VERILOOK).
    //
    // handle[in] - UMXALGO_HANDLE value
    // input[in] - you should input iris informations (image width, height, image byte array, template size to generate, eye center x, y, radius, etc..)
    //             for getting iris template
    // output[out] - you can get the iris match-template for recognition and informations about it (iris template byte array, template size, iris usable area, information if iris quality is ok, iris quality score)
    //
    // Return value - UMXALGO_ERROR_INVALID_HANDLE
    //                UMXALGO_IRIS_ERROR_WRONG_TEMPLATE_SIZE : wrong template size of "input[in]"
    //                UMXALGO_IRIS_ERROR_NO_INPUT_IMAGE : iris image of "input[in]" are NULL
    //                UMXALGO_IRIS_ERROR_FAIL_TO_GENERATE_TEMPLATE : fail to generate iris template
    //                UMXALGO_SUCCESS

    int _UMXALGO_EXPORT umxAlgo_conv_deserializeTemplate(UMXALGO_HANDLE handle, const char* serializeData, const int serializeSize, char* retDeserialize, int deserializeBufferSize);
    // converting iris feature data
    //
    // handle[in] - UMXALGO_HANDLE value
    // input[in] - serialize feature data, serialize feature data size, deserialize feature data, deserialize buffer size
    //
    // Return value - UMXALGO_ERROR_INVALID_HANDLE
    //                UMXALGO_IRIS_ERROR_FAIL_TO_GENERATE_TEMPLATE : fail to generate iris template
    //                UMXALGO_SUCCESS

    int _UMXALGO_EXPORT umxAlgo_face_type(UMXALGO_HANDLE handle);
    // Get face algorithm type.
    //
    // handle[in] - UMXALGO_HANDLE value
    //
    // Return value - UMXALGO_ERROR_INVALID_HANDLE
    //                UMXALGO_DISABLE
    //                UMXALGO_FACE_NEUROTECH_VERILOOK_LITHUANIA
    //                UMXALGO_FACE_NEC_NEOFACE_JAPAN
    //                UMXALGO_FACE_OPENCV

    int _UMXALGO_EXPORT umxAlgo_face_setParamEyesMinWidth(UMXALGO_HANDLE handle, int minWidth);
    // Set minimum eyes width.
    //
    // handle[in] - UMXALGO_HANDLE value
    // minWidth[in] - minimum eyes width
    //
    // Return value - UMXALGO_ERROR_INVALID_HANDLE
    //                UMXALGO_FACE_ERROR_OUT_OF_RANGE_MIN_EYES_WIDTH
    //                UMXALGO_SUCCESS

    int _UMXALGO_EXPORT umxAlgo_face_setParamEyesMaxWidth(UMXALGO_HANDLE handle, int maxWidth);
    // Set maximum eyes width.
    //
    // handle[in] - UMXALGO_HANDLE value
    // maxWidth[in] - maximum eyes width
    //
    // Return value - UMXALGO_ERROR_INVALID_HANDLE
    //                UMXALGO_FACE_ERROR_OUT_OF_RANGE_MAX_EYES_WIDTH
    //                UMXALGO_SUCCESS

    int _UMXALGO_EXPORT umxAlgo_face_find(UMXALGO_HANDLE handle, UMXALGO_FACE_FIND_INPUT* faceFindInput, UMXALGO_FACE_FIND_OUTPUT* faceFindOutput);
    // Find face.
    //
    // handle[in] - UMXALGO_HANDLE value
    // faceFindInput[in] - input data for finding face (for detail, refer to umxAlgoGlobal.h UMXALGO_FACE_FIND_INPUT please)
    // faceFindOutput[out] - output data of found face (for detail, refer to umxAlgoGlobal.h UMXALGO_FACE_FIND_OUTPUT please)
    //
    // Return value - UMXALGO_FACE_NEO_ERROR_NOT_INITIALIZE : Neoface license initialize error
    //                UMXALGO_FACE_NEO_ERROR_UNKNOWN : Neoface license or fail to find face error
    //                UMXALGO_FACE_ERROR_FAIL_TO_FIND_FACE : Face algorithm didn't find face
    //                UMXALGO_SUCCESS

    int _UMXALGO_EXPORT umxAlgo_face_getLEyePosition(UMXALGO_HANDLE handle, UMXALGO_POINT_XY* leye);
    // Get left eye position of a face image after finding face (umxAlgo_face_find()).
    //
    // handle[in] - UMXALGO_HANDLE value
    // leye[out] - left eye position
    //
    // Return value - UMXALGO_ERROR_INVALID_HANDLE
    //                UMXALGO_SUCCESS

    int _UMXALGO_EXPORT umxAlgo_face_getREyePosition(UMXALGO_HANDLE handle, UMXALGO_POINT_XY* reye);
    // Get right eye position of a face image after finding face (umxAlgo_face_find()).
    //
    // handle[in] - UMXALGO_HANDLE value
    // reye[out] - right eye position
    //
    // Return value - UMXALGO_ERROR_INVALID_HANDLE
    //                UMXALGO_SUCCESS

    int _UMXALGO_EXPORT umxAlgo_face_getFaceScore(UMXALGO_HANDLE handle, float* faceScore);
    // Get face score of a face image after finding face (umxAlgo_face_find()).
    //
    // handle[in] - UMXALGO_HANDLE value
    // faceScore[out] - face score
    //
    // Return value - UMXALGO_ERROR_INVALID_HANDLE
    //                UMXALGO_SUCCESS

    int _UMXALGO_EXPORT umxAlgo_face_getTemplate(UMXALGO_HANDLE handle, UMXALGO_FACE_FIND_INPUT* faceFindInput, UMXALGO_FACE_FIND_OUTPUT* faceFindOutput, UMXALGO_FACE_GET_TEMPLATE_OUTPUT* faceGetTemplateOutput);
    // Get face template of a face image.
    //
    // handle[in] - UMXALGO_HANDLE value
    // faceFindInput[in] - input data for finding face (for detail, refer to umxAlgoGlobal.h UMXALGO_FACE_FIND_INPUT please)
    // faceFindOutput[out] - output data of found face (for detail, refer to umxAlgoGlobal.h UMXALGO_FACE_FIND_OUTPUT please)
    // faceGetTemplateOutput[out] - output data of made face template (for detail, refer to  umxAlgoGlobal.h UMXALGO_FACE_GET_TEMPLATE_OUTPUT please)
    //
    // Return value - UMXALGO_ERROR_INVALID_HANDLE
    //                UMXALGO_FACE_NEO_ERROR_NOT_INITIALIZE : Neoface license initialize error
    //                UMXALGO_FACE_NEO_ERROR_UNKNOWN : Neoface license or fail to find face error
    //                UMXALGO_FACE_NEO_ERROR_FAIL_TO_SET_FEATURE : fail to set feature
    //                UMXALGO_FACE_NEO_ERROR_FAIL_TO_SERIALIZE_FEATURE : fail to serialize feature
    //                UMXALGO_FACE_ERROR_FAIL_TO_FIND_FACE : Face algorithm didn't find face
    //                UMXALGO_FACE_ERROR_FAIL_TO_GET_FACE_TEMPLATE : Face algorithm was fail to get face template from face image
    //                UMXALGO_SUCCESS

    int _UMXALGO_EXPORT umxAlgo_face_compareTemplate(UMXALGO_HANDLE handle, const unsigned char* liveFeature, const int liveFeatureSize, const unsigned char* enrolFeature, const int enrolFeatureSize, const int faceThreshold, float* retScore);
    // Compare between a face template and another face template.
    //
    // handle[in] - UMXALGO_HANDLE value
    // liveFeature[in] - live (current) face template's byte array
    // liveFeatureSize[in] - live (current) face template's size
    // enrolFeature[in] - saved (database) face template's byte array
    // enrolFeatureSize[in] - saved (database) face template's size
    // faceThreshold[in] - compare score threshold
    // retScore[out] - compared score between liveFeature and enrolFeature
    //
    // Return value - UMXALGO_ERROR_INVALID_HANDLE
    //                UMXALGO_FACE_NEO_ERROR_CREATE_CVERIFIER : fail to create CVERIFIER class of Neoface
    //                UMXALGO_FACE_NEO_ERROR_FAIL_TO_VERIFY_FACE_FEATURE : fail to verify face features (templates)
    //                UMXALGO_FACE_NEO_ERROR_WRONG_SCORE : compared score is out of range
    //                UMXALGO_FACE_NEO_ERROR_LESS_THAN_THRESHOLD_SCORE : compared score is less than threshold score
    //                UMXALGO_FACE_ERROR_FAIL_TO_COMPARE_FACE_TEMPLATES : fail to compare face templates
    //                UMXALGO_SUCCESS


    // EF-45(bkko)-28 : modify face recognition mathod of neurotech algorihtm for matching speed vvv
    int _UMXALGO_EXPORT umxAlgo_face_setSourceTemplate(UMXALGO_HANDLE handle, const unsigned char* liveFeature, const int liveFeatureSize);
    int _UMXALGO_EXPORT umxAlgo_face_setDestinationTemplate(UMXALGO_HANDLE handle, const unsigned char* enrolFeature, const int enrolFeatureSize, const unsigned char* uuid);
    int _UMXALGO_EXPORT umxAlgo_face_identifyTemplate(UMXALGO_HANDLE handle, const int faceThreshold, float* retScore, unsigned char* retUuid);
    // EF-45(bkko)-28 : modify face recognition mathod of neurotech algorihtm for matching speed ^^^

#ifdef __cplusplus
} // extern "C"
#endif

#endif // UMXALGO_H
