#ifndef RECT_H
#define RECT_H


class Rect
{
private:
    int _x, _y, _width, _height;

public:
    Rect(int x = 0, int y = 0, int width = 0, int height = 0)
        :_x(x), _y(y), _width(width), _height(height)
    {
    }

    int width() {return _width;}
    int height() {return _height;}
    int x() {return _x;}
    int y() {return _y;}
};

#endif // RECT_H
