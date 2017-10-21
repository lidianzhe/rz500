/**************************************************************************************************\

    Author:		UK
    Created:	2015.06.19

---------------------------------------------------------------------------------------------------

    Copyright (c) 2015 CMITech Ltd.

\**************************************************************************************************/

#ifndef __EVENT_LOG_DATA_ACCESS_H__
#define __EVENT_LOG_DATA_ACCESS_H__

#include <memory>

#include <Poco/Data/Common.h>
#include <Poco/Data/TypeHandler.h>
using namespace Poco::Data;

#include "DataAccess.h"

#if 1 //EF-45(unklee88)-70 : umxCommonGlobal.h includes umxCommonLib/DataTypes/LogEntry.h vvv
#include "umxCommonLib/umxCommonGlobal.h"
#else
#include <DataTypes/LogEntry.h>
#endif //EF-45(unklee88)-70 : umxCommonGlobal.h includes umxCommonLib/DataTypes/LogEntry.h ^^^

#if 1 //EF-45(unklee88)-70 : umxCommonGlobal.h includes umxCommonLib/DataTypes/LogEntry.h vvv
using namespace UMXCommon;
#endif //EF-45(unklee88)-70 : umxCommonGlobal.h includes umxCommonLib/DataTypes/LogEntry.h ^^^

namespace Poco
{

namespace Data
{

template<>
class TypeHandler<class LogEntry>
{
public:
    // event_log table has three columns.
    static std::size_t size()
    {
        return 7;
    }

    // Bind the data.  Five columns.  Advance the column index, pos, after each bind.
    static void bind(std::size_t pos, const LogEntry& obj, AbstractBinder* pBinder)
    {
        poco_assert_dbg( pBinder != 0 );
        if (obj.GetId() != -1)
        {
            TypeHandler<int>::bind(pos, obj.GetId(), pBinder);
        }
        pos++;
        TypeHandler<std::string>::bind(pos++, obj.GetEventType(), pBinder);
        TypeHandler<std::string>::bind(pos++, obj.GetTimestamp(), pBinder);
        TypeHandler<std::string>::bind(pos++, obj.GetUserUUID(), pBinder);
        TypeHandler<std::string>::bind(pos++, obj.GetInfo(), pBinder);
        TypeHandler<std::string>::bind(pos++, obj.GetAdditionalData(), pBinder);
        TypeHandler<BLOB>::bind(pos++, obj.GetImageData(), pBinder);
    }

    // Prepare the data.  Assume id, EventType, Timestamp, UserUUID, and then AdditionalData in that order.
    static void prepare(std::size_t pos, const LogEntry& obj, AbstractPreparation* pPrepare)
    {
        poco_assert_dbg(pPrepare != 0);
        TypeHandler<int>::prepare(pos++, obj.GetId(), pPrepare);
        TypeHandler<std::string>::prepare(pos++, obj.GetEventType(), pPrepare);
        TypeHandler<std::string>::prepare(pos++, obj.GetTimestamp(), pPrepare);
        TypeHandler<std::string>::prepare(pos++, obj.GetUserUUID(), pPrepare);
        TypeHandler<std::string>::prepare(pos++, obj.GetInfo(), pPrepare);
        TypeHandler<std::string>::prepare(pos++, obj.GetAdditionalData(), pPrepare);
        TypeHandler<BLOB>::prepare(pos++, obj.GetImageData(), pPrepare);
    }

    // Extract the data into an object.
    static void extract(std::size_t pos, LogEntry& obj, const LogEntry& defVal, AbstractExtractor* pExt)
    {
        poco_assert_dbg(pExt != 0);
        int id = -1;
        std::string eventType;
        std::string timestamp;
        std::string userUUID;
        std::string info;
        std::string additionalData;
        BLOB imageData;

        TypeHandler<int>::extract(pos++, id, defVal.GetId(), pExt);
        TypeHandler<std::string>::extract(pos++, eventType, defVal.GetEventType(), pExt);
        TypeHandler<std::string>::extract(pos++, timestamp, defVal.GetTimestamp(), pExt);
        TypeHandler<std::string>::extract(pos++, userUUID, defVal.GetUserUUID(), pExt);
        TypeHandler<std::string>::extract(pos++, info, defVal.GetInfo(), pExt);
        TypeHandler<std::string>::extract(pos++, additionalData, defVal.GetAdditionalData(), pExt);
        TypeHandler<BLOB>::extract(pos++, imageData, defVal.GetImageData(), pExt);

        obj.SetId( id );
        obj.SetEventType( eventType );
        obj.SetTimestamp( timestamp );
        obj.SetUserUUID( userUUID );
        obj.SetInfo( info );
        obj.SetAdditionalData( additionalData );
        obj.SetImageData( imageData );
    }
};

}

}

const std::string EventLogTableName = "event_log";
const int MaxRetryAttempts = 2;
const std::string TransactionMode = "IMMEDIATE";

class EventLogDataAccess : DataAccess
{
public:
    EventLogDataAccess();
    virtual ~EventLogDataAccess();

    void Connect();
    void Connect(const std::string& database);
    const bool isConnected() const;

    bool isTablePresent();
    void CreateTable();
    void DropTable();

    void Insert(const LogEntry& logEntry);

    std::vector<LogEntry> Select();
    std::vector<LogEntry> SelectLastN(int noEntries);
    const LogEntry Select(int id);
    const int SelectLastLogID();
    const std::vector<LogEntry> SelectLogs(int fromId, int toId);
    const std::vector<LogEntry> SelectLogsFromToByPage(const int pageNumber, const int pageSize, const int fromId, const int toId);
    const std::vector<LogEntry> SelectByPage(const int pageNumber, const int pageSize, const std::string& order);
    const std::vector<int> SelectImageLogs();

    //Search
    const std::vector<LogEntry> searchAllLogs(const int pageNumber, const int pageSize, const std::string& order, const std::string startDate, const std::string endDate,
                                              const std::string event, const std::string info, const std::string userID, const std::string additionalData);

//    bool Delete(const int id);
//    bool DeleteFirst();
    bool Delete(const int id, bool* isImage);
    bool DeleteFirst(bool* isImage);
    bool DeleteFirstImage();
    int Delete(const int fromId, const int toId);

    void VacuumServiceLog();

    const int Count();
    const int ImageCount();
private:
    std::unique_ptr<Poco::Data::Session> _pSession;
};

#endif // __EVENT_LOG_DATA_ACCESS_H__
