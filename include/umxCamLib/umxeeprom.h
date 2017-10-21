#ifndef UMXEEPROM_H
#define UMXEEPROM_H

#include <iostream>
#include <Poco/Logger.h>

#if defined(WIN32)
  #include <windows.h>
  #if defined(CMIRISLIB_LIBRARY)
	#define CMIRISLIBINTERNAL_EXPORT __declspec(dllexport)
  #else
	#define CMIRISLIBINTERNAL_EXPORT __declspec(dllimport)
  #endif
#endif

//////////////////////////////////////////////////////////////////////////////
// UMXEeprom File format
//
// Type(2 byte) cnt(2 byte - the number of bytes following) contents(cnt bytes)
///////////////////////////////////////////////////////////////////////////////

class UMXEeprom
{
public:

    enum UMXEepromType { // 2 bytes
        EEPROM_INIT_TYPE = 0x5817, // magic number
        EEPROM_VERSION_NUMBER_USHORT_TYPE = 0x1101,
        EEPROM_FIRMWARE_VERSION_NUMBER_USHORT_TYPE = 0x1102,
        EEPROM_UMXLIB_VERSION_NUMBER_USHORT_TYPE = 0x1103,
        EEPROM_MODEL_NAME_CHAR_TYPE = 0x1104,
        EEPROM_SERIAL_NUMBER_CHAR_TYPE = 0x1105,
        EEPROM_BOARD_NUMBER_CHAR_TYPE = 0x1106,
        EEPROM_PRODUCTION_REVISION_USHORT_TYPE = 0x1107,
        EEPROM_PRODUCTION_DATETIME_USHORT_TYPE = 0x1108, // year, month, date, hour, minute
        EEPROM_LICENSE_USHORT_TYPE = 0x1109,
        EEPROM_CALIB_USHORT_TYPE = 0x1110,
        EEPROM_CALIB_CORNER_IN_MM_SHORT_TYPE = 0x1111,
    };

    enum ProductionRevision {
        PROTO = 0x00,
        WORKING_SAMPLE = 0x01,
        ENGINEERING_SAMPLE = 0x02,
        PRE_PRODUCTION = 0x03,
        PRODUCTION = 0x04
    };

    enum LicenseType { // bit operation
        MIRLIN_LICENSE = 0x0001,
        NEC_LICENSE = 0x0002
    };

    enum {
        MAX_NUM_OF_Z = 20
    };

public:
    UMXEeprom();
    UMXEeprom(Poco::Logger& logger);
    ~UMXEeprom();

    void setCalibCorners(ushort left, ushort right, ushort top, ushort bottom);

    bool setCalibData(int i, ushort z, ushort nx1, ushort ny1, ushort nx2, ushort ny2,
                                 ushort nx3, ushort ny3, ushort nx4, ushort ny4,
                                 ushort wx1, ushort wy1, ushort wx2, ushort wy2,
                                 ushort wx3, ushort wy3, ushort wx4, ushort wy4);
    void prepareCalibVariables();

    bool writeEEPROM();
    bool loadEEPROM();

    bool sendEEPROM();
    bool receiveEEPROM();
    bool readEEPROMFromFile(std::string &filename);

private:
    Poco::Logger& _logger;
    int _mini, _maxi;

public:
    unsigned char *_data;
    int _dataSize;
    unsigned short _totalFollowingSize;

    unsigned short _eepromVersionNumber;
    unsigned short _firmwareVersionNumber;

    std::string _modelName;
    std::string _serialNumber;
    std::string _boardNumber;
    unsigned short _modelNameSize;
    unsigned short _serialNumberSize;
    unsigned short _boardNumberSize;

    unsigned short _productionRevision;

    unsigned short _productionDateTimeSize;
    unsigned short _year;
    unsigned short _month;
    unsigned short _day;
    unsigned short _hour;
    unsigned short _minute;
    unsigned short _second;

    unsigned short _license;
    unsigned short _calibSize;

    unsigned short _libMajorVersion;
    unsigned short _libMinorVersion;
    unsigned short _libRevisionVersion;

    // UMXEeprom internal calibration data structure.
    // After set by UMXEeprom::setCalibData(), use UMXEeprom::prepareCalibVariables()
    // to fill out the following. These data will feed to STEREO for stereo setup
    // UMXEeprom::receiveEEPROM() and UMXEeprom::loadEEPROM() will fill out these variables
    // For simulation, read eeprom data from file instead of UMXEeprom::receiveEEPROM()
    unsigned short _numOfZ, *_z;
    unsigned short *_nx1, *_ny1, *_nx2, *_ny2, *_nx3, *_ny3, *_nx4, *_ny4;
    unsigned short *_wx1, *_wy1, *_wx2, *_wy2, *_wx3, *_wy3, *_wx4, *_wy4;
    short _left,_right, _top, _bottom;

    // for calibration data input to UMXEeprom, use UMXEeprom::setCalibData()
    unsigned short _calibData[MAX_NUM_OF_Z][17];

};

#endif // UMXEEPROM_H
