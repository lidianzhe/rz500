#ifndef CONFIGURATIONPROPERTIES_H
#define CONFIGURATIONPROPERTIES_H

// Device
#define UMX_DEV_USERPOSITIONINTERFACE   "launcher.device.hidden.cameratype"
#define UMX_DEV_USERPOSITIONINTERFACE_N "launcher.device.config.userpositioninterface"
#define UMX_DEV_ENROLNOTICETIMEOUT      "launcher.device.hidden.noticestimeout"
#define UMX_DEV_ENROLNOTICETIMEOUT_N    "launcher.device.config.enrolnoticetimeout"
#define UMX_DEV_MOTIONWAITTIMEOUT       "launcher.device.hidden.recognitionrestart"
#define UMX_DEV_MOTIONWAITTIMEOUT_N     "launcher.device.config.motiondetectionwaittime"
#define UMX_DEV_MOTION_ENABLE           "launcher.device.hidden.autorestart"
#define UMX_DEV_MOTION_ENABLE_N         "launcher.device.config.motiondetection"
#define UMX_DEV_DEBUG_ENABLE            "launcher.device.hidden.debug"
#define UMX_DEV_DEBUG_ENABLE_N          "launcher.device.config.debug"

#define UMX_DEV_SECURITYLEVEL           "launcher.device.bio.securitylevel"
#define UMX_DEV_ENROLIRISUSABLEAREA     "umx.camera.enrol.MinimumUsableIrisArea"
#define UMX_DEV_ENROLIRISUSABLEAREA_N   "launcher.device.bio.iris.enrolminusablearea"
#define UMX_DEV_RECOGFALSEACCEPTRATE    "umx.iris.recog.EyeMatchThreshold"
#define UMX_DEV_RECOGFALSEACCEPTRATE_N  "launcher.device.bio.iris.recogfalseacceptrate"
#define UMX_DEV_MINDISTANCE             "launcher.device.bio.iris.mindistance"
#define UMX_DEV_FASTRECOGMODE_ENABLE    "launcher.device.bio.iris.fastrecogmode"
#define UMX_DEV_RECOGEITHEREYE_ENABLE   "umx.camera.recog.eitherEye"
#define UMX_DEV_RECOGEITHEREYE_ENABLE_N "launcher.device.bio.iris.recogeithereye"
#define UMX_DEV_ENROLEITHEREYE_ENABLE   "umx.camera.enrol.eitherEye"
#define UMX_DEV_ENROLEITHEREYE_ENABLE_N "launcher.device.bio.iris.enroleithereye"

#define UMX_DEV_FAKEFACE_ENABLE             "launcher.device.bio.face.fakeface"
#define UMX_DEV_FACECOLORCORRECTION_ENABLE  "launcher.device.bio.face.facecolorcorrection"

#define UMX_DEV_SPEAKERVOLUME         "launcher.device.volume.devicevolume"
#define UMX_DEV_MICVOLUME             "launcher.device.volume.micvolume"

#define UMX_DEV_DATETIME_TIMESYNC     "launcher.device.date.timesync"

#define UMX_DEV_DOOR_RELAY            "launcher.device.door.relay"
#define UMX_DEV_DOOR_RELAYID          "launcher.device.door.relayid"
#define UMX_DEV_DOOR_DRIVENBY         "launcher.device.door.drivenevent"
#define UMX_DEV_DOOR_DURATION         "launcher.device.door.duration"
#define UMX_DEV_DOOR_RTE              "launcher.device.door.rte"
#define UMX_DEV_DOOR_RTETYPE          "launcher.device.door.rtetype"
#define UMX_DEV_DOOR_DOORSENSOR       "launcher.device.door.doorsensor"
#define UMX_DEV_DOOR_DOORSENSORTYPE   "launcher.device.door.doorsensortype"
#define UMX_DEV_DOOR_HELDOPENPERIOD   "launcher.device.door.helpopenperiod"
#define UMX_DEV_DOOR_LOCKTIME         "launcher.device.door.locktime"
#define UMX_DEV_DOOR_UNLOCKTIME       "launcher.device.door.unlocktime"
#define UMX_DEV_DOOR_TAMPER           "launcher.device.door.tamper"

