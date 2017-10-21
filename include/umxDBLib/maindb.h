#ifndef MAINDB_H
#define MAINDB_H

/**************************************************************************************************\

    Author:		Unkyoung Lee
    Created:	03.04.2016

---------------------------------------------------------------------------------------------------

    Copyright (c) 2016 CMI-TECH Ltd.

\**************************************************************************************************/

#include <Poco/Logger.h>
#include <Poco/AutoPtr.h>
#include <Poco/Util/AbstractConfiguration.h>

#include "DataAccess/ImageCaptureDataAccess.h"
#include "DataAccess/CameraConfigurationDataAccess.h"
#include "DataAccess/EventLogDataAccess.h"
#include "DataAccess/VersionDataAccess.h"
#include "DataAccess/SubjectDataAccess.h"
#include "DataAccess/FaceDataAccess.h"
#include "DataAccess/UserInfoDataAccess.h"
#if 0 //EF-45(unklee88)-20 : moved DataCache -> umxNetLib/DataAccess/
#include "DataAccess/BiometricDataCache.h"
#endif
#if 0 //EF-45(unklee88)-41 : CameraEncounter, CameraInformation, EnrollData, EnrolTemplate, UpdateFaceDate class removed in umxConmmonLib vvv
#include "DataTypes/UpdateFaceDate.h"
#endif //EF-45(unklee88)-41 : CameraEncounter, CameraInformation, EnrollData, EnrolTemplate, UpdateFaceDate class removed in umxConmmonLib ^^^
#if 0 //EF-45(unklee88)-40 : BiometricData, CameraControlResponse, Locker, PreviewData, SelectedData, VersionConverter class moved from umxCommonLib -> umxNetLib vvv
#include "DataTypes/PreviewData.h"
#include "DataTypes/CameraControlResponse.h"
#endif //EF-45(unklee88)-40 : BiometricData, CameraControlResponse, Locker, PreviewData, SelectedData, VersionConverter class moved from umxCommonLib -> umxNetLib ^^^

#if 0 //by jheekim
#if 1 //EF-45(unklee88)-22 : For using arg type, added header
#include "umxCamLib/umxCamGlobal.h"
#include "umxAlgoLib/umxAlgoGlobal.h"
#endif
#endif

using Poco::Logger;

class MainDB
{
public:
    MainDB(Poco::Logger& logger, Poco::AutoPtr<Poco::Util::AbstractConfiguration> config);

    ~MainDB();

    bool initialize();

    u_int32_t magicID() {return _magicID;}

    int vacuumService();
    int vacuumServiceLog();
    int countLog(int* count);
    int countImageLog(int* count);
    int countSubject(int* count);
    int countFace(int* count);
    int countUserInfo(int* count);

