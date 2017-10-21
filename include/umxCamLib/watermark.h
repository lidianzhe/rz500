#ifndef WATERMARK_H
#define WATERMARK_H

#include <iostream>

#define CUR_WM_VERSION 0x0101

class WaterMark
{
public:
    WaterMark();

    void setModelName(std::string &modelName);
    void setSerialNumber(std::string &serialNumber);

    bool writeWaterMark(unsigned char *image);
    bool readWaterMark(unsigned char *image);
    bool changeEndian(unsigned char *data, int num);


public:
    uint32_t _magicNumber;
    uint16_t _WMVersion;

    uint16_t _modelNameSize;
    std::string _modelName;
    uint16_t _serialNumberSize;
    std::string _serialNumber;

    uint16_t _year;
    uint16_t _month;
    uint16_t _day;
    uint16_t _hour;
    uint16_t _minute;
    uint16_t _second;

    uint16_t _dataSize;
    unsigned char _data[160];

private:
    unsigned char _parity[256];
    unsigned char _bit[8];
    uint32_t _k[512];
    bool _isLittleEndian;
};

#endif // WATERMARK_H
