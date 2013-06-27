
#include "rpc_call_interface.h"
#include "xmpp_video.h"

CallInterface::CallInterface( QXmppVideo * parent )
    : QXmppInvocable( parent )
{

}

CallInterface::~CallInterface()
{

}

bool CallInterface::isAuthorized( const QString & jid ) const
{
    m_targetJid =  jid;
    return true;
}

void CallInterface::call()
{
    QXmppVideo * v = qobject_cast<QXmppVideo *>( parent() );
    if ( !v )
        return;
    v->setTarget( v );
    v->call();
}

void CallInterface::stopCall()
{
    QXmppVideo * v = qobject_cast<QXmppVideo *>( parent() );
    if ( !v )
        return;
    v->endCall();
}







