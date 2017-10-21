/**************************************************************************************************\

	Author:		Ralph
	Created:	17.04.2014

---------------------------------------------------------------------------------------------------

	Copyright (c) 2014 Smartsensors Ltd.

\**************************************************************************************************/

#ifndef __IMAGE_GALLERY_REQUEST_HANDLER_H__
#define __IMAGE_GALLERY_REQUEST_HANDLER_H__

#include <iostream>

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;

#if 0 //EF-45(unklee88)-23 : removed not using access class in umxNetLib
#include <DataAccess/ImageCaptureDataAccess.h>
#endif
#if 1 //EF-45(unklee88)-70 : umxCommonGlobal.h includes umxCommonLib/DataTypes/ImageCapture.h vvv
#include "umxCommonLib/umxCommonGlobal.h"
#else
#include <DataTypes/ImageCapture.h>
#endif //EF-45(unklee88)-70 : umxCommonGlobal.h includes umxCommonLib/DataTypes/ImageCapture.h ^^^
#include "HTTPRequestVerbHandler.h"
#if 1 //EF-45(unklee88)-23 : removed not using access class in umxNetLib
#if 1 //EF-45(unklee88)-57 : netglobal.h includes iNetworkmanager.h vvv
#include "umxNetLib/umxNetGlobal.h"
#else
#include "iNetworkManager.h"
#endif //EF-45(unklee88)-57 : netglobal.h includes iNetworkmanager.h ^^^
#endif

#if 1 //EF-45(unklee88)-62 : made Namespace UMXNetwork vvv
using namespace UMXNetwork;
#endif //EF-45(unklee88)-62 : made Namespace UMXNetwork ^^^
#if 1 //EF-45(unklee88)-70 : umxCommonGlobal.h includes umxCommonLib/DataTypes/ImageCapture.h vvv
using namespace UMXCommon;
#endif //EF-45(unklee88)-70 : umxCommonGlobal.h includes umxCommonLib/DataTypes/ImageCapture.h ^^^

class ImageGalleryRequestHandler : public HTTPRequestVerbHandler
{
public:
#if 1 //EF-45(unklee88)-23 : removed not using access class in umxNetLib
    ImageGalleryRequestHandler(INetworkManager *iNetworkManager);
#endif
    ~ImageGalleryRequestHandler(void);
protected:
    void handleGetRequest(HTTPServerRequest& request, HTTPServerResponse& response);
private:
	ImageGalleryRequestHandler(const ImageGalleryRequestHandler&);
	ImageGalleryRequestHandler& operator = (const ImageGalleryRequestHandler&);
private:
#if 1 //EF-45(unklee88)-23 : removed not using access class in umxNetLib
    INetworkManager* _iNetworkManager;
#endif
};

class ImageGalleryRequestHandler_usb : public ImageGalleryRequestHandler
{
public:
#if 1 //EF-45(unklee88)-23 : removed not using access class in umxNetLib
    ImageGalleryRequestHandler_usb(INetworkManager *iNetworkManager);
    std::string getResponse() {return responseAsJSONString;};
#endif
public:
    void handleGetRequest(Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response);
private:
    ImageGalleryRequestHandler_usb(const ImageGalleryRequestHandler_usb&);
    ImageGalleryRequestHandler_usb& operator = (const ImageGalleryRequestHandler_usb&);
private:
#if 1 //EF-45(unklee88)-23 : removed not using access class in umxNetLib
    INetworkManager* _iNetworkManager;
    std::string responseAsJSONString = "";
#endif
};

#endif // __IMAGE_GALLERY_REQUEST_HANDLER_H__
