/////////////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2016 CMITECH Co., Ltd.
// All rights reserved.
//
// Licensees holding valid CMITECH's CMIRIS SDK licenses may use this file in
// accordance with the CMIRIS SDK License Agreement provided with the
// Software or, alternatively, in accordance with the terms contained in
// an agreement between you and CMITECH.
////////////////////////////////////////////////////////////////////////////////////////

#ifndef __UMXPERIDEVGLOBAL_H__
#define __UMXPERIDEVGLOBAL_H__

#include <stdbool.h>

/*------------------------------------------------*/
/*-------------------- TAMPER --------------------*/
/*------------------------------------------------*/
// status: tamper status 0 or 1
// err(linux errno): 0 is normal, if err are not 0 that callback cancel 
typedef void (*tamper_cb_f)(int/* status */, int/* err */);

/*------------------------------------------------*/
/*-------------------- GPI --------------------*/
/*------------------------------------------------*/
// status: gpi value
// err(linux errno): 0 is normal, if err are not 0 that callback cancel 
typedef void (*gpi_cb_f)(int/* value */, int/* err */);

/*-------------------- MOTION --------------------*/
// x, y, z: Coordinate values
// err(linux errno): 0 is normal, if err are not 0 that callback cancel 
typedef void (*motion_cb_f)(int/* x */, int/* y */, int/* z */, int/* err */);

/*------------------------------------------------*/
/*-------------------- SECURE-IC --------------------*/
/*------------------------------------------------*/
#define UMX_ID_ERROR_CODE_TRUE			0
#define UMX_ID_ERROR_CODE_FALSE			1
#define UMX_ID_ERROR_CODE_WRITE_ADDR	10
#define UMX_ID_ERROR_CODE_WRITE_DATA	20
#define UMX_ID_ERROR_CODE_READ_ADDR		30
#define UMX_ID_ERROR_CODE_READ_DATA		40
#define UMX_ID_ERROR_CODE_START_BIT		50
#define UMX_ID_ERROR_CODE_APROCESS		60
#define UMX_ID_ERROR_CODE_DENY			70

/*------------------------------------------------*/
/*-------------------- RFID --------------------*/
/*------------------------------------------------*/
// data: data byte array pointer
// size: data byte size
// err(linux errno): 0 is normal, if err are not 0 that callback cancel
typedef void (*rfid_tagged_cb_f)(char* /* data */, int/*data_size*/ , int/* err */);

/*------------------------------------------------*/
/*-------------------- WIEGAND --------------------*/
/*------------------------------------------------*/
#define WIEGAND_DATA_MAX	34	// bytes == 272 bits
// data: data byte array pointer
// bits: data byte size
// err(linux errno): 0 is normal, if err are not 0 that callback cancel 
typedef void (*wiegand_in_cb_f)(char* /* data */, int/*data_size*/ , int/* err */);

/*------------------------------------------------*/
/*-------------------- RS232 --------------------*/
/*------------------------------------------------*/
// data: data byte array pointer
// size: data byte size
// err(linux errno): 0 is normal, if err are not 0 that callback cancel
typedef void (*rs232_recv_cb_f)(char* /* data */, int/*data_size*/ , int/* err */);

/*------------------------------------------------*/
/*-------------------- RS485 --------------------*/
/*------------------------------------------------*/
// data: data byte array pointer
// size: data byte size
// err(linux errno): 0 is normal, if err are not 0 that callback cancel
typedef void (*rs485_recv_cb_f)(char* /* data */, int/*data_size*/ , int/* err */);

/*------------------------------------------------*/
/*-------------------- Factory-Reset --------------------*/
/*------------------------------------------------*/
// status: factory-reset button status 0(released) or 1(pressed)
// err(linux errno): 0 is normal, if err are not 0 that callback cancel 
typedef void (*factoryreset_cb_f)(int/* status */, int/* err */);

