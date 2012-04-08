
#ifndef __CAM_CTRL_H_
#define __CAM_CTRL_H_

#include <string>
#include <vector>

class CCamCtrl
{
public:
    CCamCtrl();
    ~CCamCtrl();
    void setDeviceName( const std::string & devName );
    bool open();
    bool isOpen() const;
    void close();
    bool isOpened();
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
    bool started();
    std::string lastError();
};

#endif



