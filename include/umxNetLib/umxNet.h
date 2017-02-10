/////////////////////////////////////////////////////////////////////////////////////////
// umxNet.h
//
// Version 0.1.3   July 18, 2016
//                 Initial Public Release
//
// Description: umxNet.h provide the interface with the iris image capture device
//              UMX-10 (EF-45) developed by CMITECH.
//              Please see umxNetGlobal.h for detailed definitions.
//
/////////////////////////////////////////////////////////////////////////////////////////

#ifndef UMXNET_H
#define UMXNET_H

#include "umxNetGlobal.h"
#include <Poco/Logger.h>
#include <Poco/AutoPtr.h>
#include <Poco/Util/AbstractConfiguration.h>

#if __GNUC__ >= 4
    #define UMXNET_SHARED_EXPORT __attribute__ ((visibility ("default")))
#else
    #define UMXNET_SHARED_EXPORT
#endif  // __GNUC_C >= 4
#define _UMXNET_EXPORT UMXNET_SHARED_EXPORT

#ifdef __cplusplus
extern "C" {
#endif

    using namespace UMXNetwork;

    void _UMXNET_EXPORT umxNet_getVersion(unsigned int *major, unsigned int *minor, unsigned int *revision);
    // Get umxNet version and revision number for compatibility.
    // Application should check if major version number is consistent.
    //
    // major[out]
    // minor[out]
    // revision[out]

    int _UMXNET_EXPORT umxNet_create(UMXNET_HANDLE *phandle, Poco::Logger& logger, Poco::AutoPtr<Poco::Util::AbstractConfiguration> config, int type, INetworkManager *iNetworkManager);
    // Create umxNet. As soon as it is created, it can receive device manager event
    //
    // phandle[out] - UMXNET_HANDLE value if successful. Otherwise, NULL.
    // logger[in] - Poco logger's pointer
    // config[in] - Poco config's pointer
    // type[in] - UMXNET_POCO_RESTSERVICE
    // Return value - UMXNET_ERROR_CANNOT_ALLOC_MEMORY
    //                UMXNET_ERROR_IN_ARGUMENTS
    //                UMXNET_SUCCESS

    int _UMXNET_EXPORT umxNet_destroy(UMXNET_HANDLE handle);
    // Destroy umxNet.
    //
    // handle[in] - UMXNET_HANDLE value
    //
    // Return value - UMXNET_ERROR_INVALID_HANDLE
    //                UMXNET_SUCCESS

#ifdef __cplusplus
} // extern "C"
#endif

#endif // UMXNET_H
