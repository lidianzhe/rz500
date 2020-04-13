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

#define UMXDB_SUCCESS                                                                               0
#define UMXDB_ERROR_INVALID_HANDLE                                                                 -1
#define UMXDB_ERROR_CANNOT_ALLOC_MEMORY                                                            -2

#define UMXDB_ERROR_IN_ARGUMENTS_MAJOR_NULL                                                       -10
#define UMXDB_ERROR_IN_ARGUMENTS_MINOR_NULL                                                       -11
#define UMXDB_ERROR_IN_ARGUMENTS_REVISION_NULL                                                    -12

#define UMXDB_ERROR_IN_ARGUMENTS_SUBJECT_NULL_POINTER                                             -20
#define UMXDB_ERROR_IN_ARGUMENTS_SUBJECT_VECTOR_NULL_POINTER                                      -21
#define UMXDB_ERROR_IN_ARGUMENTS_SUBJECT_UUID_EXIST_NULL_POINTER                                  -22
#define UMXDB_ERROR_IN_ARGUMENTS_SUBJECT_UUID_VECTOR_NULL_POINTER                                 -23
#define UMXDB_ERROR_IN_ARGUMENTS_SUBJECT_COUNT_NULL_POINTER                                       -24

#define UMXDB_ERROR_IN_ARGUMENTS_FACE_NULL_POINTER                                                -30
#define UMXDB_ERROR_IN_ARGUMENTS_FACE_VECTOR_NULL_POINTER                                         -31
#define UMXDB_ERROR_IN_ARGUMENTS_FACE_UUID_AND_SUBID_COUNT_NULL_POINTER                           -32
#define UMXDB_ERROR_IN_ARGUMENTS_FACE_COUNT_NULL_POINTER                                          -33

#define UMXDB_ERROR_IN_ARGUMENTS_USERINFO_NULL_POINTER                                            -40
#define UMXDB_ERROR_IN_ARGUMENTS_USERINFO_VECTOR_NULL_POINTER                                     -41
#define UMXDB_ERROR_IN_ARGUMENTS_USERINFO_ADMIN_COUNT_NULL_POINTER                                -42
#define UMXDB_ERROR_IN_ARGUMENTS_USERINFO_COUNT_NULL_POINTER                                      -43

#define UMXDB_ERROR_IN_ARGUMENTS_EVENTLOG_LOGID_NULL_POINTER                                      -50
#define UMXDB_ERROR_IN_ARGUMENTS_EVENTLOG_NULL_POINTER                                            -51
#define UMXDB_ERROR_IN_ARGUMENTS_EVENTLOG_VECTOR_NULL_POINTER                                     -52
#define UMXDB_ERROR_IN_ARGUMENTS_EVENTLOG_LOG_COUNT_NULL_POINTER                                  -53
#define UMXDB_ERROR_IN_ARGUMENTS_EVENTLOG_Image_LOG_COUNT_NULL_POINTER                            -54

#define UMXDB_ERROR_IN_ARGUMENTS_IMAGECAPTURE_VECTOR_NULL_POINTER                                 -60

#define UMXDB_ERROR_TEXT_ENCRYPTION                                                               -70

#define UMXDB_ERROR_UUID_NULL_STRING                                                             -100
#define UMXDB_ERROR_PAGE_INVALID                                                                 -101
#define UMXDB_ERROR_PAGESIZE_INVALID                                                             -102

#define UMXDB_ERROR_SUBJECT_COUNT_UUID                                                           -200
#define UMXDB_ERROR_SUBJECT_COUNT_UUID_NO_EXIST                                                  -201
#define UMXDB_ERROR_SUBJECT_COUNT_UUID_ALREADY_EXIST                                             -202
#define UMXDB_ERROR_SUBJECT_COUNT_SERIALIZE_BY_RECORDVERSION                                     -203
#define UMXDB_ERROR_SUBJECT_LEFT_TEMPLATE_SIZE_OUT_OF_RANGE                                      -204
#define UMXDB_ERROR_SUBJECT_RIGHT_TEMPLATE_SIZE_OUT_OF_RANGE                                     -205
#define UMXDB_ERROR_SUBJECT_SELECT_BY_UUID                                                       -206
#define UMXDB_ERROR_SUBJECT_UPDATE_BY_RECORDVERSION                                              -207
#define UMXDB_ERROR_SUBJECT_DELETE_ALL                                                           -208
#define UMXDB_ERROR_SUBJECT_DELETE_BY_UUID                                                       -209
#define UMXDB_ERROR_SUBJECT_LASTNAME_NULL_STRING                                                 -210
#define UMXDB_ERROR_SUBJECT_DATABASE_FULL                                                        -211
#define UMXDB_ERROR_SUBJECT_COUNT                                                                -212