/*------------------------------------------------*/
/*-------------------- Network --------------------*/
/*------------------------------------------------*/
typedef enum Peridev_Net_Error {
	PERIDEV_NET_ERROR_NONE=0,
	// 1 ~ 131 : C Error Codes in Linux
	PERIDEV_NET_ERROR_WORONG_PARAMETERS=1000,
	PERIDEV_NET_ERROR_NOT_FOUND_TECHNOLOGY,
	PERIDEV_NET_ERROR_NOT_FOUND_SERVICE,
	PERIDEV_NET_ERROR_INVAILD_SERVICE,
	PERIDEV_NET_ERROR_SCAN_FAIL,
	PERIDEV_NET_ERROR_CONNECT_FAIL,
	PERIDEV_NET_ERROR_PASSPHRASE,
	PERIDEV_NET_ERROR_CONNMANCTL,
	PERIDEV_NET_ERROR_SYSTEM_DBUS=2000,
} PERIDEV_NET_ERROR;

typedef enum Peridev_Net_Event_Type {
	PERIDEV_NET_EVENT_ERROR=	0,
	PERIDEV_NET_EVENT_TECHNOLOGY_ADDED,
	PERIDEV_NET_EVENT_TECHNOLOGY_REMOVED,
	PERIDEV_NET_EVENT_SERVICE_EVENT_BEGIN,
	PERIDEV_NET_EVENT_SERVICE_CHANGED,
	PERIDEV_NET_EVENT_SERVICE_UNCHANGED,
	PERIDEV_NET_EVENT_SERVICE_REMOVED,
	PERIDEV_NET_EVENT_SERVICE_EVENT_END,
	PERIDEV_NET_EVENT_MAX,
} PERIDEV_NET_EVENT_TYPE;

// * Technology(Network device information) hierarchy ...
typedef enum Peridev_Net_Tech_Type {
	PERIDEV_NET_TECH_NONE=0,				// Technology not found
	PERIDEV_NET_TECH_ETHERNET,			// Technology Type = "ethernet"
	PERIDEV_NET_TECH_WIFI,				// Technology Type = "wifi"
	PERIDEV_NET_TECH_BLUETOOTH,			// Technology Type = "bluetooth" (TBD)
	PERIDEV_NET_TECH_MAX,
} PERIDEV_NET_TECH_TYPE;

typedef struct Peridev_Net_Technology_Info {
	PERIDEV_NET_TECH_TYPE Type;
	char Name[64];	// Name of this technology
	bool Powerd;		// Device enabled(1:true, % network interface up) or disabled(0:false)
	bool Connected;	// Network conneceted(1:true, % IP Address is binded) or disconnected(0:false)
	bool Tethering;	// Tethering activated(1:true) or deactivated(0:false)
} PERIDEV_NET_TECH_INFO;

// * Service(Network connection information) hierarchy ...
typedef enum Peridev_Net_State {
	PERIDEV_NET_STATE_FAILURE=0,			// "failure" state indicates a wrong behavior. It is similar to the "idle" state since the service is not connected.	
	PERIDEV_NET_STATE_IDLE,				// "idle", This means that this service is not in use at all at the moment. It also is not attempting to connect or do anything else.
	PERIDEV_NET_STATE_ASSOCIATION,		// "association" state indicates that this service tries to establish a low-level connection to the network.
	PERIDEV_NET_STATE_CONFIGURATION,	// "configuration" state the service indicates that it is trying to retrieve/configure IP settings.
	PERIDEV_NET_STATE_READY,				// "ready" state signals a successful connected device. This doesn't mean it has the default route, but basic IP operations will succeed.
	PERIDEV_NET_STATE_ONLINE,			// "online" signals that an Internet connection is available and has been verified.
	PERIDEV_NET_STATE_DISCONNECT,		// "disconnect"
	PERIDEV_NET_STATE_MAX,
} PERIDEV_NET_STATE;

