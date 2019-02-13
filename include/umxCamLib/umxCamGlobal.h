////////////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2011~2016 CMITECH Co., Ltd.
// All rights reserved.
//
// Licensees holding valid CMITECH's CMIRIS SDK licenses may use this file in
// accordance with the CMIRIS SDK License Agreement provided with the
// Software or, alternatively, in accordance with the terms contained in
// an agreement between you and CMITECH.
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
// umxCamGlobal.h
//
// Version 1.0.13  Aug. 10, 2016
//                 Initial Public Release
//
// Description: umxCamGlobal.h defines the constants and struct for umxCam.h
//              Please see umxCam.h for detailed interface.
//
/////////////////////////////////////////////////////////////////////////////////////////

#ifndef UMXCAMGLOBAL_H
#define UMXCAMGLOBAL_H

#include <stdint.h>
#include <string>

////////////////////////////////////////////////////////////////////////////////////////
// Model name and serial number
////////////////////////////////////////////////////////////////////////////////////////

#define UMXCAM_MODEL_NAME_MAX_SIZE    8   // ex. UMX-45

#define UMXCAM_SERIAL_NUMBER_MAX_SIZE 13  // ex. BA1205A000123

#define UMXCAM_HARDWARE_REV_MAX_SIZE  11  // ex. 1.0.1

#define UMXCAM_FIRMWARE_REV_MAX_SIZE  11  // ex. 1.1.13

typedef struct _UMXCAM_DEVICE_INFO {
	int cbSize;                                       // size of this struct
    char modelName[UMXCAM_MODEL_NAME_MAX_SIZE+1];
    char serialNumber[UMXCAM_SERIAL_NUMBER_MAX_SIZE+1];
    char hardwareRev[UMXCAM_HARDWARE_REV_MAX_SIZE+1];
    char firmwareRev[UMXCAM_FIRMWARE_REV_MAX_SIZE+1];
} UMXCAM_DEVICE_INFO;

////////////////////////////////////////////////////////////////////////////////////////
// Iris margins in the image
////////////////////////////////////////////////////////////////////////////////////////

#define UMXCAM_MARGINS_FAIL                0             // Cannot find the eye

#define UMXCAM_LEFT_MARGIN_OK              (1<<0)

#define UMXCAM_RIGHT_MARGIN_OK             (1<<1)

#define UMXCAM_TOP_MARGIN_OK               (1<<2)

#define UMXCAM_BOTTOM_MARGIN_OK            (1<<3)

#define UMXCAM_ALL_MARGINS_OK              (UMXCAM_LEFT_MARGIN_OK | UMXCAM_RIGHT_MARGIN_OK | UMXCAM_TOP_MARGIN_OK | UMXCAM_BOTTOM_MARGIN_OK)

////////////////////////////////////////////////////////////////////////////////////////
// Option to capture which eye
////////////////////////////////////////////////////////////////////////////////////////

#define UMXCAM_LEFT_EYE                            (1<<0)

#define UMXCAM_RIGHT_EYE                           (1<<1)

#define UMXCAM_BOTH_EYES                           (UMXCAM_LEFT_EYE | UMXCAM_RIGHT_EYE)

#define UMXCAM_EITHER_EYE                          (1<<2 | UMXCAM_BOTH_EYES)

////////////////////////////////////////////////////////////////////////////////////////
// begin mode
////////////////////////////////////////////////////////////////////////////////////////

#define UMXCAM_NORMAL_START_MODE                    0 // wait until the motion is detected //go to object detect mode when start camera

#define UMXCAM_RETRY_START_MODE                     1  // start right away //go to motion detection mode when start camera

////////////////////////////////////////////////////////////////////////////////////////
// enrol/recog mode
////////////////////////////////////////////////////////////////////////////////////////

#define UMXCAM_ENROL_MODE                           0 // operating range 350mm <= x <= 450mm

#define UMXCAM_RECOG_MODE                           1  // operating range is adjustable. 300mm ~ 480mm