#define UMXDB_EXCEPTION_SUBJECT_COUNT_UUID                                                       -300
#define UMXDB_EXCEPTION_SUBJECT_COUNT_ADMIN                                                      -301
#define UMXDB_EXCEPTION_SUBJECT_COUNT_SERIALIZE_BY_RECORDVERSION                                 -302
#define UMXDB_EXCEPTION_SUBJECT_INSERT                                                           -303
#define UMXDB_EXCEPTION_SUBJECT_SELECT_ALL                                                       -304
#define UMXDB_EXCEPTION_SUBJECT_SEARCH_BY_NAME                                                   -305
#define UMXDB_EXCEPTION_SUBJECT_SEARCH_BY_UUID                                                   -306
#define UMXDB_EXCEPTION_SUBJECT_SELECT_ALL_UUID                                                  -307
#define UMXDB_EXCEPTION_SUBJECT_SELECT_BY_PAGE                                                   -308
#define UMXDB_EXCEPTION_SUBJECT_SELECT_FOR_MEMORY                                                -309
#define UMXDB_EXCEPTION_SUBJECT_SELECT_BY_RECORDVERSION                                          -310
#define UMXDB_EXCEPTION_SUBJECT_SELECT_BY_PAGE_INVALID_PAGE                                      -311
#define UMXDB_EXCEPTION_SUBJECT_UPDATE                                                           -312
#define UMXDB_EXCEPTION_SUBJECT_UPDATE_NAME                                                      -313
#define UMXDB_EXCEPTION_SUBJECT_UPDATE_BY_UUID                                                   -314
#define UMXDB_EXCEPTION_SUBJECT_UPDATE_BY_RECORDVERSION                                          -315
#define UMXDB_EXCEPTION_SUBJECT_VACUUM_SERVICE                                                   -316
#define UMXDB_EXCEPTION_SUBJECT_COUNT                                                            -317
#define UMXDB_EXCEPTION_SUBJECT_DELETE_ALL                                                       -318
#define UMXDB_EXCEPTION_SUBJECT_DELETE_BY_UUID                                                   -319
#define UMXDB_EXCEPTION_SUBJECT_SELECT_BY_UUID                                                   -320
#define UMXDB_EXCEPTION_SUBJECT_FEATURE_ENCRYPTION                                               -321
#define UMXDB_EXCEPTION_SUBJECT_FEATURE_DECRYPTION                                               -322
#define UMXDB_EXCEPTION_SCHEDULE_SEARCH_BY_UUID                                                  -323
#define UMXDB_EXCEPTION_SCHEDULEINFO_SEARCH                                                      -324
#define UMXDB_EXCEPTION_SCHEDULESPECIALDAY_SEARCH                                                -325
#define UMXDB_EXCEPTION_SCHEDULETYPEINFO_SEARCH                                                  -326
#define UMXDB_EXCEPTION_SCHEDULEINFO_DELETE                                                      -327
#define UMXDB_EXCEPTION_SCHEDULESPECIALDAY_DELETE                                                -328
#define UMXDB_EXCEPTION_SCHEDULETYPEINFO_DELETE                                                  -329
#define UMXDB_EXCEPTION_SCHEDULEINFO_INSERT                                                      -330
#define UMXDB_EXCEPTION_SCHEDULESPECIALDAY_INSERT                                                -331
#define UMXDB_EXCEPTION_SCHEDULETYPEINFO_INSERT                                                  -332
#define UMXDB_EXCEPTION_SCHEDULEINFO_UPDATE                                                      -333
#define UMXDB_EXCEPTION_SCHEDULESPECIALDAY_UPDATE                                                -334
#define UMXDB_EXCEPTION_SCHEDULETYPEINFO_UPDATE                                                  -335
#define UMXDB_EXCEPTION_SCHEDULE_DELETE_BYUSER                                                   -336

#define UMXDB_ERROR_FACE_COUNT_UUID                                                              -400
#define UMXDB_ERROR_FACE_COUNT_UUID_NO_EXIST                                                     -401
#define UMXDB_ERROR_FACE_COUNT_UUID_AND_SUBID                                                    -402
#define UMXDB_ERROR_FACE_COUNT_UUID_AND_SUBID_NO_EXIST                                           -403
#define UMXDB_ERROR_FACE_COUNT_UUID_AND_SUBID_ALREADY_EXIST                                      -404
#define UMXDB_ERROR_FACE_SELECT_BY_UUID_AND_SUBID                                                -405
#define UMXDB_ERROR_FACE_DELETE_ALL                                                              -406
#define UMXDB_ERROR_FACE_DELETE_BY_UUID                                                          -407
#define UMXDB_ERROR_FACE_DELETE_BY_UUID_AND_SUBID                                                -408
#define UMXDB_ERROR_FACE_SUBID_OUT_OF_RANGE                                                      -409
#define UMXDB_ERROR_FACE_FEATURE_SIZE_OUT_OF_RANGE                                               -410
#define UMXDB_ERROR_FACE_FEATURE_BLOB_SIZE_OUT_OF_RANGE                                          -411
#define UMXDB_ERROR_FACE_FACEINFO_NULL_POINTER                                                   -412
#define UMXDB_ERROR_FACE_FEATURE_NULL_POINTER                                                    -413
#define UMXDB_ERROR_FACE_DATABASE_FULL                                                           -414