    int insertSubject(const SubjectData &subjectData);
//    int insertIris(const std::string uuid, const std::string name, const int wiegandFacility, const int wiegandCode,
//                   const UMXALGO_IRIS_GET_ENROL_TEMPLATE_OUTPUT *enrollIrisTemplates,
//                   const std::string leftEyeImagePath, const std::string rightEyeImagePath, const int recordVersion);
    int insertIris(SubjectData *subjectData);
    int selectIrisesByPage(const int page, const int pageSize, std::vector<SubjectData> *retIrises);
    int selectIrisByUUID(const std::string uuid, SubjectData *retIris);
    int selectAllIrisesUuid(std::vector<std::string> *retAllIrisesUuid);
    int selectAllIrises(std::vector<SubjectData> *retAllIrises);
    int updateSubject(const SubjectData &subjectData);
//    int updateIrisByUUID(const std::string uuid, const std::string name, const UMXALGO_IRIS_GET_ENROL_TEMPLATE_OUTPUT* enrollIrisTemplates, const std::string leftEyeImagePath, const std::string rightEyeImagePath, int recordVersion);
    int updateIrisByUUID(const std::string uuid, SubjectData &subjectData);
    int updateNameByUUID(const std::string uuid, const std::string name);
    int deleteIrisByUUID(const std::string uuid);
    int deleteIrisByUUIDList(const std::vector<std::string> *deleteUsers);
    int deleteAllIrises();
    int insertFace(const std::string uuid, const int subId, const UMXALGO_FACE_FIND_OUTPUT* faceInfo, const UMXALGO_FACE_GET_TEMPLATE_OUTPUT* faceTemplate, const std::string imagePath);
    int insertFace(FaceData& faceData);
    int selectFaceByUuIdAndSubId(const std::string uuid, const int subId, FaceData *faceData);
    int selectFacesByUUID(const std::string uuid, std::vector<FaceData> *retFaces);
    int selectFacesForMemory(std::vector<FaceData> *retFaces);
    int selectIrisForMemory(std::vector<SubjectData> *retIris);
    int selectAllFaces(std::vector<FaceData> *retAllFaces);
    int selectFacesByPage(const int page, const int pageSize, std::vector<FaceData> *retFaces);
    int updateFaceByUuIdAndSubId(const std::string uuid, const int subId, const UMXALGO_FACE_FIND_OUTPUT* faceInfo, const UMXALGO_FACE_GET_TEMPLATE_OUTPUT* faceTemplate, const std::string imagePath);
    int updateFaceByUuIdAndSubId(const std::string uuid, const int subId, FaceData& faceData);
    int deleteFaceByUuIdAndSubId(const std::string uuid, const int subId);
    int deleteFacesByUUID(const std::string uuid);
    int deleteFaceByUUIDList(const std::vector<std::string> *deleteUsers);
    int deleteAllFaces();
    int insertUserInfo(const std::string uuid, const std::string card, const std::string pin,
                          const int admin, const int groupIndex, const int byPassCard, const int indivisual,  const int threeOutStatus, const int threeOutAccessAllowed);
    int selectUserInfoByUUID(const std::string uuid, UserInfoData *retUserInfo);
    int selectUserInfoByCard(const std::string card, UserInfoData *retUserInfo);
    int selectAllUserInfoes(std::vector<UserInfoData> *retAllUserInfoes);
    int selectUserInfoByPage(const int page, const int pageSize,
                                        std::vector<UserInfoData> *retAllUserInfo);
    int updateUserInfoByUUID(const std::string uuid, const std::string card, const std::string pin,
                          const int admin, const int groupIndex, const int byPassCard, const int indivisual, const int threeOutStatus, const int threeOutAccessAllowed);
    int deleteUserInfoByUUID(const std::string uuid);
    int deleteUserInfoByUUIDList(const std::vector<std::string> *deleteUsers);
    int deleteAllUserInfoes();
    int insertLog(const std::string& type, const std::string& uuid, const std::string& info, const std::string& message, const char* matchedFaceImage, int matchedFaceImageSize);
#if 1 //EF-45(unklee88)-23 : removed not using access class in umxNetLib
    int selectLastLogID(int *lastLogID);
    int selectLogEntryByFromTo(const int fromId, const int toId, std::vector<LogEntry> *retLogEntry);
    int selectLogEntryFromToByPage(const int pageNumber, const int pageSize, const int fromId, const int toId, std::vector<LogEntry> *retLogEntry);
    int selectLogEntryByPage(const int pageNumber, const int pageSize, const std::string& order, std::vector<LogEntry> *retLogEntry);
    int selectLogEntryById(const int id, LogEntry* logEntry);
    int selectImageLogs(std::vector<int> *retImageLogID);
    int deleteLogEntryFromTo(const int fromId, const int toId);
    int deleteLogEntryById(const int id, bool* isImage);
    int deleteFirstLog(bool* isImage);
    int deleteFirstImageLog();
    int selectImageCapture(std::vector<ImageCapture> *retImageCapture);
#endif
    int deleteUserByUUID(const std::string uuid);
    int deleteUserByUUIDList(const std::vector<std::string> *deleteUsers);
    int deleteAllUsers();
    int getUUIDList(std::vector<std::string> *retUuidList);
    int isExistAdmin(int* existCnt);
    int isExistUUID(const std::string uuid, int* exist);
    int cntFaceByUUIDAndSubId(const std::string uuid, const int subid, int* count);

