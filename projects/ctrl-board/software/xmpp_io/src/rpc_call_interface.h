
#ifndef __XMPP_RPC_CALL_INTERFACE_H_
#define __XMPP_RPC_CALL_INTERFACE_H_


#include "QXmppRpcManager.h"

class QXmppVideo;

class CallInterface: public QXmppInvocable
{
    Q_OBJECT
public:
    CallInterface( QXmppVideo * parent );
    ~CallInterface();

    bool isAuthorized( const QString & jid ) const;
public slots:
    void call();
    void stopCall();
private:
    QString m_targetJid;
};


#endif



