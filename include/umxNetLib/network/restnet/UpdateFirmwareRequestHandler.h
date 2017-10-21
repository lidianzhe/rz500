/**************************************************************************************************\

	Author:		Ralph
	Created:	22.04.2014

---------------------------------------------------------------------------------------------------

	Copyright (c) 2014 Smartsensors Ltd.

\**************************************************************************************************/

#ifndef __UPDATE_FIRMWARE_REQUEST_HANDLER_H__
#define __UPDATE_FIRMWARE_REQUEST_HANDLER_H__

#include <memory>
#include <string>
#include <vector>

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;

#include "HTTPRequestVerbHandler.h"
#if 1 //EF-45(unklee88)-59 : netglobal.h includes BiometricDataCache.h vvv
#include "umxNetLib/umxNetGlobal.h"
#else
#include <DataAccess/BiometricDataCache.h>
#endif //EF-45(unklee88)-59 : netglobal.h includes BiometricDataCache.h ^^^


#define _HTTP_1_1 "HTTP/1.1"
//#define BUF_SIZE 64
//#define BUF_SIZE 512
#define BUF_SIZE 1024
//#define BUF_SIZE 2048

#define CMI_RET_SUCCESS     1
#define CMI_RET_FAIL        0
#define CMI_HTTP_RESP_OK    200
#define CMI_HTTP_RESP_NG    0

#define CMD_UPGRADE_SH  "/etc/udev/scripts/upgrade.sh"
#define CMD_FORCED_UPGRADE_SH  "/etc/udev/scripts/forced_upgrade.sh"
#define UPLOAD_EVIDENCE_PATH "/usr/local/share/CMITECH/update_temp/upgrade.lck"
#define MAXLINE             256



#if 1 //EF-45(unklee88)-62 : made Namespace UMXNetwork vvv
using namespace UMXNetwork;
#endif //EF-45(unklee88)-62 : made Namespace UMXNetwork ^^^

//- update firmware
class UpdateFirmwareRequestHandler : public HTTPRequestVerbHandler
{
public:
    UpdateFirmwareRequestHandler(INetworkManager* pINetworkManager, const std::vector<std::string>& pathSegments);
    ~UpdateFirmwareRequestHandler(void);
protected:
    void handlePostRequest(HTTPServerRequest& request, HTTPServerResponse& response);
    void handlePutRequest(HTTPServerRequest& request, HTTPServerResponse& response);

    void receiveData(HTTPServerRequest& request, HTTPServerResponse& response, bool bForce);
    int updateFirmware(char* filePath, char* fileName, bool forcedFlag);
    bool serPopen(const char* command, char* searchWord);

private:
    UpdateFirmwareRequestHandler(const UpdateFirmwareRequestHandler&);
    UpdateFirmwareRequestHandler& operator = (const UpdateFirmwareRequestHandler&);
private:

private:

    INetworkManager* _pINetworkManager;
};

#endif // __UPDATE_FIRMWARE_REQUEST_HANDLER_H__
