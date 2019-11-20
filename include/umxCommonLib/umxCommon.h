/////////////////////////////////////////////////////////////////////////////////////////
// umxCam.h
//
// Version 0.1.3   July 18, 2016
//                 Initial Public Release
//
// Description: umxCommon.h provide the interface with the iris image capture device
//              UMX-10 (EF-45) developed by CMITECH.
//              Please see umxCommonGlobal.h for detailed definitions.
//
/////////////////////////////////////////////////////////////////////////////////////////

#ifndef UMXCOMMON_H
#define UMXCOMMON_H

#include "umxCommonGlobal.h"

#if __GNUC__ >= 4
    #define UMXCOMMON_SHARED_EXPORT __attribute__ ((visibility ("default")))
#else
    #define UMXCOMMON_SHARED_EXPORT
#endif  // __GNUC_C >= 4
#define _UMXCOMMON_EXPORT UMXCOMMON_SHARED_EXPORT

#ifdef __cplusplus
extern "C" {
#endif

    void _UMXCOMMON_EXPORT umxCommon_getVersion(unsigned int *major, unsigned int *minor, unsigned int *revision);
    // Get umxCommon version and revision number for compatibility.
    // Application should check if major version number is consistent.
    //
    // major[out]
    // minor[out]
    // revision[out]

#ifdef __cplusplus
} // extern "C"
#endif

#endif // UMXCOMMON_H