#define UMXCAM_FAST_RECOG_MODE                      2  // operating range is same as UMXCAM_RECOG_MODE
                                                       // Fast capture for small 1:N recognition

////////////////////////////////////////////////////////////////////////////////////////
// boolean type information
////////////////////////////////////////////////////////////////////////////////////////

#define UMXCAM_TRUE                                 1

#define UMXCAM_FALSE                                0

#define UMXCAM_UNKNOWN                             -1

///////////////////////////////////////////////////////////////////////////////////////
// Image and camera information
////////////////////////////////////////////////////////////////////////////////////////

#define UMXCAM_FULL_RESOLUTION                       1
#define UMXCAM_SUB2_RESOLUTION                       1<<1
#define UMXCAM_SUB4_RESOLUTION                       1<<2
#define UMXCAM_ARGB_COLOR                            1<<4
#define UMXCAM_BMP_RGB_COLOR                         1<<5

#define UMXCAM_NARROW_CAM                            0
#define UMXCAM_WIDE_CAM                              1
#define UMXCAM_UNKNOWN_CAM                           -1

#define UMXCAM_MAX_ROLL_ANGLE                        3600 // cannot be larger than this angle (unit: 1/10degree)

////////////////////////////////////////////////////////////////////////////////////////
// Message to GUI in UMXCAM_IMAGE_INFO
////////////////////////////////////////////////////////////////////////////////////////

#define UMXCAM_MESSAGE_NONE                            0
#define UMXCAM_MESSAGE_MOVE_DOWN                       1
#define UMXCAM_MESSAGE_MOVE_UP                         2
#define UMXCAM_MESSAGE_OPEN_EYES_WIDE                  3
#define UMXCAM_MESSAGE_TAKE_OFF_GLASSES                4
#define UMXCAM_MESSAGE_DO_NOT_MOVE                     5
#define UMXCAM_MESSAGE_REALEYE_TEST_FAILED             6
#define UMXCAM_MESSAGE_LARGE_FACE                   9999

////////////////////////////////////////////////////////////////////////////////////////
// Indicator color to GUI in UMXCAM_IMAGE_INFO
////////////////////////////////////////////////////////////////////////////////////////

#define UMXCAM_INDICATOR_COLOR_UNKNOWN              0
#define UMXCAM_INDICATOR_COLOR_RED                  1
#define UMXCAM_INDICATOR_COLOR_GREEN                2
#define UMXCAM_INDICATOR_COLOR_BLUE                 3

typedef struct _UMXCAM_START_PARA {
    _UMXCAM_START_PARA() {
        cbSize = 0;
        startMode = UMXCAM_NORMAL_START_MODE;
        faceCaptureEnabled = UMXCAM_FALSE;
        whichEye = UMXCAM_EITHER_EYE;
        enrolRecogMode = UMXCAM_RECOG_MODE;
        minUsableIrisArea = 70;
        faceFullResolution = UMXCAM_FALSE;
        faceImageInterval = 10;
        checkFakeFace = UMXCAM_FALSE;
        faceColorCorrection = UMXCAM_FALSE;
        coverGlassTrans = 100;
        checkRealEye = UMXCAM_FALSE;
    }

    int cbSize;                              // size of this struct
    int startMode;          // UMXCAM_NORMAL_START_MODE or UMXCAM_RETRY_START_MODE
    int faceCaptureEnabled; // UMXCAM_TRUE or UMXCAM_FALSE
    int whichEye;           // UMXCAM_BOTH_EYES or UMXCAM_EITHER_EYE or UMXCAM_LEFT_EYE or UMXCAM_RIGHT_EYE
    int enrolRecogMode;     // UMXCAM_ENROL_MODE or UMXCAM_RECOG_MODE or UMXCAM_FAST_RECOG_MODE
    int minUsableIrisArea;  // 50 <= minUsableIrisArea <= 90. Default is 70%
    int faceFullResolution; // UMXCAM_TRUE or UMXCAM_FALSE. Face Full Resolution is 720x960
    int faceImageInterval;  // face image minimum interval in frames. 30 frames in 1 second.
                            // min: 3, max: 30, default: 10
    int checkFakeFace;      // UMXCAM_TRUE or UMXCAM_FALSE
    int faceColorCorrection;// UMXCAM_TRUE or UMXCAM_FALSE
    int coverGlassTrans;    // IR Transmission coefficient of additional cover glass in percentage
                            // The value between 50% and 100% is only allowed.
    int checkRealEye;       // UMXCAM_TRUE or UMXCAM_FALSE
} UMXCAM_START_PARA;

