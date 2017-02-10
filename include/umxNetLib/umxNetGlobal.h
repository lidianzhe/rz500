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

#include <Poco/Mutex.h>

#include "umxCommonLib/cjson/cJSONpp.h"
#include "umxCommonLib/umxCommonGlobal.h"

#include <Poco/Util/PropertyFileConfiguration.h>
#include <Poco/AutoPtr.h>

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
        const std::string AsJSONString() const;
        const cjsonpp::JSONObject AsJSONObject() const;

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

        const void ConvEncrypt(cjsonpp::JSONObject* obj, std::string name, std::string data) const;
        const std::string ConvEncrypt(std::string data) const;
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
        virtual std::string GetUMXLauncherVersion()=0;
        virtual Poco::AutoPtr<Poco::Util::PropertyFileConfiguration> GetPropertiesFilePointer()=0;
        virtual std::string GetUMXMode()=0;
        virtual bool SetUMXMode(std::string mode)=0;
        virtual int CurDoorStatus()=0;
        virtual CameraControlResponse ControlStatus()=0;
        virtual bool StartEnrolCamera(bool faceMode = false, bool glassesMode = false, bool bothEyeMode = false, bool eitherEyeMode = false, bool streamingMode = false)=0;
        virtual bool StopEnrolCamera()=0;
        virtual bool CaptureWideViewImage()=0;
        virtual bool GetPreviewData(PreviewData& previewData)=0;
        virtual std::shared_ptr<BiometricDataCache> GetBiometricDataCache()=0;
        virtual std::shared_ptr<SelectedDataCache> GetSelectedDataCache()=0;
        virtual std::shared_ptr<SelectedFacePreviewDataCache> GetSelectedFacePreviewDataCache()=0;
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
                                    const int admin, const int groupIndex, const int byPassCard, const int indivisual)=0;
        virtual int selectUserInfoByUUID(const std::string uuid, UserInfoData *userInfo)=0;
        virtual int selectUserInfoByCard(const std::string card, UserInfoData *userInfo)=0;
        virtual int selectAllUserInfoByPage(const int page, const int pageSize, std::vector<UserInfoData> *retAllUserInfo)=0;
        virtual int updateUserInfoByUUID(const std::string uuid, const std::string card, const std::string pin,
                                                 const int admin, const int groupIndex, const int byPassCard, const int indivisual)=0;
        virtual int deleteUserInfoByUUID(const std::string uuid)=0;
        virtual int selectLogEntryByPage(const int pageNumber, const int pageSize, const std::string& order, std::vector<LogEntry> *retLogEntry)=0;
        virtual LogEntry selectLogEntryById(const int id)=0;
        virtual bool deleteLogEntryFromTo(const int fromId, const int toId)=0;
        virtual bool deleteLogEntryById(const int id)=0;
        virtual std::vector<ImageCapture> selectImageCapture()=0;
        virtual void saveIrisAndFaceImage(const std::string uuid)=0;
        virtual void saveBMP8Image(std::string filename, unsigned char* image, int width, int height)=0;
        virtual void saveBMP24Image(std::string filename, unsigned char* image, int width, int height)=0;
        virtual void setRestData(CommuteData& data)=0;
        virtual std::vector<UMXNetwork::CommuteData>* getRestData()=0;
        virtual Poco::Mutex* getCommuteMutex()=0;
        virtual void setSendToRest(bool flag)=0;
        virtual bool getSendToRest()=0;
        virtual void* getDbManagerPtr()=0;
        virtual int getLastLogId()=0;
        virtual void getLogEntryByFromTo(const int fromId, const int toId, std::vector<LogEntry> *retLogEntry)=0;
        virtual void getSubjectDataByUuid(const std::string uuid, SubjectData *retIris)=0;
        virtual void getLogEntryById(const int id, LogEntry *retLogEntry)=0;
        virtual bool RestContorl(ControlData data)=0;

    };
}

#endif // UMXNETGLOBAL_H
