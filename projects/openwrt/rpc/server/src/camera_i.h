
#ifndef __CAMERA_I_H_
#define __CAMERA_I_H_

#include "interface.h"
#include <queue>
#include <vector>

class CameraI : public Demo::Camera
{
public:
    CameraI();
    ~CameraI();
    void setDeviceName( const std::string & devName, const Ice::Current&);
    bool open(const Ice::Current&);
    void close(const Ice::Current&);
    bool isOpened(const Ice::Current&);
    std::vector<std::string> formats( const Ice::Current & );
    std::vector<int>         resolutions( const Ice::Current & );
    bool initDevice( const std::string & format, int width, int height, const Ice::Current&);
    void imageSize( int & width, int & height, int & bufferSz, const Ice::Current & );
    bool acquire(const Ice::Current&);
    void data( int from, int length, std::vector<unsigned char> & res, const Ice::Current & );
    bool startCapture(const Ice::Current&);
    void stopCapture(const Ice::Current&);
    bool started(const Ice::Current&);
    std::string lastError(const Ice::Current&);
private:
    bool open();
    void close();
    bool isOpened();
    void stopCapture();
    bool initMMap( unsigned int buffer_size );
    void freeBuffer();
    std::string m_devName;
    int m_dev;
    int m_width,
        m_height;
    int m_index;
    bool m_capture;
    std::vector<void *>        m_buffer;
    std::vector<unsigned long> m_bufferSz;
    std::vector<unsigned char> m_data;
    std::queue<std::string> m_msgs;
};


#endif