////////////////////////////////////////////////////////////////////////////////////////
// _UMXCAM_IMAGE_INFO
////////////////////////////////////////////////////////////////////////////////////////

typedef void *UMXCAM_HANDLE;

typedef struct _UMXCAM_IMAGE_INFO {
    _UMXCAM_IMAGE_INFO() {
        cbSize = sizeof(struct _UMXCAM_IMAGE_INFO);

        leftImage = NULL;
        rightImage = NULL;
        faceImage = NULL;
        faceImageARGB32 = NULL;
        faceImageBMP24 = NULL;
        faceImageBMP8 = NULL;

        leftWidth = rightWidth = faceWidth = 0;
        leftHeight = rightHeight = faceHeight = 0;
        leftResolution = rightResolution = faceResolution = 0;
        whichCam = UMXCAM_UNKNOWN_CAM;
        leftBoundary = rightBoundary = -1;
        topBoundary = bottomBoundary = -1;

        leftEyeCenterX = rightEyeCenterX = -1;
        leftEyeCenterY = rightEyeCenterY = -1;

        leftIrisCenterX = rightIrisCenterX = -1;
        leftIrisCenterY = rightIrisCenterY = -1;
        leftIrisRadius = rightIrisRadius = -1;
        leftPupilRadius = rightPupilRadius = -1;
        leftExposedIrisArea = rightExposedIrisArea = -1;

        leftIrisMargin = rightIrisMargin = UMXCAM_MARGINS_FAIL;
        leftLiveness = rightLiveness =
                faceLiveness = UMXCAM_UNKNOWN;

        leftDistance = rightDistance = avgDistance = -1;
        leftXYMovement = rightXYMovement = -1;
        leftZMovement = rightZMovement = -1;
        ipdPixels = -1;
        ipdMicron = -1;
        rollAngle = UMXCAM_MAX_ROLL_ANGLE;
        rollAngleUncertainty = UMXCAM_MAX_ROLL_ANGLE;

        doesLeftLookFront = doesRightLookFront = UMXCAM_UNKNOWN;
        isLeftImageQualityOK = isRightImageQualityOK = UMXCAM_UNKNOWN;

        message = UMXCAM_MESSAGE_MOVE_DOWN;
        additionalInfo = NULL;

        faceImageYUVSub2 = NULL;

        irisTemplateSize = -1;
        leftIrisTemplate = NULL;
        rightIrisTemplate = NULL;

        leftPupilCenterX = -1;
        rightPupilCenterX = -1;
        leftPupilCenterY = -1;
        rightPupilCenterY = -1;

        leftUsableIrisArea = 0.0;
        rightUsableIrisArea = 0.0;
        leftQualityOk = false;
        rightQualityOk = false;
        leftQualityScore = 0.0;
        rightQualityScore = 0.0;

        indicatorColor = UMXCAM_INDICATOR_COLOR_UNKNOWN;
    }

    int cbSize;                              // size of this struct
    int frameCount;                          // frame count of images.

    //-------------------------------------------------------------------------------------------
    // rule of unsigned char * xxxImagexxx
    // if unsigned char * xxxxImagexxx == NULL, image is not available, and width, height are 0
    //-------------------------------------------------------------------------------------------

    // Left and right iris image 640x480 grayscale raw format.
    // The origin (first pixel) is left top corner.
    unsigned char *leftImage, *rightImage;
    // faceImage is not used in UMXCam
    unsigned char *faceImage;

    // face image to display on LCD. Image size is 480x480 with ARGB32 format
    unsigned char *faceImageARGB32;

    // 3:4 color face image. This only contains the data of image and the origin (first pixel)
    // is bottom left corner to meet the BMP24 format.
    // The size of image depends on the face size and BMP header is not included. Use width and height
    // to generate BMP24 header.
    unsigned char *faceImageBMP24;

    // 3:4 grayscale Infrared face image. This is the same format as faceImageBMP24 except
    // it is BMP8 grayscale. When the face images are captured, both of faceImageBMP24 and faceImageBMP8
    // will be available in the UMXCAM_EVENT UMXCAM_EVENT_FACE_IMAGES_SELECTED and
    // UMXCAM_EVENT_IRIS_IMAGES_SELECTED
    unsigned char *faceImageBMP8;
    //-------------------------------------------------------------------------------------------

    // leftxxx and rightxxx is for left and right iris image
    // facexxx is for faceImageARGB32 or faceImageBMP24 & faceImageBMP8
	int leftWidth, rightWidth, faceWidth;
	int leftHeight, rightHeight, faceHeight;

    // leftResolution, rightResolution, faceResolution are obsolete.
    // Do not need to use these fields.
	int leftResolution, rightResolution, faceResolution;

    // UMXCAM_NARROW_CAM or UMXCAM_WIDE_CAM. Do not need to use this field.
    int whichCam;

    // The box boundaries where the both eyes should be presented in faceImageARGB32 image
    int leftBoundary, rightBoundary, topBoundary, bottomBoundary;
	//----------------------------------------------------------------------------
	int faceLeft, faceRight, faceTop, faceBottom; //by dhkim
	//----------------------------------------------------------------------------
    //----------------------------------------------------------------------------
    // Both eyes location information in the face image
    // If not avaiable, the "int" values will be -1 or UMXCAM_UNKNOWN
    //----------------------------------------------------------------------------
    int leftEyeCenterX, rightEyeCenterX;
    int leftEyeCenterY, rightEyeCenterY;

	//----------------------------------------------------------------------------
	// Iris information in the image
    // If not avaiable, the "int" values will be -1 or UMXCAM_UNKNOWN
	//----------------------------------------------------------------------------
	int leftIrisCenterX, rightIrisCenterX;
	int leftIrisCenterY, rightIrisCenterY;
	int leftIrisRadius, rightIrisRadius;               // pixels
	int leftPupilRadius, rightPupilRadius;             // pixels - TBI(To Be Implemented)
	int leftExposedIrisArea, rightExposedIrisArea;     // percentage - TBI
    unsigned char leftIrisMargin;                      // enough iris margins? see Iris Margin definition above
    unsigned char rightIrisMargin;                     // enough iris margins? see Iris Margin definition above
    int leftLiveness, rightLiveness, faceLiveness;     // Live eye detection result
                                                       // UMXCAM_TRUE, UMXCAM_FALSE, UMXCAM_UNKNOWN
	//----------------------------------------------------------------------------

	//----------------------------------------------------------------------------
	// The eyes position information in 3D space
	//----------------------------------------------------------------------------
    int leftDistance;           // Distance(unit: micron) of the left eye from the front of device.
    int rightDistance;          // Distance(unit: micron) of the right eye from the front of device.
    int avgDistance;            // Average distance(unit: micron) of the object from the front of device.

    int leftXYMovement;         // XY Movement of Eye in micron during dt seconds
	int rightXYMovement;        // XY-plane is perpendicular to the optical axis of camera

	int leftZMovement;          // Z Movement of Eye in micron during dt seconds. DMX/EMX only
	int rightZMovement;         // +Z-direction is from the device to the eye.

    int ipdPixels;               // for face ipd
    int ipdMicron;               // Inter-Pupilary Distance in micron. DMX/EMX only
	int rollAngle;               // Roll angle of a line drawn between the centers of the left
								 // and right irises. Unit is 1/10 degree and it is positive if the
								 // left iris is higher than right iris. (counter-clockwise)
								 // TBI
	int rollAngleUncertainty;    // Roll angle uncertainty in 1/10 degrees. TBI
	//----------------------------------------------------------------------------

	//----------------------------------------------------------------------------
    // Additional Information - UMXCAM_YES, UMXCAM_NO, UMXCAM_DONT_KNOW
	//----------------------------------------------------------------------------
	int doesLeftLookFront;       // Does left eye look front?
	int doesRightLookFront;      // Does right eye look front?

	int isLeftImageQualityOK;    // is left/right iris image quality OK?
    int isRightImageQualityOK;

    int message;                 // message to pass to GUI

    void *additionalInfo;        // for future use only

    // Added for fast image transfer JJC 20171006
    // faceWidth and faceheight indicates targetW and targetH
    // The image size is faceWidth*faceheight*1 bytes. Need interpolation
    unsigned char *faceImageYUVSub2;

    int irisTemplateSize;
    unsigned char *leftIrisTemplate;
    unsigned char *rightIrisTemplate;

    int leftPupilCenterX, rightPupilCenterX;
    int leftPupilCenterY, rightPupilCenterY;

    double leftUsableIrisArea, rightUsableIrisArea;
    bool leftQualityOk, rightQualityOk;
    double leftQualityScore, rightQualityScore;

    int indicatorColor;
} UMXCAM_IMAGE_INFO;

