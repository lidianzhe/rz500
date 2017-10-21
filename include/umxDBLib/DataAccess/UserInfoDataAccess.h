/**************************************************************************************************\

    Author:		UK Lee
    Created:	17.02.2016

---------------------------------------------------------------------------------------------------

    Copyright (c) 2016 CMI-Tech Ltd.

\**************************************************************************************************/

#ifndef __USERINFO_DATA_ACCESS_H__
#define __USERINFO_DATA_ACCESS_H__

#include <iostream>
#include <memory>

#include <Poco/Data/Common.h>
#include <Poco/Data/TypeHandler.h>
using namespace Poco::Data;

#include "DataAccess.h"

#if 1 //EF-45(unklee88)-71 : umxCommonGlobal.h includes umxCommonLib/DataTypes/UserInfoData.h vvv
#include "umxCommonLib/umxCommonGlobal.h"
#else
#include <DataTypes/UserInfoData.h>
#endif //EF-45(unklee88)-71 : umxCommonGlobal.h includes umxCommonLib/DataTypes/UserInfoData.h ^^^

#if 1 //EF-45(unklee88)-71 : umxCommonGlobal.h includes umxCommonLib/DataTypes/UserInfoData.h vvv
using namespace UMXCommon;
#endif //EF-45(unklee88)-71 : umxCommonGlobal.h includes umxCommonLib/DataTypes/UserInfoData.h ^^^

namespace Poco
{

namespace Data
{

template<>
class TypeHandler<class UserInfoData>
{
public:
    // userinfo table has seven columns.
    static std::size_t size()
    {
        return 7;
    }

    // Bind the data.  Five columns.  Advance the column index, pos, after each bind.
    static void bind(std::size_t pos, const UserInfoData& obj, AbstractBinder* pBinder)
    {
        poco_assert_dbg( pBinder != 0 );
        TypeHandler<std::string>::bind(pos++, obj._userUUID, pBinder);
        TypeHandler<std::string>::bind(pos++, obj._card, pBinder);
        TypeHandler<std::string>::bind(pos++, obj._pin, pBinder);
        TypeHandler<int>::bind(pos++, obj._admin, pBinder);
        TypeHandler<int>::bind(pos++, obj._groupIndex, pBinder);
        TypeHandler<int>::bind(pos++, obj._byPassCard, pBinder);
        TypeHandler<int>::bind(pos++, obj._indivisual, pBinder);
        TypeHandler<int>::bind(pos++, obj._threeOutStatus, pBinder);
        TypeHandler<int>::bind(pos++, obj._threeOutAccessAllowed, pBinder);
    }

    // Prepare the data.  Assume id, EventType, Timestamp, UserUUID, and then AdditionalData in that order.
    static void prepare(std::size_t pos, const UserInfoData& obj, AbstractPreparation* pPrepare)
    {
        poco_assert_dbg(pPrepare != 0);
        TypeHandler<std::string>::prepare(pos++, obj._userUUID, pPrepare);
        TypeHandler<std::string>::prepare(pos++, obj._card, pPrepare);
        TypeHandler<std::string>::prepare(pos++, obj._pin, pPrepare);
        TypeHandler<int>::prepare(pos++, obj._admin, pPrepare);
        TypeHandler<int>::prepare(pos++, obj._groupIndex, pPrepare);
        TypeHandler<int>::prepare(pos++, obj._byPassCard, pPrepare);
        TypeHandler<int>::prepare(pos++, obj._indivisual, pPrepare);
        TypeHandler<int>::prepare(pos++, obj._threeOutStatus, pPrepare);
        TypeHandler<int>::prepare(pos++, obj._threeOutAccessAllowed, pPrepare);
    }

    // Extract the data into an object.
    static void extract(std::size_t pos, UserInfoData& obj, const UserInfoData& defVal, AbstractExtractor* pExt)
    {
        poco_assert_dbg(pExt != 0);
        if(!pExt->extract(pos++, obj._userUUID) )
            obj._userUUID = defVal._userUUID;
        if(!pExt->extract(pos++, obj._card) )
            obj._card = defVal._card;
        if (!pExt->extract(pos++, obj._pin) )
            obj._pin = defVal._pin;
        if (!pExt->extract(pos++, obj._admin ) )
            obj._admin = defVal._admin;
        if (!pExt->extract( pos++, obj._groupIndex ) )
            obj._groupIndex = defVal._groupIndex;
        if(!pExt->extract(pos++, obj._byPassCard) )
            obj._byPassCard = defVal._byPassCard;
        if(!pExt->extract(pos++, obj._indivisual) )
            obj._indivisual = defVal._indivisual;
        if(!pExt->extract(pos++, obj._threeOutStatus) )
            obj._threeOutStatus = defVal._threeOutStatus;
        if(!pExt->extract(pos++, obj._threeOutAccessAllowed) )
            obj._threeOutAccessAllowed = defVal._threeOutAccessAllowed;
    }
};

}

}


const std::string UserInfoTableName = "userinfo";

class UserInfoDataAccess : DataAccess
{
public:
    UserInfoDataAccess();
    virtual ~UserInfoDataAccess();

    void Connect();
    void Connect(const std::string& database);
    const bool isConnected() const;

    bool isTablePresent();
    void CreateTable();
    void DropTable();

    void Insert(const UserInfoData& userInfoData);

    const std::vector<UserInfoData> Select();
    const std::vector<std::string> SelectIds();
    const UserInfoData Select(const std::string& id);
    const UserInfoData SelectByCard(const std::string& card);
    const std::vector<UserInfoData> SelectByPage(const int pageNumber, const int pageSize);

    //Improve #117 : Search function added
    const std::vector<UserInfoData> SearchByUUID(const std::string& id); //search

    int DeleteAll();
    bool Delete(const std::string& userUUID);
    bool DeleteList(const std::string delUUIDs);

    void Update(const UserInfoData& userInfoData);

    const int Count();
    const int CountAdmin();
    const int CountUUID(const std::string& id);

private:
    std::unique_ptr<Poco::Data::Session> _pSession;
};

#endif // __USERINFO_DATA_ACCESS_H__
