/**************************************************************************************************\

	Author:		Ralph
	Created:	03.03.2014

---------------------------------------------------------------------------------------------------

	Copyright (c) 2014 Smartsensors Ltd.

\**************************************************************************************************/

#ifndef __HTTP_REQUEST_HANDLER_FACTORY_H__
#define __HTTP_REQUEST_HANDLER_FACTORY_H__

#include <Poco/URI.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>

#if 1 //EF-45(unklee88)-59 : netglobal.h includes BiometricDataCache.h vvv
#include "umxNetLib/umxNetGlobal.h"
#else
#include <DataAccess/BiometricDataCache.h>
#endif //EF-45(unklee88)-59 : netglobal.h includes BiometricDataCache.h ^^^

#include "BiometricDataRequestHandler.h"
#include "SelectedDataRequestHandler.h"
#include "ConfigurationRequestHandler.h"
#include "CameraConfigurationRequestHandler.h"
#include "EventLogRequestHandler.h"
#include "ImageGalleryRequestHandler.h"
#include "LockRequestHandler.h"
#include "PreviewDataRequestHandler.h"
#include "SubjectDataRequestHandler.h"
#include "FaceDataRequestHandler.h"
#include "VersionRequestHandler.h"
#include "UserInfoDataRequestHandler.h"
#include "ControlRequestHandler.h"
#include "UpdateFirmwareRequestHandler.h"
#if 1 //EF-45(unklee88)-57 : netglobal.h includes iNetworkmanager.h vvv
#include "umxNetLib/umxNetGlobal.h"
#else
#include "iNetworkManager.h"
#endif //EF-45(unklee88)-57 : netglobal.h includes iNetworkmanager.h ^^^
#include "Locker.h"

#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>

//#include <QDebug>

class HTTPRequestHandlerFactory: public Poco::Net::HTTPRequestHandlerFactory
{
public:
    HTTPRequestHandlerFactory(INetworkManager* iNetworkManager)
        : Poco::Net::HTTPRequestHandlerFactory(), _iNetworkManager(iNetworkManager)
    {}

    const std::string getPath(const std::string& request)
    {
        std::string path("/");
        Poco::URI uri(request);
        std::vector<std::string> pathSegments;
        uri.getPathSegments( pathSegments );
        if (pathSegments.size() > 0)
        {
            path = pathSegments[0];
        }
        return path;
    }

    const std::string getApiVersion(const std::string& request)
    {
        std::string version("0.0");
        Poco::URI uri(request);
        std::vector<std::string> pathSegments;
        uri.getPathSegments( pathSegments );
        if (pathSegments.size() > 0 && pathSegments[0] == "1.0")
        {
            version = pathSegments[0];
        }
        return version;
    }

    //- popVersion
    const std::vector<std::string> popVersion(const std::string& request)
    {
        Poco::URI uri(request);
        std::vector<std::string> pathSegments;
        uri.getPathSegments( pathSegments );
        if (pathSegments.size() > 0)
        {
            pathSegments.erase(pathSegments.begin());
        }
        return pathSegments;
    }

