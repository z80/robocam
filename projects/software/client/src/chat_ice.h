
#ifndef __CHAT_ICE_H_
#define __CHAT_ICE_H_

#include "client.h"
class CClientIceThread;

class CChatIce: public ::Client::CChat
{
public:
    CChatIce( CClientIceThread * owner );
    ~CChatIce();

    void acceptMessage(const ::std::string&, const ::Ice::Current& = ::Ice::Current() );
    void acceptClientList(const ::Types::TStringArray&, const std::string &, const ::Ice::Current& = ::Ice::Current());
private:
    CClientIceThread * m_owner;
};


#endif


