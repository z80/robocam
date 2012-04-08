
#ifndef __CLIENT_ICE_H_
#define __CLIENT_ICE_H_

#include "client.h"
#include "chat_ice.h"
#include "moto_ice.h"
#include "cam_ice.h"
class CClientIceThread;

class CClientIce: public ::Client::CClient
{
public:
    CClientIce( CClientIceThread * owner );
    ~CClientIce();

    ::Client::CChatPrx chat(const ::Ice::Current& = ::Ice::Current());
    ::Client::CMotoPrx moto(const ::Ice::Current& = ::Ice::Current());
    ::Client::CCamPrx  cam(const ::Ice::Current& = ::Ice::Current());
protected:
    // —обственный Proxy.
    ::Client::CClientPrx m_clientPrx;

    // —сылки на возвращаемые объекты.
    IceInternal::Handle<CChatIce> m_chat;
    IceInternal::Handle<CMotoIce> m_moto;
    IceInternal::Handle<CCamIce>  m_cam;
    ::Client::CChatPrx            m_chatPrx;
    ::Client::CMotoPrx            m_motoPrx;
    ::Client::CCamPrx             m_camPrx;
private:
    CClientIceThread * m_owner;

    friend class CClientIceThread;
};

#endif

