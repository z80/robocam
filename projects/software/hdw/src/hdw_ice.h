
#ifndef __HDW_ICE_H_
#define __HDW_ICE_H_

#include "hdw.h"

class CCamCtrl;
class CMotoCtrl;


class CHdwIce: public Hdw::CHdw
{
public:
    CHdwIce( Ice::ObjectAdapterPtr adapter );
    ~CHdwIce();

    ::Hdw::CMotoPrx moto( const ::Ice::Current& = ::Ice::Current() );
    ::Hdw::CCamPrx  cam( const ::Ice::Current& = ::Ice::Current() );
private:
    CCamCtrl  * m_camCtrl;
    CMotoCtrl * m_motoCtrl;
    ::Hdw::CMotoPtr m_moto;
    ::Hdw::CMotoPrx m_motoPrx;
    ::Hdw::CCamPtr  m_cam;
    ::Hdw::CCamPrx  m_camPrx;
};



#endif



