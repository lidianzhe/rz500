/**************************************************************************************************\

	Author:		Ralph
	Created:	23.04.2014

---------------------------------------------------------------------------------------------------

	Copyright (c) 2014 Smartsensors Ltd.

\**************************************************************************************************/

#ifndef __CAMERA_CONFIGRATION_DATA_ACCESS_H__
#define __CAMERA_CONFIGRATION_DATA_ACCESS_H__

#include <memory>

#include <Poco/Data/Common.h>
#include <Poco/Data/TypeHandler.h>
using namespace Poco::Data;

#include "DataAccess.h"

#if 1 //EF-45(unklee88)-68 : umxCommonGlobal.h includes umxCommonLib/DataTypes/CameraConfiguration.h vvv
#include "umxCommonLib/umxCommonGlobal.h"
#else
#include <DataTypes/CameraConfiguration.h>
#endif //EF-45(unklee88)-68 : umxCommonGlobal.h includes umxCommonLib/DataTypes/CameraConfiguration.h ^^^

#if 1 //EF-45(unklee88)-68 : umxCommonGlobal.h includes umxCommonLib/DataTypes/CameraConfiguration.h vvv
using namespace UMXCommon;
#endif //EF-45(unklee88)-68 : umxCommonGlobal.h includes umxCommonLib/DataTypes/CameraConfiguration.h ^^^

namespace Poco
{

namespace Data
{

template<>
class TypeHandler<class CameraConfiguration>
{
public:
    // camera_configuration table has four columns.
    static std::size_t size()
    {
        return 4;
    }

    // Bind the data.  Three columns.  Advance the column index, pos, after each bind.
    static void bind(std::size_t pos, const CameraConfiguration& obj, AbstractBinder* pBinder)
    {
        poco_assert_dbg( pBinder != 0 );
        if (obj.GetId() != -1)
        {
            TypeHandler<int>::bind(pos, obj.GetId(), pBinder);
        }
        pos++;
        TypeHandler<std::string>::bind(pos++, obj.GetSerialNumber(), pBinder);
        TypeHandler<std::string>::bind(pos++, obj.GetCameraMode()->ToString(), pBinder);
        TypeHandler<int>::bind(pos++, obj.GetAudioEnabled(), pBinder);
    }

    // Prepare the data.  Assume UUID, Timestamp and then SerialNumber in that order.
    static void prepare(std::size_t pos, const CameraConfiguration& obj, AbstractPreparation* pPrepare)
    {
        poco_assert_dbg(pPrepare != 0);
        if (obj.GetId() != -1)
        {
            TypeHandler<int>::prepare(pos, obj.GetId(), pPrepare);
        }
        pos++;
        TypeHandler<std::string>::prepare(pos++, obj.GetSerialNumber(), pPrepare);
        TypeHandler<std::string>::prepare(pos++, obj.GetCameraMode()->ToString(), pPrepare);
        TypeHandler<int>::prepare(pos++, obj.GetAudioEnabled(), pPrepare);
    }

    // Extract the data into an object.
    static void extract(std::size_t pos, CameraConfiguration& obj, const CameraConfiguration& defVal, AbstractExtractor* pExt)
    {
        poco_assert_dbg(pExt != 0);
        int id = -1;
        std::string serialNumber;
        std::string cameraMode;
        int audioEnabled = 0;

        // Skip primary key column.
        TypeHandler<int>::extract(pos++, id, defVal.GetId(), pExt);
        TypeHandler<std::string>::extract(pos++, serialNumber, defVal.GetSerialNumber(), pExt);
        TypeHandler<std::string>::extract(pos++, cameraMode, defVal.GetCameraMode()->ToString(), pExt);
        TypeHandler<int>::extract(pos++, audioEnabled, defVal.GetAudioEnabled(), pExt);

        obj.SetId( id );
        obj.SetSerialNumber( serialNumber );
        obj.SetCameraMode( CameraModeFactory::CreateCameraMode(cameraMode) );
        obj.SetAudioEnabled( audioEnabled );
    }
};

}

}

const std::string CameraConfigurationTableName = "camera_configuration";

class CameraConfigurationDataAccess : DataAccess
{
public:
    CameraConfigurationDataAccess();
    virtual ~CameraConfigurationDataAccess();

    void Connect();
    void Connect(const std::string& database);
    const bool isConnected() const;

    bool isTablePresent();
    void CreateTable();
    void DropTable();

    void Insert(const CameraConfiguration& cameraConfiguration);
    void Update(const CameraConfiguration& cameraConfiguration);
    std::vector<CameraConfiguration> Select();
    CameraConfiguration Select(const std::string& cameraSerialNumber);
private:
    std::unique_ptr<Poco::Data::Session> _pSession;
};

#endif // __CAMERA_CONFIGRATION_DATA_ACCESS_H__
