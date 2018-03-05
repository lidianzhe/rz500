////////////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2011~2012 CMITECH Co., Ltd.
// All rights reserved.
//
// Licensees holding valid CMITECH's CMIRIS SDK licenses may use this file in
// accordance with the CMIRIS SDK License Agreement provided with the
// Software or, alternatively, in accordance with the terms contained in
// an agreement between you and CMITECH.
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
// umxAlgoGlobal.h
//
// Version 1.0.0   Mar. 23, 2016
//                 Initial Public Release
//
// Version 1.0.0   Mar. 23, 2016
//
//
// Description: umxAlgoGlobal.h defines the constants and struct for umxAlgo.h
//              Please see umxAlgo.h for detailed interface.
//
////////////////////////////////////////////////////////////////////////////////////////

#ifndef UMXALGOGLOBAL_H
#define UMXALGOGLOBAL_H

typedef void *UMXALGO_HANDLE;

#include "umxCommonLib/umxCommonGlobal.h"

////////////////////////////////////////////////////////////////////////////////////////
// boolean type information
////////////////////////////////////////////////////////////////////////////////////////

#define UMXALGO_TRUE                                 1

#define UMXALGO_FALSE                                0

#define UMXALGO_UNKNOWN                             -1

////////////////////////////////////////////////////////////////////////////////////////
// array type information
////////////////////////////////////////////////////////////////////////////////////////

#define UMXALGO_IRIS_LEFT_ARR                        0

#define UMXALGO_IRIS_RIGHT_ARR                       1

#define UMXALGO_FACE_LED_OFF_ARR                     0

#define UMXALGO_FACE_LED_ON_ARR                      1

////////////////////////////////////////////////////////////////////////////////////////
// type define to select algorithm
////////////////////////////////////////////////////////////////////////////////////////

#define UMXALGO_DISABLE                                            -1

#define UMXALGO_IRIS_FOTONATION_MIRLIN_UNITEDKINGDOM                0

#define UMXALGO_IRIS_NEUROTECH_VERIEYE_LITHUANIA                    1

#define UMXALGO_IRIS_DELTAID_ACTIVEIRIS_USA                         2

#define UMXALGO_FACE_NEUROTECH_VERILOOK_LITHUANIA                   3

#define UMXALGO_FACE_NEC_NEOFACE_JAPAN                              4

#define UMXALGO_FACE_OPENCV                                         5

#define UMXALGO_FACE_EYE_DLIB                                           6
//#define UMXALGO_FACE_DLIB											6 //by dhkim
//#define UMXALGO_EYE_DLIB                                          7 //by dhkim

////////////////////////////////////////////////////////////////////////////////////////
// template type (Enrol or Recog)
////////////////////////////////////////////////////////////////////////////////////////

#define UMXALGO_IRIS_TYPE_ENROL_TEMPLATE                            1

#define UMXALGO_IRIS_TYPE_RECOG_TEMPLATE                            2

////////////////////////////////////////////////////////////////////////////////////////
// Iris : Global
////////////////////////////////////////////////////////////////////////////////////////

//#define UMXALGO_IRIS_MAX_TEMPLATE_SIZE                          2048
#define UMXALGO_IRIS_MAX_TEMPLATE_SIZE                          4096

////////////////////////////////////////////////////////////////////////////////////////
// Iris : ActiveIris (DeltaID)
////////////////////////////////////////////////////////////////////////////////////////

#define UMXALGO_IRIS_IRE_TEMPLATE_SIZE                          2048

////////////////////////////////////////////////////////////////////////////////////////
// Iris : VeriEye (Neurotechnology)
////////////////////////////////////////////////////////////////////////////////////////

#define UMXALGO_IRIS_NT_TEMPLATE_SIZE                          4096
#define UMXALGO_IRIS_NT_MINIUM_MATCH_SCORE                          48

////////////////////////////////////////////////////////////////////////////////////////
// Iris : Mirlin (Fotonation)
////////////////////////////////////////////////////////////////////////////////////////

#define UMXALGO_IRIS_MIR_ENROL_TEMPLATE_SIZE                  579

#define UMXALGO_IRIS_MIR_MATCH_ROT_0_TEMPLATE_SIZE            579   // 0 rotations

