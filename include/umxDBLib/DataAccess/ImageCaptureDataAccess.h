/**************************************************************************************************\

	Author:		Ralph
	Created:	16.04.2014

---------------------------------------------------------------------------------------------------

	Copyright (c) 2014 Smartsensors Ltd.

\**************************************************************************************************/

#ifndef __IMAGE_CAPTURE_DATA_ACCESS_H__
#define __IMAGE_CAPTURE_DATA_ACCESS_H__

#include <memory>

#include "DataAccess.h"

#include <Poco/Data/Common.h>
#include <Poco/Data/TypeHandler.h>
using namespace Poco::Data;

#if 1 //EF-45(unklee88)-70 : umxCommonGlobal.h includes umxCommonLib/DataTypes/ImageCapture.h vvv
#include "umxCommonLib/umxCommonGlobal.h"
#else
#include <DataTypes/ImageCapture.h>
#endif //EF-45(unklee88)-70 : umxCommonGlobal.h includes umxCommonLib/DataTypes/ImageCapture.h ^^^

#if 1 //EF-45(unklee88)-70 : umxCommonGlobal.h includes umxCommonLib/DataTypes/ImageCapture.h vvv
using namespace UMXCommon;
#endif //EF-45(unklee88)-70 : umxCommonGlobal.h includes umxCommonLib/DataTypes/ImageCapture.h ^^^

namespace Poco
{

namespace Data
{

template<>
class TypeHandler<class ImageCapture>
{
public:
    // Image capture table has four columns.
    static std::size_t size()
    {
        return 4;
    }

    // Bind the data.  Three columns.  Advance the column index, pos, after each bind.
    static void bind(std::size_t pos, const ImageCapture& obj, AbstractBinder* pBinder)
    {
        poco_assert_dbg( pBinder != 0 );
        if (obj.GetId() != -1)
        {
            TypeHandler<int>::bind(pos, obj.GetId(), pBinder);
        }
        pos++;
        TypeHandler<std::string>::bind(pos++, obj.GetImageCaptureUUID(), pBinder);
        TypeHandler<std::string>::bind(pos++, obj.GetTimestamp(), pBinder);
        TypeHandler<std::string>::bind(pos++, obj.GetSerialNumber(), pBinder);
    }

    // Prepare the data.  Assume UUID, Timestamp and then SerialNumber in that order.
    static void prepare(std::size_t pos, const ImageCapture& obj, AbstractPreparation* pPrepare)
    {
        poco_assert_dbg(pPrepare != 0);
        if (obj.GetId() != -1)
        {
            TypeHandler<int>::prepare(pos, obj.GetId(), pPrepare);
        }
        pos++;
        TypeHandler<std::string>::prepare(pos++, obj.GetImageCaptureUUID(), pPrepare);
        TypeHandler<std::string>::prepare(pos++, obj.GetTimestamp(), pPrepare);
        TypeHandler<std::string>::prepare(pos++, obj.GetSerialNumber(), pPrepare);
    }

    // Extract the data into an object.
    static void extract(std::size_t pos, ImageCapture& obj, const ImageCapture& defVal, AbstractExtractor* pExt)
    {
        poco_assert_dbg(pExt != 0);
        int id = -1;
        std::string imageCaptureUUID;
        std::string timestamp;
        std::string serialNumber;

        // Skip primary key column.
        TypeHandler<int>::extract(pos++, id, defVal.GetId(), pExt);
        TypeHandler<std::string>::extract(pos++, imageCaptureUUID, defVal.GetImageCaptureUUID(), pExt);
        TypeHandler<std::string>::extract(pos++, timestamp, defVal.GetTimestamp(), pExt);
        TypeHandler<std::string>::extract(pos++, serialNumber, defVal.GetSerialNumber(), pExt);

        obj.SetId( id );
        obj.SetImageCaptureUUID( imageCaptureUUID );
        obj.SetTimestamp( timestamp );
        obj.SetSerialNumber( serialNumber );
    }
};

}

}

const std::string ImageCaptureTableName = "image_capture";

class ImageCaptureDataAccess : DataAccess
{
public:
    ImageCaptureDataAccess();
    virtual ~ImageCaptureDataAccess();

    void Connect();
    void Connect(const std::string& database);
    const bool isConnected() const;

    bool isTablePresent();
    void CreateTable();
    void DropTable();

    void Insert(const ImageCapture& imageCapture);
    std::vector<ImageCapture> Select();
private:
    std::unique_ptr<Poco::Data::Session> _pSession;
};

#endif // __IMAGE_CAPTURE_DATA_ACCESS_H__
