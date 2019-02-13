/////////////////////////////////////////////////////////////////////////////////////////
// umxNetGlobal.h
//
// Version 0.1.3   July 18, 2016
//                 Initial Public Release
//
// Description: umxNetGlobal.h defines the constants and struct for umxNet.h
//              Please see umxNet.h for detailed interface.
//
/////////////////////////////////////////////////////////////////////////////////////////

#ifndef UMXNETGLOBAL_H
#define UMXNETGLOBAL_H

#include <memory>
#include <string>
#include <deque>

#include "cjson/cJSONpp.h"
#include "umxCommonGlobal.h"

#include <Poco/Util/PropertyFileConfiguration.h>
#include <Poco/AutoPtr.h>
#include <Poco/Logger.h>
#include <Poco/Mutex.h>

typedef void *UMXNET_HANDLE;

////////////////////////////////////////////////////////////////////////////////////////
// network service type information
////////////////////////////////////////////////////////////////////////////////////////

#define UMXNET_POCO_RESTSERVICE                                0

////////////////////////////////////////////////////////////////////////////////////////
// Return values
////////////////////////////////////////////////////////////////////////////////////////

#define UMXNET_SUCCESS                              0

#define UMXNET_ERROR_CANNOT_ALLOC_MEMORY           -1

#define UMXNET_ERROR_INVALID_HANDLE                -2  // Invalid UMXNET_HANDLE in argument

#define UMXNET_ERROR_IN_ARGUMENTS                  -3  // Error in arguments

using namespace UMXCommon;

namespace UMXNetwork
{
    class VersionConverter
    {
    public:
        VersionConverter(const std::string version);
        ~VersionConverter(void);

        const std::string GetVersion() const;
        const std::string AsJSONString() const;
        static VersionConverter Parse(const std::string jsonString);
    private:
        std::string _version;
    };

    class SelectedData
    {
    public:
        SelectedData(const std::string& encounterId, const std::string& timestamp, const std::string& serialNumber);
        const std::string GetEncounterId() const;
        const std::string GetTimestamp() const;
        const std::string GetSerialNumber() const;

        std::string uuid() const;
        void setUuid(const std::string &uuid);

        int logId() const;
        void setLogId(int logId);

        const std::string GetLeftEye() const;
        const std::string GetLeftEyeEnrollIrisTemplate() const;
        void SetLeftEye(std::string&& leftEye);
        void SetLeftEyeEnrollIrisTemplate(std::string&& leftEyeEnrollIrisTemplate);
        void SetLeftEyeUsableIrisArea(const double leftEyeUsableIrisArea);
        void SetLeftEyeQualityScore(const double leftEyeQualityScore);
        void SetLeftEyeQualityOk(const bool leftEyeQualityOk);

        const std::string GetRightEye() const;
        const std::string GetRightEyeEnrollIrisTemplate() const;
        void SetRightEye(std::string&& rightEye);
        void SetRightEyeEnrollIrisTemplate(std::string&& rightEyeEnrollIrisTemplate);
        void SetRightEyeUsableIrisArea(const double rightEyeUsableIrisArea);
        void SetRightEyeQualityScore(const double rightEyeQualityScore);
        void SetRightEyeQualityOk(const bool rightEyeQualityOk);

        const std::string GetIrisOffFace() const;
        const std::string GetIrisOffFaceFeature() const;
        void SetIrisOffFace(std::string&& irisOffFace);
        void SetIrisOffFaceEyeWidth(const int irisOffFaceEyeWidth);
        void SetIrisOffFaceFeature(std::string&& irisOffFaceFeature);
        void SetIrisOffFaceFeatureSize(const long irisOffFaceFeatureSize);
        void SetIrisOffFaceFrontalScore(const float irisOffFaceFrontalScore);
        void SetIrisOffFaceLEDState(const int irisOffFaceLEDState);
        void SetIrisOffFaceLeftEyeX(const int irisOffFaceLeftEyeX);
        void SetIrisOffFaceRightEyeX(const int irisOffFaceRightEyeX);
        void SetIrisOffFaceRoll(const float irisOffFaceRoll);
        void SetIrisOffFaceScore(const float irisOffFaceScore);

        const std::string GetFarOffFace() const;
        const std::string GetFarOffFaceFeature() const;
        void SetFarOffFace(std::string&& farOffFace);
        void SetFarOffFaceEyeWidth(const int farOffFaceEyeWidth);
        void SetFarOffFaceFeature(std::string&& farOffFaceFeature);
        void SetFarOffFaceFeatureSize(const long farOffFaceFeatureSize);
        void SetFarOffFaceFrontalScore(const float farOffFaceFrontalScore);
        void SetFarOffFaceLEDState(const int farOffFaceLEDState);
        void SetFarOffFaceLeftEyeX(const int farOffFaceLeftEyeX);
        void SetFarOffFaceRightEyeX(const int farOffFaceRightEyeX);
        void SetFarOffFaceRoll(const float farOffFaceRoll);
        void SetFarOffFaceScore(const float farOffFaceScore);