typedef enum Peridev_Net_State_Failure {
	PERIDEV_NET_STATE_FAIL_OUT_OF_RANGE=0,	// "out-of-range"
	PERIDEV_NET_STATE_FAIL_PIN_MISSING,		// "pin-missing"
	PERIDEV_NET_STATE_FAIL_DHCP_FAILED,		// "dhcp-failed"
	PERIDEV_NET_STATE_FAIL_CONNECT_FAILED,	// "connect-failed"
	PERIDEV_NET_STATE_FAIL_LOGIN_FAILED,		// "login-failed"
	PERIDEV_NET_STATE_FAIL_AUTH_FAILED,		// "auth-failed"
	PERIDEV_NET_STATE_FAIL_INVALID_KEY,		// "invalid-key"
	PERIDEV_NET_STATE_FAIL_MAX,
} PERIDEV_NET_STATE_FAIL;

#define	PERIDEV_NET_SECURITY_NONE		0x00		// "none"
#define	PERIDEV_NET_SECURITY_WEP			0x01		// "wep"
#define	PERIDEV_NET_SECURITY_PSK			0x02		// "psk"
#define	PERIDEV_NET_SECURITY_IEEE8021X	0x04		// "ieee8021x"
#define	PERIDEV_NET_SECURITY_WPS			0x08		// "wps"

typedef struct Peridev_Net_Ipv4 {
	char Method;					// 0="off", 1="dhcp", 2="manual"
	char Address[16];
	char Netmask[16];
	char Gateway[16];
} PERIDEV_NET_IPV4;

typedef struct Peridev_Net_Service_Info {
	PERIDEV_NET_TECH_TYPE Type;
	char DisplayName[64];		// (SSID) This name can be used for directly displaying it in the application. It has pure informational purpose and no attempt should be made to translate it.
	char DeviceName[128];		// *Service setting Name
	char Security;			// PERIDEV_NET_SECURITY_NONE | WEP | PSK | IEEE8021X | WPS
	PERIDEV_NET_STATE State;
	PERIDEV_NET_STATE_FAIL Failure;
	unsigned char Strength;		// Indicates the signal strength of the service. This is a normalized value between 0 and 100.
	bool Favorite;				// Will be true if a cable is plugged in or the user selected and successfully connected to this service.
	bool AutoConnect;			// If set to true, this service will auto-connect when no other connection is available.
	PERIDEV_NET_IPV4 IPv4;
} PERIDEV_NET_SERVICE_INFO;

typedef void (*network_cb_f)(const PERIDEV_NET_EVENT_TYPE , const PERIDEV_NET_ERROR,
	const PERIDEV_NET_TECH_INFO*, const PERIDEV_NET_SERVICE_INFO*);

typedef void (*service_cb_f)(const PERIDEV_NET_SERVICE_INFO*);


/*------------------------------------------------*/
/*-------------------- USB --------------------*/
/*------------------------------------------------*/
// status: USB status 0:Got an error, 1:Got a readable data
// err: Linux errno code and callback cancel 
typedef void (*usb_status_cb_f)(int/* status */, int/* err */);

typedef enum Peridev_usb_device_state {
	/* NOTATTACHED isn't in the USB spec, and this state acts
	 * the same as ATTACHED ... but it's clearer this way.
	 */
	PERIDEV_USB_STATE_NOTATTACHED = 0,

	/* chapter 9 and authentication (wireless) device states */
	PERIDEV_USB_STATE_ATTACHED,
	PERIDEV_USB_STATE_POWERED,			/* wired */
	PERIDEV_USB_STATE_RECONNECTING,			/* auth */
	PERIDEV_USB_STATE_UNAUTHENTICATED,		/* auth */
	PERIDEV_USB_STATE_DEFAULT,			/* limited function */
	PERIDEV_USB_STATE_ADDRESS,
	PERIDEV_USB_STATE_CONFIGURED,			/* most functions */

	PERIDEV_USB_STATE_SUSPENDED

	/* NOTE:  there are actually four different SUSPENDED
	 * states, returning to POWERED, DEFAULT, ADDRESS, or
	 * CONFIGURED respectively when SOF tokens flow again.
	 * At this level there's no difference between L1 and L2
	 * suspend states.  (L2 being original USB 1.1 suspend.)
	 */
}PERIDEV_USB_DEVICE_STATE;



#endif /* __UMXPERIDEVGLOBAL_H__ */
