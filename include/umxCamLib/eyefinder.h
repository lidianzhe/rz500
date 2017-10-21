#ifndef EYEFINDER_H
#define EYEFINDER_H

#include "labeling.h"
#include "umximage.h"
#include "stereo.h"

#include <Poco/Logger.h>
#include <Poco/Mutex.h>
#include "Poco/FileChannel.h"
#include "Poco/AutoPtr.h"

class MainProc;
class Cluster;

class EyeFinder
{
public:

    enum SizeMode {
        FULL_SIZE_MODE = 0,
        SUB2_SIZE_MODE = 1,
        SUB4_SIZE_MODE = 2,
        WIDE_SIZE_MODE = 3
    };

    enum {
        SM_IMAGE_WIDTH = 640, // SM: Single Monitor
        SM_IMAGE_HEIGHT = 480,
        SM_IMAGE_SIZE = SM_IMAGE_WIDTH*SM_IMAGE_HEIGHT,
        MAX_NUM_OF_Z = 30, // (_maxZMM - _minZMM)/_deltaZMM
        IRIS_DIV = 72
    };

    enum Resolution {
        RESOL_FULL = 0,
        RESOL_SUB2 = 1,
        RESOL_SUB4 = 2
    };

    enum {
        MIN_PUPIL_RADIUS = 2,  // at 425mm, min pupil radius = 1mm
        MAX_PUPIL_RADIUS = 31, // at 320mm, max pupil radius = 5mm
        MIN_IRIS_RADIUS = 10,
        MAX_IRIS_RADIUS = 46, // at 320mm, max iris radius = 8mm
        MIN_SPEC_VALUE = UMXImage::MIN_SPEC_VALUE,
        MAX_SPEC_SIZE_320 = 45,
        MIN_SPEC_SIZE_320 = 4,
        MAX_SPEC_SIZE_480 = 30,
        MIN_SPEC_SIZE_480 = 2,
        IRIS_RADIUS_VARIATION2 = 3, // 16mm lens
        MIN_EYE_X_SEPARATION = 100,
        MAX_EYE_Y_SEPARATION = 50,

        MIN_PUPIL_DIFF = 14,
        MIN_IRIS_DIFF = 4,

        MIN_HIST_CNT = 10,

        MIN_PUPIL_SCLERA_DIFF = 20,
        MAX_PUPIL_VALUE = 85
    };

    enum FindEyesReturn {
        FE_OK = 128,
        FE_DIST_OUT_OF_RANGE = 129,
        FE_CANNOT_FIND_PUPIL = 130,
        FE_CANNOT_FIND_IRIS = 131,
        FE_CANNOT_FIND_EYES = 132
    };

    EyeFinder(Poco::Logger& logger,  STEREO& stereo, MainProc *mainProc,
              int camera, int resol, int width, int height);
    ~EyeFinder();

    void setupArrays();
    void initStats();
    void updatePupilirisStats(float pupilRadius, float irisRadius, int curZMM);
    float findProbabilityPupiliris(float pupilRadius, float irisRadius, int curZMM);
    int findEye(unsigned char *image, unsigned char *specImage, int whichEye, int ledKind, int curZMM,
                int centerXShift, int centerYShift,
                int x1, int y1, int x2, int y2,
                int startPupilRadius = -1, int endPupilRadius = -1,
                int startIrisRadius = -1, int endIrisRadius = -1);
    int checkPupilIris(Cluster *fcluster, int pupilCenterX, int pupilCenterY);
    float getEyenessScore(Cluster *fcluster);

    int _sizeMode;

    // Image variables
    unsigned char *_orgImage; // 640x480 not allocated
    unsigned char *_pupilChecked; // 640x480 not allocated
    int _width, _height, _imageSize;
    int _ledKind;
    int _curZMM;
    int _eyeX1, _eyeY1, _eyeX2, _eyeY2;

