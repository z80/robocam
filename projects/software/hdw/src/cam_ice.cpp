
#include "cam_ice.h"
#include "cam_ctrl.h"

CCamIce::CCamIce( CCamCtrl * camCtrl )
: Hdw::CCam(), 
  m_camCtrl( camCtrl )
{
}

CCamIce::~CCamIce()
{
}

void CCamIce::setDeviceName(const ::std::string & stri, const ::Ice::Current & c )
{
    m_camCtrl->setDeviceName( stri );
}

bool CCamIce::open(const ::Ice::Current & c )
{
    return m_camCtrl->open();
}

bool CCamIce::isOpen(const ::Ice::Current & c )
{
    return m_camCtrl->isOpen();
}

void CCamIce::close(const ::Ice::Current & c )
{
    m_camCtrl->close();
}

bool CCamIce::capabilities( ::Types::TStringArray & cap, 
                            ::Types::TBoolArray & en, 
                            ::Types::TStringArray & info, 
                            const ::Ice::Current & c )
{
    return m_camCtrl->capabilities( cap, en, info );
}

bool CCamIce::formats( ::Types::TStringArray & fmt, ::Types::TLongArray & fourcc, const ::Ice::Current & c )
{
    std::vector<unsigned long> fcc;
    bool res =  m_camCtrl->formats( fmt, fcc );
    fourcc.clear();
    fourcc.reserve( fcc.size() );
    for ( unsigned i=0; i<fcc.size(); i++ )
        fourcc.push_back( fcc.at( i ) );
    return res;
}

::Types::TIntArray CCamIce::resolutions(const ::Ice::Current & c )
{
    return m_camCtrl->resolutions();
}

bool CCamIce::initDevice( bool streaming, 
                         ::Ice::Long fourcc, 
                         ::Ice::Int w, ::Ice::Int h, 
                         ::Ice::Int fps, 
                         const ::Ice::Current & c )
{
    unsigned long fcc = *((unsigned long *)(&fourcc));
    return m_camCtrl->initDevice( streaming, fcc, w, h, fps );
}

void CCamIce::imageSize( ::Ice::Int & width, ::Ice::Int & height, ::Ice::Int & bufferSize, const ::Ice::Current & c )
{
    m_camCtrl->imageSize( width, height, bufferSize );
}

bool CCamIce::startCapture(const ::Ice::Current & c )
{
    return m_camCtrl->startCapture();
}

void CCamIce::stopCapture(const ::Ice::Current & c )
{
    m_camCtrl->stopCapture();
}

bool CCamIce::started(const ::Ice::Current & c )
{
    return m_camCtrl->started();
}

bool CCamIce::acquire(const ::Ice::Current & c )
{
    return m_camCtrl->acquire();
}

bool CCamIce::release(const ::Ice::Current & c )
{
    return m_camCtrl->release();
}

void CCamIce::data( ::Ice::Int from, ::Ice::Int length, ::Types::TByteArray & data, const ::Ice::Current & c )
{
    m_camCtrl->data( from, length, data );
}

::std::string CCamIce::lastError(const ::Ice::Current & c )
{
    return m_camCtrl->lastError();
}






