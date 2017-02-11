/////////////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2016 CMITECH Co., Ltd.
// All rights reserved.
//
// Licensees holding valid CMITECH's CMIRIS SDK licenses may use this file in
// accordance with the CMIRIS SDK License Agreement provided with the
// Software or, alternatively, in accordance with the terms contained in
// an agreement between you and CMITECH.
////////////////////////////////////////////////////////////////////////////////////////

#ifndef __UMXCOMMONGLOBAL_H__
#define __UMXCOMMONGLOBAL_H__

#include <memory>
#include <string>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include "./cjson/JSONHelper.h"
#include <Poco/Data/BLOB.h>

namespace UMXCommon {
    class VersionData
    {
    public:
        VersionData();
        VersionData(const int version);
        VersionData(const int id, const int version);
        const int GetId() const;
        void SetId(const int id);
        const int GetVersion() const;
        void SetVersion(const int version);
        const std::string AsJSONString() const;
        static VersionData Parse(const std::string jsonString);
    private:
        int _id;
        int _version;
    };

    // EF-45(bkko)-34 : increase speed of iris recognition.
    struct IrisIdentifyInfo
    {
        IrisIdentifyInfo()
        {
            _userUUID = "";
            _leftScore = 0;
            _rightScore = 0;
            memset(_targetFeature, 0, sizeof(_targetFeature));
        }

        std::string _userUUID;
        double _leftScore;
        double _rightScore;
        unsigned char _targetFeature[2048];
    };

    struct UserInfoData
    {
        UserInfoData();
        UserInfoData(const std::string uuid, const std::string card, const std::string pin,
                     const int admin, const int groupIndex, const int byPassCard, const int indivisual);
        static UserInfoData Parse(const std::string jsonString);
        const std::string AsJSONString() const;
        const cjsonpp::JSONObject AsJSONObject() const;

        template<class T>
        static bool HasValue(cjsonpp::JSONObject& obj, const std::string& name);

        std::string _userUUID;
        std::string _card;
        std::string _pin;
        int _admin;
        int _groupIndex;
        int _byPassCard;
        int _indivisual;
    };

    struct SubjectData
    {
        SubjectData();
        SubjectData(const std::string& userUUID, const int& recordVersion, const std::string& firstName, const std::string& lastName, const bool& accessAllowed,
            const std::string& matchUntil, const int& wiegandFacility, const int& wiegandSite, const int& wiegandCode, const std::string& wiegandCustom,
            const Poco::Data::BLOB& leftTemplate, const Poco::Data::BLOB& rightTemplate, const std::string& leftImagePath, const std::string& rightImagePath);
        static SubjectData Parse(const std::string jsonString);
        const std::string AsJSONString() const;
        const cjsonpp::JSONObject AsJSONObject() const;

        template<class T>
        static bool HasValue(cjsonpp::JSONObject& obj, const std::string& name);

        std::string _userUUID;
        int _recordVersion;
        std::string _firstName;
        std::string _lastName;
        bool _accessAllowed;
        std::string _matchUntil;

        int _wiegandFacility;
        int _wiegandSite;
        int _wiegandCode;
        std::string _wiegandCustom;

        Poco::Data::BLOB _leftTemplate;
        Poco::Data::BLOB _rightTemplate;

        std::string _leftImagePath;
        std::string _rightImagePath;

        std::string _insertTime;
        std::string _updateTime;
    };

    struct ImageToSaveData
    {
        ImageToSaveData();
        static ImageToSaveData Parse(const std::string jsonString);

        template<class T>
        static bool HasValue(cjsonpp::JSONObject& obj, const std::string& name);

        std::string _fileName;
        std::vector<unsigned char> _image;
        int _width;
        int _height;
    };

