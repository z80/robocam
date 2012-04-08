
#include "cam_super_ice.h"
#include "host_ice_thread.h"

CCamSuperIce::CCamSuperIce( CHostIceThread * owner )
: CCamCtrlIce( owner )
{
}

CCamSuperIce::~CCamSuperIce()
{
}

void CCamSuperIce::setResolution( ::Ice::Int width, ::Ice::Int height, const ::Ice::Current & c )
{
    m_owner->m_cam->setResolution( width, height );
}

void CCamSuperIce::setDeviceName(const ::std::string& stri, const ::Ice::Current& c )
{
    m_owner->m_cam->setDeviceName( stri );
}

bool CCamSuperIce::open(const ::Ice::Current& c )
{
    return m_owner->m_cam->open();
}

void CCamSuperIce::close(const ::Ice::Current& c )
{
    m_owner->m_cam->close();
}



