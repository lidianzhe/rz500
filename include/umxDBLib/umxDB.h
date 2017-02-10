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
#include "umxAlgoLib/umxAlgoGlobal.h"
#include "umxCamLib/umxCamGlobal.h"
#include "umxCommonLib/umxCommonGlobal.h"

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

    void _UMXDB_EXPORT umxDB_getVersion(unsigned int *major, unsigned int *minor, unsigned int *revision);
    // Get umxDB version and revision number for compatibility.
    // Application should check if major version number is consistent.
    //
    // major[out]
    // minor[out]
    // revision[out]

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
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_vacuumServiceLog(UMXDB_HANDLE handle);
    // Vacuum ServiceLog.db
    //
    // handle[in] - UMXDB_HANDLE value
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_SUCCESS

    /// vvvv "/usr/local/share/CMITECH/Service.db" - subject table vvvv

    int _UMXDB_EXPORT umxDB_insertSubject(UMXDB_HANDLE handle, const SubjectData &subjectData);
    // Insert subject using SubjectData.
    //
    // handle[in] - UMXDB_HANDLE value
    // subjectData[in] - SubjectData type's iris data
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_EXIST_UUID
    //                UMXDB_ERROR_FAIL_TO_INSERT_SUBJECT
    //                UMXDB_SUCCESS

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
    //                UMXDB_ERROR_EXIST_UUID
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_insertIris2(UMXDB_HANDLE handle, SubjectData *subjectData);
    // Insert iris using SubjectData.
    //
    // handle[in] - UMXDB_HANDLE value
    // subjectData[in] - SubjectData type's iris data
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_EXIST_UUID
    //                UMXDB_ERROR_FAIL_TO_INSERT_SUBJECT
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_selectIrisesByPage(UMXDB_HANDLE handle, const int page, const int pageSize, std::vector<SubjectData> *retIrises);
    // Select iris by page.
    //
    // handle[in] - UMXDB_HANDLE value
    // page[in] - page
    // pageSize[in] - page size
    // retIrises[out] - SubjectData type's data list
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_selectIrisByUUID(UMXDB_HANDLE handle, const std::string uuid, SubjectData *retIris);
    // Select iris by uuid.
    //
    // handle[in] - UMXDB_HANDLE value
    // uuid[in] - unique id
    // retIris[out] - iris data
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_selectAllIrises(UMXDB_HANDLE handle, std::vector<SubjectData> *retAllIrises);
    // Select iris by uuid.
    //
    // handle[in] - UMXDB_HANDLE value
    // uuid[in] - unique id
    // retIris[out] - iris data
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_updateSubject(UMXDB_HANDLE handle, const SubjectData &subjectData);
    // Update subject.
    //
    // handle[in] - UMXDB_HANDLE value
    // subjectData[in] - SubjectData
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_NO_EXIST_UUID
    //                UMXDB_SUCCESS

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

    int _UMXDB_EXPORT umxDB_updateIrisByUUID2(UMXDB_HANDLE handle, const std::string uuid, SubjectData &subjectData);
    // Update iris by uuid.
    //
    // handle[in] - UMXDB_HANDLE value
    // uuid[in] - unique id to update database
    // subjectData[in] - SubjectData type's iris data to update database
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_NO_EXIST_UUID
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_updateNameByUUID(UMXDB_HANDLE handle, const std::string uuid, const std::string name);
    // Update user name in subject table by uuid.
    //
    // handle[in] - UMXDB_HANDLE value
    // uuid[in] - unique id to update database
    // name[in] - user name to update
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_NO_EXIST_UUID
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_deleteIrisByUUID(UMXDB_HANDLE handle, const std::string uuid);
    // Delete iris in subject table by uuid.
    //
    // handle[in] - UMXDB_HANDLE value
    // uuid[in] - unique id to update database
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_NO_EXIST_UUID
    //                UMXDB_ERROR_DELETE
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_deleteAllIrises(UMXDB_HANDLE handle);
    // Delete all irises in subject table.
    //
    // handle[in] - UMXDB_HANDLE value
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_DELETE
    //                UMXDB_SUCCESS

    /// ^^^^ "/usr/local/share/CMITECH/Service.db" - subject table ^^^^


    /// vvvv "/usr/local/share/CMITECH/Service.db" - face table vvvv

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
    //                UMXDB_ERROR_EXIST_UUID_AND_SUBID
    //                UMXDB_ERROR_NO_FACE_INFO
    //                UMXDB_ERROR_NO_FACE_FEATURE
    //                UMXDB_ERROR_FAIL_TO_INSERT_FACE
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_insertFace2(UMXDB_HANDLE handle, FaceData* faceData);
    // Insert face using struct FaceData.
    //
    // handle[in] - UMXDB_HANDLE value
    // faceDate[in] - struct FaceData's data
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_EXIST_UUID_AND_SUBID
    //                UMXDB_ERROR_FAIL_TO_INSERT_FACE
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_selectFaceByUuIdAndSubId(UMXDB_HANDLE handle, const std::string uuid, const int subId, FaceData *faceData);
    // Select face by uuid and subid
    //
    // handle[in] - UMXDB_HANDLE value
    // uuid[in] - unique id
    // subId[in] - face sub id
    // faceData[out] - struct FaceData's data
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_selectFacesByUUID(UMXDB_HANDLE handle, const std::string uuid, std::vector<FaceData> *retFaces);
    // Select face by uuid
    //
    // handle[in] - UMXDB_HANDLE value
    // uuid[in] - unique id
    // retFaces[out] - struct FaceData's data list
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_selectFacesForMemory(UMXDB_HANDLE handle, std::vector<FaceData> *retFaces);
    // Select faces for memory (feature is not null and eye width is not out of range)
    //
    // handle[in] - UMXDB_HANDLE value
    // retFaces[out] - struct FaceData's data list
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_selectIrisForMemory(UMXDB_HANDLE handle, std::vector<SubjectData> *retIris);
    // Select iris for memory (feature is not null and eye width is not out of range)
    //
    // handle[in] - UMXDB_HANDLE value
    // retIris[out] - struct SubjectData's data list
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_selectAllFaces(UMXDB_HANDLE handle, std::vector<FaceData> *retAllFaces);
    // Select all faces
    //
    // handle[in] - UMXDB_HANDLE value
    // retFaces[out] - struct FaceData's data list
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_selectFacesByPage(UMXDB_HANDLE handle, const int page, const int pageSize, std::vector<FaceData> *retFaces);
    // Select faces by page
    //
    // handle[in] - UMXDB_HANDLE value
    // page[int] - page
    // pageSize[in] - page size
    // retFaces[out] - struct FaceData's data list
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_SUCCESS

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
    //                UMXDB_ERROR_EXIST_UUID_AND_SUBID
    //                UMXDB_ERROR_NO_FACE_INFO
    //                UMXDB_ERROR_NO_FACE_FEATURE
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_updateFaceByUuIdAndSubId2(UMXDB_HANDLE handle, const std::string uuid, const int subId, FaceData& faceData);
    // Update face by uuid and subid
    //
    // handle[in] - UMXDB_HANDLE value
    // uuid[in] - unique id to update
    // subId[in] - face sub id to update
    // faceData[in] - struct FaceData's data to update
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_EXIST_UUID_AND_SUBID
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_deleteFaceByUuIdAndSubId(UMXDB_HANDLE handle, const std::string uuid, const int subId);
    // Delete face by uuid and subid
    //
    // handle[in] - UMXDB_HANDLE value
    // uuid[in] - unique id
    // subId[in] - face sub id
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_NO_EXIST_UUID_AND_SUBID
    //                UMXDB_ERROR_DELETE
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_deleteFacesByUUID(UMXDB_HANDLE handle, const std::string uuid);
    // Delete faces by uuid
    //
    // handle[in] - UMXDB_HANDLE value
    // uuid[in] - unique id
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_NO_EXIST_UUID
    //                UMXDB_ERROR_DELETE
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_deleteAllFaces(UMXDB_HANDLE handle);
    // Delete all faces
    //
    // handle[in] - UMXDB_HANDLE value
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_DELETE
    //                UMXDB_SUCCESS

    /// ^^^^ "/usr/local/share/CMITECH/Service.db" - face table ^^^^


    /// vvvv "/usr/local/share/CMITECH/Service.db" - userinfo table vvvv

    int _UMXDB_EXPORT umxDB_insertUserInfo(UMXDB_HANDLE handle, const std::string uuid, const std::string card, const std::string pin,
                                                     const int admin, const int groupIndex, const int byPassCard, const int indivisual);
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
    //                UMXDB_ERROR_EXIST_UUID
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_selectUserInfoByUUID(UMXDB_HANDLE handle, const std::string uuid, UserInfoData *retUserInfo);
    // Select user info by uuid.
    //
    // handle[in] - UMXDB_HANDLE value
    // uuid[in] - unique id
    // retUserInfo[out] - struct UserInfoData's data
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_selectUserInfoByCard(UMXDB_HANDLE handle, const std::string card, UserInfoData *retUserInfo);
    // Select user info by card number.
    //
    // handle[in] - UMXDB_HANDLE value
    // card[in] - card number
    // retUserInfo[out] - struct UserInfoData's data
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_selectAllUserInfoes(UMXDB_HANDLE handle, std::vector<UserInfoData> *retAllUserInfoes);
    // Select userinfo by card number.
    //
    // handle[in] - UMXDB_HANDLE value
    // card[in] - card number
    // retUserInfo[out] - struct UserInfoData's data
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_selectAllUserInfoByPage(UMXDB_HANDLE handle, const int page, const int pageSize,
                                                std::vector<UserInfoData> *retAllUserInfo);
    // Select userinfo by page
    //
    // handle[in] - UMXDB_HANDLE value
    // page[int] - page
    // pageSize[in] - page size
    // retAllUserInfo[out] - struct UserInfoData's data list
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_updateUserInfoByUUID(UMXDB_HANDLE handle, const std::string uuid, const std::string card, const std::string pin,
                                                           const int admin, const int groupIndex, const int byPassCard, const int indivisual);
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
    //                UMXDB_ERROR_NO_EXIST_UUID
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_deleteUserInfoByUUID(UMXDB_HANDLE handle, const std::string uuid);
    // Delete userinfo by uuid.
    //
    // handle[in] - UMXDB_HANDLE value
    // uuid[in] - unique id
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_NO_EXIST_UUID
    //                UMXDB_ERROR_DELETE
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_deleteAllUserInfoes(UMXDB_HANDLE handle);
    // Delete all userinfoes by uuid.
    //
    // handle[in] - UMXDB_HANDLE value
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_ERROR_DELETE
    //                UMXDB_SUCCESS

    /// ^^^^ "/usr/local/share/CMITECH/Service.db" - userinfo table ^^^^


    /// vvvv "/usr/local/share/CMITECH/ServiceLog.db" - event_log table vvvv

    int _UMXDB_EXPORT umxDB_insertLog(UMXDB_HANDLE handle, const std::string& type, const std::string& uuid, const std::string& info, const std::string& message, const char* matchedFaceImage, int matchedFaceImageSize);
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
    //                UMXDB_ERROR_FAIL_TO_INSERT_EVENT_LOG
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_selectLastLogID(UMXDB_HANDLE handle, int* lastLogID);
    // Select LogEntry.
    //
    // handle[in] - UMXDB_HANDLE value
    // lastLogID[out] - Last Log ID
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_FAIL
    //                UMXDB_SUCCESS

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
    //                UMXDB_SUCCESS

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
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_selectLogEntryById(UMXDB_HANDLE handle, const int id, LogEntry* logEntry);
    // Select LogEntry by id.
    //
    // handle[in] - UMXDB_HANDLE value
    // id[in] - log id
    // logEntry[out] - LogEntry class's instance
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_FAIL
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_deleteLogEntryFromTo(UMXDB_HANDLE handle, const int fromId, const int toId);
    // Delete LogEntry from id to id.
    //
    // handle[in] - UMXDB_HANDLE value
    // fromId[in] - from id
    // toId[in] - to id
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_FAIL
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_deleteLogEntryById(UMXDB_HANDLE handle, const int id);
    // Delete LogEntry by id.
    //
    // handle[in] - UMXDB_HANDLE value
    // id[in] - from id
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_FAIL
    //                UMXDB_SUCCESS

    /// ^^^^ "/usr/local/share/CMITECH/ServiceLog.db" - event_log table ^^^^


    /// vvvv "/usr/local/share/CMITECH/ServiceLog.db" - image_capture table vvvv

    int _UMXDB_EXPORT umxDB_selectImageCapture(UMXDB_HANDLE handle, std::vector<ImageCapture> *retImageCapture);
    // Select ImageCapture.
    //
    // handle[in] - UMXDB_HANDLE value
    // retImageCapture[out] - ImageCapture class's instance list
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
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
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_deleteAllUsers(UMXDB_HANDLE handle);
    // Delete all users of subject, face, userinfo table.
    //
    // handle[in] - UMXDB_HANDLE value
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_SUCCESS

    /// ^^^^ for deleting once - subject, face, userinfo ^^^^


    /// vvvv special function vvvv

    int _UMXDB_EXPORT umxDB_getUUIDList(UMXDB_HANDLE handle, std::vector<std::string> *retUuidList);
    // Delete all users of subject, face, userinfo table.
    //
    // handle[in] - UMXDB_HANDLE value
    // retUuidList[out] - UMXDB_HANDLE value
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_isExistAdmin(UMXDB_HANDLE handle, int* existCnt);
    // Check if admin is exist.
    //
    // handle[in] - UMXDB_HANDLE value
    // existCnt[out] - existing admin count
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_isExistUUID(UMXDB_HANDLE handle, const std::string uuid, int* exist);
    // Check if uuid is exist.
    //
    // handle[in] - UMXDB_HANDLE value
    // uuid[in] - existing admin count
    // exist[out] - existing uuid count
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_cntFaceByUUIDAndSubId(UMXDB_HANDLE handle, const std::string uuid, const int subid, int* cnt);
    // Count face in DB by uuid and subid.
    //
    // handle[in] - UMXDB_HANDLE value
    // uuid[in] - user unique id
    // subid[in] - face sub id
    // cnt[out] - face count
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_SUCCESS

