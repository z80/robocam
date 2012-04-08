
#include "cam_ctrl.h"

CCamCtrl::CCamCtrl()
{
}

CCamCtrl::~CCamCtrl()
{
}

void CCamCtrl::setDeviceName( const std::string & devName )
{
}

bool CCamCtrl::open()
{
    return true;
}

bool CCamCtrl::isOpen() const
{
    return true;
}

void CCamCtrl::close()
{
}

bool CCamCtrl::isOpened()
{
    return true;
}

bool CCamCtrl::capabilities( std::vector<std::string> & cap, std::vector<bool> & en, std::vector<std::string> & info )
{
    return true;
}

bool CCamCtrl::formats( std::vector<std::string> & fmt, std::vector<unsigned long> & fourcc )
{
    fmt.push_back( "yuyv" );
    fourcc.push_back( 1234 );
    return true;
}

std::vector<int> CCamCtrl::resolutions()
{
    std::vector<int> l;
    l.push_back( 320 );
    l.push_back( 240 );
    l.push_back( 640 );
    l.push_back( 480 );
    l.push_back( 800 );
    l.push_back( 600 );
    return l;
}

bool CCamCtrl::initDevice( bool streaming, unsigned long format, int width, int height, int fps )
{
    return true;
}

void CCamCtrl::imageSize( int & width, int & height, int & bufferSz )
{
    width = 320;
    height = 240;
    bufferSz = 320 * 240 * 3;
}

bool CCamCtrl::acquire()
{
    return true;
}

bool CCamCtrl::release()
{
    return true;
}

void CCamCtrl::data( int from, int length, std::vector<unsigned char> & res )
{
}

bool CCamCtrl::startCapture()
{
    return true;
}

void CCamCtrl::stopCapture()
{
}

bool CCamCtrl::started()
{
    return true;
}

std::string CCamCtrl::lastError()
{
    return "ok";
}




