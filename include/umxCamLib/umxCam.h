////////////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2011~2016 CMITECH Co., Ltd.
// All rights reserved.
//
// Licensees holding valid CMITECH's CMIRIS SDK licenses may use this file in
// accordance with the CMIRIS SDK License Agreement provided with the
// Software or, alternatively, in accordance with the terms contained in
// an agreement between you and CMITECH.
////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
// umxCam.h
//
// Version 1.0.13  Aug. 10, 2016
//                 Initial Public Release
//
// Version 1.0.14  Aug. 21, 2016
// - UMXCAM_FAST_RECOG_MODE was added. It is for faster capture, allowing user's larger movement.
// - Min operating range can be extended up to 300mm. It was 320mm previously.
//
// Version 1.0.19 Sep. 3, 2016
// - bug fixed for the very bright iris in 850nm (iris parameter: 0.5 -> 0.3, use specCenter not irisCenter)
//
// Version 1.0.25 oct. 8, 2016
// - False reject rate was reduced by checking the motion blur
// - "Open eyes wide" message was added during enrollment
//
// Version 1.0.27 Nov. 1, 2016
// - When the color face image is dark, imageInfo->faceImageBMP24 will be NULL
//
// Version 1.0.28 Nov. 15, 2016
// - start parameter struct UMXCAM_START_PARA is introduced in startCapture() function
// - face full resolution (720x960) option for enrollment was added
//
// Description: umxCam.h provide the interface with the iris image capture device
//              UMX-10 (EF-45) developed by CMITECH.
//              Please see umxCamGlobal.h for the constants and struct for umxCam.h
//
/////////////////////////////////////////////////////////////////////////////////////////

#ifndef UMXCAM_H
#define UMXCAM_H

#include <string>
#include <vector>
#include "umxCamGlobal.h"

#if __GNUC__ >= 4
#define UMXCAM_SHARED_EXPORT __attribute__ ((visibility ("default")))
#else
#define UMXCAM_SHARED_EXPORT
#endif  // __GNUC_C >= 4
#define _UMXCAM_EXPORT UMXCAM_SHARED_EXPORT

#define MAINIMAGERUNTHREAD		1
#define FACEEYERUNTHREAD		2