typedef struct _UMXCAM_EVENT {
	int cbSize;
	int event;
    UMXCAM_IMAGE_INFO imageInfo;
} UMXCAM_EVENT;



////////////////////////////////////////////////////////////////////////////////////////
// Return values
////////////////////////////////////////////////////////////////////////////////////////

#define UMXCAM_SUCCESS                                   0

#define UMXCAM_ERROR_CANNOT_ALLOC_MEMORY                -1

#define UMXCAM_ERROR_WAIT_TIMEOUT                       -2  // Timeout Error

#define UMXCAM_ERROR_READ_EVENT_CANCELLED               -3

#define UMXCAM_ERROR_INVALID_HANDLE                     -4  // Invalid UMXCAM_HANDLE in argument

#define UMXCAM_ERROR_INVALID_BUFFER                     -5

#define UMXCAM_ERROR_FAIL_TO_SEND_COMMAND               -6

#define UMXCAM_ERROR_CALL_GET_BUFFER_SIZE_FIRST         -7

#define UMXCAM_ERROR_BUFFER_SIZE_TOO_SMALL              -8

#define UMXCAM_ERROR_DEVICE_ALREADY_OPENED              -9  // try to open when the device is already opened

#define UMXCAM_ERROR_DEVICE_ALREADY_CLOSED              -10  // try to do action when the device is already closed

