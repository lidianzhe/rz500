#ifndef COMMAND_H
#define COMMAND_H

#include <Poco/Logger.h>

class Command
{
public:
    // FPGA Command Type
    enum CmdType  {
        CMD_FPGA_STATE =            0x01,
        CMD_FPGA_WIEGAND =          0x03,
        CMD_FPGA_MOTOR =            0x0A,
        CMD_GET_VERSION =           0x0F
    };
    // FPGA_State Type
    enum StateType  {
        STATE_STOP =                0x00,
        STATE_MOTION_DETECT =       0x01,
        STATE_OBJECT_DETECT =       0x02,
        STATE_IRIS_DETECT =         0x03,
        STATE_IRIS_CAPTURE =        0x04,
        STATE_DEBUG =               0x07
    };

	enum {CMD_SIZE = 64};
	enum {WIEGAND_MAX_SIZE = 34};
	enum MotorAction  {
		MOTOR_STOP  = 0x00,
        MOTOR_MOVE  = 0x01,
        MOTOR_ZERO  = 0x02,
        MOTOR_QUICK_ZERO  = 0x03
	};

    enum MotorMove {
        MOTOR_MOVE_DOWN = 0x01,
        MOTOR_MOVE_UP = 0x00
    };

    /*
    enum MotorPosition {
        MOTOR_POS_TOP = 792,
        MOTOR_POS_HIGH = 752, // -40 3.5 degree
        MOTOR_POS_ZERO = 512,
        MOTOR_POS_LOW = 327, // +40 3.5degree
        MOTOR_POS_BOTTOM = 287
    }; */

    enum MotorPosition {
        MOTOR_POS_TOP = 792,
        MOTOR_POS_HIGH = 752, // -40 3.5 degree
        MOTOR_POS_ZERO = 512,
        MOTOR_POS_LOW = 367, // +40 3.5degree
        MOTOR_POS_BOTTOM = 327
    };

	enum WiegandAction  {
		WIEGAND_WRITE	= 0x00,
		WIEGAND_READ	= 0x01,
		WIEGAND_SET		= 0x02,
		WIEGAND_GET		= 0x03
	};

    Command(Poco::Logger& logger);
    ~Command();

    void writeCmdBytes();

    void readCmdBytes(unsigned char *cmdBytes);

    bool setStopCmd(unsigned char  cmd);

    bool setMotionDetectCmd(unsigned char  cmd,
                             unsigned char  wideExpRange, unsigned char wideExpoCycle,
                             unsigned short wideCapX, unsigned short wideCapY,
                             unsigned short wideCapWidth, unsigned short wideCapHeight,
                             unsigned short wideExpX, unsigned short wideExpY,
                             unsigned short wideExpWidth, unsigned short wideExpHeight,
                             unsigned char  wideLedOnTarget, unsigned char wideLedOffTarget,
                             unsigned char  irRepeatNum, unsigned char ir1st,
                             unsigned char  ir2nd, unsigned char ir3rd,
                             unsigned char  ir4th, unsigned char motorUpDown,
                             unsigned short motorSteps                   );

    bool setObjectDetectCmd(unsigned char  cmd,
                             unsigned short narrLeftCapX, unsigned short narrLeftCapY,
                             unsigned short narrLeftCapWidth, unsigned short narrLeftCapHeight,
                             unsigned short narrLeftExpX, unsigned short narrLeftExpY,
                             unsigned short narrLeftExpWidth, unsigned short narrLeftExpHeight,
                             unsigned char  narrLeftLedOnTarget, unsigned char narrLeftLedOffTarget,
                             unsigned char narrLRExpRatio, unsigned short wideOnExpLimit,
                             unsigned short wideCapX, unsigned short wideCapY,
                             unsigned short wideCapWidth, unsigned short wideCapHeight,
                             unsigned short wideExpX, unsigned short wideExpY,
                             unsigned short wideExpWidth, unsigned short wideExpHeight,
                             unsigned char  wideLedOnTarget, unsigned char wideLedOffTarget,
                             unsigned char  irRepeatNum, unsigned char ir1st,
                             unsigned char  ir2nd, unsigned char ir3rd,
                             unsigned char  ir4th, unsigned char motorUpDown,
                             unsigned short motorSteps                   );