        const std::string GetFarOnFace() const;
        const std::string GetFarOnFaceFeature() const;
        void SetFarOnFace(std::string&& farOnFace);
        void SetFarOnFaceEyeWidth(const int farOnFaceEyeWidth);
        void SetFarOnFaceFeature(std::string&& farOnFaceFeature);
        void SetFarOnFaceFeatureSize(const long farOnFaceFeatureSize);
        void SetFarOnFaceFrontalScore(const float farOnFaceFrontalScore);
        void SetFarOnFaceLEDState(const int farOnFaceLEDState);
        void SetFarOnFaceLeftEyeX(const int farOnFaceLeftEyeX);
        void SetFarOnFaceRightEyeX(const int farOnFaceRightEyeX);
        void SetFarOnFaceRoll(const float farOnFaceRoll);
        void SetFarOnFaceScore(const float farOnFaceScore);

        const std::string GetNearOffFace() const;
        const std::string GetNearOffFaceFeature() const;
        void SetNearOffFace(std::string&& nearOffFace);
        void SetNearOffFaceEyeWidth(const int nearOffFaceEyeWidth);
        void SetNearOffFaceFeature(std::string&& nearOffFaceFeature);
        void SetNearOffFaceFeatureSize(const long nearOffFaceFeatureSize);
        void SetNearOffFaceFrontalScore(const float nearOffFaceFrontalScore);
        void SetNearOffFaceLEDState(const int nearOffFaceLEDState);
        void SetNearOffFaceLeftEyeX(const int nearOffFaceLeftEyeX);
        void SetNearOffFaceRightEyeX(const int nearOffFaceRightEyeX);
        void SetNearOffFaceRoll(const float nearOffFaceRoll);
        void SetNearOffFaceScore(const float nearOffFaceScore);

        const std::string GetNearOnFace() const;
        const std::string GetNearOnFaceFeature() const;
        void SetNearOnFace(std::string&& nearOnFace);
        void SetNearOnFaceEyeWidth(const int nearOnFaceEyeWidth);
        void SetNearOnFaceFeature(std::string&& nearOnFaceFeature);
        void SetNearOnFaceFeatureSize(const long nearOnFaceFeatureSize);
        void SetNearOnFaceFrontalScore(const float nearOnFaceFrontalScore);
        void SetNearOnFaceLEDState(const int nearOnFaceLEDState);
        void SetNearOnFaceLeftEyeX(const int nearOnFaceLeftEyeX);
        void SetNearOnFaceRightEyeX(const int nearOnFaceRightEyeX);
        void SetNearOnFaceRoll(const float nearOnFaceRoll);
        void SetNearOnFaceScore(const float nearOnFaceScore);

        void SetEncounterId(const std::string& encounterId);
        void SetTimestamp(const std::string& timestamp);
        void SetSerialNumber(const std::string& serialNumber);
        const std::string AsJSONString() const;
        const cjsonpp::JSONObject AsJSONObject() const;

    private:
        std::string _encounterId;
        std::string _timestamp;
        std::string _serialNumber;
        std::string _uuid;
        int _logId;
        std::string _leftEye;
        double _leftEyeUsableIrisArea;
        double _leftEyeQualityScore;
        bool _leftEyeQualityOk;
        std::string _leftEyeEnrollIrisTemplate;

        std::string _rightEye;
        double _rightEyeUsableIrisArea;
        double _rightEyeQualityScore;
        bool _rightEyeQualityOk;
        std::string _rightEyeEnrollIrisTemplate;

        std::string _irisOffFace;
        int _irisOffFaceEyeWidth;
        std::string _irisOffFaceFeature;
        int64_t _irisOffFaceFeatureSize;
        float _irisOffFaceFrontalScore;
        int _irisOffFaceLEDState;
        int _irisOffFaceLeftEyeX;
        int _irisOffFaceRightEyeX;
        float _irisOffFaceRoll;
        float _irisOffFaceScore;

        std::string _farOffFace;
        int _farOffFaceEyeWidth;
        std::string _farOffFaceFeature;
        int64_t _farOffFaceFeatureSize;
        float _farOffFaceFrontalScore;
        int _farOffFaceLEDState;
        int _farOffFaceLeftEyeX;
        int _farOffFaceRightEyeX;
        float _farOffFaceRoll;
        float _farOffFaceScore;

        std::string _farOnFace;
        int _farOnFaceEyeWidth;
        std::string _farOnFaceFeature;
        int64_t _farOnFaceFeatureSize;
        float _farOnFaceFrontalScore;
        int _farOnFaceLEDState;
        int _farOnFaceLeftEyeX;
        int _farOnFaceRightEyeX;
        float _farOnFaceRoll;
        float _farOnFaceScore;

        std::string _nearOffFace;
        int _nearOffFaceEyeWidth;
        std::string _nearOffFaceFeature;
        int64_t _nearOffFaceFeatureSize;
        float _nearOffFaceFrontalScore;
        int _nearOffFaceLEDState;
        int _nearOffFaceLeftEyeX;
        int _nearOffFaceRightEyeX;
        float _nearOffFaceRoll;
        float _nearOffFaceScore;

        std::string _nearOnFace;
        int _nearOnFaceEyeWidth;
        std::string _nearOnFaceFeature;
        int64_t _nearOnFaceFeatureSize;
        float _nearOnFaceFrontalScore;
        int _nearOnFaceLEDState;
        int _nearOnFaceLeftEyeX;
        int _nearOnFaceRightEyeX;
        float _nearOnFaceRoll;
        float _nearOnFaceScore;
    };

