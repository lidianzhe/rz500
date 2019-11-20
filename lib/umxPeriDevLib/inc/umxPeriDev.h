#ifndef __UMXPERIDEVLIB_H__
#define __UMXPERIDEVLIB_H__

#include "umxPeriDevGlobal.h"

#if __GNUC__ >= 4
    #define UMXPERIDEVLIBSHARED_EXPORT __attribute__ ((visibility ("default")))
#else
    #define UMXPERIDEVLIBSHARED_EXPORT
#endif  // __GNUC_C >= 4
#define UMXPERIDEVLIB_EXPORT UMXPERIDEVLIBSHARED_EXPORT

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------- COMMON --------------------*/
void UMXPERIDEVLIB_EXPORT umxPeriDev_getVersion(unsigned int *major, unsigned int *minor, unsigned int *revision);


/*-------------------- BUZZER --------------------*/
// Desc.: Set buzzer
// Param: value 1 is set buzzer, 0 is un-set buzzer
// Return: 0 is success, other values is linux errno 
int UMXPERIDEVLIB_EXPORT umxPeriDev_setBuzzer(int value);


/*-------------------- TAMPER --------------------*/
// Desc.: Get tamper status
// Param: Status value 1 means tamper's on the wall, 0 means tamper's off the wall
// Return: 0 is success, other values is linux errno 
int UMXPERIDEVLIB_EXPORT umxPeriDev_getTamper(int *value);
// Desc.: Set tamper callback function to sense to change tamper status
// Param: void (*tamper_cb_f)(int)
// Return: 0 is success, other values is linux errno 
int UMXPERIDEVLIB_EXPORT umxPeriDev_setTamperCB(tamper_cb_f);


/*-------------------- RELAY --------------------*/
// Desc.: Get relay status
// Param: Value 1 means relay is on, 0 means relay is off
// Return: 0 is success, other values is linux errno 
int UMXPERIDEVLIB_EXPORT umxPeriDev_getRelay(int *value);
// Desc.: Set relay
// Param: Value 1 means relay is on, 0 means relay is off
// Return: 0 is success, other values is linux errno 
int UMXPERIDEVLIB_EXPORT umxPeriDev_setRelay(int value);


/*-------------------- GPI --------------------*/
// Desc.: Get gpi1 value
// Param: *value:gpio input value
// Return: 0 is success, other values is linux errno 
int UMXPERIDEVLIB_EXPORT umxPeriDev_getGpi1(int *value);
// Desc.: Set gpi1 callback function to sense interrupt
// Param: void (*gpi_cb_f)(int)
// Return: 0 is success, other values is linux errno 
int UMXPERIDEVLIB_EXPORT umxPeriDev_setGpi1CB(gpi_cb_f);
// Desc.: Get gpi2 value
// Param: *value:gpio input value
// Return: 0 is success, other values is linux errno 
int UMXPERIDEVLIB_EXPORT umxPeriDev_getGpi2(int *value);
// Desc.: Set gpi2 callback function to sense interrupt
// Param: void (*gpi_cb_f)(int)
// Return: 0 is success, other values is linux errno 
int UMXPERIDEVLIB_EXPORT umxPeriDev_setGpi2CB(gpi_cb_f);
// Desc.: Get AdminReq value (*deprecated)
// Param: *value:gpio input value
// Return: 0 is success, other values is linux errno 
int UMXPERIDEVLIB_EXPORT umxPeriDev_getAdminReq(int *value);
// Desc.: Set AdminReq callback function to sense interrupt (*deprecated)
// Param: void (*gpi_cb_f)(int)
// Return: 0 is success, other values is linux errno 
int UMXPERIDEVLIB_EXPORT umxPeriDev_setAdminReqCB(gpi_cb_f);


/*-------------------- MOTION --------------------*/
// Desc.: Get motion status
// Param: x, y, z coordinate values
// Return: 0 is success, other values is linux errno 
//int UMXPERIDEVLIB_EXPORT umxPeriDev_getMotionPos(int *x, int *y, int *z);
// Desc.: Get motion sensing threshold
// Param: Threshold value that range 0 ~127
// Return: 0 is success, other values is linux errno 
int UMXPERIDEVLIB_EXPORT umxPeriDev_getMotionThs(int *value);
// Desc.: Set motion sensing threshold
// Param: Threshold value that range 0 ~127
// Return: 0 is success, other values is linux errno 
int UMXPERIDEVLIB_EXPORT umxPeriDev_setMotionThs(int value);
// Desc.: Set motion callback function to sense motion
// Param: void (*tamper_cb_f)(int)
// Return: 0 is success, other values is linux errno 
int UMXPERIDEVLIB_EXPORT umxPeriDev_setMotionCB(motion_cb_f);