#define UMX_DEV_DEVINFO_DEVICENAME          "launcher.device.deviceinfo.devicename"
#define UMX_DEV_DEVINFO_MODEL               "launcher.device.deviceinfo.model"
#define UMX_DEV_DEVINFO_FWVERSION           "launcher.device.deviceinfo.fwversion"
#define UMX_DEV_DEVINFO_FWVERSION_N         "launcher.device.deviceinfo.firmwarefile"
#define UMX_DEV_DEVINFO_DEVICEID            "launcher.device.deviceinfo.deviceid"
#define UMX_DEV_DEVINFO_DEVICEID_N          "launcher.device.deviceinfo.serialnumber"
#define UMX_DEV_DEVINFO_KERNELVERSION       "launcher.device.deviceinfo.kernelversion"
#define UMX_DEV_DEVINFO_HWVERSION           "launcher.device.deviceinfo.hwversion"
#define UMX_DEV_DEVINFO_MAC                 "launcher.device.deviceinfo.mac"
#define UMX_DEV_DEVINFO_BOOTVERSION         "launcher.device.deviceinfo.bootversion"
#define UMX_DEV_DEVINFO_ROOTVERSION         "launcher.device.deviceinfo.rootversion"
#define UMX_DEV_DEVINFO_RECOVERYVERSION     "launcher.device.deviceinfo.recoveryversion"
#define UMX_DEV_DEVINFO_APPLICATIONVERSION  "launcher.device.deviceinfo.applicationversion"
#define UMX_DEV_DEVINFO_FPGAVERSION         "launcher.device.deviceinfo.fpgaversion"

#define UMX_DEV_SET_CMS_DEVICENAME  "cmsenv set devicename"
#define UMX_DEV_GET_CMS_DEVICENAME  "cmsenv get devicename"
#define UMX_DEV_GET_CMS_MODEL       "cmsenv get model"
#define UMX_DEV_GET_CMS_OTAVER      "cmsenv get otaver"
#define UMX_DEV_GET_CMS_SERIAL      "cmsenv get serial"
#define UMX_DEV_GET_CMS_KERNELVER   "cmsenv get kernelver"
#define UMX_DEV_GET_CMS_HWVER       "cmsenv get hwver"
#define UMX_DEV_GET_CMS_ETHADDR     "cmsenv get ethaddr"
#define UMX_DEV_GET_CMS_BOOTVER     "cmsenv get bootver"
#define UMX_DEV_GET_CMS_ROOTVER     "cmsenv get rootver"
#define UMX_DEV_GET_CMS_RECOVERYVER "cmsenv get recoveryver"
#define UMX_DEV_GET_CMS_APPVER      "cmsenv get appver"
#define UMX_DEV_GET_CMS_FPGAVER     "cmsenv get fpgaver"

#define UMX_DEV_INTERPHONE_ENABLE     "launcher.device.interphone.enable"
#define UMX_DEV_INTERPHONE_IPADDRESS  "launcher.device.interphone.ipaddress"

#define UMX_DEV_POWERLINEFREQUENCY    "launcher.device.camera.powerlinefrequency"

#define E_DEV_USER_POSITION_INTERFACE_MIN 0
#define E_DEV_USER_POSITION_INTERFACE_MAX 1

#define E_DEV_ENROL_NOTICE_TIMEOUT_MIN    0
#define E_DEV_ENROL_NOTICE_TIMEOUT_MAX    5

#define E_DEV_MOTION_WAIT_TIMEOUT_MIN     0
#define E_DEV_MOTION_WAIT_TIMEOUT_MAX     10

#define E_DEV_SECURITY_LEVEL_MIN          0
#define E_DEV_SECURITY_LEVEL_MAX          4

const static double dev_enrol_usable_iris_area_list[] =
{
  50.0, // %
  60.0, // %
  70.0, // %
  80.0, // %
  90.0  // %
};
#define E_DEV_ENROL_USABLE_IRIS_AREA_MIN 0
#define E_DEV_ENROL_USABLE_IRIS_AREA_MAX 4