    class PreviewData
    {
    public:
        PreviewData();
        PreviewData(const std::string& leftEye, const std::string& rightEye, const std::string& faceImage);
        const std::string GetLeftEye() const;
        const std::string GetRightEye() const;
        const std::string GetFaceImage() const;
        void SetLeftEye(const std::string& leftEye);
        void SetRightEye(const std::string& rightEye);
        void SetFaceImage(const std::string& faceImage);
        const std::string AsJSONString() const;
        const bool IsValid() const;
        int getAvgDistance() const;
        void setAvgDistance(int value);
        int getLeftBoundary() const;
        void setLeftBoundary(int leftBoundary);

        int getRightBoundary() const;
        void setRightBoundary(int rightBoundary);

        int getLeftIrisCenterX() const;
        void setLeftIrisCenterX(int leftIrisCenterX);

        int getRightIrisCenterX() const;
        void setRightIrisCenterX(int rightIrisCenterX);

        int getLeftIrisCenterY() const;
        void setLeftIrisCenterY(int leftIrisCenterY);

        int getRightIrisCenterY() const;
        void setRightIrisCenterY(int rightIrisCenterY);

        int getLeftEyeCenterX() const;
        void setLeftEyeCenterX(int leftEyeCenterX);

        int getRightEyeCenterX() const;
        void setRightEyeCenterX(int rightEyeCenterX);

        int getLeftEyeCenterY() const;
        void setLeftEyeCenterY(int leftEyeCenterY);

        int getRightEyeCenterY() const;
        void setRightEyeCenterY(int rightEyeCenterY);

        int getLeftIrisRadius() const;
        void setLeftIrisRadius(int leftIrisRadius);

        int getRightIrisRadius() const;
        void setRightIrisRadius(int rightIrisRadius);

        int getLeftDistance() const;
        void setLeftDistance(int leftDistance);

        int getRightDistance() const;
        void setRightDistance(int rightDistance);

        bool getSwitchFlag() const;
        void setSwitchFlag(bool switchFlag);

        int getMessage() const;
        void setMessage(int message);

    private:
        bool _valid;
        std::string _leftEye;
        std::string _rightEye;
        std::string _faceImage;

        int _avgDistance;
        int _leftBoundary, _rightBoundary;

        int _leftIrisCenterX, _rightIrisCenterX;
        int _leftIrisCenterY, _rightIrisCenterY;

        int _leftEyeCenterX, _rightEyeCenterX;
        int _leftEyeCenterY, _rightEyeCenterY;

        int _leftIrisRadius, _rightIrisRadius;

        int _leftDistance, _rightDistance;

        int _message;

        bool _switchFlag;
    };

    class SelectedFacePreviewData
    {
    public:
        SelectedFacePreviewData();
        const std::string AsJSONString() const;
        std::string faceOff() const;
        void setFaceOff(const std::string &faceOff);
        std::string faceOn() const;
        void setFaceOn(const std::string &faceOn);
        int width() const;
        void setWidth(int width);
        int height() const;
        void setHeight(int height);

    private:
        std::string _faceOff;
        std::string _faceOn;
        int _width;
        int _height;
    };

    struct CameraControlResponse
    {
    public:
        CameraControlResponse();
        CameraControlResponse(const bool success, const std::string& status);
        const std::string AsJSONString() const;

        bool _success;
        std::string _status;
    };

    class BiometricData
    {
    public:
        BiometricData(const std::string& encounterId, const std::string& timestamp, const std::string& serialNumber);
        const std::string GetEncounterId() const;
        const std::string GetTimestamp() const;
        const std::string GetSerialNumber() const;

        const std::string GetLeftEye() const;
        const std::string GetLeftEyeEnrolTemplate() const;
        void SetLeftEye(std::string&& leftEye);
        void SetLeftEyeDuplicateUUID(const std::string& leftEyeDuplicateUUID);
        void SetLeftEyeEnrolTemplate(std::string&& leftEyeEnrolTemplate);
        void SetLeftEyeUsableIrisArea(const double leftEyeUsableIrisArea);
        void SetLeftEyeQualityScore(const double leftEyeQualityScore);
        void SetLeftEyeQualityOk(const bool leftEyeQualityOk);

        const std::string GetRightEye() const;
        const std::string GetRightEyeEnrolTemplate() const;
        void SetRightEye(std::string&& rightEye);
        void SetRightEyeDuplicateUUID(const std::string& rightEyeDuplicateUUID);
        void SetRightEyeEnrolTemplate(std::string&& rightEyeEnrolTemplate);
        void SetRightEyeUsableIrisArea(const double rightEyeUsableIrisArea);
        void SetRightEyeQualityScore(const double rightEyeQualityScore);
        void SetRightEyeQualityOk(const bool rightEyeQualityOk);

