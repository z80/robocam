
#ifndef __CAM_CTRL_H_
#define __CAM_CTRL_H_

#include <string>
#include <queue>
#include <vector>

class CCamCtrl
{
public:
    CCamCtrl();
    ~CCamCtrl();
    void setDeviceName( const std::string & devName );
    bool open();
    void close();
    bool isOpen() const;
    bool capabilities( std::vector<std::string> & cap, std::vector<bool> & en, std::vector<std::string> & info );
    bool formats( std::vector<std::string> & fmt, std::vector<unsigned long> & fourcc );
    std::vector<int>         resolutions();
    bool initDevice( bool streaming, unsigned long format, int width, int height, int fps = 10 );
    void imageSize( int & width, int & height, int & bufferSz );
    bool acquire();
    bool release();
    void data( int from, int length, std::vector<unsigned char> & res );
    bool startCapture();
    void stopCapture();
    bool started() const;
    std::string lastError();
private:
    bool setFps( int fps );
    bool initMMap( unsigned int buffer_size );
    void freeBuffer();

    class PD;
    PD * pd;

    std::string m_devName;
    int m_dev;
    int m_width,
        m_height;
    int m_index;
    bool m_capture;
    std::vector<void *>        m_buffer;
    std::vector<unsigned long> m_bufferSz;
    std::vector<unsigned char> m_data;
    std::queue<std::string>    m_msgs;
    int m_fps;
};


#endif