    Labeling *_whiteLabeling;
    int32_t *_whiteLabelImage;  // specular images, 640x480
    Cluster *_eyeCluster;
    std::deque<Cluster *> _selectedClusterList;
    std::deque<Cluster *> *_fClusterList;

    int _minZMM, _maxZMM, _middleZMM;

    float _minIrisRadiusMM, _maxIrisRadiusMM;
    float _minPupilRadiusMM, _maxPupilRadiusMM;
    int _maxIrisRadius01MM, _maxPupilRadius01MM;
    float _convertDistToPixelPerMM;
    float _convertDistToPixelPerMMWide;
    float _convertDistToPixelPerMMNarrow;
    float _pupilSearchRadiusMM;
    float _irisSearchRadiusMM, _irisMinThicknessMM;

    int _minPupilSearchRadius, _maxPupilSearchRadius;
    int _curPupilSearchRadius;
    int _curIrisSearchRadius;
    int _curIrisMinThickness;

    int _minClusterSize, _maxClusterSize;

    // eye search
    int _maxNumOfZ;
    int _numOfIrisAngles, _minIrisRadiusAll, _maxIrisRadiusAll;
    int _minPupilRadiusAll, _maxPupilRadiusAll;
    int _curZ, _deltaZMM;
    int _numOfPupilDiv, _numOfPupilDiv2;
    int *_pupilArray;
    int _minPupilRadius[MAX_NUM_OF_Z], _maxPupilRadius[MAX_NUM_OF_Z]; // float pixel
    int _numOfPupilRadius[MAX_NUM_OF_Z];
    int *_pupilSum, *_pupilCnt, *_pupilSum2;
    int *_pupilHist, _histCnt;

    int *_irisArray;
    int _minIrisRadius[MAX_NUM_OF_Z], _maxIrisRadius[MAX_NUM_OF_Z];
    int _numOfIrisRadius[MAX_NUM_OF_Z];
    //int _drIrisPixel[MAX_NUM_OF_Z];
    int *_irisRSum, *_irisRCnt;
    int *_irisRSum2;
    int *_irisLSum, *_irisLCnt;
    int *_irisLSum2;
    int *_irisHist;
    int *_irisValue, *_irisValue2;

    int _specPF[4], _specNF[8];

    int _latestPupilCenterX;
    int _latestPupilCenterY;
    int _latestPupilRadius;
    int _latestIrisCenterX;
    int _latestIrisCenterY;
    int _latestIrisRadius;

    int _specCenterX, _specCenterY;

    int _startPupilRadius, _endPupilRadius;
    int _startIrisRadius, _endIrisRadius;

    int _startAngleIndexR, _endAngleIndexR, _endScanIndexR;
    int _startAngleIndexL, _endAngleIndexL, _endScanIndexL;
    int _numOfScanAngles, _scanAngleIndexAmount;

    float _minSpecRadiusMM, _maxSpecRadiusMM;
    int _minSpecRadius, _maxSpecRadius;
    int _pupilStartM, _pupilEndM, _irisStartM, _irisEndM;

    float _minPupilDiffRatio, _minIrisDiffRatio;

    int _newPupilCenterX, _newPupilCenterY, _newPupilRadius;
    int _newIrisCenterX, _newIrisCenterY, _newIrisRadius;
    int _irisPartR, _irisPartL;

    float _pupilInsideAvg, _pupilOutsideAvg;
    float _pupilInsideVar, _pupilOutsideVar;
    float _pupilScore, _irisScore;
    float _irisInsideAvg, _irisOutsideAvg;
    float _irisInsideVar, _irisOutsideVar;

    int _histPupil[256], _histIris[256], _histSclera[256];
    int _histPupilCnt, _histIrisCnt, _histScleraCnt;

private:
    Poco::Logger& _logger;
    STEREO& _stereo;
    MainProc *_mainProc;
    int _camera;

};

#endif // EYEFINDER_H
