const static double dev_recog_false_accept_rate_list[] =
{
  0.33, // 10E-5
  0.3,  // 10E-6
  0.26, // 10E-7
  0.23, // 10E-8
  0.2,  // 10E-9
  0.16, // 10E-10
  0.13, // 10E-11
  0.1,  // 10E-12
  0.06, // 10E-13
  0.03  // 10E-14
};
#define E_DEV_RECOG_FALSE_ACCEPT_RATE_MIN 0
#define E_DEV_RECOG_FALSE_ACCEPT_RATE_MAX 9

#define E_DEV_MIN_DISTACE_MIN     30
#define E_DEV_MIN_DISTACE_MAX     35

#define E_DEV_SPAEKER_VOLUME_MIN  0
#define E_DEV_SPAEKER_VOLUME_MAX  10

#define E_DEV_MIC_VOLUME_MIN      0
#define E_DEV_MIC_VOLUME_MAX      10

#define E_DEV_DOOR_RELAY_MIN      0
#define E_DEV_DOOR_RELAY_MAX      2

#define E_DEV_DOOR_DRIVEN_BY_MIN  0
#define E_DEV_DOOR_DRIVEN_BY_MAX  4

#define E_DEV_DOOR_DURATION_MIN   0
#define E_DEV_DOOR_DURATION_MAX   10

#define E_DEV_DOOR_RTE_GPIO_MIN   0
#define E_DEV_DOOR_RTE_GPIO_MAX   2

#define E_DEV_DOOR_RTE_TYPE_MIN   0
#define E_DEV_DOOR_RTE_TYPE_MAX   1

#define E_DEV_DOOR_SENSOR_GPIO_MIN 0
#define E_DEV_DOOR_SENSOR_GPIO_MAX 2

#define E_DEV_DOOR_SENSOR_TYPE_MIN 0
#define E_DEV_DOOR_SENSOR_TYPE_MAX 1

#define E_DEV_DOOR_HELD_OPEN_PERIOD_MIN 0
#define E_DEV_DOOR_HELD_OPEN_PERIOD_MAX 600

#define E_DEV_DOOR_LOCK_TIME_MIN      0
#define E_DEV_DOOR_LOCK_TIME_MAX      1

#define E_DEV_DOOR_UNLOCK_TIME_MIN    0
#define E_DEV_DOOR_UNLOCK_TIME_MAX    1

#define E_DEV_POWERLINE_FREQUENCY_MIN 0
#define E_DEV_POWERLINE_FREQUENCY_MAX 1

// Network
#define UMX_NET_TCPIP_LANTYPE             "launcher.network.tcpip.lantype"
#define UMX_NET_TCPIP_DHCP_ENABLE         "launcher.network.tcpip.dhcp"
#define UMX_NET_TCPIP_IPADDRESS           "launcher.network.tcpip.ipaddress"
#define UMX_NET_TCPIP_GATEWAY             "launcher.network.tcpip.gateway"
#define UMX_NET_TCPIP_SUBNET              "launcher.network.tcpip.subnet"

#define UMX_NET_SERVER_ENABLE             "launcher.network.server.useserver"
#define UMX_NET_SERVER_IPADDRESS          "launcher.network.server.serverip"
#define UMX_NET_SERVER_PORT               "launcher.network.server.port"

#define UMX_NET_SERVER_MANUALCMD_ENABLE   "launcher.network.server.manualMode"
#define UMX_NET_SERVER_MANUALCMD_ENABLE_N "launcher.network.server.manualcommand"
#define UMX_NET_SERVER_SERVERAUTH         "launcher.network.server.auth"
#define UMX_NET_SERVER_SERVERAUTH_N       "launcher.network.server.serverauthentication"

#define UMX_NET_SERIAL_RS485PC            "launcher.network.serial.rs485pc"
#define UMX_NET_SERIAL_RS485NET           "launcher.network.serial.rs485net"
#define UMX_NET_SERIAL_RS232              "launcher.network.serial.rs232"

