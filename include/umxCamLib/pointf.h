#ifndef POINTF_H
#define POINTF_H

#include "point.h"

class PointF
{
private:
    float _xval, _yval;

public:
    // Constructor uses default arguments to allow calling with zero, one,
    // or two values.
    PointF(float x = 0.0, float y = 0.0) {
        _xval = x;
        _yval = y;
    }

    // Extractors.
    float x() { return _xval; }
    float y() { return _yval; }

    void setX(float x) {_xval = x;}
    void setY(float y) {_yval = y;}

    // Distance to another point.  Pythagorean thm.
    double dist(PointF other) {
        float xd = _xval - other._xval;
        float yd = _yval - other._yval;
        return (float)sqrt(xd*xd + yd*yd);
    }

    // Add or subtract two points.
    PointF operator+(PointF b)
    {
        return PointF(_xval + b._xval, _yval + b._yval);
    }
    PointF operator-(PointF b)
    {
        return PointF(_xval - b._xval, _yval - b._yval);
    }

    PointF operator*(int n)
    {
        return PointF(_xval*n, _yval*n);
    }
    PointF operator/(int n)
    {
        return PointF(_xval/n, _yval/n);
    }

    void operator=(PointF b)
    {
        _xval = b.x();
        _yval = b.y();
    }

    void operator=(Point b)
    {
        _xval = b.x();
        _yval = b.y();
    }

    // Move the existing point.
    void move(float a, float b)
    {
        _xval += a;
        _yval += b;
    }
};

#endif // POINTF_H
