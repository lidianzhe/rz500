/////////////////////////////////////////////////////////////////////////////////////////
// umxDB.h
//
// Version 0.1.3   July 18, 2016
//                 Initial Public Release
//
// Description: umxDB.h provide the interface with the iris image capture device
//              UMX-10 (EF-45) developed by CMITECH.
//              Please see umxDBGlobal.h for detailed definitions.
//
/////////////////////////////////////////////////////////////////////////////////////////

#ifndef UMXDB_H
#define UMXDB_H

#include <string>
#include <vector>
#include <Poco/Logger.h>
#include <Poco/AutoPtr.h>
#include <Poco/Util/AbstractConfiguration.h>
#include "umxDBGlobal.h"
#include "umxAlgoGlobal.h"
#include "umxCamGlobal.h"
#include "umxCommonGlobal.h"

using namespace UMXCommon;

#if __GNUC__ >= 4
    #define UMXDB_SHARED_EXPORT __attribute__ ((visibility ("default")))
#else
    #define UMXDB_SHARED_EXPORT
#endif  // __GNUC_C >= 4
#define _UMXDB_EXPORT UMXDB_SHARED_EXPORT

#ifdef __cplusplus
extern "C" {
#endif

    int _UMXDB_EXPORT umxDB_getVersion(unsigned int *major, unsigned int *minor, unsigned int *revision);
    // Get umxDB version and revision number for compatibility.
    // Application should check if major version number is consistent.
    //
    // major[out]
    // minor[out]
    // revision[out]
    //
    // Return value - UMXDB_ERROR_IN_ARGUMENTS_MAJOR_NULL
    //                UMXDB_ERROR_IN_ARGUMENTS_MINOR_NULL
    //                UMXDB_ERROR_IN_ARGUMENTS_REVISION_NULL
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_create_ADR(UMXDB_HANDLE *phandle);

    int _UMXDB_EXPORT umxDB_create(UMXDB_HANDLE *phandle, Poco::Logger& logger, Poco::AutoPtr<Poco::Util::AbstractConfiguration> config);
    // Create umxDB.
    //
    // phandle[out] - UMXDB_HANDLE value if successful. Otherwise, NULL.
    // logger[in] - Poco logger's pointer
    // config[in] - Poco config's pointer
    //
    // Return value - UMXDB_ERROR_CANNOT_ALLOC_MEMORY
    //                UMXALGO_SUCCESS

    int _UMXDB_EXPORT umxDB_destroy(UMXDB_HANDLE handle);
    // Destroy umxDB.
    //
    // handle[in] - UMXDB_HANDLE value
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_vacuumService(UMXDB_HANDLE handle);
    // Vacuum Service.db
    //
    // handle[in] - UMXDB_HANDLE value
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_EXCEPTION_SUBJECT_VACUUM_SERVICE
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_vacuumServiceLog(UMXDB_HANDLE handle);
    // Vacuum ServiceLog.db
    //
    // handle[in] - UMXDB_HANDLE value
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_EXCEPTION_EVENTLOG_VACUUM_SERVICELOG
    //                UMXDB_SUCCESS

    /// vvvv "/usr/local/share/CMITECH/Service.db" - subject table vvvv

    int _UMXDB_EXPORT umxDB_countSubject(UMXDB_HANDLE handle, int* count);
    // Count subject
    //
    // handle[in] - UMXDB_HANDLE value
    // count[out] - subject count
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_IN_ARGUMENTS_SUBJECT_COUNT_NULL_POINTER
    //                UMXDB_EXCEPTION_SUBJECT_COUNT
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_countFace(UMXDB_HANDLE handle, int* count);
    // Count face
    //
    // handle[in] - UMXDB_HANDLE value
    // count[out] - face count
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_IN_ARGUMENTS_FACE_COUNT_NULL_POINTER
    //                UMXDB_EXCEPTION_FACE_COUNT
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_countUserInfo(UMXDB_HANDLE handle, int* count);
    // Count userinfo
    //
    // handle[in] - UMXDB_HANDLE value
    // count[out] - userinfo count
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_IN_ARGUMENTS_USERINFO_COUNT_NULL_POINTER
    //                UMXDB_EXCEPTION_USERINFO_COUNT
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_countUserInfoByIndivisual(UMXDB_HANDLE handle, const std::string mode, int* count);
    // Count userinfo by mode
    //
    // handle[in] - UMXDB_HANDLE value
    // mode[in] - indivisual_mode value
    // count[out] - userinfo count
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_IN_ARGUMENTS_USERINFO_COUNT_NULL_POINTER
    //                UMXDB_EXCEPTION_USERINFO_COUNT
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_insertSubject_ADR(UMXDB_HANDLE handle, const SubjectData_ADR &subjectData);

    int _UMXDB_EXPORT umxDB_insertSubject(UMXDB_HANDLE handle, const SubjectData &subjectData);
    // Insert subject using SubjectData.
    //
    // handle[in] - UMXDB_HANDLE value
    // subjectData[in] - SubjectData type's iris data
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_UUID_NULL_STRING
    //                UMXDB_ERROR_SUBJECT_LASTNAME_NULL_STRING
    //                UMXDB_ERROR_SUBJECT_COUNT_UUID_ALREADY_EXIST
    //                UMXDB_ERROR_SUBJECT_COUNT_UUID
    //                UMXDB_EXCEPTION_SUBJECT_COUNT_UUID
    //                UMXDB_EXCEPTION_SUBJECT_INSERT
    //                UMXDB_SUCCESS

#if 0
    int _UMXDB_EXPORT umxDB_insertIris(UMXDB_HANDLE handle, const std::string uuid, const std::string name, const int wiegandFacility, const int wiegandCode,
                                       const UMXALGO_IRIS_GET_ENROL_TEMPLATE_OUTPUT* enrollIrisTemplates,
                                       const std::string leftEyeImagePath, const std::string rightEyeImagePath,
                                       const int recordVersion);
    // Insert iris using UMXCAM_IMAGE_INFO.
    //
    // handle[in] - UMXDB_HANDLE value
    // uuid[in] - unique id
    // name[in] - user name
    // wiegandFacility[in] - wiegand facility value
    // wiegandCode[in] - wiegand code value
    // enrollIrisTemplates[in] - iris template informations
    // leftEyeImagePath[in] - left eye image path to save
    // rightEyeImagePath[in] - right eye image path to save
    // recordVersion[in] - feature data version
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_ALREADY_EXIST_UUID
    //                UMXDB_ERROR_FAIL_TO_INSERT_SUBJECT
    //                UMXDB_SUCCESS
#endif

    int _UMXDB_EXPORT umxDB_insertIris2_ADR(UMXDB_HANDLE handle, SubjectData_ADR *subjectData);

    int _UMXDB_EXPORT umxDB_insertIris2(UMXDB_HANDLE handle, SubjectData *subjectData);
    // Insert iris using SubjectData.
    //
    // handle[in] - UMXDB_HANDLE value
    // subjectData[out] - SubjectData type's iris data
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_IN_ARGUMENTS_SUBJECT_NULL_POINTER
    //                UMXDB_ERROR_UUID_NULL_STRING
    //                UMXDB_ERROR_SUBJECT_LASTNAME_NULL_STRING
    //                UMXDB_ERROR_SUBJECT_COUNT_UUID_ALREADY_EXIST
    //                UMXDB_ERROR_SUBJECT_COUNT_UUID
    //                UMXDB_EXCEPTION_SUBJECT_COUNT_UUID
    //                UMXDB_ERROR_SUBJECT_LEFT_TEMPLATE_SIZE_OUT_OF_RANGE
    //                UMXDB_ERROR_SUBJECT_RIGHT_TEMPLATE_SIZE_OUT_OF_RANGE
    //                UMXDB_EXCEPTION_SUBJECT_INSERT
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_countAllIrises(UMXDB_HANDLE handle, int* retCount);
    // Count iris in DB.
    //
    // handle[in] - UMXDB_HANDLE value
    // retCount[out] - iris count
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_IN_ARGUMENTS_FACE_UUID_AND_SUBID_COUNT_NULL_POINTER
    //                UMXDB_ERROR_SUBJECT_COUNT
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_selectIrisesByPage_ADR(UMXDB_HANDLE handle, const int page, const int pageSize, std::vector<SubjectData_ADR> *retIrises);

    int _UMXDB_EXPORT umxDB_selectIrisesByPage(UMXDB_HANDLE handle, const int page, const int pageSize, std::vector<SubjectData> *retIrises);
    // Select iris by page.
    //
    // handle[in] - UMXDB_HANDLE value
    // page[in] - page
    // pageSize[in] - page size
    // retIrises[out] - SubjectData type's data list
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_IN_ARGUMENTS_SUBJECT_VECTOR_NULL_POINTER
    //                UMXDB_ERROR_PAGE_INVALID
    //                UMXDB_ERROR_PAGESIZE_INVALID
    //                UMXDB_EXCEPTION_SUBJECT_SELECT_BY_PAGE_INVALID_PAGE
    //                UMXDB_EXCEPTION_SUBJECT_SELECT_BY_PAGE
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_selectIrisByUUID_ADR(UMXDB_HANDLE handle, const char* uuid, SubjectData_ADR *retIris);

    int _UMXDB_EXPORT umxDB_selectIrisByUUID(UMXDB_HANDLE handle, const std::string uuid, SubjectData *retIris);
    // Select iris by uuid.
    //
    // handle[in] - UMXDB_HANDLE value
    // uuid[in] - unique id
    // retIris[out] - iris data
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_IN_ARGUMENTS_SUBJECT_NULL_POINTER
    //                UMXDB_ERROR_UUID_NULL_STRING
    //                UMXDB_ERROR_SUBJECT_SELECT_BY_UUID
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_selectIrisForMemory_ADR(UMXDB_HANDLE handle, std::vector<SubjectData_ADR> *retIris);

    int _UMXDB_EXPORT umxDB_selectIrisForMemory(UMXDB_HANDLE handle, std::vector<SubjectData> *retIris);
    // Select iris for memory (feature is not null and eye width is not out of range)
    //
    // handle[in] - UMXDB_HANDLE value
    // retIris[out] - struct SubjectData's data list
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_IN_ARGUMENTS_SUBJECT_VECTOR_NULL_POINTER
    //                UMXDB_EXCEPTION_SUBJECT_SELECT_FOR_MEMORY
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_selectAllIrisesUuid_ADR(UMXDB_HANDLE handle, std::vector<char*> *retAllIrisesUuid);

    int _UMXDB_EXPORT umxDB_selectAllIrisesUuid(UMXDB_HANDLE handle, std::vector<std::string> *retAllIrisesUuid);
    // Select iris for uuid.
    //
    // handle[in] - UMXDB_HANDLE value
    // retAllIrisesUuid[out] - iris uuid
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_IN_ARGUMENTS_SUBJECT_VECTOR_NULL_POINTER
    //                UMXDB_EXCEPTION_SUBJECT_SELECT_ALL
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_selectAllIrises_ADR(UMXDB_HANDLE handle, std::vector<SubjectData_ADR> *retAllIrises);

    int _UMXDB_EXPORT umxDB_selectAllIrises(UMXDB_HANDLE handle, std::vector<SubjectData> *retAllIrises);
    // Select iris by uuid.
    //
    // handle[in] - UMXDB_HANDLE value
    // uuid[in] - unique id
    // retIris[out] - iris data
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_IN_ARGUMENTS_SUBJECT_VECTOR_NULL_POINTER
    //                UMXDB_EXCEPTION_SUBJECT_SELECT_ALL
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_updateSubject_ADR(UMXDB_HANDLE handle, const SubjectData_ADR &subjectData);

    int _UMXDB_EXPORT umxDB_updateSubject(UMXDB_HANDLE handle, const SubjectData &subjectData);
    // Update subject.
    //
    // handle[in] - UMXDB_HANDLE value
    // subjectData[in] - SubjectData
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_UUID_NULL_STRING
    //                UMXDB_ERROR_SUBJECT_COUNT_UUID_NO_EXIST
    //                UMXDB_ERROR_SUBJECT_COUNT_UUID
    //                UMXDB_EXCEPTION_SUBJECT_COUNT_UUID
    //                UMXDB_EXCEPTION_SUBJECT_UPDATE
    //                UMXDB_SUCCESS

#if 0
    int _UMXDB_EXPORT umxDB_updateIrisByUUID(UMXDB_HANDLE handle, const std::string uuid, const std::string name, const UMXCAM_IMAGE_INFO* imageInfo, const UMXALGO_IRIS_GET_ENROL_TEMPLATE_OUTPUT* enrollIrisTemplates, const std::string leftEyeImagePath, const std::string rightEyeImagePath, int recordVersion);
    // Update iris by uuid.
    //
    // handle[in] - UMXDB_HANDLE value
    // uuid[in] - unique id to update
    // name[in] - user name to update
    // imageInfo[in] - iris image informations to update database
    // enrollIrisTemplates[in] - iris template informations to update database
    // leftEyeImagePath[in] - left eye image path to update database
    // rightEyeImagePath[in] - right eye image path to update database
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_NO_EXIST_UUID
    //                UMXDB_SUCCESS
#endif

    int _UMXDB_EXPORT umxDB_updateIrisByUUID2_ADR(UMXDB_HANDLE handle, const char* uuid, SubjectData_ADR &subjectData);

    int _UMXDB_EXPORT umxDB_updateIrisByUUID2(UMXDB_HANDLE handle, const std::string uuid, SubjectData &subjectData);
    // Update iris by uuid.
    //
    // handle[in] - UMXDB_HANDLE value
    // uuid[in] - unique id to update database
    // subjectData[in] - SubjectData type's iris data to update database
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_UUID_NULL_STRING
    //                UMXDB_ERROR_SUBJECT_COUNT_UUID_NO_EXIST
    //                UMXDB_ERROR_SUBJECT_COUNT_UUID
    //                UMXDB_EXCEPTION_SUBJECT_COUNT_UUID
    //                UMXDB_EXCEPTION_SUBJECT_UPDATE_BY_UUID
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_updateNameByUUID_ADR(UMXDB_HANDLE handle, const char* uuid, const char* name);

    int _UMXDB_EXPORT umxDB_updateNameByUUID(UMXDB_HANDLE handle, const std::string uuid, const std::string name);
    // Update user name in subject table by uuid.
    //
    // handle[in] - UMXDB_HANDLE value
    // uuid[in] - unique id to update database
    // name[in] - user name to update
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_UUID_NULL_STRING
    //                UMXDB_ERROR_SUBJECT_LASTNAME_NULL_STRING
    //                UMXDB_ERROR_SUBJECT_COUNT_UUID_NO_EXIST
    //                UMXDB_ERROR_SUBJECT_COUNT_UUID
    //                UMXDB_EXCEPTION_SUBJECT_COUNT_UUID
    //                UMXDB_EXCEPTION_SUBJECT_UPDATE_NAME
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_deleteIrisByUUID_ADR(UMXDB_HANDLE handle, const char* uuid);

    int _UMXDB_EXPORT umxDB_deleteIrisByUUID(UMXDB_HANDLE handle, const std::string uuid);
    // Delete iris in subject table by uuid.
    //
    // handle[in] - UMXDB_HANDLE value
    // uuid[in] - unique id to update database
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_UUID_NULL_STRING
    //                UMXDB_ERROR_SUBJECT_COUNT_UUID_NO_EXIST
    //                UMXDB_ERROR_SUBJECT_COUNT_UUID
    //                UMXDB_EXCEPTION_SUBJECT_COUNT_UUID
    //                UMXDB_ERROR_SUBJECT_DELETE_BY_UUID
    //                UMXDB_ERROR_DELETE
    //                UMXDB_EXCEPTION_SUBJECT_VACUUM_SERVICE
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_deleteAllIrises(UMXDB_HANDLE handle);
    // Delete all irises in subject table.
    //
    // handle[in] - UMXDB_HANDLE value
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_SUBJECT_DELETE_ALL
    //                UMXDB_EXCEPTION_SUBJECT_VACUUM_SERVICE
    //                UMXDB_SUCCESS

    /// ^^^^ "/usr/local/share/CMITECH/Service.db" - subject table ^^^^


    /// vvvv "/usr/local/share/CMITECH/Service.db" - face table vvvv

#if 0
    int _UMXDB_EXPORT umxdb_insertFace(UMXDB_HANDLE handle, const std::string uuid, const int subId, const UMXALGO_FACE_FIND_OUTPUT* faceInfo, const UMXALGO_FACE_GET_TEMPLATE_OUTPUT* faceTemplate, const std::string imagePath);
    // Insert face using struct UMXALGO_FACE_FIND_OUTPUT.
    //
    // handle[in] - UMXDB_HANDLE value
    // uuid[in] - unique id
    // subId[in] - face sub id
    // faceInfo[in] - struct UMXALGO_FACE_FIND_OUTPUT's data
    // faceTemplate[in] - struct UMXALGO_FACE_GET_TEMPLATE_OUTPUT's data
    // imagePath[in] - face image path to save
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_ALREADY_EXIST_UUID_AND_SUBID
    //                UMXDB_ERROR_FACE_NO_FACE_INFO
    //                UMXDB_ERROR_NO_FACE_FEATURE
    //                UMXDB_ERROR_FAIL_TO_INSERT_FACE
    //                UMXDB_SUCCESS
#endif

    int _UMXDB_EXPORT umxDB_insertFace2_ADR(UMXDB_HANDLE handle, FaceData_ADR* faceData);

    int _UMXDB_EXPORT umxDB_insertFace2(UMXDB_HANDLE handle, FaceData* faceData);
    // Insert face using struct FaceData.
    //
    // handle[in] - UMXDB_HANDLE value
    // faceDate[in] - struct FaceData's data
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_IN_ARGUMENTS_FACE_NULL_POINTER
    //                UMXDB_ERROR_UUID_NULL_STRING
    //                UMXDB_ERROR_FACE_SUBID_OUT_OF_RANGE
    //                UMXDB_ERROR_FACE_COUNT_UUID_AND_SUBID_ALREADY_EXIST
    //                UMXDB_ERROR_FACE_COUNT_UUID_AND_SUBID
    //                UMXDB_EXCEPTION_FACE_COUNT_UUID_AND_SUBID
    //                UMXDB_ERROR_FACE_FEATURE_SIZE_OUT_OF_RANGE
    //                UMXDB_ERROR_FACE_FEATURE_BLOB_SIZE_OUT_OF_RANGE
    //                UMXDB_EXCEPTION_FACE_INSERT
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_selectFaceByUuIdAndSubId_ADR(UMXDB_HANDLE handle, const char* uuid, const int subId, FaceData_ADR *faceData);

    int _UMXDB_EXPORT umxDB_selectFaceByUuIdAndSubId(UMXDB_HANDLE handle, const std::string uuid, const int subId, FaceData *faceData);
    // Select face by uuid and subid
    //
    // handle[in] - UMXDB_HANDLE value
    // uuid[in] - unique id
    // subId[in] - face sub id
    // faceData[out] - struct FaceData's data
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_IN_ARGUMENTS_FACE_NULL_POINTER
    //                UMXDB_ERROR_UUID_NULL_STRING
    //                UMXDB_ERROR_FACE_SUBID_OUT_OF_RANGE
    //                UMXDB_ERROR_FACE_SELECT_BY_UUID_AND_SUBID
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_selectFacesByUUID_ADR(UMXDB_HANDLE handle, const char* uuid, std::vector<FaceData_ADR> *retFaces);

    int _UMXDB_EXPORT umxDB_selectFacesByUUID(UMXDB_HANDLE handle, const std::string uuid, std::vector<FaceData> *retFaces);
    // Select face by uuid
    //
    // handle[in] - UMXDB_HANDLE value
    // uuid[in] - unique id
    // retFaces[out] - struct FaceData's data list
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_IN_ARGUMENTS_FACE_VECTOR_NULL_POINTER
    //                UMXDB_ERROR_UUID_NULL_STRING
    //                UMXDB_EXCEPTION_FACE_SELECT_BY_UUID
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_selectFacesForMemory_ADR(UMXDB_HANDLE handle, std::vector<FaceData_ADR> *retFaces);

    int _UMXDB_EXPORT umxDB_selectFacesForMemory(UMXDB_HANDLE handle, std::vector<FaceData> *retFaces);
    // Select faces for memory (feature is not null and eye width is not out of range)
    //
    // handle[in] - UMXDB_HANDLE value
    // retFaces[out] - struct FaceData's data list
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_IN_ARGUMENTS_FACE_VECTOR_NULL_POINTER
    //                UMXDB_EXCEPTION_FACE_SELECT_FOR_MEMORY
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_selectAllFaces_ADR(UMXDB_HANDLE handle, std::vector<FaceData_ADR> *retAllFaces);

    int _UMXDB_EXPORT umxDB_selectAllFaces(UMXDB_HANDLE handle, std::vector<FaceData> *retAllFaces);
    // Select all faces
    //
    // handle[in] - UMXDB_HANDLE value
    // retFaces[out] - struct FaceData's data list
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_IN_ARGUMENTS_FACE_VECTOR_NULL_POINTER
    //                UMXDB_EXCEPTION_FACE_SELECT_ALL
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_selectFacesByPage_ADR(UMXDB_HANDLE handle, const int page, const int pageSize, std::vector<FaceData_ADR> *retFaces);

    int _UMXDB_EXPORT umxDB_selectFacesByPage(UMXDB_HANDLE handle, const int page, const int pageSize, std::vector<FaceData> *retFaces);
    // Select faces by page
    //
    // handle[in] - UMXDB_HANDLE value
    // page[int] - page
    // pageSize[in] - page size
    // retFaces[out] - struct FaceData's data list
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_IN_ARGUMENTS_FACE_VECTOR_NULL_POINTER
    //                UMXDB_ERROR_PAGE_INVALID
    //                UMXDB_ERROR_PAGESIZE_INVALID
    //                UMXDB_EXCEPTION_FACE_SELECT_BY_PAGE
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_updateFaceByUuIdAndSubId_ADR(UMXDB_HANDLE handle, const char* uuid, const int subId, const UMXALGO_FACE_FIND_OUTPUT* faceInfo, const UMXALGO_FACE_GET_TEMPLATE_OUTPUT* faceTemplate, const char* imagePath);

    int _UMXDB_EXPORT umxDB_updateFaceByUuIdAndSubId(UMXDB_HANDLE handle, const std::string uuid, const int subId, const UMXALGO_FACE_FIND_OUTPUT* faceInfo, const UMXALGO_FACE_GET_TEMPLATE_OUTPUT* faceTemplate, const std::string imagePath);
    // Update face by uuid and subid
    //
    // handle[in] - UMXDB_HANDLE value
    // uuid[in] - unique id to update
    // subId[in] - face sub id to update
    // faceInfo[in] - struct UMXALGO_FACE_FIND_OUTPUT's data to update
    // faceTemplate[in] - struct UMXALGO_FACE_GET_TEMPLATE_OUTPUT's data to update
    // imagePath[in] - face image path to update
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_FACE_FACEINFO_NULL_POINTER
    //                UMXDB_ERROR_FACE_FEATURE_NULL_POINTER
    //                UMXDB_ERROR_FACE_COUNT_UUID_AND_SUBID_NO_EXIST
    //                UMXDB_ERROR_FACE_COUNT_UUID_AND_SUBID
    //                UMXDB_EXCEPTION_FACE_COUNT_UUID_AND_SUBID
    //                UMXDB_EXCEPTION_FACE_UPDATE_BY_UUID_AND_SUBID
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_updateFaceByUuIdAndSubId2_ADR(UMXDB_HANDLE handle, const char* uuid, const int subId, FaceData_ADR& faceData);

    int _UMXDB_EXPORT umxDB_updateFaceByUuIdAndSubId2(UMXDB_HANDLE handle, const std::string uuid, const int subId, FaceData& faceData);
    // Update face by uuid and subid
    //
    // handle[in] - UMXDB_HANDLE value
    // uuid[in] - unique id to update
    // subId[in] - face sub id to update
    // faceData[in] - struct FaceData's data to update
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_UUID_NULL_STRING
    //                UMXDB_ERROR_FACE_SUBID_OUT_OF_RANGE
    //                UMXDB_ERROR_FACE_COUNT_UUID_AND_SUBID_NO_EXIST
    //                UMXDB_ERROR_FACE_COUNT_UUID_AND_SUBID
    //                UMXDB_EXCEPTION_FACE_COUNT_UUID_AND_SUBID
    //                UMXDB_ERROR_FACE_FEATURE_SIZE_OUT_OF_RANGE
    //                UMXDB_ERROR_FACE_FEATURE_BLOB_SIZE_OUT_OF_RANGE
    //                UMXDB_EXCEPTION_FACE_UPDATE_BY_UUID_AND_SUBID
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_deleteFaceByUuIdAndSubId_ADR(UMXDB_HANDLE handle, const char* uuid, const int subId);

    int _UMXDB_EXPORT umxDB_deleteFaceByUuIdAndSubId(UMXDB_HANDLE handle, const std::string uuid, const int subId);
    // Delete face by uuid and subid
    //
    // handle[in] - UMXDB_HANDLE value
    // uuid[in] - unique id
    // subId[in] - face sub id
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_UUID_NULL_STRING
    //                UMXDB_ERROR_FACE_SUBID_OUT_OF_RANGE
    //                UMXDB_ERROR_FACE_COUNT_UUID_AND_SUBID_NO_EXIST
    //                UMXDB_ERROR_FACE_COUNT_UUID_AND_SUBID
    //                UMXDB_EXCEPTION_FACE_COUNT_UUID_AND_SUBID
    //                UMXDB_ERROR_FACE_DELETE_BY_UUID_AND_SUBID
    //                UMXDB_EXCEPTION_SUBJECT_VACUUM_SERVICE
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_deleteFacesByUUID_ADR(UMXDB_HANDLE handle, const char* uuid);

    int _UMXDB_EXPORT umxDB_deleteFacesByUUID(UMXDB_HANDLE handle, const std::string uuid);
    // Delete faces by uuid
    //
    // handle[in] - UMXDB_HANDLE value
    // uuid[in] - unique id
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_UUID_NULL_STRING
    //                UMXDB_ERROR_FACE_COUNT_UUID_NO_EXIST
    //                UMXDB_ERROR_FACE_COUNT_UUID
    //                UMXDB_EXCEPTION_FACE_COUNT_UUID_AND_SUBID
    //                UMXDB_ERROR_FACE_DELETE_BY_UUID
    //                UMXDB_EXCEPTION_SUBJECT_VACUUM_SERVICE
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_deleteAllFaces(UMXDB_HANDLE handle);
    // Delete all faces
    //
    // handle[in] - UMXDB_HANDLE value
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_EXCEPTION_SUBJECT_VACUUM_SERVICE
    //                UMXDB_ERROR_FACE_DELETE_ALL
    //                UMXDB_SUCCESS

    /// ^^^^ "/usr/local/share/CMITECH/Service.db" - face table ^^^^


    /// vvvv "/usr/local/share/CMITECH/Service.db" - userinfo table vvvv

    int _UMXDB_EXPORT umxDB_insertUserInfo_ADR(UMXDB_HANDLE handle, const char* uuid, const char* card, const char* pin,
                                                     const int admin, const int groupIndex, const int byPassCard, const int indivisual,
                                                     const int threeOutStatus, const int threeOutAccessAllowed, const int jobCode, const int timeScheduleCode,
                                                     const int apbStatus, const std::string message);

    int _UMXDB_EXPORT umxDB_insertUserInfo(UMXDB_HANDLE handle, const std::string uuid, const std::string card, const std::string pin,
                                                     const int admin, const int groupIndex, const int byPassCard, const int indivisual,
                                                     const int threeOutStatus, const int threeOutAccessAllowed, const int jobCode, const int timeScheduleCode,
                                                     const int apbStatus, const std::string message);

    int _UMXDB_EXPORT umxDB_selectCardInfoByUUID(UMXDB_HANDLE handle, const std::string uuid, std::vector<CardInfoData> *retCardInfo);
    int _UMXDB_EXPORT umxDB_selectCardInfoByCard(UMXDB_HANDLE handle, const std::string card, CardInfoData *retCardInfo);
    int _UMXDB_EXPORT umxDB_selectCardNumberByUUIDandSubId(UMXDB_HANDLE handle, const std::string uuid, const int subId, CardInfoData *card);
    int _UMXDB_EXPORT umxDB_updateCardNumberByUUIDandSubId(UMXDB_HANDLE handle, const std::string uuid, const int subId, const std::string card);
    int _UMXDB_EXPORT umxDB_insertCard(UMXDB_HANDLE handle, const CardInfoData card_info);
    int _UMXDB_EXPORT umxDB_deleteCardByUUIDandSubId(UMXDB_HANDLE handle, const std::string uuid, const int subId);
    int _UMXDB_EXPORT umxDB_delete_Table_then_insert_CardinfoByUUID(UMXDB_HANDLE handle, const std::string uuid, std::vector<CardInfoData> *retCardInfo);
    int _UMXDB_EXPORT umxDB_selectCardInfoByPage(UMXDB_HANDLE handle, const int page, const int pageSize, std::vector<CardInfoData> *retAllCardInfo);
    // Insert user info.
    //
    // handle[in] - UMXDB_HANDLE value
    // uuid[in] - unique id
    // card[in] - card number
    // pin[in] - pin number
    // admin[in] - admin authorization
    // groupIndex[in] - group index
    // indivisual[in] - indivisual mode
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_UUID_NULL_STRING
    //                UMXDB_ERROR_USERINFO_COUNT_UUID_ALREADY_EXIST
    //                UMXDB_ERROR_USERINFO_COUNT_UUID
    //                UMXDB_EXCEPTION_USERINFO_COUNT_UUID
    //                UMXDB_EXCEPTION_USERINFO_INSERT
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_selectUserInfoByUUID_ADR(UMXDB_HANDLE handle, const char* uuid, UserInfoData_ADR *retUserInfo);

    int _UMXDB_EXPORT umxDB_selectUserInfoByUUID(UMXDB_HANDLE handle, const std::string uuid, UserInfoData *retUserInfo);
    // Select user info by uuid.
    //
    // handle[in] - UMXDB_HANDLE value
    // uuid[in] - unique id
    // retUserInfo[out] - struct UserInfoData's data
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_IN_ARGUMENTS_USERINFO_NULL_POINTER
    //                UMXDB_ERROR_UUID_NULL_STRING
    //                UMXDB_ERROR_USERINFO_COUNT_UUID_NO_EXIST
    //                UMXDB_ERROR_USERINFO_COUNT_UUID
    //                UMXDB_EXCEPTION_USERINFO_COUNT_UUID
    //                UMXDB_EXCEPTION_USERINFO_SELECT_BY_UUID
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_selectUserInfoByCard_ADR(UMXDB_HANDLE handle, const char* card, UserInfoData_ADR *retUserInfo);

    int _UMXDB_EXPORT umxDB_selectUserInfoByCard(UMXDB_HANDLE handle, const std::string card, UserInfoData *retUserInfo);
    // Select user info by card number.
    //
    // handle[in] - UMXDB_HANDLE value
    // card[in] - card number
    // retUserInfo[out] - struct UserInfoData's data
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_IN_ARGUMENTS_USERINFO_NULL_POINTER
    //                UMXDB_ERROR_USERINFO_CARD_NULL_STRING
    //                UMXDB_ERROR_USERINFO_SELECT_BY_CARD
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_selectAllUserInfoes_ADR(UMXDB_HANDLE handle, std::vector<UserInfoData_ADR> *retAllUserInfoes);

    int _UMXDB_EXPORT umxDB_selectAllUserInfoes(UMXDB_HANDLE handle, std::vector<UserInfoData> *retAllUserInfoes);
    // Select userinfo by card number.
    //
    // handle[in] - UMXDB_HANDLE value
    // card[in] - card number
    // retUserInfo[out] - struct UserInfoData's data
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_IN_ARGUMENTS_USERINFO_VECTOR_NULL_POINTER
    //                UMXDB_EXCEPTION_USERINFO_SELECT_ALL
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_selectUserInfoByPage_ADR(UMXDB_HANDLE handle, const int page, const int pageSize,
                                                std::vector<UserInfoData_ADR> *retAllUserInfo);

    int _UMXDB_EXPORT umxDB_selectUserInfoByPage(UMXDB_HANDLE handle, const int page, const int pageSize,
                                                std::vector<UserInfoData> *retAllUserInfo);
    // Select userinfo by page
    //
    // handle[in] - UMXDB_HANDLE value
    // page[int] - page
    // pageSize[in] - page size
    // retAllUserInfo[out] - struct UserInfoData's data list
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_IN_ARGUMENTS_USERINFO_VECTOR_NULL_POINTER
    //                UMXDB_ERROR_PAGE_INVALID
    //                UMXDB_ERROR_PAGESIZE_INVALID
    //                UMXDB_EXCEPTION_USERINFO_SELECT_BY_PAGE
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_updateUserInfoByUUID_ADR(UMXDB_HANDLE handle, const char* uuid, const char* card, const char* pin,
                                                           const int admin, const int groupIndex, const int byPassCard, const int indivisual,
                                                           const int threeOutStatus, const int threeOutAccessAllowed, const int jobCode, const int timeScheduleCode,
                                                           const int apbStatus, const std::string message);

    int _UMXDB_EXPORT umxDB_updateUserInfoByUUID(UMXDB_HANDLE handle, const std::string uuid, const std::string card, const std::string pin,
                                                           const int admin, const int groupIndex, const int byPassCard, const int indivisual,
                                                           const int threeOutStatus, const int threeOutAccessAllowed, const int jobCode, const int timeScheduleCode,
                                                           const int apbStatus, const std::string message);
    // Update userinfo by uuid.
    //
    // handle[in] - UMXDB_HANDLE value
    // uuid[in] - unique id
    // card[in] - card number
    // pin[in] - pin number
    // admin[in] - admin authorization
    // groupIndex[in] - group index
    // indivisual[in] - indivisual mode
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_UUID_NULL_STRING
    //                UMXDB_ERROR_USERINFO_COUNT_UUID_NO_EXIST
    //                UMXDB_ERROR_USERINFO_COUNT_UUID
    //                UMXDB_EXCEPTION_USERINFO_COUNT_UUID
    //                UMXDB_EXCEPTION_USERINFO_UPDATE_BY_UUID
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_deleteUserInfoByUUID_ADR(UMXDB_HANDLE handle, const char* uuid);

    int _UMXDB_EXPORT umxDB_deleteUserInfoByUUID(UMXDB_HANDLE handle, const std::string uuid);
    // Delete userinfo by uuid.
    //
    // handle[in] - UMXDB_HANDLE value
    // uuid[in] - unique id
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_UUID_NULL_STRING
    //                UMXDB_ERROR_USERINFO_COUNT_UUID_NO_EXIST
    //                UMXDB_ERROR_USERINFO_COUNT_UUID
    //                UMXDB_EXCEPTION_USERINFO_COUNT_UUID
    //                UMXDB_ERROR_USERINFO_DELETE_BY_UUID
    //                UMXDB_EXCEPTION_SUBJECT_VACUUM_SERVICE
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_deleteCardInfoByUUID(UMXDB_HANDLE handle, const std::string uuid);
    // Delete userinfo by uuid.
    //
    // handle[in] - UMXDB_HANDLE value
    // uuid[in] - unique id
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_UUID_NULL_STRING
    //                UMXDB_ERROR_CARDINFO_COUNT_UUID_NO_EXIST
    //                UMXDB_ERROR_CARDINFO_COUNT_UUID
    //                UMXDB_EXCEPTION_CARDINFO_COUNT_UUID
    //                UMXDB_ERROR_CARDINFO_DELETE_BY_UUID
    //                UMXDB_EXCEPTION_SUBJECT_VACUUM_SERVICE
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_deleteAllUserInfoes(UMXDB_HANDLE handle);
    // Delete all userinfoes by uuid.
    //
    // handle[in] - UMXDB_HANDLE value
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_USERINFO_DELETE_ALL
    //                UMXDB_EXCEPTION_SUBJECT_VACUUM_SERVICE
    //                UMXDB_SUCCESS

    /// ^^^^ "/usr/local/share/CMITECH/Service.db" - userinfo table ^^^^


    /// vvvv "/usr/local/share/CMITECH/ServiceLog.db" - event_log table vvvv

    int _UMXDB_EXPORT umxDB_insertLog_ADR(UMXDB_HANDLE handle, const char* type, const char* uuid, const char* info, const char* message, const char* matchedFaceImage, int matchedFaceImageSize);

    int _UMXDB_EXPORT umxDB_insertLog(UMXDB_HANDLE handle, const std::string& type, const std::string& uuid, const std::string& info, const std::string& message, const char* matchedFaceImage, int matchedFaceImageSize, std::string timestamp);
    // Insert log into event_log table of ServiceLog.db.
    //
    // handle[in] - UMXDB_HANDLE value
    // type[in] - EventType in event_log table of ServiceLog.db
    // info[in] - Info in event_log table of ServiceLog.db
    // message[in] - AdditionalData in event_log table of ServiceLog.db
    // matchedFaceImage[in] - matched face image for log
    // matchedFaceImageSize[in] - matched face image size
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_EXCEPTION_EVENTLOG_INSERT
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_countLog(UMXDB_HANDLE handle, int* count);
    // Count log
    //
    // handle[in] - UMXDB_HANDLE value
    // count[out] - log count
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_IN_ARGUMENTS_LOG_COUNT_NULL_POINTER
    //                UMXDB_EXCEPTION_EVENTLOG_LOG_COUNT
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_countImageLog(UMXDB_HANDLE handle, int* count);
    // Count log
    //
    // handle[in] - UMXDB_HANDLE value
    // count[out] - image log count
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_IN_ARGUMENTS_EVENTLOG_Image_LOG_COUNT_NULL_POINTER
    //                UMXDB_EXCEPTION_EVENTLOG_IMAGE_LOG_COUNT
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_selectLastLogID(UMXDB_HANDLE handle, int* lastLogID);
    // Select LogEntry.
    //
    // handle[in] - UMXDB_HANDLE value
    // lastLogID[out] - Last Log ID
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_IN_ARGUMENTS_EVENTLOG_LOGID_NULL_POINTER
    //                UMXDB_ERROR_EVENTLOG_SELECT_BY_LAST_LOGID
    //                UMXDB_EXCEPTION_EVENTLOG_SELECT_BY_LAST_LOGID
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_selectLogEntryFromTo_ADR(UMXDB_HANDLE handle, const int fromId, const int toId, std::vector<LogEntry_ADR> *retLogEntry);

    int _UMXDB_EXPORT umxDB_selectLogEntryFromTo(UMXDB_HANDLE handle, const int fromId, const int toId, std::vector<LogEntry> *retLogEntry);
    // Select LogEntry from id to id.
    //
    // handle[in] - UMXDB_HANDLE value
    // fromId[in] - from id
    // toId[in] - to id
    //
    // retLogEntry[out] - LogEntry class's instance list
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_IN_ARGUMENTS_EVENTLOG_VECTOR_NULL_POINTER
    //                UMXDB_ERROR_EVENTLOG_LOGID_FROM_TO_WRONG_RANGE
    //                UMXDB_EXCEPTION_EVENTLOG_SELECT_LOGS_BY_LOGID_FROM_TO
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_selectLogEntryFromToByPage_ADR(UMXDB_HANDLE handle, const int pageNumber, const int pageSize, const int fromId, const int toId, std::vector<LogEntry_ADR> *retLogEntry);

    int _UMXDB_EXPORT umxDB_selectLogEntryFromToByPage(UMXDB_HANDLE handle, const int pageNumber, const int pageSize, const int fromId, const int toId, std::vector<LogEntry> *retLogEntry);
    // Select LogEntry from id to id by page.
    //
    // handle[in] - UMXDB_HANDLE value
    // pageNumber[in] - page number
    // pageSize[in] - page size
    // fromId[in] - from id
    // toId[in] - to id
    // retLogEntry[out] - LogEntry class's instance list
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_IN_ARGUMENTS_EVENTLOG_VECTOR_NULL_POINTER
    //                UMXDB_ERROR_PAGE_INVALID
    //                UMXDB_ERROR_PAGESIZE_INVALID
    //                UMXDB_ERROR_EVENTLOG_LOGID_FROM_TO_WRONG_RANGE
    //                UMXDB_EXCEPTION_EVENTLOG_SELECT_LOG_PAGE_BY_LOGID_FROM_TO_INVALID_PAGE
    //                UMXDB_EXCEPTION_EVENTLOG_SELECT_LOG_PAGE_BY_LOGID_FROM_TO
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_selectLogEntryFromCount(UMXDB_HANDLE handle, const int fromId, const int count, std::vector<LogEntry> *retLogEntry);
    // Select LogEntry from id to id by page.
    //
    // handle[in] - UMXDB_HANDLE value
    // fromId[in] - from id
    // count[in] - limit count
    // retLogEntry[out] - LogEntry class's instance list
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_IN_ARGUMENTS_EVENTLOG_VECTOR_NULL_POINTER
    //                UMXDB_ERROR_PAGE_INVALID
    //                UMXDB_ERROR_PAGESIZE_INVALID
    //                UMXDB_ERROR_EVENTLOG_LOGID_FROM_TO_WRONG_RANGE
    //                UMXDB_EXCEPTION_EVENTLOG_SELECT_LOG_PAGE_BY_LOGID_FROM_TO_INVALID_PAGE
    //                UMXDB_EXCEPTION_EVENTLOG_SELECT_LOG_PAGE_BY_LOGID_FROM_TO
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_selectLogEntryByPage_ADR(UMXDB_HANDLE handle, const int pageNumber, const int pageSize, const char* order, std::vector<LogEntry_ADR> *retLogEntry);

    int _UMXDB_EXPORT umxDB_selectLogEntryByPage(UMXDB_HANDLE handle, const int pageNumber, const int pageSize, const std::string& order, std::vector<LogEntry> *retLogEntry);
    // Select LogEntry.
    //
    // handle[in] - UMXDB_HANDLE value
    // pageNumber[in] - page number
    // pageSize[in] - page size
    // order[in] - sql query's order by
    // retLogEntry[out] - LogEntry class's instance list
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_IN_ARGUMENTS_EVENTLOG_VECTOR_NULL_POINTER
    //                UMXDB_ERROR_PAGE_INVALID
    //                UMXDB_ERROR_PAGESIZE_INVALID
    //                UMXDB_EXCEPTION_EVENTLOG_SELECT_BY_PAGE_INVALID_PAGE
    //                UMXDB_EXCEPTION_EVENTLOG_SELECT_BY_PAGE
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_selectLogEntryById_ADR(UMXDB_HANDLE handle, const int id, LogEntry_ADR* logEntry);

    int _UMXDB_EXPORT umxDB_selectLogEntryById(UMXDB_HANDLE handle, const int id, LogEntry* logEntry);
    // Select LogEntry by id.
    //
    // handle[in] - UMXDB_HANDLE value
    // id[in] - log id
    // logEntry[out] - LogEntry class's instance
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_IN_ARGUMENTS_EVENTLOG_NULL_POINTER
    //                UMXDB_EXCEPTION_EVENTLOG_SELECT_BY_LOGID
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_selectImageLogs(UMXDB_HANDLE handle, std::vector<int> *retImageLogID);
    // Select selectImageLogs.
    //
    // handle[in] - UMXDB_HANDLE value
    // retImageLogID[out] - Image Log ID list
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_IN_ARGUMENTS_EVENTLOG_NULL_POINTER
    //                UMXDB_EXCEPTION_EVENTLOG_SELECT_IMAGE_LOGS
    //                UMXDB_SUCCESS


    int _UMXDB_EXPORT umxDB_deleteLogEntryFromTo(UMXDB_HANDLE handle, const int fromId, const int toId);
    // Delete LogEntry from id to id.
    //
    // handle[in] - UMXDB_HANDLE value
    // fromId[in] - from id
    // toId[in] - to id
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_EVENTLOG_LOGID_FROM_TO_WRONG_RANGE
    //                UMXDB_ERROR_EVENTLOG_DELETE_BY_LOGID_FROM_TO
    //                UMXDB_EXCEPTION_EVENTLOG_VACUUM_SERVICELOG
    //                UMXDB_SUCCESS

    //int _UMXDB_EXPORT umxDB_deleteLogEntryById(UMXDB_HANDLE handle, const int id);
    int _UMXDB_EXPORT umxDB_deleteLogEntryById(UMXDB_HANDLE handle, const int id, bool* isImage);
    // Delete LogEntry by id.
    //
    // handle[in] - UMXDB_HANDLE value
    // id[in] - from id
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_EVENTLOG_DELETE_BY_LOGID
    //                UMXDB_EXCEPTION_SUBJECT_VACUUM_SERVICE
    //                UMXDB_SUCCESS

    //int _UMXDB_EXPORT umxDB_deleteFirstLog(UMXDB_HANDLE handle);
    int _UMXDB_EXPORT umxDB_deleteFirstLog(UMXDB_HANDLE handle, bool* isImage);
    // Delete First Log.
    //
    // handle[in] - UMXDB_HANDLE value
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_EVENTLOG_DELETE_FIRST_LOG
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_deleteFirstImageLog(UMXDB_HANDLE handle);
    // Delete First Image Log.
    //
    // handle[in] - UMXDB_HANDLE value
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_EVENTLOG_DELETE_FIRST_IMAGE_LOG
    //                UMXDB_SUCCESS

    /// ^^^^ "/usr/local/share/CMITECH/ServiceLog.db" - event_log table ^^^^
    /// vvvv "/usr/local/share/CMITECH/ServiceLog.db" - image_capture table vvvv

    int _UMXDB_EXPORT umxDB_selectImageCapture_ADR(UMXDB_HANDLE handle, std::vector<ImageCapture_ADR> *retImageCapture);

    int _UMXDB_EXPORT umxDB_selectImageCapture(UMXDB_HANDLE handle, std::vector<ImageCapture> *retImageCapture);
    // Select ImageCapture.
    //
    // handle[in] - UMXDB_HANDLE value
    // retImageCapture[out] - ImageCapture class's instance list
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_IN_ARGUMENTS_IMAGECAPTURE_VECTOR_NULL_POINTER
    //                UMXDB_EXCEPTION_IMAGECAPTURE_SELECT_ALL
    //                UMXDB_SUCCESS

    /// ^^^^ "/usr/local/share/CMITECH/ServiceLog.db" - image_capture table ^^^^


    /// vvvv for deleting once - subject, face, userinfo vvvv

    int _UMXDB_EXPORT umxDB_deleteUserByUUID(UMXDB_HANDLE handle, const std::string uuid);
    // Delete user by uuid.
    //
    // handle[in] - UMXDB_HANDLE value
    // uuid[in] - user unique id
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_UUID_NULL_STRING
    //                UMXDB_ERROR_SUBJECT_COUNT_UUID_NO_EXIST
    //                UMXDB_ERROR_SUBJECT_COUNT_UUID
    //                UMXDB_EXCEPTION_SUBJECT_COUNT_UUID
    //                UMXDB_ERROR_SUBJECT_DELETE_BY_UUID
    //                UMXDB_EXCEPTION_SUBJECT_DELETE_BY_UUID
    //                UMXDB_ERROR_USERINFO_COUNT_UUID_NO_EXIST
    //                UMXDB_ERROR_USERINFO_COUNT_UUID
    //                UMXDB_EXCEPTION_USERINFO_COUNT_UUID
    //                UMXDB_ERROR_USERINFO_DELETE_BY_UUID
    //                UMXDB_EXCEPTION_USERINFO_DELETE
    //                UMXDB_ERROR_FACE_COUNT_UUID_NO_EXIST
    //                UMXDB_ERROR_FACE_COUNT_UUID
    //                UMXDB_EXCEPTION_FACE_COUNT_UUID_AND_SUBID
    //                UMXDB_ERROR_FACE_DELETE_BY_UUID
    //                UMXDB_EXCEPTION_FACE_DELETE_BY_UUID
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_deleteUserByUUIDList(UMXDB_HANDLE handle, const std::vector<std::string> deleteUsers);
    // Delete user by uuid list.
    //
    // handle[in] - UMXDB_HANDLE value
    // deleteUsers[in] - user unique id list
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_UUID_NULL_STRING
    //                UMXDB_ERROR_SUBJECT_DELETE_BY_UUID
    //                UMXDB_EXCEPTION_SUBJECT_DELETE_BY_UUID
    //                UMXDB_ERROR_USERINFO_DELETE_BY_UUID
    //                UMXDB_EXCEPTION_USERINFO_DELETE
    //                UMXDB_ERROR_FACE_DELETE_BY_UUID
    //                UMXDB_EXCEPTION_FACE_DELETE_BY_UUID
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_deleteAllUsers(UMXDB_HANDLE handle);
    // Delete all users of subject, face, userinfo table.
    //
    // handle[in] - UMXDB_HANDLE value
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_SUBJECT_DELETE_ALL
    //                UMXDB_ERROR_FACE_DELETE_ALL
    //                UMXDB_ERROR_USERINFO_DELETE_ALL
    //                UMXDB_EXCEPTION_SUBJECT_VACUUM_SERVICE
    //                UMXDB_SUCCESS

    /// ^^^^ for deleting once - subject, face, userinfo ^^^^


    /// vvvv special function vvvv

    int _UMXDB_EXPORT umxDB_getUUIDList_ADR(UMXDB_HANDLE handle, std::vector<char*> *retUuidList);

    int _UMXDB_EXPORT umxDB_getUUIDList(UMXDB_HANDLE handle, std::vector<std::string> *retUuidList);
    // Delete all users of subject, face, userinfo table.
    //
    // handle[in] - UMXDB_HANDLE value
    // retUuidList[out] - UMXDB_HANDLE value
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_IN_ARGUMENTS_SUBJECT_UUID_VECTOR_NULL_POINTER
    //                UMXDB_EXCEPTION_SUBJECT_SELECT_ALL_UUID
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_isExistAdmin(UMXDB_HANDLE handle, int* existCnt);
    // Check if admin is exist.
    //
    // handle[in] - UMXDB_HANDLE value
    // existCnt[out] - existing admin count
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_IN_ARGUMENTS_USERINFO_ADMIN_COUNT_NULL_POINTER
    //                UMXDB_EXCEPTION_SUBJECT_COUNT_ADMIN
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_isExistUUID_ADR(UMXDB_HANDLE handle, const char* uuid, int* exist);

    int _UMXDB_EXPORT umxDB_isExistUUID(UMXDB_HANDLE handle, const std::string uuid, int* exist);
    // Check if uuid is exist.
    //
    // handle[in] - UMXDB_HANDLE value
    // uuid[in] - existing admin count
    // exist[out] - existing uuid count
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_IN_ARGUMENTS_SUBJECT_UUID_EXIST_NULL_POINTER
    //                UMXDB_ERROR_UUID_NULL_STRING
    //                UMXDB_ERROR_SUBJECT_COUNT_UUID_NO_EXIST
    //                UMXDB_ERROR_SUBJECT_COUNT_UUID
    //                UMXDB_EXCEPTION_SUBJECT_COUNT_UUID
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_cntFaceByUUIDAndSubId_ADR(UMXDB_HANDLE handle, const char* uuid, const int subid, int* cnt);

    int _UMXDB_EXPORT umxDB_cntFaceByUUIDAndSubId(UMXDB_HANDLE handle, const std::string uuid, const int subid, int* cnt);
    // Count face in DB by uuid and subid.
    //
    // handle[in] - UMXDB_HANDLE value
    // uuid[in] - user unique id
    // subid[in] - face sub id
    // cnt[out] - face count
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_IN_ARGUMENTS_FACE_UUID_AND_SUBID_COUNT_NULL_POINTER
    //                UMXDB_ERROR_UUID_NULL_STRING
    //                UMXDB_ERROR_FACE_SUBID_OUT_OF_RANGE
    //                UMXDB_ERROR_FACE_COUNT_UUID_AND_SUBID_NO_EXIST
    //                UMXDB_ERROR_FACE_COUNT_UUID_AND_SUBID
    //                UMXDB_SUCCESS

#if 1 //Improve #117 : Search function added
    int _UMXDB_EXPORT umxDB_searchAllIrisByUUID_ADR(UMXDB_HANDLE handle, const char* uuid, std::vector<SubjectData_ADR> *retAllIrises);

    int _UMXDB_EXPORT umxDB_searchAllIrisByUUID(UMXDB_HANDLE handle, const std::string uuid, std::vector<SubjectData> *retAllIrises);
    // Search iris by uuid.
    //
    // handle[in] - UMXDB_HANDLE value
    // uuid[in] - contains id
    // retIris[out] - iris data
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_IN_ARGUMENTS_SUBJECT_VECTOR_NULL_POINTER
    //                UMXDB_ERROR_UUID_NULL_STRING
    //                UMXDB_EXCEPTION_SUBJECT_SEARCH_BY_UUID
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_searchAllIrisByName_ADR(UMXDB_HANDLE handle, const char* name, std::vector<SubjectData_ADR> *retAllIrises);

    int _UMXDB_EXPORT umxDB_searchAllIrisByName(UMXDB_HANDLE handle, const std::string name, std::vector<SubjectData> *retAllIrises);
    // Search iris by name.
    //
    // handle[in] - UMXDB_HANDLE value
    // name[in] - contains name
    // retIris[out] - iris data
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_IN_ARGUMENTS_SUBJECT_VECTOR_NULL_POINTER
    //                UMXDB_ERROR_SUBJECT_LASTNAME_NULL_STRING
    //                UMXDB_EXCEPTION_SUBJECT_SEARCH_BY_NAME
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_searchAllUserInfoesByUUID_ADR(UMXDB_HANDLE handle, const char* uuid, std::vector<UserInfoData_ADR> *retAllUserInfoes);

    int _UMXDB_EXPORT umxDB_searchAllUserInfoesByUUID(UMXDB_HANDLE handle, const std::string uuid, std::vector<UserInfoData> *retAllUserInfoes);
    // Select user info by uuid.
    //
    // handle[in] - UMXDB_HANDLE value
    // uuid[in] - unique id
    // retUserInfo[out] - struct UserInfoData's data
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_IN_ARGUMENTS_USERINFO_VECTOR_NULL_POINTER
    //                UMXDB_ERROR_UUID_NULL_STRING
    //                UMXDB_EXCEPTION_USERINFO_SEARCH_BY_UUID
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_searchAllLogs_ADR(UMXDB_HANDLE handle, const int pageNumber, const int pageSize, const char* order, const char* startDate, const char* endDate,
                                          const char* event, const char* info, const char* userID, const char* additionalData, std::vector<LogEntry_ADR> *retLogEntry);

    int _UMXDB_EXPORT umxDB_searchAllLogs(UMXDB_HANDLE handle, const int pageNumber, const int pageSize, const std::string& order, const std::string startDate, const std::string endDate,
                                          const std::string event, const std::string info, const std::string userID, const std::string additionalData, std::vector<LogEntry> *retLogEntry);
    // Select log info by date,event, t&a event, user id etc
    //
    // handle[in] - UMXDB_HANDLE value
    // pageNumber[in] - page number
    // pageSize[in] - page size
    // order[in] - sql query's order by
    // startDate[in] - start date
    // endDate[in] - end date
    // event[in] - event
    // info[in] - info
    // userID[in] - unique id
    // addtionalData[in] - addtional data
    // retLogEntry[out] - LogEntry class's instance list
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_IN_ARGUMENTS_EVENTLOG_VECTOR_NULL_POINTER
    //                UMXDB_ERROR_PAGE_INVALID
    //                UMXDB_ERROR_PAGESIZE_INVALID
    //                UMXDB_EXCEPTION_EVENTLOG_SEARCH_ALL_BY_CASES
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_isDeserializeIrisFeatureData(UMXDB_HANDLE handle, int recordVersion);
    // Check if serialized data is exist.
    //
    // handle[in] - UMXDB_HANDLE value
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_SUBJECT_COUNT_SERIALIZE_BY_RECORDVERSION
    //                UMXDB_EXCEPTION_SUBJECT_COUNT_SERIALIZE_BY_RECORDVERSION
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_getSerializeIrisFeatureData_ADR(UMXDB_HANDLE handle, int recordVersion, std::vector<SubjectData_ADR>* retIris);

    int _UMXDB_EXPORT umxDB_getSerializeIrisFeatureData(UMXDB_HANDLE handle, int recordVersion, std::vector<SubjectData>* retIris);
    // Get serialize data.
    //
    // handle[in] - UMXDB_HANDLE value
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_IN_ARGUMENTS_SUBJECT_VECTOR_NULL_POINTER
    //                UMXDB_EXCEPTION_SUBJECT_SELECT_BY_RECORDVERSION
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_setDeserializeIrisFeatureData_ADR(UMXDB_HANDLE handle, const SubjectData_ADR* subject);

    int _UMXDB_EXPORT umxDB_setDeserializeIrisFeatureData(UMXDB_HANDLE handle, const SubjectData* subject);
    // Set deserialize data.
    //
    // handle[in] - UMXDB_HANDLE value
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_IN_ARGUMENTS_SUBJECT_NULL_POINTER
    //                UMXDB_ERROR_UUID_NULL_STRING
    //                UMXDB_ERROR_SUBJECT_UPDATE_BY_RECORDVERSION
    //                UMXDB_EXCEPTION_SUBJECT_UPDATE_BY_RECORDVERSION
    //                UMXDB_SUCCESS


    int _UMXDB_EXPORT umxDB_setEncryptFaceFeatureData(UMXDB_HANDLE handle, unsigned char* src, int srcSize, unsigned char* ret, int* retSize);
    // Set encrypt data.
    //
    // handle[in] - UMXDB_HANDLE value
    // src[in] - feature data
    // srcSize[in] - feature data size
    // ret[out] - encrypted feature data
    // retSize[out] - encrypted feature data size
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_setEncryptFaceData(UMXDB_HANDLE handle, FaceData* subject);
    // Set encrypt data.
    //
    // handle[in] - UMXDB_HANDLE value
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_setEncryptIrisFeatureData(UMXDB_HANDLE handle, unsigned char* src, int srcSize, unsigned char* ret, int* retSize);
    // Set encrypt data.
    //
    // handle[in] - UMXDB_HANDLE value
    // src[in] - feature data
    // srcSize[in] - feature data size
    // ret[out] - encrypted feature data
    // retSize[out] - encrypted feature data size
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_setEncryptIrisSubjectData(UMXDB_HANDLE handle, SubjectData* subject);
    // Set encrypt data.
    //
    // handle[in] - UMXDB_HANDLE value
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_encryptPlainText(UMXDB_HANDLE handle, unsigned char* src, int srcSize, unsigned char* ret, int* retSize);
    // Set encrypt data.
    //
    // handle[in] - UMXDB_HANDLE value
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_setDecryptFaceFeatureData(UMXDB_HANDLE handle, unsigned char* src, int srcSize, unsigned char* ret, int* retSize);
    // Set decrypt data.
    //
    // handle[in] - UMXDB_HANDLE value
    // src[in] - feature data
    // srcSize[in] - feature data size
    // ret[out] - encrypted feature data
    // retSize[out] - encrypted feature data size
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_setDecryptFaceData(UMXDB_HANDLE handle, FaceData* face);
    // Set decrypt data.
    //
    // handle[in] - UMXDB_HANDLE value
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_setDecryptIrisFeatureData(UMXDB_HANDLE handle, unsigned char* src, int srcSize, unsigned char* ret, int* retSize);
    // Set decrypt data.
    //
    // handle[in] - UMXDB_HANDLE value
    // src[in] - feature data
    // srcSize[in] - feature data size
    // ret[out] - encrypted feature data
    // retSize[out] - encrypted feature data size
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_setDecryptIrisSubjectData(UMXDB_HANDLE handle, SubjectData* subject);
    // Set decrypt data.
    //
    // handle[in] - UMXDB_HANDLE value
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_checkLicense(UMXDB_HANDLE handle, const long maxNumOfUsers, const char* lic_path);
    // Check license for max number of users.
    //
    // handle[in] - UMXDB_HANDLE value
    // maxNumOfUsers[in] - maximum number of users
    // lic_path[in] - license file path
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_isEncryptedDB(UMXDB_HANDLE handle);
    // Check encrypted database.
    //
    // handle[in] - UMXDB_HANDLE value
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_setVersionInfoForEncryptedDB(UMXDB_HANDLE handle);
    // insert transaction database for version info.
    //
    // handle[in] - UMXDB_HANDLE value
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_setIrisAlgoType(UMXDB_HANDLE handle, const int type);
    // insert iris algorithm type info.
    //
    // handle[in] - UMXDB_HANDLE value
    // type[in] - algorithm type
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_setFaceAlgoType(UMXDB_HANDLE handle, const int type);
    // insert face algorithm type info.
    //
    // handle[in] - UMXDB_HANDLE value
    // type[in] - algorithm type
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_test_ADR(UMXDB_HANDLE handle, char* str0, std::string& str1, std::vector<std::string> *strAll, LogEntry* logEntry, ImageCapture* imageCapture);

    int _UMXDB_EXPORT umxDB_insertUser(UMXDB_HANDLE handle, SubjectData *subjectData, std::vector<FaceData>* faceDatas, UserInfoData* userInfoData, CardInfoData card_info);
    // Insert subject using SubjectData.
    //
    // handle[in] - UMXDB_HANDLE value
    // subjectData[in] - SubjectData type's iris data
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_UUID_NULL_STRING
    //                UMXDB_ERROR_SUBJECT_LASTNAME_NULL_STRING
    //                UMXDB_ERROR_SUBJECT_COUNT_UUID_ALREADY_EXIST
    //                UMXDB_ERROR_SUBJECT_COUNT_UUID
    //                UMXDB_EXCEPTION_SUBJECT_COUNT_UUID
    //                UMXDB_EXCEPTION_SUBJECT_INSERT
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_insertUser2(UMXDB_HANDLE handle, SubjectData *subjectData, std::vector<FaceData>* faceDatas, UserInfoData* userInfoData, std::vector<CardInfoData>* cardInfoDatas);
    // Insert subject using SubjectData.
    //
    // handle[in] - UMXDB_HANDLE value
    // subjectData[in] - SubjectData type's iris data
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_UUID_NULL_STRING
    //                UMXDB_ERROR_SUBJECT_LASTNAME_NULL_STRING
    //                UMXDB_ERROR_SUBJECT_COUNT_UUID_ALREADY_EXIST
    //                UMXDB_ERROR_SUBJECT_COUNT_UUID
    //                UMXDB_EXCEPTION_SUBJECT_COUNT_UUID
    //                UMXDB_EXCEPTION_SUBJECT_INSERT
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_deleteUserByUUID2(UMXDB_HANDLE handle, const std::string uuid);
    // Delete user by uuid.
    //
    // handle[in] - UMXDB_HANDLE value
    // uuid[in] - user unique id
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_UUID_NULL_STRING
    //                UMXDB_ERROR_SUBJECT_COUNT_UUID_NO_EXIST
    //                UMXDB_ERROR_SUBJECT_COUNT_UUID
    //                UMXDB_EXCEPTION_SUBJECT_COUNT_UUID
    //                UMXDB_ERROR_SUBJECT_DELETE_BY_UUID
    //                UMXDB_EXCEPTION_SUBJECT_DELETE_BY_UUID
    //                UMXDB_ERROR_USERINFO_COUNT_UUID_NO_EXIST
    //                UMXDB_ERROR_USERINFO_COUNT_UUID
    //                UMXDB_EXCEPTION_USERINFO_COUNT_UUID
    //                UMXDB_ERROR_USERINFO_DELETE_BY_UUID
    //                UMXDB_EXCEPTION_USERINFO_DELETE
    //                UMXDB_ERROR_FACE_COUNT_UUID_NO_EXIST
    //                UMXDB_ERROR_FACE_COUNT_UUID
    //                UMXDB_EXCEPTION_FACE_COUNT_UUID_AND_SUBID
    //                UMXDB_ERROR_FACE_DELETE_BY_UUID
    //                UMXDB_EXCEPTION_FACE_DELETE_BY_UUID
    //                UMXDB_SUCCESS

#endif

    int _UMXDB_EXPORT umxDB_integrityServiceDB(UMXDB_HANDLE handle);
    // Integrity check (Service.db)
    //
    // handle[in] - UMXDB_HANDLE value
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_UUID_NULL_STRING
    //                UMXDB_ERROR_SUBJECT_LASTNAME_NULL_STRING
    //                UMXDB_ERROR_SUBJECT_COUNT_UUID_ALREADY_EXIST
    //                UMXDB_ERROR_SUBJECT_COUNT_UUID
    //                UMXDB_EXCEPTION_SUBJECT_COUNT_UUID
    //                UMXDB_EXCEPTION_SUBJECT_INSERT
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_integrityServiceLogDB(UMXDB_HANDLE handle);
    // Integrity check (ServiceLog.db)
    //
    // handle[in] - UMXDB_HANDLE value
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_UUID_NULL_STRING
    //                UMXDB_ERROR_SUBJECT_LASTNAME_NULL_STRING
    //                UMXDB_ERROR_SUBJECT_COUNT_UUID_ALREADY_EXIST
    //                UMXDB_ERROR_SUBJECT_COUNT_UUID
    //                UMXDB_EXCEPTION_SUBJECT_COUNT_UUID
    //                UMXDB_EXCEPTION_SUBJECT_INSERT
    //                UMXDB_SUCCESS


    int _UMXDB_EXPORT umxDB_selectUserScheduleUsed(UMXDB_HANDLE handle, std::string id);
    // select pattern for user
    //
    // handle[in] - UMXDB_HANDLE value
    // id[in] - user unique id
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_UUID_NULL_STRING
    //                UMXDB_ERROR_SUBJECT_LASTNAME_NULL_STRING
    //                UMXDB_ERROR_SUBJECT_COUNT_UUID_ALREADY_EXIST
    //                UMXDB_ERROR_SUBJECT_COUNT_UUID
    //                UMXDB_EXCEPTION_SUBJECT_COUNT_UUID
    //                UMXDB_EXCEPTION_SUBJECT_INSERT
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_selectScheduleTypeInfoByUser(UMXDB_HANDLE handle, std::string uuid);
    // select type_info for user
    //
    // handle[in] - UMXDB_HANDLE value
    // uuid[in] - user id (if type is device)
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_UUID_NULL_STRING
    //                UMXDB_ERROR_SUBJECT_LASTNAME_NULL_STRING
    //                UMXDB_ERROR_SUBJECT_COUNT_UUID_ALREADY_EXIST
    //                UMXDB_ERROR_SUBJECT_COUNT_UUID
    //                UMXDB_EXCEPTION_SUBJECT_COUNT_UUID
    //                UMXDB_EXCEPTION_SUBJECT_INSERT
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_selectScheduleTypeInfoByDevice(UMXDB_HANDLE handle, int sc_idx);
    // select type_info for device
    //
    // handle[in] - UMXDB_HANDLE value
    // sc_idx[in] - schedule type value
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_UUID_NULL_STRING
    //                UMXDB_ERROR_SUBJECT_LASTNAME_NULL_STRING
    //                UMXDB_ERROR_SUBJECT_COUNT_UUID_ALREADY_EXIST
    //                UMXDB_ERROR_SUBJECT_COUNT_UUID
    //                UMXDB_EXCEPTION_SUBJECT_COUNT_UUID
    //                UMXDB_EXCEPTION_SUBJECT_INSERT
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_selectUserScheduleDataByUUID(UMXDB_HANDLE handle, std::string uuid, UserScheduleData *retUserScheduleData);
    // select schedule data for user
    //
    // handle[in] - UMXDB_HANDLE value
    // uuid[in] - user unique id
    // retUserScheduleData[out] - schedule data
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_UUID_NULL_STRING
    //                UMXDB_ERROR_SUBJECT_LASTNAME_NULL_STRING
    //                UMXDB_ERROR_SUBJECT_COUNT_UUID_ALREADY_EXIST
    //                UMXDB_ERROR_SUBJECT_COUNT_UUID
    //                UMXDB_EXCEPTION_SUBJECT_COUNT_UUID
    //                UMXDB_EXCEPTION_SUBJECT_INSERT
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_deleteAllScheduleData(UMXDB_HANDLE handle);
    // delete all schedule data
    //
    // handle[in] - UMXDB_HANDLE value
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_deleteScheduleDataByUUID(UMXDB_HANDLE handle, std::string uuid);
    // delete schedule data for specific user
    //
    // handle[in] - UMXDB_HANDLE value
    // uuid[in] - user id
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_UUID_NULL_STRING
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_insertScheduleData(UMXDB_HANDLE handle, UserScheduleData* data);
    // delete schedule data for specific user
    //
    // handle[in] - UMXDB_HANDLE value
    // UserScheduleData[in] - user schedule data
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_UUID_NULL_STRING
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_updateScheduleData(UMXDB_HANDLE handle, UserScheduleData* data);
    // update schedule data for specific user
    //
    // handle[in] - UMXDB_HANDLE value
    // UserScheduleData[in] - user schedule data
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_UUID_NULL_STRING
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_selectScheduleInfo(UMXDB_HANDLE handle, const int scIdx, const int siIdx, std::vector<Schedule>* retData);
    // select schedule info
    //
    // handle[in] - UMXDB_HANDLE value
    // scIdx[in] - schedule code
    // siIdx[in] - schedule repeating cycle number
    // retData[out] - schedule info
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_UUID_NULL_STRING
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_selectScheduleSpecialDay(UMXDB_HANDLE handle, const std::string sdType, const std::string uuid, std::string sdDate, std::vector<ScheduleSpecialDay>* retData);
    // select schedule special day
    //
    // handle[in] - UMXDB_HANDLE value
    // sdType[in] - device and user classification
    // uuid[in] - user id
    // sdDate[in] - schedule date
    // retData[out] - schedule special day
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_UUID_NULL_STRING
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_selectScheduleTypeInfo(UMXDB_HANDLE handle, const int stiIdx, const int stIdx, std::vector<ScheduleTypeInfo>* retData);
    // select schedule type info
    //
    // handle[in] - UMXDB_HANDLE value
    // stiIdx[in] - main key
    // stIdx[in] - sub key
    // retData[out] - schedule type info
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_UUID_NULL_STRING
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_deleteScheduleBySchedule(UMXDB_HANDLE handle, Schedule* data);
    // delete schedule
    //
    // handle[in] - UMXDB_HANDLE value
    // data[in] - schedule data pointer
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_UUID_NULL_STRING
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_deleteScheduleByScheduleSpecialDay(UMXDB_HANDLE handle, ScheduleSpecialDay* data);
    // delete schedule special day
    //
    // handle[in] - UMXDB_HANDLE value
    // data[in] - ScheduleSpecialDay data pointer
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_UUID_NULL_STRING
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_deleteScheduleByScheduleTypeInfo(UMXDB_HANDLE handle, ScheduleTypeInfo* data);
    // delete schedule type info
    //
    // handle[in] - UMXDB_HANDLE value
    // data[in] - ScheduleTypeInfo data pointer
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_UUID_NULL_STRING
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_insertScheduleBySchedule(UMXDB_HANDLE handle, Schedule* data);
    // insert schedule
    //
    // handle[in] - UMXDB_HANDLE value
    // data[in] - schedule data pointer
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_UUID_NULL_STRING
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_insertScheduleByScheduleSpecialDay(UMXDB_HANDLE handle, ScheduleSpecialDay* data);
    // insert schedule special day
    //
    // handle[in] - UMXDB_HANDLE value
    // data[in] - ScheduleSpecialDay data pointer
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_UUID_NULL_STRING
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_insertScheduleByScheduleTypeInfo(UMXDB_HANDLE handle, ScheduleTypeInfo* data);
    // insert schedule type info
    //
    // handle[in] - UMXDB_HANDLE value
    // data[in] - ScheduleTypeInfo data pointer
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_UUID_NULL_STRING
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_updateScheduleBySchedule(UMXDB_HANDLE handle, Schedule* data);
    // update schedule
    //
    // handle[in] - UMXDB_HANDLE value
    // data[in] - schedule data pointer
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_UUID_NULL_STRING
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_updateScheduleByScheduleSpecialDay(UMXDB_HANDLE handle, ScheduleSpecialDay* data);
    // update schedule special day
    //
    // handle[in] - UMXDB_HANDLE value
    // data[in] - ScheduleSpecialDay data pointer
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_UUID_NULL_STRING
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_updateScheduleByScheduleTypeInfo(UMXDB_HANDLE handle, ScheduleTypeInfo* data);
    // update schedule type info
    //
    // handle[in] - UMXDB_HANDLE value
    // data[in] - ScheduleTypeInfo data pointer
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_UUID_NULL_STRING
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_updateUserScheduleByUsersInfoData(UMXDB_HANDLE handle, std::vector<UserInfoData>* data);
    // update schedule code to userinfo table
    //
    // handle[in] - UMXDB_HANDLE value
    // data[in] - userinfodata pointer
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_UUID_NULL_STRING
    //                UMXDB_SUCCESS


    /// ^^^^ special function ^^^^

#ifdef __cplusplus
} // extern "C"
#endif

#endif // UMXDB_H