#if 1 //Improve #117 : Search function added
    int _UMXDB_EXPORT umxDB_searchAllIrisByUUID(UMXDB_HANDLE handle, const std::string uuid, std::vector<SubjectData> *retAllIrises);
    // Search iris by uuid.
    //
    // handle[in] - UMXDB_HANDLE value
    // uuid[in] - contains id
    // retIris[out] - iris data
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_searchAllIrisByName(UMXDB_HANDLE handle, const std::string name, std::vector<SubjectData> *retAllIrises);
    // Search iris by name.
    //
    // handle[in] - UMXDB_HANDLE value
    // name[in] - contains name
    // retIris[out] - iris data
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_searchAllUserInfoesByUUID(UMXDB_HANDLE handle, const std::string uuid, std::vector<UserInfoData> *retAllUserInfoes);
    // Select user info by uuid.
    //
    // handle[in] - UMXDB_HANDLE value
    // uuid[in] - unique id
    // retUserInfo[out] - struct UserInfoData's data
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_SUCCESS

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
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_isDeserializeIrisFeatureData(UMXDB_HANDLE handle, int recordVersion);
    // Check if serialized data is exist.
    //
    // handle[in] - UMXDB_HANDLE value
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_getSerializeIrisFeatureData(UMXDB_HANDLE handle, int recordVersion, std::vector<SubjectData>* retIris);
    // Get serialize data.
    //
    // handle[in] - UMXDB_HANDLE value
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_SUCCESS

    int _UMXDB_EXPORT umxDB_setDeserializeIrisFeatureData(UMXDB_HANDLE handle, const SubjectData* subject);
    // Set deserialize data.
    //
    // handle[in] - UMXDB_HANDLE value
    //
    // Return value - UMXDB_ERROR_INVALID_HANDLE
    //                UMXDB_SUCCESS

#endif


    /// ^^^^ special function ^^^^

#ifdef __cplusplus
} // extern "C"
#endif

#endif // UMXDB_H