#define UMXDB_EXCEPTION_FACE_COUNT_UUID_AND_SUBID                                                -500
#define UMXDB_EXCEPTION_FACE_INSERT                                                              -501
#define UMXDB_EXCEPTION_FACE_SELECT_ALL                                                          -502
#define UMXDB_EXCEPTION_FACE_SELECT_BY_PAGE                                                      -503
#define UMXDB_EXCEPTION_FACE_SELECT_BY_UUID                                                      -504
#define UMXDB_EXCEPTION_FACE_SELECT_FOR_MEMORY                                                   -505
#define UMXDB_EXCEPTION_FACE_UPDATE_BY_UUID_AND_SUBID                                            -506
#define UMXDB_EXCEPTION_FACE_COUNT                                                               -507
#define UMXDB_EXCEPTION_FACE_DELETE_ALL                                                          -508
#define UMXDB_EXCEPTION_FACE_DELETE_BY_UUID                                                      -509
#define UMXDB_EXCEPTION_FACE_DELETE_BY_UUID_AND_SUBID                                            -510
#define UMXDB_EXCEPTION_FACE_SELECT_BY_UUID_AND_SUBID                                            -511
#define UMXDB_EXCEPTION_FACE_FEATURE_ENCRYPTION                                                  -512
#define UMXDB_EXCEPTION_FACE_FEATURE_DECRYPTION                                                  -513

#define UMXDB_ERROR_USERINFO_COUNT_UUID                                                          -600
#define UMXDB_ERROR_USERINFO_COUNT_UUID_NO_EXIST                                                 -601
#define UMXDB_ERROR_USERINFO_COUNT_UUID_ALREADY_EXIST                                            -602
#define UMXDB_ERROR_USERINFO_SELECT_BY_CARD                                                      -603
#define UMXDB_ERROR_USERINFO_DELETE_ALL                                                          -604
#define UMXDB_ERROR_USERINFO_DELETE_BY_UUID                                                      -605
#define UMXDB_ERROR_USERINFO_CARD_NULL_STRING                                                    -606
#define UMXDB_ERROR_USERINFO_DATABASE_FULL                                                       -607

#define UMXDB_EXCEPTION_USERINFO_COUNT_UUID                                                      -700
#define UMXDB_EXCEPTION_USERINFO_INSERT                                                          -701
#define UMXDB_EXCEPTION_USERINFO_SEARCH_BY_UUID                                                  -702
#define UMXDB_EXCEPTION_USERINFO_SELECT_ALL                                                      -703
#define UMXDB_EXCEPTION_USERINFO_SELECT_BY_UUID                                                  -704
#define UMXDB_EXCEPTION_USERINFO_SELECT_BY_PAGE                                                  -705
#define UMXDB_EXCEPTION_USERINFO_UPDATE_BY_UUID                                                  -706
#define UMXDB_EXCEPTION_USERINFO_COUNT                                                           -707
#define UMXDB_EXCEPTION_USERINFO_DELETE_ALL                                                      -708
#define UMXDB_EXCEPTION_USERINFO_DELETE                                                          -709
#define UMXDB_EXCEPTION_USERINFO_SELECT_BY_CARD                                                  -710

#define UMXDB_ERROR_CARDINFO_COUNT_UUID                                                          -740
#define UMXDB_ERROR_CARDINFO_COUNT_UUID_NO_EXIST                                                 -741
#define UMXDB_ERROR_CARDINFO_DELETE_ALL                                                          -742
#define UMXDB_ERROR_CARDINFO_DELETE_BY_UUID                                                      -743

#define UMXDB_EXCEPTION_CARDINFO_SELECT_BY_UUID                                                  -750
#define UMXDB_EXCEPTION_CARDINFO_INSERT_BY_UUID                                                  -751
#define UMXDB_EXCEPTION_CARDINFO_COUNT_UUID_AND_SUBID                                            -752
#define UMXDB_EXCEPTION_CARDINFO_DELETE_ALL                                                      -753
#define UMXDB_EXCEPTION_CARDINFO_DELETE_BY_UUID                                                  -754
#define UMXDB_EXCEPTION_CARDINFO_SELECT_BY_PAGE                                                  -755
#define UMXDB_EXCEPTION_CARDINFO_DELETE                                                          -756