#define UMXALGO_IRIS_MIR_MATCH_ROT_5_TEMPLATE_SIZE            2879  // 5 rotations

#define UMXALGO_IRIS_MIR_MATCH_ROT_7_TEMPLATE_SIZE            4029  // 7 rotations

#define UMXALGO_IRIS_MIR_MATCH_ROT_9_TEMPLATE_SIZE            5179  // 9 rotations

#define UMXALGO_IRIS_MIR_MATCH_ROT_13_TEMPLATE_SIZE           7479  // 13 rotations - default

#define UMXALGO_IRIS_MIR_MATCH_ROT_25_TEMPLATE_SIZE           14379 // 25 rotations

#define UMXALGO_IRIS_MIR_DO_NOT_SHOW_SEGMENTATION             0

#define UMXALGO_IRIS_MIR_SHOW_SEGMENTATION                    1

////////////////////////////////////////////////////////////////////////////////////////
// Face : Global
////////////////////////////////////////////////////////////////////////////////////////

#define UMXALGO_FACE_TEMPLATE_SIZE                      1024*4

#define UMXALGO_FACE_NEUROTECH_VERILOOK                         "verilook"
#define UMXALGO_FACE_NEC_NEOFACE                                "neoface"
#define UMXALGO_FACE_DLIB 										"dlib" 	   //by dhkim
#define UMXALGO_FACE_DLIBFACE									"dlibface" //by dhkim
#define UMXALGO_FACE_DLIBEYE									"dlibeye" //by dhkim

////////////////////////////////////////////////////////////////////////////////////////
// Threads
////////////////////////////////////////////////////////////////////////////////////////
#define ALGO_SUB_THREADS_MAX        128
#define ALGO_SUB_THREADS_CNT        4

////////////////////////////////////////////////////////////////////////////////////////
// Image format
////////////////////////////////////////////////////////////////////////////////////////
#define CMID_IRIS_BMP_FORMAT                                        1
#define CMID_IRIS_RAW_FORMAT                                        2

#define CMID_LEFT_EYE               1
#define CMID_RIGHT_EYE              2
#define CMID_BOTH_EYE               3

////////////////////////////////////////////////////////////////////////////////////////
// structs
////////////////////////////////////////////////////////////////////////////////////////

// Iris : Global
typedef struct _UMXALGO_IRIS_GET_TEMPLATE_INPUT {
    int cbSize;                   // size of this struct
    unsigned char *image;
    int width, height;
    int templateSize;
    int centerX, centerY, radius;
    int showSegmentation;
} UMXALGO_IRIS_GET_TEMPLATE_INPUT;

typedef struct _UMXALGO_IRIS_GET_ENROL_TEMPLATE_OUTPUT {
    int cbSize;                   // size of this struct
    //unsigned char temPlate[UMXALGO_IRIS_MIR_ENROL_TEMPLATE_SIZE];
    unsigned char temPlate[UMXALGO_IRIS_MAX_TEMPLATE_SIZE];// EF-45(bkko)-19 : Added Iris recognition engine for DeltaID
    int size;
    double usableIrisArea;
    bool qualityOk;
    double qualityScore;
    // added by JJC 20161008
    int irisCenterX;
    int irisCenterY;
    int irisDiameter;
    int pupilCenterX;
    int pupilCenterY;
    int pupilDiameter;
} UMXALGO_IRIS_GET_ENROL_TEMPLATE_OUTPUT;

typedef struct _UMXALGO_IRIS_GET_TEMPLATE_OUTPUT {
    int cbSize;                   // size of this struct
    unsigned char* temPlate;
    int size;
    double usableIrisArea;
    bool qualityOk;
    double qualityScore;
    // added by UK 20170928
    int irisCenterX;
    int irisCenterY;
    int irisDiameter;
    int pupilCenterX;
    int pupilCenterY;
    int pupilDiameter;
} UMXALGO_IRIS_GET_TEMPLATE_OUTPUT;