        const std::string GetIrisOffFace() const;
        const std::string GetIrisOffFaceFeature() const;
        void SetIrisOffFace(std::string&& irisOffFace);
        void SetIrisOffFaceDuplicateUUID(const std::string& irisOffFaceDuplicateUUID);
        void SetIrisOffFaceEyeWidth(const int irisOffFaceEyeWidth);
        void SetIrisOffFaceFeature(std::string&& irisOffFaceFeature);
        void SetIrisOffFaceFeatureSize(const long irisOffFaceFeatureSize);
        void SetIrisOffFaceFrontalScore(const float irisOffFaceFrontalScore);
        void SetIrisOffFaceLEDState(const int irisOffFaceLEDState);
        void SetIrisOffFaceLeftEyeX(const int irisOffFaceLeftEyeX);
        void SetIrisOffFaceRightEyeX(const int irisOffFaceRightEyeX);
        void SetIrisOffFaceRoll(const float irisOffFaceRoll);
        void SetIrisOffFaceScore(const float irisOffFaceScore);

        const std::string GetFarOffFace() const;
        const std::string GetFarOffFaceFeature() const;
        void SetFarOffFace(std::string&& farOffFace);
        void SetFarOffFaceDuplicateUUID(const std::string& farOffFaceDuplicateUUID);
        void SetFarOffFaceEyeWidth(const int farOffFaceEyeWidth);
        void SetFarOffFaceFeature(std::string&& farOffFaceFeature);
        void SetFarOffFaceFeatureSize(const long farOffFaceFeatureSize);
        void SetFarOffFaceFrontalScore(const float farOffFaceFrontalScore);
        void SetFarOffFaceLEDState(const int farOffFaceLEDState);
        void SetFarOffFaceLeftEyeX(const int farOffFaceLeftEyeX);
        void SetFarOffFaceRightEyeX(const int farOffFaceRightEyeX);
        void SetFarOffFaceRoll(const float farOffFaceRoll);
        void SetFarOffFaceScore(const float farOffFaceScore);

        const std::string GetFarOnFace() const;
        const std::string GetFarOnFaceFeature() const;
        void SetFarOnFace(std::string&& farOnFace);
        void SetFarOnFaceDuplicateUUID(const std::string& farOnFaceDuplicateUUID);
        void SetFarOnFaceEyeWidth(const int farOnFaceEyeWidth);
        void SetFarOnFaceFeature(std::string&& farOnFaceFeature);
        void SetFarOnFaceFeatureSize(const long farOnFaceFeatureSize);
        void SetFarOnFaceFrontalScore(const float farOnFaceFrontalScore);
        void SetFarOnFaceLEDState(const int farOnFaceLEDState);
        void SetFarOnFaceLeftEyeX(const int farOnFaceLeftEyeX);
        void SetFarOnFaceRightEyeX(const int farOnFaceRightEyeX);
        void SetFarOnFaceRoll(const float farOnFaceRoll);
        void SetFarOnFaceScore(const float farOnFaceScore);

        const std::string GetNearOffFace() const;
        const std::string GetNearOffFaceFeature() const;
        void SetNearOffFace(std::string&& nearOffFace);
        void SetNearOffFaceDuplicateUUID(const std::string& nearOffFaceDuplicateUUID);
        void SetNearOffFaceEyeWidth(const int nearOffFaceEyeWidth);
        void SetNearOffFaceFeature(std::string&& nearOffFaceFeature);
        void SetNearOffFaceFeatureSize(const long nearOffFaceFeatureSize);
        void SetNearOffFaceFrontalScore(const float nearOffFaceFrontalScore);
        void SetNearOffFaceLEDState(const int nearOffFaceLEDState);
        void SetNearOffFaceLeftEyeX(const int nearOffFaceLeftEyeX);
        void SetNearOffFaceRightEyeX(const int nearOffFaceRightEyeX);
        void SetNearOffFaceRoll(const float nearOffFaceRoll);
        void SetNearOffFaceScore(const float nearOffFaceScore);

        const std::string GetNearOnFace() const;
        const std::string GetNearOnFaceFeature() const;
        void SetNearOnFace(std::string&& nearOnFace);
        void SetNearOnFaceDuplicateUUID(const std::string& nearOnFaceDuplicateUUID);
        void SetNearOnFaceEyeWidth(const int nearOnFaceEyeWidth);
        void SetNearOnFaceFeature(std::string&& nearOnFaceFeature);
        void SetNearOnFaceFeatureSize(const long nearOnFaceFeatureSize);
        void SetNearOnFaceFrontalScore(const float nearOnFaceFrontalScore);
        void SetNearOnFaceLEDState(const int nearOnFaceLEDState);
        void SetNearOnFaceLeftEyeX(const int nearOnFaceLeftEyeX);
        void SetNearOnFaceRightEyeX(const int nearOnFaceRightEyeX);
        void SetNearOnFaceRoll(const float nearOnFaceRoll);
        void SetNearOnFaceScore(const float nearOnFaceScore);

        void SetErrorMessage(const std::string& errorMessage);

        void SetEncounterId(const std::string& encounterId);
        void SetTimestamp(const std::string& timestamp);
        void SetSerialNumber(const std::string& serialNumber);

        void SetRecordVersion(const int version);

        const std::string AsJSONString() const;
        const cjsonpp::JSONObject AsJSONObject() const;

        const std::string AsJSONStringVer1() const;
        const cjsonpp::JSONObject AsJSONObjectVer1() const;