/*-------------------- SECURE-IC --------------------*/
// Desc.: Identify umx device
// Param: 
// Return: UMX_ID_ERRR_CODE_TRUE or UMX_ID_ERRR_CODE_xxx from umxPeriDevGlobal.h
int UMXPERIDEVLIB_EXPORT umxPeriDev_identify();


/*-------------------- RFID --------------------*/
// Desc.: Set RFID card tagged callback function to read data
// Param: void (*rfid_tagged_cb_f)(char*,int,int)
// Return: 0 is success, other values is linux errno
int UMXPERIDEVLIB_EXPORT umxPeriDev_setRFIDTaggedCB(rfid_tagged_cb_f);

int UMXPERIDEVLIB_EXPORT umxPeriDev_setRFIDOpMode(const int opmode, const unsigned char* ldata, const int ldata_size, const unsigned char* rdata, const int rdata_size, char* cid, char* name);
int UMXPERIDEVLIB_EXPORT umxPeriDev_setRFIDAutoMode(void);

int UMXPERIDEVLIB_EXPORT umxPeriDev_getRFIDUserData(char *uid, unsigned char* cid, int* cid_size, unsigned char* data, int* data_size);
int UMXPERIDEVLIB_EXPORT umxPeriDev_setRFIDUserDataMode(const int opmode, char* cid, const unsigned char* data, const int data_size);

int UMXPERIDEVLIB_EXPORT umxPeriDev_setRFIDMifareKey(unsigned char *key, int len);
int UMXPERIDEVLIB_EXPORT umxPeriDev_setRFIDMifareBlock(int startBlock, int blocks);
int UMXPERIDEVLIB_EXPORT umxPeriDev_setRFIDDesfireApp(unsigned char *app, int len);
int UMXPERIDEVLIB_EXPORT umxPeriDev_setRFIDDesfireBlock(int fileno, int offset, int bytes);
int UMXPERIDEVLIB_EXPORT umxPeriDev_setRFIDDesfireKey(int keyindex, int keytype, unsigned char *key, int keylen, int enciphered);

int UMXPERIDEVLIB_EXPORT umxPeriDev_updateRFIDFirmware(char *firmwarefile);
int UMXPERIDEVLIB_EXPORT umxPeriDev_getRFIDFirmwareVersion(char *version);

// Desc.: Get UID
// Param: uid=UID buffer, size= buffer size
// Return: 0 is success, other values is linux errno 
//int UMXPERIDEVLIB_EXPORT umxPeriDev_getRFIDuid(char *uid, int size);
int UMXPERIDEVLIB_EXPORT umxPeriDev_getRFIDuid(char *uid, int size, unsigned char* ldata, int* ldata_size, unsigned char* rdata, int* rdata_size, char* cid, char* name);
// Desc.: Read data from card memory
// Param: buffer=data buffer to read, buffer_size=buffer size, *read_size=Return real read size
// Return: 0 is success, other values is linux errno 
int UMXPERIDEVLIB_EXPORT umxPeriDev_readRFID(char *buffer, const int buffer_size, int *read_size);
// Desc.: Write data to card memory
// Param: data=data buffer to write, data_size=data size, *write_size=Return real writed size
// Return: 0 is success, other values is linux errno 
int UMXPERIDEVLIB_EXPORT umxPeriDev_writeRFID(const char *data, const int data_size, int *write_size);


/*-------------------- WIEGAND --------------------*/
// Desc.: Get wiegand in/out configure values
// Param: in_bits: bits value buffer, in_pulse_width: pulse width value buffer, in_pulse_height: pulse height value buffer
//             out_bits: bits value buffer, out_pulse_width: pulse width value buffer, out_pulse_height: pulse height value buffer
// Return: 0 is success, other values is linux errno 
int UMXPERIDEVLIB_EXPORT umxPeriDev_getWiegandConfig(
	int *in_bits, int *in_pulse_width, int *in_pulse_interval, int *out_bits, int *out_pulse_width, int *out_pulse_interval);
