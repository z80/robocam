
#include "cam_view_ice.h"
#include "host_ice_thread.h"

CCamViewIce::CCamViewIce( CHostIceThread * owner )
: ::Host::CCam(), 
  m_owner( owner )
{
}

CCamViewIce::~CCamViewIce()
{
}

bool CCamViewIce::isOpen(const ::Ice::Current& c )
{
    return m_owner->m_cam->isOpen();
}

void CCamViewIce::setResolution( ::Ice::Int with, ::Ice::Int height, const ::Ice::Current & c )
{
}

void CCamViewIce::resolution(::Ice::Int& width, ::Ice::Int& height, const ::Ice::Current& c )
{
    m_owner->m_cam->resolution( width, height );
}

::Ice::Double CCamViewIce::period(const ::Ice::Current& c )
{
    return m_owner->m_cam->period();
}

bool CCamViewIce::image( ::Types::TByteArray & data, const ::Ice::Current& c )
{
    return m_owner->m_cam->image( data );
}

void CCamViewIce::setReceiveImages(bool en, const ::Ice::Current& c )
{
}

bool CCamViewIce::receiveImages(const ::Ice::Current& c )
{
    return m_owner->m_cam->receiveImages();
}

::std::string CCamViewIce::deviceName(const ::Ice::Current& c )
{
    return m_owner->m_cam->deviceName();
}

void CCamViewIce::setPeriod(::Ice::Double period, const ::Ice::Current& c )
{
}

void CCamViewIce::setDeviceName(const ::std::string & stri, const ::Ice::Current& c )
{
}

bool CCamViewIce::open(const ::Ice::Current& c )
{
    return false;
}

void CCamViewIce::close(const ::Ice::Current& c )
{
}