    private:
        std::string _encounterId;
        std::string _timestamp;
        std::string _serialNumber;
        std::string _leftEye;
        double _leftEyeUsableIrisArea;
        double _leftEyeQualityScore;
        bool _leftEyeQualityOk;
        std::string _leftEyeEnrolTemplate;
        std::string _leftEyeDuplicateUUID;

        std::string _rightEye;
        double _rightEyeUsableIrisArea;
        double _rightEyeQualityScore;
        bool _rightEyeQualityOk;
        std::string _rightEyeEnrolTemplate;
        std::string _rightEyeDuplicateUUID;

        std::string _irisOffFace;
        std::string _irisOffFaceDuplicateUUID;
        int _irisOffFaceEyeWidth;
        std::string _irisOffFaceFeature;
        int64_t _irisOffFaceFeatureSize;
        float _irisOffFaceFrontalScore;
        int _irisOffFaceLEDState;
        int _irisOffFaceLeftEyeX;
        int _irisOffFaceRightEyeX;
        float _irisOffFaceRoll;
        float _irisOffFaceScore;

        std::string _farOffFace;
        std::string _farOffFaceDuplicateUUID;
        int _farOffFaceEyeWidth;
        std::string _farOffFaceFeature;
        int64_t _farOffFaceFeatureSize;
        float _farOffFaceFrontalScore;
        int _farOffFaceLEDState;
        int _farOffFaceLeftEyeX;
        int _farOffFaceRightEyeX;
        float _farOffFaceRoll;
        float _farOffFaceScore;

        std::string _farOnFace;
        std::string _farOnFaceDuplicateUUID;
        int _farOnFaceEyeWidth;
        std::string _farOnFaceFeature;
        int64_t _farOnFaceFeatureSize;
        float _farOnFaceFrontalScore;
        int _farOnFaceLEDState;
        int _farOnFaceLeftEyeX;
        int _farOnFaceRightEyeX;
        float _farOnFaceRoll;
        float _farOnFaceScore;

        std::string _nearOffFace;
        std::string _nearOffFaceDuplicateUUID;
        int _nearOffFaceEyeWidth;
        std::string _nearOffFaceFeature;
        int64_t _nearOffFaceFeatureSize;
        float _nearOffFaceFrontalScore;
        int _nearOffFaceLEDState;
        int _nearOffFaceLeftEyeX;
        int _nearOffFaceRightEyeX;
        float _nearOffFaceRoll;
        float _nearOffFaceScore;

        std::string _nearOnFace;
        std::string _nearOnFaceDuplicateUUID;
        int _nearOnFaceEyeWidth;
        std::string _nearOnFaceFeature;
        int64_t _nearOnFaceFeatureSize;
        float _nearOnFaceFrontalScore;
        int _nearOnFaceLEDState;
        int _nearOnFaceLeftEyeX;
        int _nearOnFaceRightEyeX;
        float _nearOnFaceRoll;
        float _nearOnFaceScore;

        std::string _errorMessage;

        int _recordVersion;
    };

    class BiometricDataCache
    {
    public:
        BiometricDataCache(const int cacheSize);
        ~BiometricDataCache();

        void Insert(const BiometricData& biometricData);
        std::deque<BiometricData> Select();
        bool Delete(const std::string& encounterId);
    private:
        std::deque<BiometricData> _biometricData;
        const int _cacheSize;
        Poco::Mutex _mutex;
    };

    class SelectedDataCache
    {
    public:
        SelectedDataCache(const int cacheSize);
        ~SelectedDataCache();

        void Insert(const SelectedData& selectedData);
        std::deque<SelectedData> Select();
        bool Delete(const std::string& encounterId);
    private:
        std::deque<SelectedData> _selectedData;
        const int _cacheSize;
        Poco::Mutex _mutex;
    };

    class SelectedFacePreviewDataCache
    {
    public:
        SelectedFacePreviewDataCache(const int cacheSize);
        ~SelectedFacePreviewDataCache();

        void Insert(const SelectedFacePreviewData& selectedFacePreviewData);
        std::deque<SelectedFacePreviewData> Select();
        void DeleteAll();
    private:
        std::deque<SelectedFacePreviewData> _selectedFacePreviewData;
        const int _cacheSize;
        Poco::Mutex _mutex;
    };

    class ReturnData
    {
    public:
        ReturnData(){}
        ReturnData(const int retCode, const std::string retMsg) : _retCode(retCode), _retMsg(retMsg)
        {

        }

        int _retCode;
        std::string _retMsg;

        template<class T>
        static bool HasValue(cjsonpp::JSONObject& obj, const std::string& name)
        {
            bool hasValue = false;
            try
            {
                obj.get<T>(name.c_str());
                hasValue = true;
            }
            catch(cjsonpp::JSONError&)
            {
            }
            return hasValue;
        }

        static ReturnData Parse(const std::string jsonString)
        {
            ReturnData data;

            if(jsonString.length() == 0)
            {
                data._retCode = 0;
                return data;
            }

        //    std::cout << jsonString << std::endl;
            cjsonpp::JSONObject obj = cjsonpp::parse( jsonString );


            if (HasValue<int>( obj, "resultCode" ) )
            {
                data._retCode = obj.get<int>("resultCode");
            }
            if (HasValue<std::string>( obj, "resultMsg" ) )
            {
                data._retMsg = obj.get<std::string>("resultMsg");
            }

            return data;
        }

    };

