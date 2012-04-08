
#include "cam_ctrl_ice.h"
#include "host_ice_thread.h"

CCamCtrlIce::CCamCtrlIce( CHostIceThread * owner )
: CCamViewIce( owner )
{
}

CCamCtrlIce::~CCamCtrlIce()
{
}

void CCamCtrlIce::setPeriod(::Ice::Double period, const ::Ice::Current& c )
{
    m_owner->m_cam->setPeriod( period );
}

void CCamCtrlIce::setReceiveImages(bool en, const ::Ice::Current & c )
{
    m_owner->m_cam->setReceiveImages( en );
}



