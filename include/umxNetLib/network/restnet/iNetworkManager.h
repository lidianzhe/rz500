/**************************************************************************************************\

    Author:		Unkyoung Lee
    Created:	2016-04-25

---------------------------------------------------------------------------------------------------

    Copyright (c) 2014 CMI-Tech Ltd.

\**************************************************************************************************/

#ifndef __INETWORK_MANAGER_H__
#define __INETWORK_MANAGER_H__

#include <memory>
#include <string>

#include <DataTypes/CameraConfiguration.h>
#include <DataTypes/CameraControlResponse.h>
#include <DataTypes/PreviewData.h>
#include <DataTypes/SubjectData.h>
#include <DataTypes/FaceData.h>
#include <DataTypes/SelectedData.h>
#if 1 //EF-45(unklee88)-23 : removed not using access class in netLib
#include <DataTypes/LogEntry.h>
#include <DataTypes/ImageCapture.h>
#endif

#include <DataAccess/BiometricDataCache.h>
#include <DataAccess/SelectedDataCache.h>
#if 0 //EF-45(unklee88)-18 : removed DataAccess in netLib
#include <DataAccess/SubjectDataAccess.h>
#include <DataAccess/FaceDataAccess.h>
#endif

class INetworkManager
{
public:
    virtual std::string GetUMXMode()=0;
    virtual bool SetUMXMode(std::string mode)=0;
    virtual CameraControlResponse ControlStatus()=0;
#if 1 //EF-45(unklee88)-8 : INetworkManager virtual function return value type change
    virtual bool StartEnrolCamera()=0;
    virtual bool StopEnrolCamera()=0;
#endif
    virtual bool GetPreviewData(PreviewData& previewData)=0;
    virtual std::shared_ptr<BiometricDataCache> GetBiometricDataCache()=0;
    virtual std::shared_ptr<SelectedDataCache> GetSelectedDataCache()=0;
#if 0 //EF-45(unklee88)-7 : removed DataAccess in netLib
    virtual SubjectDataAccess* GetSubjectDataAccess()=0;
    virtual FaceDataAccess* GetFaceDataAccess()=0;
#endif
#if 1 //EF-45(unklee88)-9 : INetworkManager new virtual function added about database
	virtual int insertIris(SubjectData *subjectData)=0;
    virtual SubjectData selectIrisByUUID(const std::string uuid)=0;
    virtual int selectIrisesByPage(const int page, const int pageSize, std::vector<SubjectData> *retIrises)=0;
    virtual int updateIrisByUUID(const std::string uuid, SubjectData& subjectData)=0;
    virtual int deleteIrisByUUID(const std::string uuid)=0;
#endif
    virtual int insertFace(FaceData* faceData)=0;
#if 1 //EF-45(unklee88)-9 : INetworkManager new virtual function added about database
	virtual int selectFacesByPage(const int page, const int pageSize, std::vector<FaceData> *retFaces)=0;
    virtual int selectFacesByUUID(const std::string uuid, std::vector<FaceData> *retFaces)=0;
    virtual int selectFaceByUuIdAndSubId(const std::string uuid, const int subId, FaceData *faceData)=0;
    virtual int updateFaceByUuIdAndSubId(const std::string& uuid, const int subId, const FaceData& faceData)=0;
#endif
    virtual int deleteFaceByUuIdAndSubId(const std::string uuid, const int subId)=0;
    virtual int insertUserInfo(const std::string uuid, const std::string card, const std::string pin,
                                const int admin, const int groupIndex, const int byPassCard, const int indivisual)=0;
    virtual int deleteUserInfoByUUID(const std::string uuid)=0;
#if 1 //EF-45(unklee88)-23 : removed not using access class in netLib
    virtual int selectLogEntryByPage(const int pageNumber, const int pageSize, const std::string& order, std::vector<LogEntry> *retLogEntry)=0;
    virtual LogEntry selectLogEntryById(const int id)=0;
    virtual bool deleteLogEntryFromTo(const int fromId, const int toId)=0;
    virtual bool deleteLogEntryById(const int id)=0;
    virtual std::vector<ImageCapture> selectImageCapture()=0;
#endif
    virtual void saveIrisAndFaceImage(const std::string uuid)=0;
};

#endif // __INETWORK_MANAGER_H__