// Desc.: Set wiegand in/out configuration
// Param: in_bits: bits value(Max 272 bit), in_pulse_width: pulse width value, pulse_height: pulse height value
//             out_bits: bits value(Max 272 bit), out_pulse_width: pulse width value, out_pulse_height: pulse height value
// Return: 0 is success, other values is linux errno 
int UMXPERIDEVLIB_EXPORT umxPeriDev_setWiegandConfig(
	int in_bits, int in_pulse_width, int in_pulse_interval, int out_bits, int out_pulse_width, int out_pulse_interval);
// Desc.: Get Wiegand in data on GPI mode
// Param: value 0xFF or 0x00
// Return: 0 is success, -1 fail
int UMXPERIDEVLIB_EXPORT umxPeriDev_getWiegandInGpiValue(char *value);
// Desc.: Set Wiegand in signal callback function that ready to read data
// Param: void (*wiegand_in_cb_f)(int)
// Return: 0 is success, other values is linux errno
int UMXPERIDEVLIB_EXPORT umxPeriDev_setWiegandInCB(wiegand_in_cb_f);
// Desc.: Write data
// Param: data=data buffer to write, data_size=data size
// Return: 0 is success, other values is linux errno 
int UMXPERIDEVLIB_EXPORT umxPeriDev_writeWiegandData(const char *data, const unsigned int data_size);

/*-------------------- LED --------------------*/
// Desc.: Set led F1 brightness
// Param: Value range (0 ~ 255)
// Return: 0 is success, other values is linux errno 
int UMXPERIDEVLIB_EXPORT umxPeriDev_setLedF1Brightness(const int value);
// Desc.: Set led F2 brightness
// Param: Value range (0 ~ 255)
// Return: 0 is success, other values is linux errno 
int UMXPERIDEVLIB_EXPORT umxPeriDev_setLedF2Brightness(const int value);
// Desc.: Set led F3 brightness
// Param: Value range (0 ~ 255)
// Return: 0 is success, other values is linux errno 
int UMXPERIDEVLIB_EXPORT umxPeriDev_setLedF3Brightness(const int value);
// Desc.: Set led F4 brightness
// Param: Value range (0 ~ 255)
// Return: 0 is success, other values is linux errno 
int UMXPERIDEVLIB_EXPORT umxPeriDev_setLedF4Brightness(const int value);
// Desc.: Set led F5 brightness
// Param: Value range (0 ~ 255)
// Return: 0 is success, other values is linux errno 
int UMXPERIDEVLIB_EXPORT umxPeriDev_setLedF5Brightness(const int value);
// Desc.: Set led F6 brightness
// Param: Value range (0 ~ 255)
// Return: 0 is success, other values is linux errno 
int UMXPERIDEVLIB_EXPORT umxPeriDev_setLedF6Brightness(const int value);
// Desc.: Set led indicator brightness
// Param: Red, Green, Blue range (0 ~ 255)
// Return: 0 is success, other values is linux errno 
int UMXPERIDEVLIB_EXPORT umxPeriDev_setLedIndicatorBrightness(const int red, const int green, const int blue);
int UMXPERIDEVLIB_EXPORT umxPeriDev_setLedIndicatorDimming(const int value);

int UMXPERIDEVLIB_EXPORT umxPeriDev_setLedDownBrightness_EF45ML(const int value);
int UMXPERIDEVLIB_EXPORT umxPeriDev_setLedRightBrightness_EF45ML(const int value);
int UMXPERIDEVLIB_EXPORT umxPeriDev_setLedUpBrightness_EF45ML(const int value);
int UMXPERIDEVLIB_EXPORT umxPeriDev_setLedLeftBrightness_EF45ML(const int value);
int UMXPERIDEVLIB_EXPORT umxPeriDev_setLedIndicatorDistance_EF45ML(const int red, const int green, const int blue);

int UMXPERIDEVLIB_EXPORT umxPeriDev_setLedLeftBrightness_EF50(const int value);
int UMXPERIDEVLIB_EXPORT umxPeriDev_setLedRightBrightness_EF50(const int value);

