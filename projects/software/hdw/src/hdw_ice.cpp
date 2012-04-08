
#include "hdw_ice.h"
#include "cam_ctrl.h"
#include "moto_ctrl.h"
#include "cam_ice.h"
#include "moto_ice.h"
#include <IceE/IceE.h>

CHdwIce::CHdwIce( Ice::ObjectAdapterPtr adapter )
: Hdw::CHdw()
{
    m_camCtrl  = new CCamCtrl();
    m_motoCtrl = new CMotoCtrl();

    m_cam  = new CCamIce( m_camCtrl );
    m_moto = new CMotoIce( m_motoCtrl );

    m_camPrx  = Hdw::CCamPrx::uncheckedCast( adapter->addWithUUID( m_cam ) );
    m_motoPrx = Hdw::CMotoPrx::uncheckedCast( adapter->addWithUUID( m_moto ) );
}

CHdwIce::~CHdwIce()
{
    delete m_camCtrl;
}

::Hdw::CMotoPrx CHdwIce::moto( const ::Ice::Current & c )
{
    return m_motoPrx;
}

::Hdw::CCamPrx  CHdwIce::cam( const ::Ice::Current & c )
{
    return m_camPrx;
}