#define UMXCAM_ERROR_DEVICE_ALREADY_STARTED             -11  // try to start when the device have already started

#define UMXCAM_ERROR_DEVICE_ALREADY_STOPPED             -12  // Capture process has not started yet.

#define UMXCAM_ERROR_FAIL_TO_START                      -13

#define UMXCAM_ERROR_FAIL_TO_STOP                       -14

#define UMXCAM_ERROR_IN_ARGUMENTS                       -15  // Error in arguments

#define UMXCAM_ERROR_IN_NARROW_CAMERA                   -16

#define UMXCAM_ERROR_IN_WIDE_CAMERA                     -17

#define UMXCAM_ERROR_EEPROM_READ                        -18  // Error in reading EEPROM during UMXCAM_openDevice().

#define UMXCAM_ERROR_EEPROM_VERSION_INVALID             -19 // EEPROM version is invalid in UMXCAM_openDevice()
                                                            // UMXCAM_closeDevice() have to be called in the applicaion

#define UMXCAM_ERROR_FIRMWARE_VERSION_INVALID           -20 // Invalid firmware version

#define UMXCAM_ERROR_CANNOT_FIND_HAARCASCADE_FILES      -21 // Cannot find ./haarcasecade/haarcascade_frontalface_alt.xml
                                                            // UMXCAM_closeDevice() have to be called in the applicaion