typedef struct _UMXALGO_IRIS_GET_TEMPLATE {
    UMXALGO_IRIS_GET_TEMPLATE_INPUT*    input;
    UMXALGO_IRIS_GET_TEMPLATE_OUTPUT*   output;
    UMXALGO_IRIS_GET_ENROL_TEMPLATE_OUTPUT* outputEnroll;
} UMXALGO_IRIS_GET_TEMPLATE;

typedef struct _UMXALGO_IRIS_COMPARE_TEMPLATE_INPUT {
    int cbSize;                   // size of this struct
    unsigned char *enrolTemplate;
    unsigned char *matchTemplate;
    int matchTemplateSize;
} UMXALGO_IRIS_COMPARE_TEMPLATE_INPUT;

typedef struct _UMXALGO_IRIS_COMPARE_TEMPLATE_OUTPUT {
    int cbSize;                   // size of this struct
    double hammingDistance;
    double coOcclusion;
} UMXALGO_IRIS_COMPARE_TEMPLATE_OUTPUT;

typedef struct _UMXALGO_IRIS_IDENTIFY_INFO {
    UMXALGO_IRIS_GET_TEMPLATE    left;
    UMXALGO_IRIS_GET_TEMPLATE    right;
    int eitherEyeEnabledStatus;
    double matchThreshlod;
    char uuid[256];    // 1:1
//    UMXALGO_IRIS_COMPARE_TEMPLATE_INPUT* left_verificationData;  // 1:1
//    UMXALGO_IRIS_COMPARE_TEMPLATE_INPUT* right_verificationData;  // 1:1
    // return value
    char retUuid[ALGO_SUB_THREADS_MAX][256];
    double retLeftScore[ALGO_SUB_THREADS_MAX];
    double retRightScore[ALGO_SUB_THREADS_MAX];
    double retMergedScore[ALGO_SUB_THREADS_MAX];
    int retBestArray;
    bool duplicate;
} UMXALGO_IRIS_IDENTIFY_INFO;

// Face : Global
typedef struct _UMXALGO_POINT_XY
{
    int  x;
    int  y;
} UMXALGO_POINT_XY;

typedef struct _UMXALGO_FACE_FIND_INPUT {
    int cbSize;
    unsigned char* image;
    int width;
    int height;
    int bmpBit;
}UMXALGO_FACE_FIND_INPUT;

typedef struct _UMXALGO_FACE_FIND_OUTPUT {
    int cbSize;
    int isFaceFound;
    int eyeWidth;
    int leftEyeX;            // left eye's x coordinate
    int leftEyeY;            // left eye's y coordinate
    int rightEyeX;           // right eye's x coordinate which has smaller value than leftEyeX
    int rightEyeY;           // right eye's y coordinate which has smaller value than leftEyeY
    int leftFaceX;
    int rightFaceX;
    int topFaceY;
    int bottomFaceY;
    float roll;              // angle between the horizontal axis and the line connecting left with right eye.
                             // For enrollment, this should be between -9 and +9 degree
                             // For recognition, it can be relaxed to +/-15 degree.
    float tilt;
    float pan;               // angle between the vertical axis and the line connecting left with right eye.
                             // For enrollment, this should be between -9 and +9 degree
                             // For recognition, it can be relaxed to +/-15 degree.
    float faceScore;             // represents the dependability of face. The recommended value is bigger than 0.45
    float frontalFaceScore;  // indicates how much the face is facing front.
                             // It is between 0 and 1 and 1 means the face is facing straight front.
                             // The recommended frontalFaceScore should be bigger than 0.4
    int ledState;
}UMXALGO_FACE_FIND_OUTPUT;

typedef struct _UMXALGO_FACE_GET_TEMPLATE_OUTPUT {
    int cbSize;
    int isTemplateGenerated;
    unsigned char temPlate[UMXALGO_FACE_TEMPLATE_SIZE];
    int size;        // typically 579 and shall not be bigger than 1024
}UMXALGO_FACE_GET_TEMPLATE_OUTPUT;

enum
{
    SUB_T_IDLE = 10,
    SUB_T_BUSY,
    SUB_T_COMPLETE
};

////////////////////////////////////////////////////////////////////////////////////////
// Return values - errors
////////////////////////////////////////////////////////////////////////////////////////

#define UMXALGO_SUCCESS                                             0           // success