#define UMXDB_ERROR_USER_COUNT_UUID                                                              -760
#define UMXDB_ERROR_USER_COUNT_UUID_NO_EXIST                                                     -761
#define UMXDB_ERROR_USER_DELETE_BY_UUID                                                          -762
#define UMXDB_EXCEPTION_USER_COUNT_UUID                                                          -763
#define UMXDB_EXCEPTION_USER_INSERT                                                              -764

#define UMXDB_ERROR_SCHEDULEDATA_DELETE_ALL                                                      -770
#define UMXDB_EXCEPTION_SCHEDULEDATA_DELETE_ALL                                                  -771
#define UMXDB_ERROR_SCHEDULEDATA_DELETE_BY_UUID                                                  -772
#define UMXDB_EXCEPTION_SCHEDULEDATA_DELETE_BY_UUID                                              -773

#define UMXDB_ERROR_EVENTLOG_SELECT_BY_LAST_LOGID                                                -800
#define UMXDB_ERROR_EVENTLOG_DELETE_BY_LOGID                                                     -801
#define UMXDB_ERROR_EVENTLOG_DELETE_BY_LOGID_FROM_TO                                             -802
#define UMXDB_ERROR_EVENTLOG_LOGID_FROM_TO_WRONG_RANGE                                           -803
#define UMXDB_ERROR_EVENTLOG_DELETE_FIRST_LOG                                                    -804
#define UMXDB_ERROR_EVENTLOG_DELETE_FIRST_IMAGE_LOG                                              -805

#define UMXDB_EXCEPTION_EVENTLOG_INSERT                                                          -900
#define UMXDB_EXCEPTION_EVENTLOG_SEARCH_ALL_BY_CASES                                             -901
#define UMXDB_EXCEPTION_EVENTLOG_SELECT_BY_PAGE                                                  -902
#define UMXDB_EXCEPTION_EVENTLOG_SELECT_BY_LOGID                                                 -903
#define UMXDB_EXCEPTION_EVENTLOG_SELECT_BY_LAST_LOGID                                            -904
#define UMXDB_EXCEPTION_EVENTLOG_SELECT_BY_PAGE_INVALID_PAGE                                     -905
#define UMXDB_EXCEPTION_EVENTLOG_SELECT_LOGS_BY_LOGID_FROM_TO                                    -906
#define UMXDB_EXCEPTION_EVENTLOG_SELECT_LOG_PAGE_BY_LOGID_FROM_TO                                -907
#define UMXDB_EXCEPTION_EVENTLOG_SELECT_LOG_PAGE_BY_LOGID_FROM_TO_INVALID_PAGE                   -908
#define UMXDB_EXCEPTION_EVENTLOG_VACUUM_SERVICELOG                                               -909
#define UMXDB_EXCEPTION_EVENTLOG_LOG_COUNT                                                       -910
#define UMXDB_EXCEPTION_EVENTLOG_IMAGE_LOG_COUNT                                                 -911
#define UMXDB_EXCEPTION_EVENTLOG_DELETE_FIRST_IMAGE_LOG                                          -912
#define UMXDB_EXCEPTION_EVENTLOG_DELETE_FIRST_LOG                                                -913
#define UMXDB_EXCEPTION_EVENTLOG_DELETE_BY_LOGID                                                 -914
#define UMXDB_EXCEPTION_EVENTLOG_SELECT_IMAGE_LOGS                                               -915
#define UMXDB_EXCEPTION_EVENTLOG_SELECT_LOG_INVALID_ARGUMENTS                                    -916
#define UMXDB_EXCEPTION_EVENTLOG_SELECT_LOG                                                      -917

#define UMXDB_EXCEPTION_IMAGECAPTURE_SELECT_ALL                                                 -1000

#define UMXDB_EXCEPTION_MAIN_DB_INTEGRITY                                                        -1100
#define UMXDB_EXCEPTION_EVENT_DB_INTEGRITY                                                       -1101

#define DB_NEUROTECH_FEATURE_VERSION_6_0                                                        0x3600
#define DB_NEUROTECH_FEATURE_VERSION_10_0                                                       0x3A00

#define DB_DEFAULT_FEATURE_VERSION                                                              DB_DELTAID_FEATURE_VERSION
#define DB_DELTAID_FEATURE_VERSION                                                              0x2310
#define DB_DLIB_FEATURE_VERSION                                                                 0x61000000
#define DB_NEUROTECH_FEATURE_VERSION                                                            DB_NEUROTECH_FEATURE_VERSION_6_0
#define DB_ENCRYPT_VERSIONDATA_ID                                                               1   // 0: DB_Version 1: Is it encrypted or not?
#define DB_ENCRYPT_VERSIONDATA_VERSION                                                          1   // 1:encrypted

#endif // UMXDBGLOBAL_H
