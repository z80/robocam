
#ifndef __XMPP_PEER_H_
#define __XMPP_PEER_H_

#include "QXmppClient.h"

class QXmppPeer: public QXmppClient
{
    Q_OBJECT
public:
    QXmppPeer( QObject * parent = 0 );
    virtual ~QXmppPeer();

    void setTarget( const QString & jid, bool update = true );
    const QString & target() const;
    void connect( const QString & jid, const QString & password, const QString & host = QString(), int port = -1, bool tls = true );
    void disconnect();

    // Pure text message.
    void sendMessage( const QString & stri );

signals:
    void log( const QString & );
    void textmsg( const QString & );
    void sigSendMessage( const QString & );
private slots:
    void slotSendMessage( const QString & );
    // QXMPP related slots:
    void qxmppLog( QXmppLogger::MessageType type, const QString & text );
    void qxmppConnected();
    void qxmppDisconnected();
    void qxmppError( QXmppClient::Error );
    void qxmppMessageReceived( const QXmppMessage & );

private:
    class PD;
    PD * pd;
};

#endif