// Global
#define UMXALGO_ERROR_CANNOT_ALLOC_MEMORY                           -1          // handler was not created

#define UMXALGO_ERROR_INVALID_HANDLE                                -2          // Invalid UMXALGO_HANDLE in argument

#define UMXALGO_ERROR_IN_ARGUMENTS                                  -3          // Error in arguments

// Iris : Global
#define UMXALGO_IRIS_ERROR_WRONG_TEMPLATE_SIZE                      -1000       // wrong template size

#define UMXALGO_IRIS_ERROR_NO_INPUT_IMAGE                           -1001       // no input image

#define UMXALGO_IRIS_ERROR_FAIL_TO_GENERATE_TEMPLATE                -1002       // fail to generate iris template

#define UMXALGO_IRIS_ERROR_COMPARE_RESULT                           -1003       // invalid compare result

#define UMXALGO_IRIS_ERROR_FAIL_TO_COMPARE_TEMPLATES                -1004       // fail to compare templates

// Iris : Mirlin (Fotonation)
#define UMXALGO_IRIS_MIR_ERROR_INVALID_LICENSE                      -2000       // invalid mirlin license

#define UMXALGO_IRIS_MIR_ERROR_EMPTY_ENROL_TEMPLATE                 -2001       // empty enrol iris template

// Face : Global
#define UMXALGO_FACE_ERROR_OUT_OF_RANGE_MIN_EYES_WIDTH              -4000       // eyes width is out of minimum range

#define UMXALGO_FACE_ERROR_OUT_OF_RANGE_MAX_EYES_WIDTH              -4001       // eyes width is out of maximum range

#define UMXALGO_FACE_ERROR_FAIL_TO_FIND_FACE                        -4002       // fail to find face

#define UMXALGO_FACE_ERROR_FAIL_TO_GET_FACE_TEMPLATE                -4003       // fail to get face template (features)

#define UMXALGO_FACE_ERROR_FAIL_TO_COMPARE_FACE_TEMPLATES           -4004       // fail to compare face templates

// Face : NeoFace (NEC)
#define UMXALGO_FACE_NEO_ERROR_UNKNOWN                              -5000       // Neoface unknown error

#define UMXALGO_FACE_NEO_ERROR_NOT_INITIALIZE                       -5001       // Neoface license initialize error

#define UMXALGO_FACE_NEO_ERROR_CREATE_CFACEINFO                     -5002       // fail to create Neoface's CFaceInfo class

#define UMXALGO_FACE_NEO_ERROR_CREATE_CFACEFEATURE                  -5003       // fail to create Neoface's CFaceFeature class

#define UMXALGO_FACE_NEO_ERROR_FAIL_TO_SET_FEATURE                  -5004       // fail to set feature by Neoface

#define UMXALGO_FACE_NEO_ERROR_FAIL_TO_SERIALIZE_FEATURE            -5005       // fail to serialize feature by Neoface

#define UMXALGO_FACE_NEO_ERROR_CREATE_CVERIFIER                     -5006       // fail to create Neoface's CVerifier class

#define UMXALGO_FACE_NEO_ERROR_FAIL_TO_VERIFY_FACE_FEATURE          -5007       // fail to verify face features

#define UMXALGO_FACE_NEO_ERROR_WRONG_SCORE                          -5008       // wrong score (out of normal range)

#define UMXALGO_FACE_NEO_ERROR_LESS_THAN_THRESHOLD_SCORE            -5009       // score is less than threshold

#define UMXALGO_FACE_NEO_ERROR_INSUFFICIENT_FACESCORE               -5010       // insufficient face score

#define UMXALGO_FACE_NEO_ERROR_INSUFFICIENT_FACEROLL                -5011       // insufficient face roll

#define UMXALGO_FACE_NEO_ERROR_INSUFFICIENT_FACETILT                -5012       // insufficient face tilt

namespace UMXAlgorithm
{
    class IAlgorithm
    {
    public:
        virtual std::vector<UMXCommon::SubjectData>* getIrisSubjectData()=0;
        virtual Poco::Mutex* getIrisSubjectMutex()=0;
    };
}

#endif // UMXALGOGLOBAL_H
