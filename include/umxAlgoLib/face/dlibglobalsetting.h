/**
 *
 * @file dlibglobalsetting.h
 *
 * Copyright (c) 2017 CMITECH Inc. All Rights Reserved.
 *
 * Confidential Information
 *
 * All parts of the CMITECH program source are protected by copyright law and
 * all rights are reserved. Redistribution and use in source and binary forms,
 * in whole or in part, with or without modification, are not permitted without
 * prior consent, in writing, from CMITECH Inc.
 *
 */

#ifndef DLIBGLOBALSETTING_H
#define DLIBGLOBALSETTING_H

//#define FACE_RECOG_SPEED_TEST

////////////////////////////////////////////////////////////////////// /////////
///////////////////                                     /////////////// ////////
//////////////////           HEADER FILES                /////////////// ///////
///////////////////                                     /////////////// ////////
////////////////////////////////////////////////////////////////////// /////////

#include <omp.h>
#include <vector>

#if defined (FACE_RECOG_SPEED_TEST)
#include <Poco/Logger.h>
#include <Poco/FileChannel.h>
#include <Poco/FormattingChannel.h>
#include <Poco/PatternFormatter.h>
#include <Poco/AutoPtr.h>
#include <Poco/FileStream.h>

using Poco::Logger;
using Poco::FileChannel;
using Poco::FormattingChannel;
using Poco::PatternFormatter;
using Poco::AutoPtr;

static unsigned int _totalTime1  = 0;
static unsigned int _totalTime2  = 0;
static unsigned int _totalTime3  = 0;
static unsigned int _totalTime4  = 0;
static unsigned int _totalTime5  = 0;
static unsigned int _totalTime6  = 0;
#endif

////////////////////////////////////////////////////////////////////// /////////
///////////////////                                     /////////////// ////////
//////////////////         MACRO DEFINITIONS             /////////////// ///////
///////////////////                                     /////////////// ////////
////////////////////////////////////////////////////////////////////// /////////

#define FEATURE_USING_LOCAL_OPENMP1     //_totalTime1
//#define FEATURE_USING_LOCAL_OPENMP2   //_totalTime2
//#define FEATURE_USING_LOCAL_OPENMP3     //_totalTime3
//#define FEATURE_USING_LOCAL_OPENMP13    //_totalTime4
//#define FEATURE_USING_LOCAL_OPENMP39    //_totalTime5
#define FEATURE_USING_LOCAL_OPENMP41    //_totalTime6

////////////////////////////////////////////////////////////////////// /////////
///////////////////                                     /////////////// ////////
//////////////////       GLOBAL TYPE DEFINITIONS         /////////////// ///////
///////////////////                                     /////////////// ////////
////////////////////////////////////////////////////////////////////// /////////

typedef struct {
    long top;
	long left;
	long right;
	long bottom;
} rectInfo_t;

typedef struct {
    unsigned long level;
    rectInfo_t rect;
} detInfo_t;

static bool glevelSetMode;

static unsigned long gDiffPramidLevel;
static std::vector<detInfo_t> gFaceDetInfo;
static std::vector<detInfo_t> gEyeDetInfo;

////////////////////////////////////////////////////////////////////// /////////
///////////////////                                     /////////////// ////////
//////////////////        EXPORT GLOBAL VARIABLES        /////////////// ///////
///////////////////                                     /////////////// ////////
////////////////////////////////////////////////////////////////////// /////////


////////////////////////////////////////////////////////////////////// /////////
///////////////////                                     /////////////// ////////
//////////////////        EXPORT GLOBAL FUNTIONS         /////////////// ///////
///////////////////                                     /////////////// ////////
////////////////////////////////////////////////////////////////////// /////////


////////////////////////////////////////////////////////////////////// /////////
///////////////////                                     /////////////// ////////
//////////////////          CLASS DEFINITIONS            /////////////// ///////
///////////////////                                     /////////////// ////////
////////////////////////////////////////////////////////////////////// /////////


class dlibGlobalSetting
{
public:
    dlibGlobalSetting(){}
    ~dlibGlobalSetting(){}

    void setFaceDetInfo(std::vector<detInfo_t> det_info);
    void setEyeDetInfo(std::vector<detInfo_t> det_info);
    void setPyramidLevel(bool flag);
    void setPyramidLevelValue(long start_level, long end_level);

    bool getPyramidLevel(void);

    unsigned long getPyramidLevelValue();

    std::vector<detInfo_t> getFaceDetInfo();
    std::vector<detInfo_t> getEyeDetInfo();

    #if defined(FACE_RECOG_SPEED_TEST)
    unsigned int  getTotalTime(unsigned int section);
    void 		  AddTime(unsigned int time, unsigned int section);
    void          InitTime();
    #endif
public:
};

#endif // DLIBGLOBALSETTING_H