#ifdef __cplusplus
extern "C" {
#endif

    void _UMXCAM_EXPORT umxCam_getVersion(unsigned int *major, unsigned int *minor, unsigned int *revision);
	// Get umxCam version and revision number for compatibility.
    // Application should check if major version number is consistent.
    //
    // major[out]
    // minor[out]
    // revision[out]

    int _UMXCAM_EXPORT umxCam_create(UMXCAM_HANDLE *phandle);
    // Create umxCam.
    //
    // phandle[out] - UMXCAM_HANDLE value if successful. Otherwise, NULL.
    //
    // Return value - UMXCAM_ERROR_CANNOT_ALLOC_MEMORY
    //                UMXCAM_SUCCESS

    int _UMXCAM_EXPORT umxCam_destroy(UMXCAM_HANDLE handle);
    // Destroy umxCam.
    //
    // handle[in] - UMXCAM_HANDLE value
    //
    // Return value - UMXCAM_ERROR_INVALID_HANDLE
    //                UMXCAM_SUCCESS

    int _UMXCAM_EXPORT umxCam_readEvent(UMXCAM_HANDLE handle, UMXCAM_EVENT *event, long timeout);
    // Read event. UMXCAM_EVENT...
    //
    // handle[in] - UMXCAM_HANDLE value
    // event[out] - event occurred
    // timeout[in] - time out in milliseconds
    //
    // Return value - UMXCAM_ERROR_INVALID_HANDLE
    //                UMXCAM_ERROR_WAIT_TIMEOUT : timeout
    //                UMXCAM_ERROR_READ_EVENT_CANCELLED : canceled pending readEvent
    //                UMXCAM_SUCCESS : event occured

    int _UMXCAM_EXPORT umxCam_clearEventQueue(UMXCAM_HANDLE handle);
    // Clear UMXCAM_EVENT queue
    //
    // handle[in] - UMXCAM_HANDLE value
    //
    // Return value - UMXCAM_ERROR_INVALID_HANDLE
    //                UMXCAM_SUCCESS

    int _UMXCAM_EXPORT umxCam_cancelPendingReadEvent(UMXCAM_HANDLE handle);
    // Cancel pending umxCam_readEvent()
    //
    // handle[in] - UMXCAM_HANDLE value
    //
    // Return value - UMXCAM_ERROR_INVALID_HANDLE
    //                UMXCAM_SUCCESS

    int _UMXCAM_EXPORT umxCam_openDevice(UMXCAM_HANDLE handle);
    // Open the device.
    //
    // handle[in] - UMXCAM_HANDLE value
    //
    // Return value - UMXCAM_ERROR_INVALID_HANDLE
    //                UMXCAM_ERROR_IN_ARGUMENTS
    //                UMXCAM_ERROR_DEVICE_ALREADY_OPENED
    //                UMXCAM_ERROR_EEPROM_READ
    //                UMXCAM_ERROR_EEPROM_VERSION_INVALID
    //                UMXCAM_ERROR_IN_CALIBRATION
    //                UMXCAM_ERROR_FAIL_TO_CREATE_UMXALGO
    //                UMXCAM_ERROR_IN_WIDE_CAMERA
    //                UMXCAM_ERROR_IN_NARROW_CAMERA
    //                UMXCAM_SUCCESS

    int _UMXCAM_EXPORT umxCam_closeDevice(UMXCAM_HANDLE handle);
    // Close the currently opened device.
    //
    // handle[in] - UMXCAM_HANDLE value
    //
    // Return value - UMXCAM_ERROR_INVALID_HANDLE
    //                UMXCAM_SUCCESS

    int _UMXCAM_EXPORT umxCam_getBufferSize(UMXCAM_HANDLE handle, int *bufferSize);
    // Get buffer size for the specified number of preview frames (1 frame contains one eye image)
    // This function should be called after umxCam_openDevice() and before umxCam_startCapture().
    // Otherwise, UMXCAM_ERROR_CALL_GET_BUFFER_SIZE_FIRST will be returned in umxCam_startCapture().
    // After umxCam_stopCapture(), this function does not need to be called
    // again, if the allocated buffer is not freed.
    //
    // handle[in] - UMXCAM_HANDLE value
    // bufferSize[out] - necessary buffer size
    //
    // Return value - UMXCAM_ERROR_INVALID_HANDLE
    //                UMXCAM_SUCCESS

    int _UMXCAM_EXPORT umxCam_startCapture(UMXCAM_HANDLE handle, int bufferSize, unsigned char *buffer,
                                     UMXCAM_START_PARA *startPara);
    // Start capture.
    //
    // handle[in] - UMXCAM_HANDLE value
    // bufferSize[in] - working buffer size allocated by application
    // buffer[in] - working buffer allocated by application
    //
    // UMXCAM_START_PARA *startPara:
	//
    // 		startMode[in] - UMXCAM_NORMAL_START_MODE
    //                 		UMXCAM_RETRY_START_MODE
    // 		faceCaptureEnabled[in] - UMXCAM_TRUE : face capture mode
    //                          	 UMXCAM_FALSE : iris capture mode
    // 		whichEye[in] - UMXCAM_LEFT_EYE
    //                	   UMXCAM_RIGHT_EYE
    //                	   UMXCAM_BOTH_EYES
    //                	   UMXCAM_EITHER_EYE
    // 		enrolRecogMode[in] - UMXCAM_ENROL_MODE
    //                      	 UMXCAM_RECOG_MODE
    //                      	 UMXCAM_FAST_RECOG_MODE
    // 		minUsableIrisArea[in] - Minmum usable iris area (1 ~ 99).
    //                         		It only applies to enrollment mode.
    //                              In recognition mode, it is 40.
    //
    // 		faceFullResolution[in] - UMXCAM_TRUE : returns face image with full resolution 720x960 for enrollment
    //                          	 UMXCAM_FALSE : return cropped face image for enrollment
    // 		faceImageInterval[in] - face image minimum interval in frames. 30 frames in 1 second.
    //                         		min: 10, max: 60, default: 10
    //      checkFakeFace[in] - UMXCAM_TRUE : Check fake face for face enrollment and recognition
    //                          UMXCAM_FALSE : Do not heck fake face for face enrollment and recognition
    //      faceColorCorrection[in] - UMXCAM_TRUE : Face color correction
    //                                UMXCAM_FALSE : No Face color correction
    //
    // Return value - UMXCAM_ERROR_INVALID_HANDLE
    //                UMXCAM_ERROR_IN_ARGUMENTS
    //                UMXCAM_ERROR_DEVICE_ALREADY_STARTED
    //                UMXCAM_ERROR_CALL_GET_BUFFER_SIZE_FIRST
    //                UMXCAM_ERROR_INVALID_BUFFER
    //                UMXCAM_ERROR_FAIL_TO_SEND_COMMAND
    //                UMXCAM_SUCCESS

    int _UMXCAM_EXPORT umxCam_switchCaptureMode(UMXCAM_HANDLE handle, int *faceCaptureEnabled);
    // Switch to capture mode
    //
    // handle[in] - UMXCAM_HANDLE value
    // faceCaptureEnabled[out] - UMXCAM_TRUE or UMXCAM_FALSE
    //
    // Return value - UMXCAM_ERROR_INVALID_HANDLE
    //                UMXCAM_SUCCESS
    //                UMXCAM_ERROR_INVALID_STATE

    int _UMXCAM_EXPORT umxCam_isFaceCaptureMode(UMXCAM_HANDLE handle);
    // Check if current captrure is face capture mode
    //
    // handle[in] - UMXCAM_HANDLE value
    //
    // Return value - UMXCAM_TRUE
    //                UMXCAM_FALSE

    int _UMXCAM_EXPORT umxCam_isStartCapture(UMXCAM_HANDLE handle);
    // Check if capture start
    //
    // handle[in] - UMXCAM_HANDLE value
    //
    // Return value - UMXCAM_ERROR_INVALID_HANDLE
    //                UMXCAM_ERROR_DEVICE_ALREADY_STARTED
    //                UMXCAM_ERROR_DEVICE_ALREADY_STOPPED

#ifdef ANDROID
	int _UMXCAM_EXPORT umxCam_releasePreviewBuffer_ADR(UMXCAM_HANDLE handle, UMXCAM_HANDLE buffer);
    // Release preview buffer to re-use in the next UMXCAM_EVENT_PREVIEW_IMAGE event.
    // For each image pointer, leftImage, rightImage and faceImage, if it is not NULL
    // this function should be called separately.
    //
    // handle[in] - UMXCAM_HANDLE value
    // buffer[in] - leftImage, rightImage, or faceImage in UMXCAM_IMAGE_INFO
    //
    // Return value - UMXCAM_ERROR_INVALID_HANDLE
    //                UMXCAM_SUCCESS
#endif

    int _UMXCAM_EXPORT umxCam_releasePreviewBuffer(UMXCAM_HANDLE handle, unsigned char *buffer);
    // Release preview buffer to re-use in the next UMXCAM_EVENT_PREVIEW_IMAGE event.
    // For each image pointer, leftImage, rightImage and faceImage, if it is not NULL
    // this function should be called separately.
    //
    // handle[in] - UMXCAM_HANDLE value
    // buffer[in] - leftImage, rightImage, or faceImage in UMXCAM_IMAGE_INFO
    //
    // Return value - UMXCAM_ERROR_INVALID_HANDLE
    //                UMXCAM_SUCCESS

    int _UMXCAM_EXPORT umxCam_releaseFaceBuffer(UMXCAM_HANDLE handle, unsigned char *buffer);
    // Release face buffer to re-use in the next UMXCAM_EVENT_FACE_IMAGES_SELECTED event.
    // For each image pointer, faceImageBMP24 and faceImageBMP8, if it is not NULL
    // this function should be called separately.
    //
    // handle[in] - UMXCAM_HANDLE value
    // buffer[in] - faceImageBMP24 or faceImageBMP8 in UMXCAM_IMAGE_INFO
    //
    // Return value - UMXCAM_ERROR_INVALID_HANDLE
    //                UMXCAM_SUCCESS

    int _UMXCAM_EXPORT umxCam_captureWideViewImage(UMXCAM_HANDLE handle);
    // Capture wide view image and generate UMXCAM_EVENT_WIDE_VIEW_IMAGE.
    // If the face has been found, the latest face image will be returned.
    // Otherwise, the most latest scene will be captured.
    //
    // handle[in] - UMXCAM_HANDLE value
    //
    // Return value - UMXCAM_ERROR_INVALID_HANDLE
    //                UMXCAM_ERROR_DEVICE_ALREADY_STOPPED
    //                UMXCAM_ERROR_FAIL_TO_CAPTURE_WIDE_VIEW_IMAGE
    //                UMXCAM_SUCCESS

    int _UMXCAM_EXPORT umxCam_stopCapture(UMXCAM_HANDLE handle, bool goToMotorZero = true);
    // Stop capturing. It will clean the event queue and return after all images
    // go through. umxCam_cancelPendingReadEvent() can be called if necessary.
    //
    // handle[in] - UMXCAM_HANDLE value
    //
    // Return value - UMXCAM_ERROR_INVALID_HANDLE
    //                UMXCAM_ERROR_DEVICE_ALREADY_STOPPED
    //                UMXCAM_ERROR_FAIL_TO_SEND_COMMAND
    //                UMXCAM_SUCCESS

    bool _UMXCAM_EXPORT umxCam_saveAllImages_ADR(UMXCAM_HANDLE handle, const char* dirName);

    bool _UMXCAM_EXPORT umxCam_saveAllImages(UMXCAM_HANDLE handle, const std::string &dirName);
    // Save debug images
    //
    // handle[in] - UMXCAM_HANDLE value
    // dirName[in] - image path to save
    //
    // Return value - true : success to save
    //                false : fail to save

    int _UMXCAM_EXPORT umxCam_getWhichEye(UMXCAM_HANDLE handle, int *whichEye);

    int _UMXCAM_EXPORT umxCam_setWhichEye(UMXCAM_HANDLE handle, int whichEye);
    // Get/Set whichEye option
    //
    // handle[in] - UMXCAM_HANDLE value
    // whichEye[in/out] - UMXCAM_LEFT_EYE, UMXCAM_RIGHT_EYE, UMXCAM_BOTH_EYES, UMXCAM_EITHER_EYE
    //
    // Return value - UMXCAM_ERROR_INVALID_HANDLE
    //                UMXCAM_ERROR_IN_ARGUMENTS
    //                UMXCAM_SUCCESS

    int _UMXCAM_EXPORT umxCam_getMaxFrameDiffInEitherEyeMode(UMXCAM_HANDLE handle, int *maxFrameDiffinEitherEyeMode);

    int _UMXCAM_EXPORT umxCam_setMaxFrameDiffInEitherEyeMode(UMXCAM_HANDLE handle, int maxFrameDiffinEitherEyeMode);
    // Get/Set maximum number of frames difference allowed for both eyes capture in "Either Eye" mode.
    // 3 to 9 is allowed and the values outside this range will result in UMXCAM_ERROR_IN_ARGUMENTS return.
    // If this value is set to 3, it only capture both eyes if the frame difference is 3 and it will capture
    // one eye otherwise. This is the fastest "Either Eye" capture mode.
    //
    // handle[in] - UMXCAM_HANDLE value
    // maxFrameDiffinEitherEyeMode[in/out] - If it not in the range of 3 to 9, UMXCAM_ERROR_IN_ARGUMENTS will return
    //                                       Default is 9.
    //
    // Return value - UMXCAM_ERROR_INVALID_HANDLE
    //                UMXCAM_ERROR_IN_ARGUMENTS
    //                UMXCAM_SUCCESS

    int _UMXCAM_EXPORT umxCam_getOperatingRange(UMXCAM_HANDLE handle, int *minOperatingRangeMM, int *maxOperatingRangeMM);

    int _UMXCAM_EXPORT umxCam_setOperatingRange(UMXCAM_HANDLE handle, int minOperatingRangeMM, int maxOperatingRangeMM);
    // Get/Set operating range in mm unit. The default minimum is 350mm and maximum 450mm.
    // The maximum can be set less than 480mm
    //
    // handle[in] - UMXCAM_HANDLE value
    // minOperatingRangeMM[in/out] - minimum operating range (mm)
    // maxOperatingRangeMM[in/out] - maximum operating range (mm)
    //
    // Return value - UMXCAM_ERROR_INVALID_HANDLE
    //                UMXCAM_ERROR_IN_ARGUMENTS
    //                UMXCAM_SUCCESS

    int _UMXCAM_EXPORT umxCam_openDevice_simul(UMXCAM_HANDLE handle, int mode, const char* dirName);
    // Open the device for simul.

    int _UMXCAM_EXPORT umxCam_clear_simul(UMXCAM_HANDLE handle);
    // clear processDeque for simul.

	bool _UMXCAM_EXPORT umxCam_setCamLibThreadWaitFlag(UMXCAM_HANDLE handle, bool matchStart, int stopThreadIndex); //by dhkim
	bool _UMXCAM_EXPORT umxCam_restartCamLibThread(UMXCAM_HANDLE handle, int reStartThreadIndex); //by dhkim

    #ifdef APP_CALIB
    int _UMXCAM_EXPORT umxCam_motMove(UMXCAM_HANDLE handle, unsigned char Movetype, unsigned char MoveDir, unsigned short MoveStep);
    #endif

    int _UMXCAM_EXPORT umxCam_printDebugMSG(UMXCAM_HANDLE handle, char* func,
                                             int line, char* additional = nullptr);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // UMXCAM_H