    bool setIrisDetectCmd(unsigned char  cmd,
                           unsigned short narrLeftCapX, unsigned short narrLeftCapY,
                           unsigned short narrLeftCapWidth, unsigned short narrLeftCapHeight,
                           unsigned short narrLeftExpX, unsigned short narrLeftExpY,
                           unsigned short narrLeftExpWidth, unsigned short narrLeftExpHeight,
                          unsigned short narrowLeftExposure,
                           //unsigned char  narrLeftLedOnTarget, unsigned char narrLeftLedOffTarget,
                           unsigned short narrRightCapX, unsigned short narrRightCapY,
                           unsigned short narrRightCapWidth, unsigned short narrRightCapHeight,
                           unsigned short narrRightExpX, unsigned short narrRightExpY,
                           unsigned short narrRightExpWidth, unsigned short narrRightExpHeight,
                          unsigned short narrowRightExposure,
                           //unsigned char  narrRightLedOnTarget, unsigned char narrRightLedOffTarget,
                           unsigned short wideCapX, unsigned short wideCapY,
                           unsigned short wideCapWidth, unsigned short wideCapHeight,
                           unsigned short wideExpX, unsigned short wideExpY,
                           unsigned short wideExpWidth, unsigned short wideExpHeight,
                           unsigned char  wideLedOnTarget, unsigned char wideLedOffTarget,
                           unsigned char  irRepeatNum, unsigned char ir1st,
                           unsigned char  ir2nd, unsigned char ir3rd,
                           unsigned char  ir4th, unsigned char motorUpDown,
                           unsigned short motorSteps,
                           unsigned short additionalGain = 0);

    bool setIrisCaptureCmd(unsigned char  cmd,
                           unsigned short narrLeftCapX, unsigned short narrLeftCapY,
                           unsigned short narrLeftCapWidth, unsigned short narrLeftCapHeight,
                           unsigned short narrLeftExpX, unsigned short narrLeftExpY,
                           unsigned short narrLeftExpWidth, unsigned short narrLeftExpHeight,
                           unsigned char  narrLeftLedOnTarget, unsigned char narrLeftLedOffTarget,
                           unsigned short narrRightCapX, unsigned short narrRightCapY,
                           unsigned short narrRightCapWidth, unsigned short narrRightCapHeight,
                           unsigned short narrRightExpX, unsigned short narrRightExpY,
                           unsigned short narrRightExpWidth, unsigned short narrRightExpHeight,
                           unsigned char  narrRightLedOnTarget, unsigned char narrRightLedOffTarget,
                           unsigned short wideCapX, unsigned short wideCapY,
                           unsigned short wideCapWidth, unsigned short wideCapHeight,
                           unsigned short wideExpX, unsigned short wideExpY,
                           unsigned short wideExpWidth, unsigned short wideExpHeight,
                           unsigned char  wideLedOnTarget, unsigned char wideLedOffTarget,
                           unsigned char  irRepeatNum, unsigned char ir1st,
                           unsigned char  ir2nd, unsigned char ir3rd,
                           unsigned char  ir4th, unsigned char motorUpDown,
                           unsigned short motorSteps                   );

    bool setDebugCmd(unsigned char  cmd,
                           unsigned short narrLeftCapX, unsigned short narrLeftCapY,
                           unsigned short narrLeftCapWidth, unsigned short narrLeftCapHeight,
                           unsigned short narrDebugExpVal,
                           unsigned short wideCapX, unsigned short wideCapY,
                           unsigned short wideCapWidth, unsigned short wideCapHeight,
                           unsigned short wideDebugExpVal,
                           unsigned char  irRepeatNum, unsigned char ir1st,
                           unsigned char  ir2nd, unsigned char ir3rd,
                           unsigned char  ir4th, unsigned char motorUpDown,
                           unsigned short motorSteps                   );

    bool setMotorCmd(unsigned char  cmd,
                      unsigned char motorMotorAction,
                      unsigned char motorUpDown,
                      unsigned short motorSteps,
                      unsigned char motorSpeedSetFlag,
                      unsigned short motorMinPps, unsigned short motorMaxPps );

