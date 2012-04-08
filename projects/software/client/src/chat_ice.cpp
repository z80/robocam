
#include "chat_ice.h"
#include "client_ice_thread.h"

CChatIce::CChatIce( CClientIceThread * owner )
: ::Client::CChat(), 
  m_owner( owner )
{
}

CChatIce::~CChatIce()
{
}

void CChatIce::acceptMessage(const ::std::string & stri, const ::Ice::Current& c )
{
    m_owner->m_acceptMessageCb( stri );
}

void CChatIce::acceptClientList(const ::Types::TStringArray & clients, const std::string & driverNickname, const ::Ice::Current& c )
{
    m_owner->m_acceptClientListCb( clients, driverNickname );
}

