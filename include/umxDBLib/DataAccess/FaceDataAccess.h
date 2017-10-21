/**************************************************************************************************\

    Author:		UK
    Created:	2015.06.19

---------------------------------------------------------------------------------------------------

    Copyright (c) 2015 CMITech Ltd.

\**************************************************************************************************/

#ifndef __FACE_DATA_ACCESS_H__
#define __FACE_DATA_ACCESS_H__

#include <iostream>
#include <memory>

#include <Poco/Data/Common.h>
#include <Poco/Data/TypeHandler.h>
using namespace Poco::Data;

#include "DataAccess.h"

#if 1 //EF-45(unklee88)-69 : umxCommonGlobal.h includes umxCommonLib/DataTypes/FaceData.h vvv
#include "umxCommonLib/umxCommonGlobal.h"
#else
#include <DataTypes/FaceData.h>
#endif //EF-45(unklee88)-69 : umxCommonGlobal.h includes umxCommonLib/DataTypes/FaceData.h ^^^

#if 0 //EF-45(unklee88)-70 : umxCommonGlobal.h includes umxCommonLib/DataTypes/FaceDataWithSubjectInfo.h vvv
#include <DataTypes/FaceDataWithSubjectInfo.h>
#endif //EF-45(unklee88)-70 : umxCommonGlobal.h includes umxCommonLib/DataTypes/FaceDataWithSubjectInfo.h ^^^


#if 1 //EF-45(unklee88)-69 : umxCommonGlobal.h includes umxCommonLib/DataTypes/FaceData.h vvv
using namespace UMXCommon;
#endif //EF-45(unklee88)-69 : umxCommonGlobal.h includes umxCommonLib/DataTypes/FaceData.h ^^^

namespace Poco
{

namespace Data
{

template<>
class TypeHandler<class FaceData>
{
public:
    // face table has twelve columns.
    static std::size_t size()
    {
        return 12;
    }

    // Bind the data.  Five columns.  Advance the column index, pos, after each bind.
    static void bind(std::size_t pos, const FaceData& obj, AbstractBinder* pBinder)
    {
        poco_assert_dbg( pBinder != 0 );
        TypeHandler<std::string>::bind(pos++, obj._userUUID, pBinder);
        TypeHandler<int>::bind(pos++, obj._subId, pBinder);
        TypeHandler<int>::bind(pos++, obj._faceEyeWidth, pBinder);
        TypeHandler<int64_t>::bind(pos++, obj._faceFeatureSize, pBinder);
        TypeHandler<float>::bind(pos++, obj._faceFrontalScore, pBinder);
        TypeHandler<int>::bind(pos++, obj._faceLeftEyeX, pBinder);
        TypeHandler<int>::bind(pos++, obj._faceRightEyeX, pBinder);
        TypeHandler<float>::bind(pos++, obj._faceRoll, pBinder);
        TypeHandler<float>::bind(pos++, obj._faceScore, pBinder);
        TypeHandler<float>::bind(pos++, obj._faceLEDState, pBinder);
        TypeHandler<BLOB>::bind(pos++, obj._faceFeature, pBinder);
        TypeHandler<std::string>::bind(pos++, obj._imagePath, pBinder);
    }

    // Prepare the data.  Assume id, EventType, Timestamp, UserUUID, and then AdditionalData in that order.
    static void prepare(std::size_t pos, const FaceData& obj, AbstractPreparation* pPrepare)
    {
        poco_assert_dbg(pPrepare != 0);
        TypeHandler<std::string>::prepare(pos++, obj._userUUID, pPrepare);
        TypeHandler<int>::prepare(pos++, obj._subId, pPrepare);
        TypeHandler<int>::prepare(pos++, obj._faceEyeWidth, pPrepare);
        TypeHandler<int64_t>::prepare(pos++, obj._faceFeatureSize, pPrepare);
        TypeHandler<float>::prepare(pos++, obj._faceFrontalScore, pPrepare);
        TypeHandler<int>::prepare(pos++, obj._faceLeftEyeX, pPrepare);
        TypeHandler<int>::prepare(pos++, obj._faceRightEyeX, pPrepare);
        TypeHandler<float>::prepare(pos++, obj._faceRoll, pPrepare);
        TypeHandler<float>::prepare(pos++, obj._faceScore, pPrepare);
        TypeHandler<int>::prepare(pos++, obj._faceLEDState, pPrepare);
        TypeHandler<BLOB>::prepare(pos++, obj._faceFeature, pPrepare);
        TypeHandler<std::string>::prepare(pos++, obj._imagePath, pPrepare);
    }

