/**************************************************************************************************\

	Author:		Ralph
	Created:	24.04.2014

---------------------------------------------------------------------------------------------------

	Copyright (c) 2014 Smartsensors Ltd.

\**************************************************************************************************/

#ifndef __SUBJECT_DATA_ACCESS_H__
#define __SUBJECT_DATA_ACCESS_H__

#include <iostream>
#include <memory>

#include <Poco/Data/Common.h>
#include <Poco/Data/TypeHandler.h>
using namespace Poco::Data;

#include "DataAccess.h"
#if 1 //EF-45(unklee88)-70 : umxCommonGlobal.h includes umxCommonLib/DataTypes/SubjectData.h vvv
#include "umxCommonLib/umxCommonGlobal.h"
#else
#include <DataTypes/SubjectData.h>
#endif //EF-45(unklee88)-70 : umxCommonGlobal.h includes umxCommonLib/DataTypes/SubjectData.h ^^^

#if 1 //EF-45(unklee88)-70 : umxCommonGlobal.h includes umxCommonLib/DataTypes/SubjectData.h vvv
using namespace UMXCommon;
#endif //EF-45(unklee88)-70 : umxCommonGlobal.h includes umxCommonLib/DataTypes/SubjectData.h ^^^

namespace Poco
{

namespace Data
{

template<>
class TypeHandler<class SubjectData>
{
public:
    // subject table has fourteens columns.
    static std::size_t size()
    {
        return 14;
    }

    // Bind the data.  Five columns.  Advance the column index, pos, after each bind.
    static void bind(std::size_t pos, const SubjectData& obj, AbstractBinder* pBinder)
    {
        poco_assert_dbg( pBinder != 0 );
        TypeHandler<std::string>::bind(pos++, obj._userUUID, pBinder);
        TypeHandler<int>::bind(pos++, obj._recordVersion, pBinder);

        TypeHandler<std::string>::bind(pos++, obj._firstName, pBinder);
        TypeHandler<std::string>::bind(pos++, obj._lastName, pBinder);

        TypeHandler<int>::bind(pos++, obj._accessAllowed, pBinder);
        TypeHandler<std::string>::bind(pos++, obj._matchUntil, pBinder);

        TypeHandler<int>::bind(pos++, obj._wiegandFacility, pBinder);
        TypeHandler<int>::bind(pos++, obj._wiegandSite, pBinder);
        TypeHandler<int>::bind(pos++, obj._wiegandCode, pBinder);
        TypeHandler<std::string>::bind(pos++, obj._wiegandCustom, pBinder);
        TypeHandler<BLOB>::bind(pos++, obj._leftTemplate, pBinder);
        TypeHandler<BLOB>::bind(pos++, obj._rightTemplate, pBinder);
        TypeHandler<std::string>::bind(pos++, obj._leftImagePath, pBinder);
        TypeHandler<std::string>::bind(pos++, obj._rightImagePath, pBinder);
    }

    // Prepare the data.  Assume id, EventType, Timestamp, UserUUID, and then AdditionalData in that order.
    static void prepare(std::size_t pos, const SubjectData& obj, AbstractPreparation* pPrepare)
    {
        poco_assert_dbg(pPrepare != 0);
        TypeHandler<std::string>::prepare(pos++, obj._userUUID, pPrepare);
        TypeHandler<int>::prepare(pos++, obj._recordVersion, pPrepare);

        TypeHandler<std::string>::prepare(pos++, obj._firstName, pPrepare);
        TypeHandler<std::string>::prepare(pos++, obj._lastName, pPrepare);

        TypeHandler<int>::prepare(pos++, obj._accessAllowed, pPrepare);
        TypeHandler<std::string>::prepare(pos++, obj._matchUntil, pPrepare);

        TypeHandler<int>::prepare(pos++, obj._wiegandFacility, pPrepare);
        TypeHandler<int>::prepare(pos++, obj._wiegandSite, pPrepare);
        TypeHandler<int>::prepare(pos++, obj._wiegandCode, pPrepare);
        TypeHandler<std::string>::prepare(pos++, obj._wiegandCustom, pPrepare);
        TypeHandler<BLOB>::prepare(pos++, obj._leftTemplate, pPrepare);
        TypeHandler<BLOB>::prepare(pos++, obj._rightTemplate, pPrepare);
        TypeHandler<std::string>::prepare(pos++, obj._leftImagePath, pPrepare);
        TypeHandler<std::string>::prepare(pos++, obj._rightImagePath, pPrepare);
    }