/*-------------------- RS232 --------------------*/
// Desc.: Set RS232 port receive callback function to read data
// Param: void (*rs232_recv_cb_f)(char*,int,int)
// Return: 0 is success, other values is linux errno
int UMXPERIDEVLIB_EXPORT umxPeriDev_setRs232RecvCB(rs232_recv_cb_f);
// Desc.: Set RS232 baudrate and others(later)
// Param: baudrate=baudrate
// Return:
void umxPeriDev_setupRs232(int baudrate);
// Desc.: Read data from RS232 port
// Param: buffer=data buffer to read, buffer_size=buffer size, *read_size=Return real read size
// Return: 0 is success, other values is linux errno 
int UMXPERIDEVLIB_EXPORT umxPeriDev_readRs232(char *buffer, const int buffer_size, int *read_size);
// Desc.: Write data to RS232 port
// Param: data=data buffer to write, data_size=data size, *write_size=Return real writed size
// Return: 0 is success, other values is linux errno 
int UMXPERIDEVLIB_EXPORT umxPeriDev_writeRs232(const char *data, const int data_size, int *write_size);

/*-------------------- RS485 --------------------*/
// Desc.: Set RS485 port receive callback function to read data
// Param: void (*rs485_recv_cb_f)(char*,int,int)
// Return: 0 is success, other values is linux errno
int UMXPERIDEVLIB_EXPORT umxPeriDev_setRs485RecvCB(rs485_recv_cb_f);
// Desc.: Set RS485 baudrate and others(later)
// Param: baudrate=baudrate
// Return:
void umxPeriDev_setupRs485(int baudrate);
// Desc.: Read data from RS485 port
// Param: buffer=data buffer to read, buffer_size=buffer size, *read_size=Return real read size
// Return: 0 is success, other values is linux errno 
int UMXPERIDEVLIB_EXPORT umxPeriDev_readRs485(char *buffer, const int buffer_size, int *read_size);
// Desc.: Write data to RS485 port
// Param: data=data buffer to write, data_size=data size, *write_size=Return real writed size
// Return: 0 is success, other values is linux errno 
int UMXPERIDEVLIB_EXPORT umxPeriDev_writeRs485(const char *data, const int data_size, int *write_size);

/*-------------------- Factory-Reset --------------------*/
// Desc.: Get fatory-reset button status
// Param: Status value 1 means factory-reset's button clicked, 0 means factory-reset's button not clicked 
// Return: 0 is success, other values is linux errno 
// * Caustion: Not supported on Android
int UMXPERIDEVLIB_EXPORT umxPeriDev_getFactoryReset(int *value);
// Desc.: Set factory-reset callback function to sense to change button status
// Param: void (*factoryreset_cb_f)(int)
// Return: 0 is success, other values is linux errno 
int UMXPERIDEVLIB_EXPORT umxPeriDev_setFactoryResetCB(factoryreset_cb_f);