#define UMX_NET_USBMEMORY_ENABLE          "launcher.network.usbmemory.enable"

#define UMX_NET_WIEGAND_ENABLE            "launcher.network.wiegand.enable"
#define UMX_NET_WIEGAND_BITS              "launcher.network.wiegand.bits"
#define UMX_NET_WIEGAND_IN_BITS           "launcher.network.wiegand.in.bits"
#define UMX_NET_WIEGAND_IN_PULSEWIDTH     "launcher.network.wiegand.in.pulse.width"
#define UMX_NET_WIEGAND_IN_PULSEINTERVAL  "launcher.network.wiegand.in.pulse.interval"
#define UMX_NET_WIEGAND_OUT_BITS          "launcher.network.wiegand.out.bits"
#define UMX_NET_WIEGAND_OUT_PULSEWIDTH    "launcher.network.wiegand.out.pulse.width"
#define UMX_NET_WIEGAND_OUT_PULSEINTERVAL "launcher.network.wiegand.out.pulse.interval"

#define E_NET_TCPIP_LAN_TYPE_MIN  0
#define E_NET_TCPIP_LAN_TYPE_MAX  1

#define E_NET_SERVER_SERVERAUTH_MIN   0
#define E_NET_SERVER_SERVERAUTH_MAX   2

#define E_NET_SERIAL_RS485PC_MIN  0
#define E_NET_SERIAL_RS485PC_MAX  5

#define E_NET_SERIAL_RS485NET_MIN 0
#define E_NET_SERIAL_RS485NET_MAX 2

#define E_NET_SERIAL_RS232_MIN    0
#define E_NET_SERIAL_RS232_MAX    5

// Display
#define UMX_DIS_VOICEINSTRUCTION            "launcher.display.voiceinstruction"
#define UMX_DIS_CENTURALTIMEDISPLAY_ENABLE  "launcher.display.centraltimedisplay"
#define UMX_DIS_MENUTIMEOUT                 "launcher.display.menutimeout"
#define UMX_DIS_POPUPTIMEOUT                "launcher.display.popuptime"
#define UMX_DIS_BACKLIGHTTIMEOUT            "launcher.display.backlighttimeout"
#define UMX_DIS_DATEDISPLAY                 "launcher.display.datedisplay"
#define UMX_DIS_LANGUAGE                    "launcher.display.language"

#define UMX_DIS_SCREENSAVER_ENABLE        "launcher.display.screensaver.use"
#define UMX_DIS_SCREENSAVER_ENABLE_N      "launcher.display.screensaver"
#define UMX_DIS_SCREENSAVER_TIMEDISPLAY   "launcher.display.screensaver.timedisplay"
#define UMX_DIS_SCREENSAVER_TIMEDISPLAY_N "launcher.display.screensaver.timedisplayposition"
#define UMX_DIS_SCREENSAVER_WAITTIME      "launcher.display.screensaver.waittime"

#define E_DIS_VOICEINSTRUCTION_MIN  0
#define E_DIS_VOICEINSTRUCTION_MAX  3

#define E_DIS_MENU_TIMEOUT_MIN      0
#define E_DIS_MENU_TIMEOUT_MAX      4

#define E_DIS_SCREENSAVER_TIMEDISP_MIN      0
#define E_DIS_SCREENSAVER_TIMEDISP_MAX      1

#define E_DIS_SCREENSAVER_WAITTIME_MIN      0
#define E_DIS_SCREENSAVER_WAITTIME_MAX      4

const static int dis_popup_timeout_list[] =
{
  1,
  2,
  3,
  4,
  5
};
#define E_DIS_POPUP_TIMEOUT_MIN     0
#define E_DIS_POPUP_TIMEOUT_MAX     4

#define E_DIS_BACKLIGHT_TIMEOUT_MIN 0
#define E_DIS_BACKLIGHT_TIMEOUT_MAX 6

#define E_DIS_DATE_DIPLAY_MIN       0
#define E_DIS_DATE_DIPLAY_MAX       1

#define E_DIS_LANGUAGE_MIN          0
#define E_DIS_LANGUAGE_MAX          6