    class CryptoData
    {
    public:
        CryptoData();

        const char* getIfToIP(char *ifName) const;
        const char* getIfToMacAddress(char *ifName) const;
        const void Char2Hex(unsigned char ch, char* szHex) const;
        const void Hex2Char(char const* szHex, unsigned char& rch) const;
        const void CharStr2HexStr(unsigned char const* pucCharStr, char* pszHexStr, int iSize) const;
        const void HexStr2CharStr(char const* pszHexStr, unsigned char* pucCharStr, int iSize) const;

        const std::string ConvEncrypt(std::string data) const;
        const std::string ConvEncrypt(char* key, std::string data) const;
        const std::string ConvKTTEncrypt(char* key, std::string data) const;
        const std::string ConvKTTdecrypt(std::string encjsonString) const;
        const void ConvEncrypt(cjsonpp::JSONObject* obj, std::string name, std::string data) const;

    public:
        std::string _lockUuid;
        std::string _serialNo;
        int _encryptMethod;

    private:
        const char* getKey() const;
        const char* createOcpKey() const;
        const std::string replaceString(std::string subject, const std::string &search, const std::string &replace) const;
    };

    class CommuteData : public CryptoData
    {
    public:
        CommuteData();

        const std::string AsJSONString() const;
        const cjsonpp::JSONObject AsJSONObject() const;
        static CommuteData CreateCommuteData();

        std::string _macAddr;
        int _commuteKind;
        std::string _userId;
        std::string _userName;
        std::string _employeeNum;
        int _authType;
        int _authTypeSub;
        int _authResult;
        std::string _deviceTime;
        int _logId;
        std::string _ipAddr;
    };

    class ServerAuthData : public CryptoData
    {
    public:
        ServerAuthData();

        enum {
            IDENTIFY_IMAGE = 1,
            IDENTIFY_FEATURE,
            IDENTIFY_MAX
        };

        const std::string AsJSONString() const;
        const cjsonpp::JSONObject AsJSONObject() const;
        static ServerAuthData CreateData();
        void initData();
        int getServerAuthKind(int restAuthMode);

        std::string _macAddr;
        int _operationMode;
        int _identifyKind;

        std::string _leftFeature;
        std::string _rightFeature;
        std::string _leftImgData;
        std::string _rightImgData;
        std::string _irisCapturedFace;

        int _leftImgHeight;
        int _leftImgWidth;
        int _rightImgHeight;
        int _rightImgWidth;
        int _leftIrisCenterX;
        int _rightIrisCenterX;
        int _leftIrisCenterY;
        int _rightIrisCenterY;
        int _leftIrisRadius;
        int _rightIrisRadius;
        int _leftPupilRadius;
        int _rightPupilRadius;
        int _irisCapturedFaceImgHeight;
        int _irisCapturedFaceImgWidth;
        int _irisCapturedFaceImgSize;

    };

    class ServerEnrolData : public CryptoData
    {
    public:
        ServerEnrolData();

        const std::string AsJSONString() const;
        const cjsonpp::JSONObject AsJSONObject() const;

        std::string _macAddr;
        int _operationMode;
        int _identifyKind;
        std::string _userId;
    };

    class KTTDMSPostData : public CryptoData
    {
    public:
        KTTDMSPostData(){}

        const std::string AsJSONString() const;
        const cjsonpp::JSONObject AsJSONObject() const;

        std::string _kttSystemID;
        std::string _macAddr;
        std::string _deviceCode;
        std::string _manufacturer;
        std::string _modelname;
        std::string _fwversion;
        std::string _alarmStatus;
        std::string _mcInfo;
        std::string _deviceID;
        std::string _ipAddress;
        std::string _subnetMask;
        std::string _gateway;
        std::string _informServerAddress;
        std::string _informInterval;
    };

    class KTTDMSRespData : public CryptoData
    {
    public:
        KTTDMSRespData(){}

        std::string _returnCode;
        int _actType;
        std::string _upgradeServerIp;
        int _upgradeServerPort;
        std::string _upgradeUserName;
        std::string _upgradeUserPassword;
        std::string _upgradeImagePath;
        std::string _upgradeImageName;
        int _upgradeImageSize;
        std::string _upgradeImagehash;
        int _sysReboot;
        int _sysRebootSource;
        std::string _informServerAddress;
        int _informInterval;
    };

    class AcceptableData : public CryptoData
    {
    public:
        AcceptableData();

        const std::string AsJSONString() const;
        const cjsonpp::JSONObject AsJSONObject() const;

        std::string _macAddr;
    };

    class INetworkManager
    {
    public:
#ifdef ANDROID
        virtual ~INetworkManager() {}
#endif
        enum : int
        {
            INET_MANAGER_SUCCESS =                                                                                     0,

            INET_MANAGER_ERROR_SHOULD_NOT_BE_HAPPENED =                                                               -1,
            INET_MANAGER_ERROR_DB_INVALID_HANDLE =                                                                    -2,