/*-------------------- Netwrok(WiFi) --------------------*/
// * Caustion: Not supported on Android
// Desc.: Register network event callback function. It will working until to set NULL to cb.
// Param: void (*network_cb_f)(int)
// Return: PERIDEV_NET_ERROR
PERIDEV_NET_ERROR UMXPERIDEVLIB_EXPORT umxPeriDev_setNetEventCB(network_cb_f cb);
// Desc.: Get specify network type technology(information)
// Param: type(The type that technologiy ethernet or wiif), tech(Buffer of technology information)
// Return: PERIDEV_NET_ERROR
PERIDEV_NET_ERROR UMXPERIDEVLIB_EXPORT umxPeriDev_getNetTechnology(const PERIDEV_NET_TECH_TYPE type, PERIDEV_NET_TECH_INFO *tech);
// Desc.: Get all PERIDEV_NET_SERVICE_INFO by callback.
// Param: void (*net_service_cb_f)(PERIDEV_NET_SERVICE);
//		% PERIDEV_NET_SERVICE_INFO delivered via the callback is available, only the value Type, DisplayName, DeviceName.
// Return: PERIDEV_NET_ERROR
PERIDEV_NET_ERROR UMXPERIDEVLIB_EXPORT umxPeriDev_getNetServices(service_cb_f cb);
// Desc.: Get a network service info specified by Service.Name.
// Param: deviceName: DeviceName of a service , service: The buffer of PERIDEV_NET_SERVICE_INFO
// Return: PERIDEV_NET_ERROR
PERIDEV_NET_ERROR UMXPERIDEVLIB_EXPORT umxPeriDev_getNetService(const char* deviceName, PERIDEV_NET_SERVICE_INFO *service);
// Desc.: Enables given technology
// Return: PERIDEV_NET_ERROR
PERIDEV_NET_ERROR UMXPERIDEVLIB_EXPORT umxPeriDev_enableNetTechnology(const PERIDEV_NET_TECH_TYPE type);
// Desc.: Disables given technology
// Return: PERIDEV_NET_ERROR
PERIDEV_NET_ERROR UMXPERIDEVLIB_EXPORT umxPeriDev_disableNetTechnology(const PERIDEV_NET_TECH_TYPE type);
// Desc.: Scans for new services for given technology
// Return: PERIDEV_NET_ERROR 
PERIDEV_NET_ERROR UMXPERIDEVLIB_EXPORT umxPeriDev_scanNetTechnology(const PERIDEV_NET_TECH_TYPE type);
// Desc.: Connect with given network.
// Param: deviceName: DeviceName of a service ,passphrase(Password if it necessery)
// Return: PERIDEV_NET_ERROR
PERIDEV_NET_ERROR UMXPERIDEVLIB_EXPORT umxPeriDev_connectNetService(const char* deviceName, const char* passphrase);
// Desc.: Disconnect with given connected network.
// Param: deviceName: DeviceName of a service
// Return: PERIDEV_NET_ERROR
PERIDEV_NET_ERROR UMXPERIDEVLIB_EXPORT umxPeriDev_disconnectNetService(const char* deviceName);
// Desc.: Remove configuration with given network.
// Param: deviceName: DeviceName of a service
// Return: PERIDEV_NET_ERROR
PERIDEV_NET_ERROR UMXPERIDEVLIB_EXPORT umxPeriDev_removeNetService(const char* deviceName);
// Desc.: Get network state.
// Param: state: buffer to get network state
// Return: PERIDEV_NET_ERROR
PERIDEV_NET_ERROR UMXPERIDEVLIB_EXPORT umxPeriDev_getNetState(PERIDEV_NET_STATE* state);
// Desc.: Set IPv4 method, adress to the given network
// Param: deviceName(network device name), method(1:dhcp, 2:static)
// Return: PERIDEV_NET_ERROR
PERIDEV_NET_ERROR UMXPERIDEVLIB_EXPORT umxPeriDev_setNetIPv4(const char* deviceName, const char method,
	const char* address, const char* netmask, const char* gateway);
PERIDEV_NET_ERROR UMXPERIDEVLIB_EXPORT umxPeriDev_setNetIPv4ToFirstService(const char method,
	const char* address, const char* netmask, const char* gateway);
PERIDEV_NET_ERROR UMXPERIDEVLIB_EXPORT umxPeriDev_getNetIPv4ToFirstService(char *type, char *method, char* address, char* netmask, char* gateway);

/*-------------------- Backlight(LCD) --------------------*/
// * Caustion: Not supported on Android
// Desc.: Get LCD backlight brightness
// Param: value(Buffer of brightness)
// Return: 0 is success, other values is linux errno 
int UMXPERIDEVLIB_EXPORT umxPeriDev_getBacklightBrightness(unsigned char *value);
// Desc.: Set LCD backlight brightness
// Param: value(brightness 0 ~ 7)
// Return: 0 is success, other values is linux errno 
int UMXPERIDEVLIB_EXPORT umxPeriDev_setBacklightBrightness(const unsigned char value/*0~7*/);


/*-------------------- USB --------------------*/
// * Caustion: Not prepared on Android yet...
// Desc.: Set USB status callback function to know readable data or error
// Param: void (*usb_status_cb_f)(int,int)
// Return: 0 is success, other values is linux errno
int UMXPERIDEVLIB_EXPORT umxPeriDev_setUSBDataCB(usb_status_cb_f);
// Desc.: Read data from USB Host Device
// Param: buffer=data buffer to read, buffer_size=buffer size, *read_size=Return real read size
// Return: 0 is success, other values is linux errno
int UMXPERIDEVLIB_EXPORT umxPeriDev_readUSBData(char *buffer, const int buffer_size, int *read_size);
// Desc.: Write data to USB Host Device
// Param: data=data buffer to write, data_size=data size, *write_size=Return real writed size
// Return: 0 is success, other values is linux errno
int UMXPERIDEVLIB_EXPORT umxPeriDev_writeUSBData(const char *data, const int data_size, int *write_size);
// Desc.: Get USB device state
// Param: state: buffer to get USB device state
// Return: 0 is success, other values is linux errno
int UMXPERIDEVLIB_EXPORT umxPeriDev_getUSBDeviceState(PERIDEV_USB_DEVICE_STATE* state);


#ifdef __cplusplus
} // extern "C"
#endif

#endif /* __UMXPERIDEVLIB_H__ */