    //- createRequestHandler
    Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request)
    {
        std::string version = getApiVersion(request.getURI());
        if (version == "1.0")
        {
            return createAPI10RequestHandler( request, popVersion( request.getURI() ) );
        }
        else
        {
#if defined(UMX_DEBUG_ENABLE)
            std::cout << version << std::endl;
#endif
        }
        return 0;
    }

    //- createRequestHandler
    Poco::Net::HTTPRequestHandler* createRequestHandler_usb(const Poco::Net::HTTPRequest& request, std::string sendJson)
    {
        std::string version = getApiVersion(request.getURI());
        if (version == "1.0")
        {
            return createAPI10RequestHandler_usb( request, popVersion( request.getURI() ), sendJson);
        }
        else
        {
#if defined(UMX_DEBUG_ENABLE)
            std::cout << version << std::endl;
#endif
        }
        return 0;
    }

    //- createAPI10RequestHandler
    Poco::Net::HTTPRequestHandler* createAPI10RequestHandler(const Poco::Net::HTTPServerRequest& request, const std::vector<std::string>& pathSegments)
    {
        // version - get version number for APP - DONE.
        // biometric-data - get all biometric data captured by the device - DONE.
        // biometric-data/{id} - get the biometric data specified by the id - DONE.
        // galleries - get all the galleries on the device.  E.g. enrol, blacklist
        // galleries/{id} - get all the subjects for the gallery specified by the gallery id
        // logs - get all the log entries on the device.  Paginated by 100 (default) items.  Can be overriden in the query to request all. PART missing paging.
        // logs/{id} - manipulate a single log entry.  E.g. delete it.
        // subjects - get all the subjects.
        // configuration - get all the configuration data.
        // configuration/camera - get all the configuration data pertinent to the camera
        // configuration/camera/{id}/mode - put the camera in enrol, match or enrol/match mode
        //std::cout << request.getURI() << " first segment " << pathSegments[0] << std::endl;
        //for(auto idx = begin(pathSegments); idx != end(pathSegments); ++idx)
        //{
        //    std::cout << *idx << std::endl;
        //}

        Poco::URI uri(request.getURI());

        if (pathSegments[0] == "version")
        {
            //std::cout << "** createAPI10RequestHandler : version " << std::endl;
            return new VersionRequestHandler(_iNetworkManager);
        }
        else if (pathSegments[0] == "lock")
        {
            std::cout << "** createAPI10RequestHandler : lock " << std::endl;
            return new LockRequestHandler(&_locker, pathSegments);
        }
//        else if (pathSegments[0] == "control")
//        {
//            //std::cout << "** createAPI10RequestHandler : control " << std::endl;
//            return new ControlRequestHandler(_iNetworkManager, pathSegments);
//        }
        else if (_locker.IsLocked(uri.getQuery()))
        {
            if (pathSegments[0] == "imagecapture")
            {
                //std::cout << "** createAPI10RequestHandler : imagecapture " << std::endl;
                return new ImageGalleryRequestHandler(_iNetworkManager);//_iNetworkManager->GetDatabaseConnection()); //EF-45(unklee88)-23 : removed not using access class in umxNetLib
            }
            else if (pathSegments[0] == "biometric-data")
            {
                //std::cout << "** createAPI10RequestHandler : biometric-data " << std::endl;
                return new BiometricDataRequestHandler(_iNetworkManager, _iNetworkManager->GetBiometricDataCache(), pathSegments);
            }
            else if (pathSegments[0] == "match-data")
            {
                //std::cout << "** createAPI10RequestHandler : match-data " << std::endl;
                return new SelectedDataRequestHandler(_iNetworkManager->GetSelectedDataCache(), pathSegments);
            }
            else if (pathSegments[0] == "config")
            {
                //std::cout << "** createAPI10RequestHandler : config " << std::endl;
                return new ConfigurationRequestHandler(_iNetworkManager, pathSegments);
            }
            else if (pathSegments[0] == "camera")
            {
                //std::cout << "** createAPI10RequestHandler : camera " << std::endl;
                return new CameraConfigurationRequestHandler(_iNetworkManager, pathSegments);
            }
            else if (pathSegments[0] == "logs")
            {
                //std::cout << "** createAPI10RequestHandler : logs " << std::endl;
                return new EventLogRequestHandler(_iNetworkManager, pathSegments);//_iNetworkManager->GetEventLogDatabaseConnection(), pathSegments); //EF-45(unklee88)-23 : removed not using access class in umxNetLib
            }
            else if (pathSegments[0] == "preview")
            {
                //std::cout << "** createAPI10RequestHandler : preview " << std::endl;
                return new PreviewDataRequestHandler(_iNetworkManager, pathSegments);
            }
            else if (pathSegments[0] == "user-info")
            {
                //std::cout << "** createAPI10RequestHandler : user-info " << std::endl;
                return new UserInfoDataRequestHandler(_iNetworkManager, pathSegments);
            }
            else if (pathSegments[0] == "faces")
            {
                //std::cout << "** createAPI10RequestHandler : faces " << std::endl;
                return new FaceDataRequestHandler(_iNetworkManager, pathSegments);
            }
            else if (pathSegments[0] == "subjects")
            {
                //std::cout << "** createAPI10RequestHandler : subjects " << std::endl;
                return new SubjectDataRequestHandler(_iNetworkManager, pathSegments);
            }
            else if (pathSegments[0] == "control")
            {
                //std::cout << "** createAPI10RequestHandler : control " << std::endl;
                return new ControlRequestHandler(_iNetworkManager, pathSegments);
            }
            //- update firmware
            else if (pathSegments[0] == "update")
            {
                //std::cout << "** createAPI10RequestHandler : update " << std::endl;
                //std::cout << "** createAPI10RequestHandler 2 : update " << pathSegments[0] << " " << pathSegments[1]<< std::endl;
                //qDebug("** createAPI10RequestHandler : update : %s : %s ** \n", pathSegments[0].c_str(), pathSegments[1].c_str());
                return new UpdateFirmwareRequestHandler(_iNetworkManager, pathSegments);
            }
        }
        else
            return 0;
    }

    Poco::Net::HTTPRequestHandler* createAPI10RequestHandler_usb(const Poco::Net::HTTPRequest& request, const std::vector<std::string>& pathSegments, std::string sendJson)
    {
         Poco::URI uri(request.getURI());
        if (pathSegments[0] == "version")
        {
            //std::cout << "** createAPI10RequestHandler_usb : version" << std::endl;

            VersionRequestHandler_usb* pVersionRequestHandler_usb = new VersionRequestHandler_usb(_iNetworkManager);
            Poco::Net::HTTPResponse res;

            std::string strMethod = request.getMethod();
            if(strMethod == "GET")
                pVersionRequestHandler_usb->handleGetRequest((Poco::Net::HTTPRequest&)request, (Poco::Net::HTTPResponse&)res);
            return pVersionRequestHandler_usb;
        }
        else if (pathSegments[0] == "lock")
        {
            //std::cout << "** createAPI10RequestHandler_usb : lock" << std::endl;
            //return new LockRequestHandler(&_locker, pathSegments);
            LockRequestHandler_usb* pLockRequestHandler_usb = new LockRequestHandler_usb(&_locker, pathSegments);
            Poco::Net::HTTPResponse res;

            std::string strMethod = request.getMethod();
            if(strMethod == "POST")
                pLockRequestHandler_usb->handlePostRequest((Poco::Net::HTTPRequest&)request, (Poco::Net::HTTPResponse&)res);
            else if(strMethod == "PUT")
                pLockRequestHandler_usb->handlePutRequest((Poco::Net::HTTPRequest&)request, (Poco::Net::HTTPResponse&)res);
            else if(strMethod == "DELETE")
                pLockRequestHandler_usb->handleDeleteRequest((Poco::Net::HTTPRequest&)request, (Poco::Net::HTTPResponse&)res);
            return pLockRequestHandler_usb;
        }
        else if (pathSegments[0] == "control")
        {
            std::cout << "** createAPI10RequestHandler_usb : control" << std::endl;
            //return new ControlRequestHandler(_iNetworkManager, pathSegments);
            //return new ControlRequestHandler_usb(_iNetworkManager, pathSegments, sendJson);

            ControlRequestHandler_usb* pControlRequestHandler_usb = new ControlRequestHandler_usb(_iNetworkManager, pathSegments, sendJson);
            Poco::Net::HTTPResponse res;

            std::string strMethod = request.getMethod();
            if(strMethod == "GET")
                pControlRequestHandler_usb->handleGetRequest((Poco::Net::HTTPRequest&)request, (Poco::Net::HTTPResponse&)res);
            else if(strMethod == "POST")
                pControlRequestHandler_usb->handlePostRequest((Poco::Net::HTTPRequest&)request, (Poco::Net::HTTPResponse&)res);
            else if(strMethod == "PUT")
                pControlRequestHandler_usb->handlePutRequest((Poco::Net::HTTPRequest&)request, (Poco::Net::HTTPResponse&)res);
            else if(strMethod == "DELETE")
                pControlRequestHandler_usb->handleDeleteRequest((Poco::Net::HTTPRequest&)request, (Poco::Net::HTTPResponse&)res);
            return pControlRequestHandler_usb;
        }

//- usb com : pass Lock
//        else if (_locker.IsLocked(uri.getQuery()))
        {
//- not userd
//            if (pathSegments[0] == "imagecapture")
//            {
//                std::cout << "** createAPI10RequestHandler_usb : imagecapture" << std::endl;
//                return new ImageGalleryRequestHandler(_iNetworkManager);//_iNetworkManager->GetDatabaseConnection()); //EF-45(unklee88)-23 : removed not using access class in umxNetLib
//            }
            if (pathSegments[0] == "biometric-data")
            {
                //std::cout << "** createAPI10RequestHandler_usb : biometric-data" << std::endl;

                BiometricDataRequestHandler_usb* pBiometricDataRequestHandler_usb = new BiometricDataRequestHandler_usb(_iNetworkManager, _iNetworkManager->GetBiometricDataCache(), pathSegments, sendJson);
                Poco::Net::HTTPResponse res;

                std::string strMethod = request.getMethod();
                if(strMethod == "GET")
                    pBiometricDataRequestHandler_usb->handleGetRequest((Poco::Net::HTTPRequest&)request, (Poco::Net::HTTPResponse&)res);
                else if(strMethod == "DELETE")
                    pBiometricDataRequestHandler_usb->handleDeleteRequest((Poco::Net::HTTPRequest&)request, (Poco::Net::HTTPResponse&)res);
                else if(strMethod == "PUT")
                    pBiometricDataRequestHandler_usb->handlePutRequest((Poco::Net::HTTPRequest&)request, (Poco::Net::HTTPResponse&)res);
                return pBiometricDataRequestHandler_usb;
            }
            else if (pathSegments[0] == "camera")
            {
                //std::cout << "** createAPI10RequestHandler_usb : camera" << std::endl;

                CameraConfigurationRequestHandler_usb* pCameraConfigurationRequestHandler_usb = new CameraConfigurationRequestHandler_usb(_iNetworkManager, pathSegments, sendJson);
                Poco::Net::HTTPResponse res;

                std::string strMethod = request.getMethod();
                if(strMethod == "GET")
                    pCameraConfigurationRequestHandler_usb->handleGetRequest((Poco::Net::HTTPRequest&)request, (Poco::Net::HTTPResponse&)res);
                else if(strMethod == "POST")
                    pCameraConfigurationRequestHandler_usb->handlePostRequest((Poco::Net::HTTPRequest&)request, (Poco::Net::HTTPResponse&)res);
                else if(strMethod == "PUT")
                    pCameraConfigurationRequestHandler_usb->handlePutRequest((Poco::Net::HTTPRequest&)request, (Poco::Net::HTTPResponse&)res);
                return pCameraConfigurationRequestHandler_usb;
            }
            else if (pathSegments[0] == "config")
            {
                //std::cout << "** createAPI10RequestHandler_usb : config" << std::endl;

                ConfigurationRequestHandler_usb* pConfigurationRequestHandler_usb = new ConfigurationRequestHandler_usb(_iNetworkManager, pathSegments, sendJson);
                Poco::Net::HTTPResponse res;

                std::string strMethod = request.getMethod();
                if(strMethod == "GET")
                    pConfigurationRequestHandler_usb->handleGetRequest((Poco::Net::HTTPRequest&)request, (Poco::Net::HTTPResponse&)res);
                else if(strMethod == "POST")
                    pConfigurationRequestHandler_usb->handlePostRequest((Poco::Net::HTTPRequest&)request, (Poco::Net::HTTPResponse&)res);
                else if(strMethod == "PUT")
                    pConfigurationRequestHandler_usb->handlePutRequest((Poco::Net::HTTPRequest&)request, (Poco::Net::HTTPResponse&)res);
                return pConfigurationRequestHandler_usb;
            }
            else if (pathSegments[0] == "preview")
            {
                //std::cout << "** createAPI10RequestHandler_usb : preview" << std::endl;

                PreviewDataRequestHandler_usb* pPreviewDataRequestHandler_usb = new PreviewDataRequestHandler_usb(_iNetworkManager, pathSegments);
                Poco::Net::HTTPResponse res;

                std::string strMethod = request.getMethod();
                if(strMethod == "GET")
                    pPreviewDataRequestHandler_usb->handleGetRequest((Poco::Net::HTTPRequest&)request, (Poco::Net::HTTPResponse&)res);
                else if(strMethod == "DELETE")
                    pPreviewDataRequestHandler_usb->handleDeleteRequest((Poco::Net::HTTPRequest&)request, (Poco::Net::HTTPResponse&)res);
                return pPreviewDataRequestHandler_usb;
            }
            else if (pathSegments[0] == "match-data")
            {
                //std::cout << "** createAPI10RequestHandler_usb : match-data" << std::endl;
                SelectedDataRequestHandler_usb* pSelectedDataRequestHandler_usb = new SelectedDataRequestHandler_usb(_iNetworkManager->GetSelectedDataCache(), pathSegments);
                Poco::Net::HTTPResponse res;

                std::string strMethod = request.getMethod();
                if(strMethod == "GET")
                    pSelectedDataRequestHandler_usb->handleGetRequest((Poco::Net::HTTPRequest&)request, (Poco::Net::HTTPResponse&)res);
                else if(strMethod == "DELETE")
                    pSelectedDataRequestHandler_usb->handleDeleteRequest((Poco::Net::HTTPRequest&)request, (Poco::Net::HTTPResponse&)res);
                return pSelectedDataRequestHandler_usb;
            }
            else if (pathSegments[0] == "logs")
            {
                //std::cout << "** createAPI10RequestHandler_usb : logs" << std::endl;

                EventLogRequestHandler_usb* pEventLogRequestHandler_usb = new EventLogRequestHandler_usb(_iNetworkManager, pathSegments);
                Poco::Net::HTTPResponse res;

                std::string strMethod = request.getMethod();
                if(strMethod == "GET")
                    pEventLogRequestHandler_usb->handleGetRequest((Poco::Net::HTTPRequest&)request, (Poco::Net::HTTPResponse&)res);
                else if(strMethod == "POST")
                    pEventLogRequestHandler_usb->handlePostRequest((Poco::Net::HTTPRequest&)request, (Poco::Net::HTTPResponse&)res);
                else if(strMethod == "DELETE")
                    pEventLogRequestHandler_usb->handleDeleteRequest((Poco::Net::HTTPRequest&)request, (Poco::Net::HTTPResponse&)res);
                return pEventLogRequestHandler_usb;
            }
            else if (pathSegments[0] == "faces")
            {
                //std::cout << "** createAPI10RequestHandler_usb : faces" << std::endl;

                FaceDataRequestHandler_usb* pFaceDataRequestHandler_usb = new FaceDataRequestHandler_usb(_iNetworkManager, pathSegments, sendJson);
                Poco::Net::HTTPResponse res;

                std::string strMethod = request.getMethod();
                if(strMethod == "GET")
                    pFaceDataRequestHandler_usb->handleGetRequest((Poco::Net::HTTPRequest&)request, (Poco::Net::HTTPResponse&)res);
                else if(strMethod == "POST")
                    pFaceDataRequestHandler_usb->handlePostRequest((Poco::Net::HTTPRequest&)request, (Poco::Net::HTTPResponse&)res);
                else if(strMethod == "PUT")
                    pFaceDataRequestHandler_usb->handlePutRequest((Poco::Net::HTTPRequest&)request, (Poco::Net::HTTPResponse&)res);
                else if(strMethod == "DELETE")
                    pFaceDataRequestHandler_usb->handleDeleteRequest((Poco::Net::HTTPRequest&)request, (Poco::Net::HTTPResponse&)res);
                return pFaceDataRequestHandler_usb;
            }
            else if (pathSegments[0] == "user-info")
            {
                //std::cout << "** createAPI10RequestHandler_usb : user-info" << std::endl;

                UserInfoDataRequestHandler_usb* pUserInfoDataRequestHandler_usb = new UserInfoDataRequestHandler_usb(_iNetworkManager, pathSegments, sendJson);
                Poco::Net::HTTPResponse res;

                std::string strMethod = request.getMethod();
                if(strMethod == "GET")
                    pUserInfoDataRequestHandler_usb->handleGetRequest((Poco::Net::HTTPRequest&)request, (Poco::Net::HTTPResponse&)res);
                else if(strMethod == "POST")
                    pUserInfoDataRequestHandler_usb->handlePostRequest((Poco::Net::HTTPRequest&)request, (Poco::Net::HTTPResponse&)res);
                else if(strMethod == "PUT")
                    pUserInfoDataRequestHandler_usb->handlePutRequest((Poco::Net::HTTPRequest&)request, (Poco::Net::HTTPResponse&)res);
                else if(strMethod == "DELETE")
                    pUserInfoDataRequestHandler_usb->handleDeleteRequest((Poco::Net::HTTPRequest&)request, (Poco::Net::HTTPResponse&)res);
                return pUserInfoDataRequestHandler_usb;
            }
            else if (pathSegments[0] == "subjects")
            {
                //std::cout << "** createAPI10RequestHandler_usb : subjects" << std::endl;

                SubjectDataRequestHandler_usb* pSubjectDataRequestHandler_usb = new SubjectDataRequestHandler_usb(_iNetworkManager, pathSegments, sendJson);
                Poco::Net::HTTPResponse res;

                std::string strMethod = request.getMethod();
                if(strMethod == "GET")
                    pSubjectDataRequestHandler_usb->handleGetRequest((Poco::Net::HTTPRequest&)request, (Poco::Net::HTTPResponse&)res);
                else if(strMethod == "POST")
                    pSubjectDataRequestHandler_usb->handlePostRequest((Poco::Net::HTTPRequest&)request, (Poco::Net::HTTPResponse&)res);
                else if(strMethod == "PUT")
                    pSubjectDataRequestHandler_usb->handlePutRequest((Poco::Net::HTTPRequest&)request, (Poco::Net::HTTPResponse&)res);
                else if(strMethod == "DELETE")
                    pSubjectDataRequestHandler_usb->handleDeleteRequest((Poco::Net::HTTPRequest&)request, (Poco::Net::HTTPResponse&)res);
                return pSubjectDataRequestHandler_usb;
            }
        }
//        else
            return 0;
    }

private:
    Locker _locker;
    INetworkManager* _iNetworkManager;
};



#endif // __HTTP_REQUEST_HANDLER_FACTORY_H__
