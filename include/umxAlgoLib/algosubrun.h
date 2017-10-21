#ifndef ALGOSUBRUN_H
#define ALGOSUBRUN_H
#include <Poco/Logger.h>
#include <Poco/Mutex.h>
#include <Poco/Condition.h>
#include <Poco/Runnable.h>
#include "umxAlgoGlobal.h"
#include "umxCommonLib/umxCommon.h"

#define UMXCAM_LEFT_EYE                            (1<<0)
#define UMXCAM_RIGHT_EYE                           (1<<1)
#define UMXCAM_BOTH_EYES                           (UMXCAM_LEFT_EYE | UMXCAM_RIGHT_EYE)
#define UMXCAM_EITHER_EYE                          (1<<2 | UMXCAM_BOTH_EYES)

class AlgoSubRun : public Poco::Runnable
{
public:
    AlgoSubRun(Poco::Logger& _logger, void*, long threadNo, long maxThreadNo);
    ~AlgoSubRun();

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
        unsigned char _targetFeature[UMXALGO_IRIS_MAX_TEMPLATE_SIZE];
    };

    void run();
    void abort();
    void pause(bool flag);
    void exec();
    int irisIdentify(bool dbSearch, int whichEye, std::vector<IrisIdentifyInfo>* retVerifyInfoList, unsigned char *leftIrisTemplate, int templateSize, std::string uuid, bool duplicate);

private:
    Poco::Logger& _logger;
    void* _parent;
    bool _abort;
    long _threadNo;
    long _maxThreadNo;

public:
    std::vector<UMXALGO_IRIS_GET_TEMPLATE*> _requestBuffer;
    Poco::Mutex _mutexRequestBuffer;

    std::vector<UMXALGO_IRIS_IDENTIFY_INFO*> _requestIdentifyBuffer;
    Poco::Mutex _mutexRequestIdentifyBuffer;

    std::vector<UMXCommon::SubjectData>* _iris;
    //Poco::Mutex* _irisMutex;

    bool _pause;
    int _status;
};

#endif // ALGOSUBRUN_H
