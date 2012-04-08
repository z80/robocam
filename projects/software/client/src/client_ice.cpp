
#include "client_ice.h"
#include "client_ice_thread.h"

CClientIce::CClientIce( CClientIceThread * owner )
: ::Client::CClient()
{
    m_owner = owner;

    ::Ice::ObjectAdapterPtr & a = owner->m_adapter;

    m_clientPrx = ::Client::CClientPrx::uncheckedCast( a->addWithUUID( this ) );

    m_chat    = new CChatIce( owner );
    m_chatPrx = ::Client::CChatPrx::uncheckedCast( a->addWithUUID( m_chat ) );

    m_moto    = new CMotoIce( owner );
    m_motoPrx = ::Client::CMotoPrx::uncheckedCast( a->addWithUUID( m_moto ) );

    m_cam    = new CCamIce( owner );
    m_camPrx = ::Client::CCamPrx::uncheckedCast( a->addWithUUID( m_cam ) );
}

CClientIce::~CClientIce()
{
}

::Client::CChatPrx CClientIce::chat( const ::Ice::Current& c )
{
    return m_chatPrx;
}

::Client::CMotoPrx CClientIce::moto( const ::Ice::Current& c )
{
    return m_motoPrx;
}

::Client::CCamPrx  CClientIce::cam( const ::Ice::Current& c )
{
    return m_camPrx;
}


