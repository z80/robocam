
#include "cam_ice.h"
#include "client_ice_thread.h"

CCamIce::CCamIce( CClientIceThread * owner )
: ::Client::CCam(), 
  m_owner( owner )
{
}

CCamIce::~CCamIce()
{
}

void CCamIce::acceptImage( const ::Types::TByteArray & data, const ::Ice::Current& c )
{
    if ( m_owner->m_acceptImageCb )
        m_owner->m_acceptImageCb( data );
}

void CCamIce::acceptResolution( ::Ice::Int width, ::Ice::Int height, const ::Ice::Current& c )
{
}

void CCamIce::acceptPeriod(::Ice::Double, const ::Ice::Current& c )
{
}

