#ifndef UMXCAMERA_H
#define UMXCAMERA_H

#include <sys/types.h>

#if __GNUC__
    #if __x86_64__ || __ppc64__
        #define ENV64
        #define TO_INT u_int64_t
    #else
        #define ENV32
        #define TO_INT u_int32_t
    #endif
#endif

class UMXCamera
{
public:
    UMXCamera();
    ~UMXCamera();

public:
    int getData(char* buf, unsigned int buf_len);

public: // methods
    int setup();
    int start();
    int stop();

protected:
    void setDevice(const char* path);

public:
    char* getDevice() { return _device;}

    void setWidth(int w) { _width = w;}
    int getWidth() { return _width;}

    void setHeight(int h) { _height=h;}
    int getHeight() { return _height;}

    void setFps(int f) { _fps = f;}
    int getFps() { return _fps;}

    void setFormat(int f) { _format = f;}
    int getFormat() { return _format;}

    unsigned int getSizeImage() { return _sizeImage;}

public:
    enum CameraStateType  {
        STATE_CLOSE =              0x00,
        STATE_OPEN =               0x01,
        STATE_CAPTURE =            0x02,
    };
    CameraStateType getState() { return _state;}

private: // properties
    char _device[16];

    int _width;
    int _height;
    unsigned int _sizeImage;
    int _fps;
    int _format;
    int _extraPixel;
    int _inputMode; // 0-use csi->prp_enc->mem, 1-use csi->mem

protected:
    CameraStateType _state;
    int _v4lFd;

    class Buffer {
    public:
        unsigned char *start;
        size_t offset;
        unsigned int length;
    };
    Buffer **_buffers;

};

#endif // UMXCAMERA_H