    class LogEntry
    {
    public:
        LogEntry();
        LogEntry(const std::string& eventType, const std::string& timestamp, const std::string& userUUID, const std::string& info, const std::string& additionalData, const Poco::Data::BLOB& imageData);
        LogEntry(const int id, const std::string& eventType, const std::string& timestamp, const std::string& userUUID, const std::string& info, const std::string& additionalData, const Poco::Data::BLOB& imageData);
        const int GetId() const;
        const std::string GetEventType() const;
        const std::string GetTimestamp() const;
        const std::string GetUserUUID() const;
        const std::string GetInfo() const;
        const std::string GetAdditionalData() const;
        const Poco::Data::BLOB GetImageData() const;
        void SetId(const int id);
        void SetEventType(std::string& eventType);
        void SetTimestamp(std::string& timestamp);
        void SetUserUUID(std::string& userUUID);
        void SetInfo(std::string& info);
        void SetAdditionalData(std::string& additionalData);
        void SetImageData(Poco::Data::BLOB& imageData);
        const std::string AsJSONString() const;
        const cjsonpp::JSONObject AsJSONObject() const;
    private:
        int _id;
        std::string _eventType;
        std::string _timestamp;
        std::string _userUUID;
        std::string _info;
        std::string _additionalData;
        Poco::Data::BLOB _imageData;
    };

    class ImageCapture
    {
    public:
        ImageCapture();
        ImageCapture(const std::string& imageCaptureUUID, const std::string& timestamp, const std::string& serialNumber, bool enrol);
        const std::string GetLeftEyeImageFilename() const;
        const std::string GetRightEyeImageFilename() const;
        const std::string GetFaceImageFilename() const;
        const int GetId() const;
        const std::string GetImageCaptureUUID() const;
        const std::string GetTimestamp() const;
        const std::string GetSerialNumber() const;
        void SetId(const int id);
        void SetImageCaptureUUID(const std::string& imageCaptureUUID);
        void SetTimestamp(const std::string& timestamp);
        void SetSerialNumber(const std::string& serialNumber);
        const std::string AsJSONString() const;
        ImageCapture Parse(const std::string jsonString);
    private:
        int _id;
        std::string _imageCaptureUUID;
        std::string _timestamp;
        std::string _serialNumber;
        bool _enrol;
    };

    struct FaceDataWithSubjectInfo
    {
        FaceDataWithSubjectInfo();
        static FaceDataWithSubjectInfo Parse(const std::string jsonString);
        const std::string AsJSONString() const;
        const cjsonpp::JSONObject AsJSONObject() const;

        template<class T>
        static bool HasValue(cjsonpp::JSONObject& obj, const std::string& name);

        std::string _firstName;
        std::string _lastName;

        int _wiegandFacility;
        int _wiegandSite;
        int _wiegandCode;

        std::string _userUUID;
        int _subId;
        int _faceEyeWidth;
        int64_t _faceFeatureSize;
        float _faceFrontalScore;
        int _faceLeftEyeX;
        int _faceRightEyeX;
        float _faceRoll;
        float _faceScore;
        int _faceLEDState;
        Poco::Data::BLOB _faceFeature;
        std::string _imagePath;
    };

    struct FaceData
    {
        FaceData();
        FaceData(const std::string& userUUID, const int& subId, const Poco::Data::BLOB& faceFeature);
        static FaceData Parse(const std::string jsonString);
        const std::string AsJSONString() const;
        const cjsonpp::JSONObject AsJSONObject() const;

        template<class T>
        static bool HasValue(cjsonpp::JSONObject& obj, const std::string& name);

        std::string _userUUID;
        int _subId;
        int _faceEyeWidth;
        int64_t _faceFeatureSize;
        float _faceFrontalScore;
        int _faceLeftEyeX;
        int _faceRightEyeX;
        float _faceRoll;
        float _faceScore;
        int _faceLEDState;
        Poco::Data::BLOB _faceFeature;
        std::string _imagePath;
        std::string _insertTime;
        std::string _updateTime;
    };

    namespace CameraDefaults
    {
        // Movement values are in microns.
        const int MaxXYMovementEnrollment = 400;
        const int MaxZMovementEnrollment = 4000;
        const int MaxXYMovementRecognition = 1000;
        const int MaxZMovementRecognition = 12000;
        const int MaxFrameDifferenceInEitherEyeSlave = 3;
        const int MaxFrameDifferenceInEitherEyeEnrollment = 9;
        const int MaxFrameDifferenceInEitherEyeRecognition = 3;
    };

    struct MovementLimits
    {
        MovementLimits(const int maximumXYMovement, const int maximumZMovement)
            : XY(maximumXYMovement), Z(maximumZMovement)
        {
        };
        int XY;
        int Z;
    };

    class CameraMode
    {
    public:
        CameraMode(const int movementXYLimit, const int movementZLimit)
            : _movementLimits(movementXYLimit, movementZLimit)
        {};