    bool setGetVersionCmd(unsigned char  cmd );

    bool setWiegandCmd(unsigned char  cmd,
                        unsigned char  wiegandCmdType,
                        unsigned short wiegandInBits,
                        unsigned short wiegandInWidth,
                        unsigned short wiegandInInterval,
                        unsigned short wiegandOutBits,
                        unsigned short wiegandOutWidth,
                        unsigned short wiegandOutInterval,
                        unsigned char *wiegandOutData  );

    bool sendCmdBytes();
    bool receiveCmdBytes();
	
public:
	//
    unsigned char		_cmd, _state, _model;
    unsigned char		_cmdBytes[CMD_SIZE+1];
	// Capture Area, Exposure Area, Exposure TargetValue
    unsigned short		_narrLeftCapX, 		_narrLeftCapY;			//Narrow Left Capture Start Point
    unsigned short		_narrLeftCapWidth,		_narrLeftCapHeight;	//Narrow Left Capture W, H
    unsigned short		_narrRightCapX, 		_narrRightCapY;		//Narrow Right Capture Start Point
    unsigned short		_narrRightCapWidth,	_narrRightCapHeight;	//Narrow Right Capture W, H

    unsigned char       _narrLRExpRatio;
    unsigned short      _wideOnExpLimit;

    unsigned short		_wideCapX, 			_wideCapY;				//Wide Capture Start Point
    unsigned short		_wideCapWidth, 		_wideCapHeight;		//Wide Capture W, H
    unsigned short		_narrLeftExpX, 		_narrLeftExpY;			//Narrow Left Exposure Start Point
    unsigned short		_narrLeftExpWidth, 	_narrLeftExpHeight;	//Narrow Left Exposure W, H
    unsigned short		_narrRightExpX, 		_narrRightExpY;		//Narrow Right Exposure Start Point
    unsigned short		_narrRightExpWidth,	_narrRightExpHeight;	//Narrow Right Exposure W, H
    unsigned short		_wideExpX, 			_wideExpY;				//Wide Exposure Start Point
    unsigned short		_wideExpWidth,			_wideExpHeight;		//Wide Exposure W, H
    unsigned short      _narrowLeftExposure, _narrowRightExposure;
    unsigned char		_narrLeftLedOnTarget,	_narrLeftLedOffTarget;	//Narrow Left IRLED-ON/OFF Target Bright
    unsigned char		_narrRightLedOnTarget,	_narrRightLedOffTarget;//Narrow Right IRLED-ON/OFF Target Bright
    unsigned char		_wideLedOnTarget,		_wideLedOffTarget;		//Wide IRLED-ON/OFF Target Bright
    unsigned char		_wideExpRange, 		_wideExpoCycle;		//Wide Exposure Randge & Cycle
    unsigned short		_narrDebugExpVal, 		_wideDebugExpVal;		//Exposure Value in debug
	// LED Control 
    unsigned char		_irRepeatNum;									//Max Repeat Number = 4;
    unsigned char		_ir1st, _ir2nd, _ir3rd, _ir4th;				//IRLED
	// Motor Control
    unsigned char		_motorMotorAction;
    unsigned char		_motorUpDown, _motorSpeedSetFlag;
    unsigned short		_motorSteps, _motorMinPps, _motorMaxPps;
	// Firmware Version
    unsigned char		_fwMajor, _fwMinor;
	// Wiegand
    unsigned char		_wiegandCmdType;	//_wiegandCmdWrite, _wiegandCmdRead, _wiegandCmdSet, _wiegandCmdGet;
    unsigned short		_wiegandInBits, _wiegandInWidth, _wiegandInInterval, _wiegandOutBits, _wiegandOutWidth, _wiegandOutInterval;
    unsigned char		_wiegandOutData[WIEGAND_MAX_SIZE+1], _wiegandInData[WIEGAND_MAX_SIZE+1];

    static int          s_motorPos;

private:
    Poco::Logger& _logger;
    static Poco::Mutex s_mutex;
};

#endif // COMMAND_H
