#ifndef CLUSTER_H
#define CLUSTER_H

#include "point.h"
#include "pointf.h"
#include "rect.h"
#include "clusterpoint.h"
#include <deque>

#define MAX_NUM_OF_CLUSTER_POINT 307200 // 640*480

class Cluster
{
public:
	enum {NO_CLUSTER= 0};
	enum {MAX_SPEC_AREA = 180};
	enum {MAX_CLUSTER_ID = 8192,
		  MAX_BOUNDARY_LAYER = 3};

	enum {SPEC_ON_EYE = 1,
		  SPEC_ON_GLASS = 2,
		  SATURATE_ON_SKIN = 3,
		  UNKNOWN = 4};

public:
    Cluster();
    Cluster(Cluster *cluster);

    void initialize();
    void addPoint(int i, int j, unsigned char value);
    bool getClusterInfo(int x1, int y1, int x2, int y2);
    int getNeighborMin();

    float getScore();
    bool findCluster(signed short clusterID, int threshold, int maxSize);
    static int getOtsuThreshold(int *hist, int size);

    /////////////////////////////////////////////////////////////////////

    int type() {return _type;}
    void setType (int type) {_type = type;}

    unsigned char *image() {return _image;}
    void setImage(unsigned char *image) {_image = image;}

    signed short *clusterImage() {return _clusterImage;}
    void setClusterImage(signed short *clusterImage) {_clusterImage = clusterImage;}

    int width() {return _width;}
    void setWidth (int width) {_width = width;}

    int height() {return _height;}
    void setHeight (int height) {_height = height;}

    float score() {return _score;}
    void setScore (float score) {_score = score;}

    int x1() {return _x1;}
    void setX1 (int x1) {_x1 = x1;}

    int x2() {return _x2;}
    void setX2 (int x2) {_x2 = x2;}

    int y1() {return _y1;}
    void setY1 (int y1) {_y1 = y1;}

    int y2() {return _y2;}
    void setY2 (int y2) {_y2 = y2;}

    int irisCenterX() {return _irisCenterX;}
    void setIrisCenterX (int irisCenterX) {_irisCenterX = irisCenterX;}

    int irisCenterY() {return _irisCenterY;}
    void setIrisCenterY (int irisCenterY) {_irisCenterY = irisCenterY;}

    int irisRadius() {return _irisRadius;}
    void setIrisRadius (int irisRadius) {_irisRadius = irisRadius;}

    float pupilScore() {return _pupilScore;}
    void setPupilScore (float pupilScore) {_pupilScore = pupilScore;}

    int pupilCenterX() {return _pupilCenterX;}
    void setPupilCenterX (int pupilCenterX) {_pupilCenterX = pupilCenterX;}

    int pupilCenterY() {return _pupilCenterY;}
    void setPupilCenterY (int pupilCenterY) {_pupilCenterY = pupilCenterY;}

    int pupilRadius() {return _pupilRadius;}
    void setPupilRadius (int pupilRadius) {_pupilRadius = pupilRadius;}

    float centerXShift() {return _centerXShift;}
    void setCenterXShift (float centerXShift) {_centerXShift = centerXShift;}

    float thirdBondaryAvg() {return _thirdBondaryAvg;}

    float scleraIntensity() {return _scleraIntensity;}
    void setScleraIntensity (float scleraIntensity) {_scleraIntensity = scleraIntensity;}

    float irisIntensity() {return _irisIntensity;}
    void setIrisIntensity (float irisIntensity) {_irisIntensity = irisIntensity;}

	// Use the following settings
    void setImagesAndSize(unsigned char *image, signed short *clusterImage, int width, int height) {
        _image = image; _clusterImage = clusterImage; _width = width; _height = height;
	}
	void setRegion(int x1, int y1, int x2, int y2) {
        _x1 = x1; _y1 = y1; _x2 = x2; _y2 = y2;
	}

    int clusterID() {return _clusterID;}
    void setClusterID (int clusterID) {_clusterID = clusterID;}

    int size() {return _size;}

    PointF center() {return _center;}

    PointF xyPos() {return _xyPos;}
    void setXyPos(const PointF &xyPos) {_xyPos = xyPos;}

    float distance() {return _distance;}
    void setDistance (float distance) {_distance = distance;}

    Point seed() {return _seed;}
    void setSeed (const Point &seed) {_seed = seed;}

    Rect boundingBox() {return _boundingBox;}

    Rect searchBox() {return _searchBox;}
    void setSearchBox(const Rect &searchBox) {_searchBox = searchBox;}

    Point faceClusterCenter() {return _faceClusterCenter;}
    void setFaceClusterCenter (const Point &faceClusterCenter) {_faceClusterCenter = faceClusterCenter;}

    Point eyeClusterCenter() {return _eyeClusterCenter;}
    void setEyeClusterCenter (const Point &eyeClusterCenter) {_eyeClusterCenter = eyeClusterCenter;}

    std::deque<int> xList() {return _xList;}
    std::deque<int> yList() {return _yList;}

    Cluster *pairCluster() {return _pairCluster;}
    void setPairCluster(Cluster *pairCluster) {_pairCluster = pairCluster;}

    int pupilValue() {return _pupilValue;}
    void setPupilValue (int pupilValue) {_pupilValue = pupilValue;}

    bool isScleraSaturated() {return _isScleraSaturated;}
    void setScleraSaturated (bool isScleraSaturated) {_isScleraSaturated = isScleraSaturated;}

    bool lookFront() {return _lookFront;}
    void setLookFront (bool lookFront) {_lookFront = lookFront;}

    float maxPupilDiff() {return _maxPupilDiff;}
    void setMaxPupilDiff (float maxPupilDiff) {_maxPupilDiff = maxPupilDiff;}

    float maxIrisDiff() {return _maxIrisDiff;}
    void setMaxIrisDiff (float maxIrisDiff) {_maxIrisDiff = maxIrisDiff;}


public:
    // For debugging
    PointF _eyeSpecCenter, _faceSpecCenter;
    int _neighborAvg;

private:
    int _type;
    unsigned char *_image;
    signed short *_clusterImage;
    int _width, _height;
    int _x1, _y1, _x2, _y2;
    int _clusterID;
    int _size;
    float _avg;
    float _thirdBondaryAvg;
    float _scleraIntensity, _irisIntensity;
    Rect _boundingBox;
    Rect _searchBox;

    Point _seed;
    PointF _center;
    PointF _xyPos;
    float _distance;
    Point _faceClusterCenter;
    Point _eyeClusterCenter;

    std::deque<ClusterPoint *> _boundaryPointList;
    std::deque<int> _xList, _yList;

    Cluster *_pairCluster;
    float _score;

    int _irisCenterX, _irisCenterY;
    int _irisRadius;
    float _pupilScore;
    int _pupilCenterX, _pupilCenterY;
    int _pupilRadius;
    float _centerXShift; // mm
    int _pupilValue;

    float _maxPupilDiff, _maxIrisDiff;

    static ClusterPoint s_clusterPoint[MAX_NUM_OF_CLUSTER_POINT];
    static int s_counter;

    int _minx, _maxx, _miny, _maxy;
    int _xsum, _ysum;

    bool _isScleraSaturated;

    // BM
    bool _lookFront;

};

#endif // CLUSTER_H