#define UMXCAM_ERROR_IN_CALIBRATION                     -22 // Error in calibration

#define UMXCAM_ERROR_FAIL_TO_CREATE_UMXALGO             -23 // Fail to create umxAlgo for face detecting

#define UMXCAM_ERROR_INVALID_STATE                      -24 // Invalid state

#define UMXCAM_ERROR_FAIL_TO_CAPTURE_WIDE_VIEW_IMAGE    -25


////////////////////////////////////////////////////////////////////////////////////////
// Event value for UMXCAM_EVENT structure (Image capture event)
////////////////////////////////////////////////////////////////////////////////////////

#define UMXCAM_EVENT_PREVIEW_IMAGE                  0  // Intermediate left or right Iris Image for display
													// and image information

#define UMXCAM_EVENT_PREVIEW_INFO                   1 // Not use
                                                    // Intermediate face image information
                                                    // no images

#define UMXCAM_EVENT_CAPTURE_DONE                   2  // Capture finished and can play the capture sound
                                                    // UMXCAM_IMAGE_INFO leftImage and rightImage are NULL.

#define UMXCAM_EVENT_FACE_IMAGES_SELECTED           3  // Capture finished and can play the capture sound
                                                    // UMXCAM_IMAGE_INFO leftImage and rightImage are NULL.

#define UMXCAM_EVENT_IRIS_IMAGES_SELECTED           4  // Selected left and right Iris Images are returned
													// IPD will be available for DMX and EMX

#define UMXCAM_EVENT_WIDE_VIEW_IMAGE                5  // Wide view image captured when "stop" is called
                                                    // only faceImageBMP24 will be returned

// Error occured during image capture
#define UMXCAM_EVENT_VIDEO_ERROR                    6  // Internal error (possibly hardware problem)
                                                    // Application should call UMXCAM_closeDevice().

////////////////////////////////////////////////////////////////////////////////////////
// Event value for UMXCAM_DM_EVENT structure (Tamper switch and Function Key) - EMA/EMB only
////////////////////////////////////////////////////////////////////////////////////////

#define UMXCAM_EVENT_TAMPER_SWITCH_OPEN             11

#define UMXCAM_EVENT_TAMPER_SWITCH_CLOSED           12

#define UMXCAM_EVENT_CALL_KEY_PRESSED               13

#define UMXCAM_EVENT_CALL_KEY_RELEASED              14

#define UMXCAM_EVENT_FUNC_KEY_1_PRESSED             15

#define UMXCAM_EVENT_FUNC_KEY_1_RELEASED            16

#define UMXCAM_EVENT_FUNC_KEY_2_PRESSED             17

#define UMXCAM_EVENT_FUNC_KEY_2_RELEASED            18

#define UMXCAM_EVENT_FUNC_KEY_3_PRESSED             19

#define UMXCAM_EVENT_FUNC_KEY_3_RELEASED            20

#define UMXCAM_EVENT_FUNC_KEY_4_PRESSED             21

#define UMXCAM_EVENT_FUNC_KEY_4_RELEASED            22

#define UMXCAM_EVENT_FUNC_KEY_5_PRESSED             23

#define UMXCAM_EVENT_FUNC_KEY_5_RELEASED            24

////////////////////////////////////////////////////////////////////////////////////////
// Current Indicator LED color - leftPosition/rightPosition in UMXCAM_IMAGE_INFO, EMX/EMA/EMB only
////////////////////////////////////////////////////////////////////////////////////////

#define UMXCAM_VOICE_COME_CLOSER                     4

#define UMXCAM_VOICE_MOVE_BACK                       5

#endif // UMXCAMGLOBAL_H
