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
// umxDBGlobal.h
//
// Version 1.0.0   Mar. 03, 2016
//                 Initial Public Release
//
// Version 1.0.0   Mar. 03, 2016
//
//
// Description: umxDBGlobal.h defines the constants and struct for umxDB.h
//              Please see umxDB.h for detailed interface.
//
////////////////////////////////////////////////////////////////////////////////////////

#ifndef UMXDBGLOBAL_H
#define UMXDBGLOBAL_H

typedef void *UMXDB_HANDLE;

////////////////////////////////////////////////////////////////////////////////////////
// Return values
////////////////////////////////////////////////////////////////////////////////////////

#define UMXDB_SUCCESS                                         0

#define UMXDB_FAIL                                           -1

#define UMXDB_ERROR_INVALID_HANDLE                           -2

#define UMXDB_ERROR_CANNOT_ALLOC_MEMORY                      -3

#define UMXDB_ERROR_IN_ARGUMENTS                             -4

#define UMXDB_ERROR_DELETE                                -2001

#define UMXDB_ERROR_EXIST_UUID                            -2002

#define UMXDB_ERROR_NO_EXIST_UUID                         -2003

#define UMXDB_ERROR_EXIST_UUID_AND_SUBID                  -2004

#define UMXDB_ERROR_NO_EXIST_UUID_AND_SUBID               -2005

#define UMXDB_ERROR_NO_FACE_INFO                          -2006

#define UMXDB_ERROR_NO_FACE_FEATURE                       -2007

#define UMXDB_ERROR_FAIL_TO_INSERT_FACE                   -2008

#define UMXDB_ERROR_FAIL_TO_INSERT_SUBJECT                -2009

#define UMXDB_ERROR_FAIL_TO_INSERT_EVENT_LOG              -2010

#define UMXDB_ERROR_UUID_IS_EMPTY                         -2011

#define UMXDB_ERROR_SUBID_IS_EMPTY                        -2012

#define UMXDB_ERROR_FACEINFO_NULL                         -2013

#define UMXDB_ERROR_FACETEMPLATE_NULL                     -2014

#define UMXDB_ERROR_IMAGEPATH_IS_EMPTY                    -2015

#define UMXDB_ERROR_ALREADY_EXIST_FACE                    -2016

#define UMXDB_ERROR_FACETEMPLATE_SIZE_OUT_OF_RANGE        -2017

#define UMXDB_ERROR_FACEDATA_NULL                         -2018

#define UMXDB_ERROR_FACETEMPLATE_DATA_SIZE_OUT_OF_RANGE   -2019

#define UMXDB_ERROR_SUBJECTDATA_NULL                      -2020

#define UMXDB_ERROR_LASTNAME_IS_EMPTY                     -2021

#define UMXDB_ERROR_LEFT_TEMPLATE_SIZE_OUT_OF_RANGE       -2022

#define UMXDB_ERROR_LEFT_IMAGE_PATH_IS_EMPTY              -2023

#define UMXDB_ERROR_RIGHT_TEMPLATE_SIZE_OUT_OF_RANGE      -2024

#define UMXDB_ERROR_RIGHT_IMAGE_PATH_IS_EMPTY             -2025

#define UMXDB_ERROR_IMAGEINFO_NULL                        -2026

#define UMXDB_ERROR_ENROL_TEMPLATES_NULL                            -2027

#define UMXDB_ERROR_LEFT_IMAGEPATH_IS_EMPTY                         -2028

#define UMXDB_ERROR_RIGHT_IMAGEPATH_IS_EMPTY                        -2029

#define UMXDB_ERROR_LEFT_TEMPLATE_IS_NULL                           -2030

#define UMXDB_ERROR_RIGHT_TEMPLATE_IS_NULL                          -2031

#define UMXDB_ERROR_NOT_EXIST_FACE                                  -2032

#define UMXDB_ERROR_NOT_MATCH_FEATUREDATA_SIZE_AND_SIZE_INFO        -2033

#define UMXDB_ERROR_FAIL_TO_UPDATE_SUBJECT                          -2034

#endif // UMXDBGLOBAL_H
