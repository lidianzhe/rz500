/**************************************************************************************************\

        Author:		Unkyoung Lee
        Created:	2016.05.18

---------------------------------------------------------------------------------------------------

        Copyright (c) 2014 CMI-Tech Ltd.

\**************************************************************************************************/

#ifndef __VERSION_DATA_ACCESS_H__
#define __VERSION_DATA_ACCESS_H__

#include <iostream>
#include <memory>

#include <Poco/Data/Common.h>
#include <Poco/Data/TypeHandler.h>
using namespace Poco::Data;

#include "DataAccess.h"

#if 1 //EF-45(unklee88)-72 : umxCommonGlobal.h includes umxCommonLib/DataTypes/VersionData.h vvv
#include "umxCommonLib/umxCommonGlobal.h"
#else
#include <DataTypes/VersionData.h>
#endif //EF-45(unklee88)-72 : umxCommonGlobal.h includes umxCommonLib/DataTypes/VersionData.h ^^^

#if 1 //EF-45(unklee88)-72 : umxCommonGlobal.h includes umxCommonLib/DataTypes/VersionData.h vvv
using namespace UMXCommon;
#endif //EF-45(unklee88)-72 : umxCommonGlobal.h includes umxCommonLib/DataTypes/VersionData.h ^^^

namespace Poco
{

namespace Data
{

template<>
class TypeHandler<class VersionData>
{
public:
    // version table has two columns.
    static std::size_t size()
    {
        return 2;
    }

    // Bind the data.  Five columns.  Advance the column index, pos, after each bind.
    static void bind(std::size_t pos, const VersionData& obj, AbstractBinder* pBinder)
    {
        poco_assert_dbg( pBinder != 0 );
        if (obj.GetId() != -1)
        {
            TypeHandler<int>::bind(pos, obj.GetId(), pBinder);
        }
        pos++;
        TypeHandler<int>::bind(pos++, obj.GetVersion(), pBinder);
    }

    // Prepare the data.  Assume id, EventType, Timestamp, UserUUID, and then AdditionalData in that order.
    static void prepare(std::size_t pos, const VersionData& obj, AbstractPreparation* pPrepare)
    {
        poco_assert_dbg(pPrepare != 0);
        if (obj.GetId() != -1)
        {
            TypeHandler<int>::prepare(pos, obj.GetId(), pPrepare);
        }
        pos++;
        TypeHandler<int>::prepare(pos++, obj.GetVersion(), pPrepare);
    }

    // Extract the data into an object.
    static void extract(std::size_t pos, VersionData& obj, const VersionData& defVal, AbstractExtractor* pExt)
    {
        poco_assert_dbg(pExt != 0);
        int id = -1;
        int version = -1;

        // Skip primary key column.
        TypeHandler<int>::extract(pos++, id, defVal.GetId(), pExt);
        TypeHandler<int>::extract(pos++, version, defVal.GetVersion(), pExt);

        obj.SetId( id );
        obj.SetVersion( version );
    }
};

}

}

const std::string VersionTableName = "version";

class VersionDataAccess : DataAccess
{
public:
    VersionDataAccess();
    virtual ~VersionDataAccess();

    void Connect();
    void Connect(const std::string& database);
    const bool isConnected() const;

    bool isTablePresent();
    void CreateTable();
    void DropTable();

    void Insert(const VersionData& versionData);

    std::vector<VersionData> Select();
    bool Delete();

    void Update(const VersionData& versionData);

    const int Count();
private:
    std::unique_ptr<Poco::Data::Session> _pSession;
};

#endif // __VERSION_DATA_ACCESS_H__
