#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <math.h>

using namespace std;

class Point
{
private:
    int _xval, _yval;

public:
    // Constructor uses default arguments to allow calling with zero, one,
    // or two values.
    Point(int x = 0, int y = 0) {
        _xval = x;
        _yval = y;
    }

    // Extractors.
    int x() { return _xval; }
    int y() { return _yval; }

    void setX(int x) {_xval = x;}
    void setY(int y) {_yval = y;}


    // Distance to another point.  Pythagorean thm.
    double dist(Point other) {
        int xd = _xval - other._xval;
        int yd = _yval - other._yval;
        return sqrt(xd*xd + yd*yd);
    }

    // Add or subtract two points.
    Point operator+(Point b)
    {
        return Point(_xval + b._xval, _yval + b._yval);
    }
    Point operator-(Point b)
    {
        return Point(_xval - b._xval, _yval - b._yval);
    }

    void operator=(Point b)
    {
        _xval = b.x();
        _yval = b.y();
    }

    // Move the existing point.
    void move(int a, int b)
    {
        _xval += a;
        _yval += b;
    }
};

#endif // POINT_H
