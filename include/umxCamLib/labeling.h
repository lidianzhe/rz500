#ifndef LABELING_H
#define LABELING_H

// A Linear-Time Two-Scan Labeling Algorithm
// by Lifeng He, ...

#include "labeling.h"

#include <Poco/Logger.h>
#include <Poco/Mutex.h>
#include "Poco/FileChannel.h"
#include "Poco/AutoPtr.h"

#include <deque>
#include <iostream>

class Cluster;

class Labeling
{
public:
    Labeling();
    ~Labeling();

    unsigned char *image() {return _image;}
    void setImage(unsigned char *image) {_image = image;}

    int width() {return _width;}
    void setWidth (int width) {_width = width;}

    int height() {return _height;}
    void setHeight (int height) {_height = height;}

    void setImagesAndSize(unsigned char *image, int width, int height) {
        _image = image; _width = width; _height = height;
    }

    int x1() {return _x1;}
    void setX1 (int x1) {_x1 = x1;}

    int x2() {return _x2;}
    void setX2 (int x2) {_x2 = x2;}

    int y1() {return _y1;}
    void setY1 (int y1) {_y1 = y1;}

    int y2() {return _y2;}
    void setY2 (int y2) {_y2 = y2;}

    void setRegion(int x1, int y1, int x2, int y2) {
        _x1 = x1; _y1 = y1; _x2 = x2; _y2 = y2;
    }

    int minSize() {return _minSize;}
    void setMinSize (int minSize) {_minSize = minSize;}

    int maxSize() {return _maxSize;}
    void setMaxSize (int maxSize) {_maxSize = maxSize;}

    void setMinMaxSize (int minSize, int maxSize) {
        _minSize = minSize; _maxSize = maxSize;
    }

    // bigger than threshold
    int threshold() {return _threshold;}
    void setThreshold (int threshold) {_threshold = threshold;}

    bool findBrightClusters();
    void clearLabelImage(Cluster *cluster);
    bool findDarkClusters(); // not implemented yet
    bool findClustersInRegion();
    void markSimilarSpeculars(int diffFromMin, int boundaryThickness);


    std::deque<Cluster *>& getClusters() {
        std::deque<Cluster *>& list = _clusterList;
        return list;
    }

    std::deque<Cluster *> *getPClusters() {
        return &_clusterList;
    }

    int *labelImage() {return _labelImage;}

public:
    int32_t *_labelImage;
    // output
    std::deque<Cluster *> _clusterList;
    Cluster *_clusters;

private:
    // input
    unsigned char *_image; // original image
    int _width, _height, _imageSize;
    int _allocImageSize, _maxAllocLabel;
    int _x1, _y1, _x2, _y2;
    int _minSize, _maxSize;
    int _threshold;
    int _maxLabel;

    // internal   
    int32_t *_rlTable, *_nextTable, *_tailTable, *_count;

    int _clusterSize;
    int _maxClusterID;
};

#endif // LABELING_H