    // Extract the data into an object.
    static void extract(std::size_t pos, FaceData& obj, const FaceData& defVal, AbstractExtractor* pExt)
    {
        poco_assert_dbg(pExt != 0);
        if(!pExt->extract(pos++, obj._userUUID) )
            obj._userUUID = defVal._userUUID;
        if (!pExt->extract(pos++, obj._subId) )
            obj._subId = defVal._subId;
        if (!pExt->extract(pos++, obj._faceEyeWidth) )
            obj._faceEyeWidth = defVal._faceEyeWidth;
        if (!pExt->extract(pos++, obj._faceFeatureSize) )
            obj._faceFeatureSize = defVal._faceFeatureSize;
        if (!pExt->extract(pos++, obj._faceFrontalScore) )
            obj._faceFrontalScore = defVal._faceFrontalScore;
        if (!pExt->extract(pos++, obj._faceLeftEyeX) )
            obj._faceLeftEyeX = defVal._faceLeftEyeX;
        if (!pExt->extract(pos++, obj._faceRightEyeX) )
            obj._faceRightEyeX = defVal._faceRightEyeX;
        if (!pExt->extract(pos++, obj._faceRoll) )
            obj._faceRoll = defVal._faceRoll;
        if (!pExt->extract(pos++, obj._faceScore) )
            obj._faceScore = defVal._faceScore;
        if (!pExt->extract(pos++, obj._faceLEDState) )
            obj._faceLEDState = defVal._faceLEDState;
        if (!pExt->extract( pos++, obj._faceFeature) )
            obj._faceFeature = defVal._faceFeature;
        if(!pExt->extract(pos++, obj._imagePath) )
            obj._imagePath = defVal._imagePath;
    }
};

template<>
class TypeHandler<class FaceDataWithSubjectInfo>
{
public:
    // table to join subject with face has seventeen columns.
    static std::size_t size()
    {
        return 17;
    }

    // Bind the data.  Five columns.  Advance the column index, pos, after each bind.
    static void bind(std::size_t pos, const FaceDataWithSubjectInfo& obj, AbstractBinder* pBinder)
    {
        poco_assert_dbg( pBinder != 0 );
        TypeHandler<std::string>::bind(pos++, obj._firstName, pBinder);
        TypeHandler<std::string>::bind(pos++, obj._lastName, pBinder);

        TypeHandler<int>::bind(pos++, obj._wiegandFacility, pBinder);
        TypeHandler<int>::bind(pos++, obj._wiegandSite, pBinder);
        TypeHandler<int>::bind(pos++, obj._wiegandCode, pBinder);

        TypeHandler<std::string>::bind(pos++, obj._userUUID, pBinder);
        TypeHandler<int>::bind(pos++, obj._subId, pBinder);
        TypeHandler<int>::bind(pos++, obj._faceEyeWidth, pBinder);
        TypeHandler<int64_t>::bind(pos++, obj._faceFeatureSize, pBinder);
        TypeHandler<float>::bind(pos++, obj._faceFrontalScore, pBinder);
        TypeHandler<int>::bind(pos++, obj._faceLeftEyeX, pBinder);
        TypeHandler<int>::bind(pos++, obj._faceRightEyeX, pBinder);
        TypeHandler<float>::bind(pos++, obj._faceRoll, pBinder);
        TypeHandler<float>::bind(pos++, obj._faceScore, pBinder);
        TypeHandler<float>::bind(pos++, obj._faceLEDState, pBinder);
        TypeHandler<BLOB>::bind(pos++, obj._faceFeature, pBinder);
        TypeHandler<std::string>::bind(pos++, obj._imagePath, pBinder);
    }

    // Prepare the data.  Assume id, EventType, Timestamp, UserUUID, and then AdditionalData in that order.
    static void prepare(std::size_t pos, const FaceDataWithSubjectInfo& obj, AbstractPreparation* pPrepare)
    {
        poco_assert_dbg(pPrepare != 0);
        TypeHandler<std::string>::prepare(pos++, obj._firstName, pPrepare);
        TypeHandler<std::string>::prepare(pos++, obj._lastName, pPrepare);

        TypeHandler<int>::prepare(pos++, obj._wiegandFacility, pPrepare);
        TypeHandler<int>::prepare(pos++, obj._wiegandSite, pPrepare);
        TypeHandler<int>::prepare(pos++, obj._wiegandCode, pPrepare);

        TypeHandler<std::string>::prepare(pos++, obj._userUUID, pPrepare);
        TypeHandler<int>::prepare(pos++, obj._subId, pPrepare);
        TypeHandler<int>::prepare(pos++, obj._faceEyeWidth, pPrepare);
        TypeHandler<int64_t>::prepare(pos++, obj._faceFeatureSize, pPrepare);
        TypeHandler<float>::prepare(pos++, obj._faceFrontalScore, pPrepare);
        TypeHandler<int>::prepare(pos++, obj._faceLeftEyeX, pPrepare);
        TypeHandler<int>::prepare(pos++, obj._faceRightEyeX, pPrepare);
        TypeHandler<float>::prepare(pos++, obj._faceRoll, pPrepare);
        TypeHandler<float>::prepare(pos++, obj._faceScore, pPrepare);
        TypeHandler<int>::prepare(pos++, obj._faceLEDState, pPrepare);
        TypeHandler<BLOB>::prepare(pos++, obj._faceFeature, pPrepare);
        TypeHandler<std::string>::prepare(pos++, obj._imagePath, pPrepare);
    }