            INET_MANAGER_EXCEPTION_VACUUM_SERVICE =                                                                 -100,
            INET_MANAGER_EXCEPTION_VACUUM_SERVICELOG =                                                              -101,

            INET_MANAGER_ERROR_ALREADY_START =                                                                      -200,
            INET_MANAGER_ERROR_CAN_NOT_ENROLL_FOR_DB_FULL =                                                         -201,
            INET_MANAGER_ERROR_WRONG_START_MODE =                                                                   -202,
            INET_MANAGER_ERROR_IRIS_DB_IS_FULL =                                                                    -203,
            INET_MANAGER_ERROR_FACE_DB_IS_FULL =                                                                    -204,
            INET_MANAGER_ERROR_UNKNOWN_START_MODE =                                                                 -205,
            INET_MANAGER_ERROR_IRIS_AND_FACE_DB_ALL_IS_FULL =                                                       -206,
            INET_MANAGER_ERROR_NOT_LAUNCHER_MODE =                                                                  -207,
            INET_MANAGER_ERROR_NOT_SLAVE_MODE =                                                                     -208,

            INET_MANAGER_ERROR_RELAY_IS_DISABLE =                                                                   -300,
            INET_MANAGER_ERROR_RELAY_UNKNOWN =                                                                      -301
        };