    //Improve #117 : Search function added
    int searchAllIrisByUUID(const std::string uuid, std::vector<SubjectData> *retAllIrises);
    int searchAllIrisByName(const std::string name, std::vector<SubjectData> *retAllIrises);
    int searchUserInfoByUUID(const std::string uuid, std::vector<UserInfoData> *retAllUserInfoes);
    int searchAllLogs(const int pageNumber, const int pageSize, const std::string& order, const std::string startDate, const std::string endDate,
                      const std::string event, const std::string info, const std::string userID, const std::string additionalData, std::vector<LogEntry> *retLogEntry);

    // EF-45(bkko)-47 : Change iris feature data to deserialize from db
    int isDeserializeIrisFeatureData(int recordVersion);
    int getSerializeIrisFeatureData(int recordVersion, std::vector<SubjectData>* retIris);
    int setDeserializeIrisFeatureData(const SubjectData* subject);

    int setEncryptFaceFeatureData(FaceData* face);
    int setDecryptFaceFeatureData(FaceData* face);
    int setEncryptFaceFeatureData(unsigned char* src, int srcSize, unsigned char* ret, int* retSize);
    int setDecryptFaceFeatureData(unsigned char* src, int srcSize, unsigned char* ret, int* retSize);
    int encryptFaceFeatureData(FaceData* face);
    int decryptFaceFeatureData(FaceData* face);

    int setEncryptIrisFeatureData(SubjectData* subjectData);
    int setDecryptIrisFeatureData(SubjectData* subject);
    int setEncryptIrisFeatureData(unsigned char* src, int srcSize, unsigned char* ret, int* retSize);
    int setDecryptIrisFeatureData(unsigned char* src, int srcSize, unsigned char* ret, int* retSize);
    int encryptIrisFeatureData(SubjectData* subject);
    int decryptIrisFeatureData(SubjectData* subject);

    int cntAllIrises(int* retCount);

    bool checkLicense(const long maxNumOfUsers, const char* path);
    int isEncryptedDB();
    int setVersionInfoForEncryptedDB();

private:
    int insertFaceForMemory(FaceData faceData);
    int deleteFaceForMemory(const std::string uuid);
    int deleteFaceForMemoryByUuIdAndSubId(const std::string uuid, const int subId);
    int deleteAllFacesForMemory();

    const std::string GetEventLogDatabaseConnection() const;

private:
    Poco::Logger& _logger;
    const Poco::AutoPtr<Poco::Util::AbstractConfiguration> _config;
    const Poco::AutoPtr<Poco::Util::AbstractConfiguration> _matcherConfig;

    u_int32_t _magicID;

    // Database
    std::string _dataBasePath;
    static const std::string DefaultDataBasePath;

    // Service.db
    Poco::Mutex _serviceDBMutex;
    std::unique_ptr<VersionDataAccess> _versionDataAccess;
    CameraConfigurationDataAccess _cameraConfigurationDataAccess;
    std::unique_ptr<SubjectDataAccess> _subjectDataAccess;
    std::unique_ptr<FaceDataAccess> _faceDataAccess;
    std::unique_ptr<UserInfoDataAccess> _userInfoDataAccess;

    // ServiceLog.db
    Poco::Mutex _serviceLogDBMutex;
    EventLogDataAccess _eventLogDataAccess;
    ImageCaptureDataAccess _imageCaptureDataAccess;

    // encryption key
    bool getPublicKey(unsigned char* key_path);
    unsigned char _pszCryptoKey[16];
};

#endif // MAINDB_H