    // Extract the data into an object.
    static void extract(std::size_t pos, FaceDataWithSubjectInfo& obj, const FaceDataWithSubjectInfo& defVal, AbstractExtractor* pExt)
    {
        poco_assert_dbg(pExt != 0);
        if (!pExt->extract(pos++, obj._firstName ) )
            obj._firstName = defVal._firstName;
        if (!pExt->extract( pos++, obj._lastName ) )
            obj._lastName = defVal._lastName;

        if (!pExt->extract(pos++, obj._wiegandFacility) )
            obj._wiegandFacility = defVal._wiegandFacility;
        if (!pExt->extract(pos++, obj._wiegandSite) )
            obj._wiegandSite = defVal._wiegandSite;
        if (!pExt->extract(pos++, obj._wiegandCode ) )
            obj._wiegandCode = defVal._wiegandCode;

        if(!pExt->extract(pos++, obj._userUUID) )
            obj._userUUID = defVal._userUUID;
        if (!pExt->extract(pos++, obj._subId) )
            obj._subId = defVal._subId;
        if (!pExt->extract(pos++, obj._faceEyeWidth) )
            obj._faceEyeWidth = defVal._faceEyeWidth;
        if (!pExt->extract(pos++, obj._faceFeatureSize) )
            obj._faceFeatureSize = defVal._faceFeatureSize;
        if (!pExt->extract(pos++, obj._faceFrontalScore) )
            obj._faceFrontalScore = defVal._faceFrontalScore;
        if (!pExt->extract(pos++, obj._faceLeftEyeX) )
            obj._faceLeftEyeX = defVal._faceLeftEyeX;
        if (!pExt->extract(pos++, obj._faceRightEyeX) )
            obj._faceRightEyeX = defVal._faceRightEyeX;
        if (!pExt->extract(pos++, obj._faceRoll) )
            obj._faceRoll = defVal._faceRoll;
        if (!pExt->extract(pos++, obj._faceScore) )
            obj._faceScore = defVal._faceScore;
        if (!pExt->extract(pos++, obj._faceLEDState) )
            obj._faceLEDState = defVal._faceLEDState;
        if (!pExt->extract( pos++, obj._faceFeature) )
            obj._faceFeature = defVal._faceFeature;
        if (!pExt->extract( pos++, obj._imagePath ) )
            obj._imagePath = defVal._imagePath;
    }
};

}

}

const std::string FaceTableName = "face";

class FaceDataAccess : DataAccess
{
public:
    FaceDataAccess();
    virtual ~FaceDataAccess();

    void Connect();
    void Connect(const std::string& database);
    const bool isConnected() const;

    bool isTablePresent();
    void CreateTable();
    void DropTable();

    void Insert(const FaceData& FaceData);

    const std::vector<FaceData> Select();
    const std::vector<FaceData> SelectAll();
    const std::vector<FaceDataWithSubjectInfo> JoinWithSubject();
    const std::vector<FaceData> Select(const std::string& id);
    const std::vector<FaceData> SelectIds();
    const FaceData Select(const std::string& id, const int subId);
    const std::vector<FaceData> SelectByPage(const int pageNumber, const int pageSize);

    int DeleteAll();
    int DeleteByUUID(const std::string& userUUID);
    bool Delete(const std::string& userUUID, const int subId);
    bool DeleteList(const std::string delUUIDs);

    void Update(const FaceData& FaceData);

    const int Count();
    const int CountUUID(const std::string& id);
    const int CountUUIDAndSubId(const std::string& id, const int subId);

    const int setEncryptFeatureData(const FaceData& subject);
private:
    std::unique_ptr<Poco::Data::Session> _pSession;
};

#endif // __FACE_DATA_ACCESS_H__