// Authentication
#define UMX_AUTH_STARTMODE        "launcher.auth.mode.start"
#define UMX_AUTH_COMBINATIONSTEP1 "launcher.auth.mode.combi.step1"
#define UMX_AUTH_TA_ENABLE        "launcher.auth.ta.enable"
#define UMX_AUTH_TA_MANUALORDER   "launcher.auth.ta.manual"
#define UMX_AUTH_TAMODE_MODE      "launcher.auth.tamode.mode"
#define UMX_AUTH_TAMODE_VALUE     "launcher.auth.tamode.value"

#define UMX_AUTH_ADMINPASSWORD_ENABLE     "launcher.auth.adminpass.enable"
#define UMX_AUTH_ADMINPASSWORD_ENABLE_N   "launcher.auth.adminpassword"          // hidden
#define UMX_AUTH_ADMINPASSWORD_PASSWORD   "launcher.auth.adminpass.passwd"
#define UMX_AUTH_ADMINPASSWORD_PASSWORD_N "launcher.auth.adminpassword.password" // hidden

const static int auth_start_mode_list[] =
{
  1,  // bio
  2,  // id
  3   // card
};
#define E_AUTH_START_MODE_MIN             0
#define E_AUTH_START_MODE_MAX             2

#define E_AUTH_COMBINATION_STEP1_MODE_MIN 0
#define E_AUTH_COMBINATION_STEP1_MODE_MAX 4

#define E_AUTH_TA_MANUAL_ORDER_MIN        0
#define E_AUTH_TA_MANUAL_ORDER_MAX        2

#define E_AUTH_TAMODE_MODE_MIN            0
#define E_AUTH_TAMODE_MODE_MAX            3

const static int auth_tamode_value_list[] =
{
  1,  // in
  2,  // out
  3,  // leave
  4   // return
};
#define E_AUTH_TAMODE_VALUE_MIN 0
#define E_AUTH_TAMODE_VALUE_MAX 3

// Mode
#define UMX_MOD_FACEDETECTION             "launcher.mode.operation.facedetection"
#define UMX_MOD_FACEDETECTION_N           "launcher.mode.operation.faceimagelog"
#define UMX_MOD_INDIVIDUALAUTHENTICATION  "launcher.mode.operation.individualmode"
#define UMX_MOD_DUALAUTHENTICATION        "launcher.mode.operation.dualauthentication"
#define UMX_MOD_MATCHTIMEOUT              "launcher.mode.operation.matchtimeout"
#define UMX_MOD_CARDMODE                  "launcher.mode.operation.cardmode"

#define UMX_MOD_CAMERAEVENT_ENABLE        "launcher.mode.operation.cameraevent"

#define UMX_MOD_CONTINUOUSRECOGNITION_ENABLE    "launcher.mode.operation.continuerecog"
#define UMX_MOD_CONTINUOUSRECOGNITION_ENABLE_N  "launcher.mode.operation.continuousrecognition"
#define UMX_MOD_WIEGAND_OUTPUTTYPE              "launcher.mode.wiegand.outputtype"

#define E_MODE_DUAL_AUTH_MIN      0
#define E_MODE_DUAL_AUTH_MAX      1

#define E_MODE_MATCH_TIMEOUT_MIN  0
#define E_MODE_MATCH_TIMEOUT_MAX  5

#define E_MODE_CARD_MODE_MIN      0
#define E_MODE_CARD_MODE_MAX      1

#define E_MODE_WIEGAND_OUTPUTTYPE_MIN      0
#define E_MODE_WIEGAND_OUTPUTTYPE_MAX      2

#define E_CONFIG_DISABLE  0
#define E_CONFIG_ENABLE   1

#define E_CONFIG_FALSE    false
#define E_CONFIG_TRUE     true

#define E_CONFIG_SET_ERROR  0
#define E_CONFIG_SET_INT    1
#define E_CONFIG_SET_DOUBLE 2
#define E_CONFIG_SET_BOOL   3

#endif // CONFIGURATIONPROPERTIES_H