    public:
        virtual std::string GetUMXLauncherVersion()=0;
        virtual unsigned int GetSubjectRecordVersion()=0;
        virtual Poco::Logger& GetLogger()=0;
        virtual Poco::AutoPtr<Poco::Util::PropertyFileConfiguration> GetPropertiesFilePointer()=0;
        virtual std::string GetUMXMode()=0;
        virtual bool SetUMXMode(std::string mode)=0;
        virtual int CurDoorStatus()=0;
        virtual int GetDoorStatus()=0;
        virtual int relay(bool forced, int duration)=0;
        virtual CameraControlResponse ControlStatus()=0;
        virtual int StartEnrolCamera(bool faceMode = false, bool glassesMode = false, bool bothEyeMode = false, bool eitherEyeMode = false, bool streamingMode = false, bool recogMode = false,  bool tcpPreviewMode = false, std::string addr = "")=0;
        virtual int MatchTemplate(std::string seqUID, SubjectData subjectData)=0;
        virtual bool StopEnrolCamera()=0;
        virtual void StartReadCard()=0;
        virtual void StopReadCard()=0;
        virtual bool CaptureWideViewImage()=0;
        virtual bool GetPreviewData(PreviewData& previewData)=0;
        virtual std::shared_ptr<BiometricDataCache> GetBiometricDataCache()=0;
        virtual std::shared_ptr<SelectedDataCache> GetSelectedDataCache()=0;
        virtual std::shared_ptr<SelectedFacePreviewDataCache> GetSelectedFacePreviewDataCache()=0;
        virtual int vacuumService()=0;
        virtual int vacuumServiceLog()=0;
        virtual int getUserList(std::vector<UserSimpleData> *userList)=0;
        virtual int isExistTemplate(SubjectData* subjectData, std::string* duplicateUUID)=0;
        virtual int insertIris(SubjectData *subjectData)=0;
        virtual SubjectData selectIrisByUUID(const std::string uuid)=0;
        virtual int selectIrisesByPage(const int page, const int pageSize, std::vector<SubjectData> *retIrises)=0;
        virtual int updateIrisByUUID(const std::string uuid, SubjectData& subjectData)=0;
        virtual int deleteIrisByUUID(const std::string uuid)=0;
        virtual int insertFace(FaceData* faceData)=0;
        virtual int selectFacesByPage(const int page, const int pageSize, std::vector<FaceData> *retFaces)=0;
        virtual int selectFacesByUUID(const std::string uuid, std::vector<FaceData> *retFaces)=0;
        virtual int selectFaceByUuIdAndSubId(const std::string uuid, const int subId, FaceData *faceData)=0;
        virtual int updateFaceByUuIdAndSubId(const std::string& uuid, const int subId, FaceData& faceData)=0;
        virtual int deleteFaceByUuIdAndSubId(const std::string uuid, const int subId)=0;
        virtual int insertUserInfo(const std::string uuid, const std::string card, const std::string pin,
                                    const int admin, const int groupIndex, const int byPassCard, const int indivisual,
                                    const int threeOutStatus, const int threeOutAccessAllowed, const int jobCode, const int timeScheduleCode,
                                    const int apbStatus, const std::string message)=0;
        virtual int selectUserInfoByUUID(const std::string uuid, UserInfoData *userInfo)=0;
        virtual int selectUserInfoByCard(const std::string card, UserInfoData *userInfo)=0;
        virtual int selectUserInfoByPage(const int page, const int pageSize, std::vector<UserInfoData> *retAllUserInfo)=0;
        virtual int updateUserInfoByUUID(const std::string uuid, const std::string card, const std::string pin,
                                                 const int admin, const int groupIndex, const int byPassCard, const int indivisual,
                                                 const int threeOutStatus, const int threeOutAccessAllowed, const int jobCode, const int timeScheduleCode,
                                                 const int apbStatus, const std::string message)=0;
        virtual int deleteUserInfoByUUID(const std::string uuid)=0;
        virtual int deleteAllUsers()=0;
        virtual int selectLogEntryFromToByPage(const int pageNumber, const int pageSize, const int fromId, const int toId, std::vector<LogEntry> *retLogEntry)=0;
        virtual int selectLogEntryByPage(const int pageNumber, const int pageSize, const std::string& order, std::vector<LogEntry> *retLogEntry)=0;
        virtual LogEntry selectLogEntryById(const int id)=0;
        virtual bool deleteLogEntryFromTo(const int fromId, const int toId)=0;
        virtual bool deleteLogEntryById(const int id)=0;
        virtual void deleteServiceLogDB()=0;
        virtual std::vector<ImageCapture> selectImageCapture()=0;
        virtual void saveIrisAndFaceImage(const std::string uuid)=0;
        virtual void deleteIrisAndFaceImage(const std::string uuid)=0;
        virtual void deleteIrisImageByUUID(const std::string uuid)=0;
        virtual void deleteFaceImageByUUID(const std::string uuid)=0;
        virtual void deleteFaceImageBySubId(const std::string uuid, const int subId)=0;
        virtual void saveBMP8Image(std::string filename, unsigned char* image, int width, int height)=0;
        virtual void saveBMP24Image(std::string filename, unsigned char* image, int width, int height)=0;
        virtual void saveFile(std::string filename, unsigned char* file, int size)=0;
        virtual void loadFile(std::string filename, std::vector<unsigned char>* file)=0;
        virtual void save8bitToJPG(char* szPathName, void* lpBits, int w, int h, int targetW, int targetH)=0;
        virtual void save24bitToJPG(char* szPathName, void* lpBits, int w, int h, int targetW, int targetH)=0;
        virtual void setRestData(CommuteData& data)=0;
        virtual void setRestServerEnrolData(UMXNetwork::ServerEnrolData& data)=0;
        virtual std::vector<UMXNetwork::CommuteData>* getRestData()=0;
        virtual std::vector<UMXNetwork::ServerAuthData>* getRestServerAuthData()=0;
        virtual std::vector<UMXNetwork::ServerEnrolData>* getRestServerEnrolData()=0;
        virtual std::vector<UMXNetwork::KTTDMSPostData>* getKTTDMSPostData()=0;
        virtual std::vector<UMXNetwork::KTTDMSRespData>* getKTTDMSRespData()=0;
        virtual Poco::Mutex* getCommuteMutex()=0;
        virtual Poco::Mutex* getServerAuthDataMutex()=0;
        virtual Poco::Mutex* getServerEnrolMutex()=0;
        virtual Poco::Mutex* getKTTDMSMutex()=0;
        virtual void setSendToRest(bool flag)=0;
        virtual bool getSendToRest()=0;
        virtual bool getServerAuthDataSendToRest()=0;
        virtual void setServerAuthDataSendToRest(bool flag)=0;
        virtual bool getSendToRestForEnrol()=0;
        virtual bool setSendToRestForEnrol(bool flag)=0;
        virtual bool getSendToRestForKTTDMS()=0;
        virtual bool setSendToRestForKTTDMS(bool flag)=0;
        virtual void* getDbManagerPtr()=0;
        virtual void* getAlgoMangerPtr()=0;
        virtual int getLastLogId()=0;
        virtual void getLogEntryByFromTo(const int fromId, const int toId, std::vector<LogEntry> *retLogEntry)=0;
        virtual void getSubjectDataByUuid(const std::string uuid, SubjectData *retIris)=0;
        virtual void getLogEntryById(const int id, LogEntry *retLogEntry)=0;
        virtual bool RestContorl(ControlData data)=0;
        virtual int updateFirmware(char* filePath, char* fileName, bool forcedFlag)=0;
        virtual void setPreivewStartFlag(bool previewStart)=0;
        virtual bool getPreivewStartFlag()=0;
        virtual void setPreivewReqFlag(bool previewReq)=0;
        virtual bool getPreviewReqFlag()=0;
        virtual std::string getCard()=0;
        virtual void setCard(std::string card)=0;
        virtual bool getFaceRaw(char** data, int* size)=0;
        virtual std::string getRequestIPAddress()=0;
        virtual void setRequestIPAddress(std::string addr)=0;
        virtual void heartBeat()=0;

        //- update config properties
        virtual int GetUpdateConfigProperties()=0;
        virtual void SetUpdateConfigProperties(int nUpdateConfigProperties)=0;

        //- update firmware
        virtual int GetUpdateFirmwareSize()=0;
        virtual void SetUpdateFirmwareSize(int nUpdateFirmwarSize)=0;

        virtual void setAPBMode(int enable)=0;
        virtual void clearAPBStatus(std::string uuid = "", bool all = true)=0;

        virtual void setLockUuid(std::string lockUuid) = 0;
        virtual std::string getLockUuid() = 0;
        virtual void setSerialNo(std::string serialNo) = 0;
        virtual std::string getSerialNo() = 0;

        virtual int insertUser(SubjectData *subjectData,
                               std::vector<FaceData>* faceData,
                               UserInfoData* userInfoData) = 0;
        virtual int deleteUserByUUID(const std::string uuid) = 0;
    };
}

#endif // UMXNETGLOBAL_H