    // Extract the data into an object.
    static void extract(std::size_t pos, SubjectData& obj, const SubjectData& defVal, AbstractExtractor* pExt)
    {
        poco_assert_dbg(pExt != 0);
        if(!pExt->extract(pos++, obj._userUUID) )
            obj._userUUID = defVal._userUUID;
        if (!pExt->extract(pos++, obj._recordVersion) )
            obj._recordVersion = defVal._recordVersion;
        if (!pExt->extract(pos++, obj._firstName ) )
            obj._firstName = defVal._firstName;
        if (!pExt->extract( pos++, obj._lastName ) )
            obj._lastName = defVal._lastName;

        if(!pExt->extract(pos++, obj._accessAllowed) )
            obj._accessAllowed = defVal._accessAllowed;
        if(!pExt->extract(pos++, obj._matchUntil) )
            obj._matchUntil = defVal._matchUntil;

        if (!pExt->extract(pos++, obj._wiegandFacility) )
            obj._wiegandFacility = defVal._wiegandFacility;
        if (!pExt->extract(pos++, obj._wiegandSite) )
            obj._wiegandSite = defVal._wiegandSite;
        if (!pExt->extract(pos++, obj._wiegandCode ) )
            obj._wiegandCode = defVal._wiegandCode;
        if (!pExt->extract( pos++, obj._wiegandCustom ) )
            obj._wiegandCustom = defVal._wiegandCustom;
        if (!pExt->extract(pos++, obj._leftTemplate) )
            obj._leftTemplate = defVal._leftTemplate;
        if (!pExt->extract( pos++, obj._rightTemplate) )
            obj._rightTemplate = defVal._rightTemplate;
        if (!pExt->extract(pos++, obj._leftImagePath) )
            obj._leftImagePath = defVal._leftImagePath;
        if (!pExt->extract( pos++, obj._rightImagePath) )
            obj._rightImagePath = defVal._rightImagePath;
    }
};

}

}

const std::string SubjectTableName = "subject";

class SubjectDataAccess : DataAccess
{
public:
    SubjectDataAccess();
    virtual ~SubjectDataAccess();

    void Connect();
    void Connect(const std::string& database);
    const bool isConnected() const;

    bool isTablePresent();
    void CreateTable();
    void DropTable();

    void Insert(const SubjectData& subjectData);

    const std::vector<SubjectData> Select();
    const std::vector<std::string> SelectIds();
    const SubjectData Select(const std::string& id);
    const std::vector<SubjectData> SelectByPage(const int pageNumber, const int pageSize);

    //Improve #117 : Search function added
    const std::vector<SubjectData> SearchByUUID(const std::string& userUUID); //search
    const std::vector<SubjectData> SearchByName(const std::string& name); //search

    int DeleteAll();
    bool Delete(const std::string& userUUID);
    bool DeleteList(const std::string delUUIDs);

    void Update(const SubjectData& subjectData);
    void UpdateName(const SubjectData& subjectData);

    void VacuumService();

    const int Count();
    const int CountUUID(const std::string& id);

    const int serializeCount(int recordVersion);
    const std::vector<SubjectData> getSerializeFeatureData(int recordVersion);
    const int setDeserializeFeatureData(const SubjectData& subject);
    const int setEncryptFeatureData(const SubjectData& subject);
private:
    std::unique_ptr<Poco::Data::Session> _pSession;
};

#endif // __SUBJECT_DATA_ACCESS_H__