        virtual ~CameraMode()
        {};

        virtual const std::string ToString() const=0;
        virtual const bool AutoStart() const=0;
        virtual const int MaxFrameDifferenceInEitherEye() const=0;
        virtual const MovementLimits MaxMovement() const
        {
            return _movementLimits;
        }
    private:
        const MovementLimits _movementLimits;
    };

    class SlaveCameraMode : public CameraMode
    {
    public:
        SlaveCameraMode() : CameraMode(CameraDefaults::MaxXYMovementEnrollment, CameraDefaults::MaxZMovementEnrollment)
        {};

        virtual const std::string ToString() const
        {
            return "Slave";
        };

        virtual const bool AutoStart() const
        {
            return true;
        };

        virtual const int MaxFrameDifferenceInEitherEye() const
        {
            return CameraDefaults::MaxFrameDifferenceInEitherEyeSlave;
        };
    };

    class EnrolCameraMode : public CameraMode
    {
    public:
        EnrolCameraMode() : CameraMode(CameraDefaults::MaxXYMovementEnrollment, CameraDefaults::MaxZMovementEnrollment)
        {};

        virtual const std::string ToString() const
        {
            return "Enrol";
        };

        virtual const bool AutoStart() const
        {
            return true;
        };

        virtual const int MaxFrameDifferenceInEitherEye() const
        {
            return CameraDefaults::MaxFrameDifferenceInEitherEyeEnrollment;
        };
    };

    class RecogCameraMode : public CameraMode
    {
    public:
        RecogCameraMode() : CameraMode(CameraDefaults::MaxXYMovementRecognition, CameraDefaults::MaxZMovementRecognition)
        {};

        virtual const std::string ToString() const
        {
            return "Recog";
        };

        virtual const bool AutoStart() const
        {
            return true;
        };

        virtual const int MaxFrameDifferenceInEitherEye() const
        {
            return CameraDefaults::MaxFrameDifferenceInEitherEyeRecognition;
        };
    };

    class CameraModeFactory
    {
    public:
        static std::shared_ptr<CameraMode> CreateCameraMode(const std::string& mode)
        {
            std::shared_ptr<CameraMode> cameraMode;
            if (mode == "Slave")
                cameraMode.reset(new SlaveCameraMode());
            else if (mode == "Enrol")
                cameraMode.reset(new EnrolCameraMode());
            else if (mode == "Recog")
                cameraMode.reset(new RecogCameraMode());
            else
            {
                std::ostringstream os;
                os << "Camera mode '" << mode << "' is invalid.";
                throw std::invalid_argument(os.str());
            }
            return cameraMode;
        };
    };

    class CameraConfiguration
    {
    public:
        CameraConfiguration();
        CameraConfiguration(const std::string& serialNumber, const bool audioEnabled);
        CameraConfiguration(const std::string& serialNumber, const std::shared_ptr<CameraMode>& cameraMode, const bool audioEnabled);
        const int GetId() const;
        const std::string GetSerialNumber() const;
        const std::shared_ptr<CameraMode> GetCameraMode() const;
        const bool GetAudioEnabled() const;
        void SetId(const int id);
        void SetSerialNumber(const std::string& serialNumer);
        void SetCameraMode(const std::shared_ptr<CameraMode>& cameraMode);
        void SetCameraConfigure(const std::string& serialNumber, const std::string& cameraMode, const bool audioEnabled);
        void SetAudioEnabled(const bool audioEnabled);
        const std::string AsJSONString() const;
        static CameraConfiguration Parse(const std::string jsonString);
    private:
        int _id;
        std::string _serialNumber;
        std::shared_ptr<CameraMode> _cameraMode;
        bool _audioEnabled;
    };

    class ControlData
    {
    public:
        ControlData();
        ControlData(const bool result, const bool recogStart, const std::string& wavPath);

        static ControlData Parse(const std::string jsonString);
        static ControlData Parse(cjsonpp::JSONObject& obj);
        const std::string AsJSONString() const;
        const cjsonpp::JSONObject AsJSONObject() const;

        template<class T>
        static bool HasValue(cjsonpp::JSONObject& obj, const std::string& name);
    public:
        bool _result;
        bool _recogStart;
        std::string _wavPath;
    };
}

#endif /* __UMXCOMMONGLOBAL_H__ */