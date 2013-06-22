
#include "QXmppClient.h"

class QXmppPeer: public QXmppClient
{
    Q_OBJECT
public:
    QXmppPeer( QObject * parent = 0 );
    virtual ~QXmppPeer();

    void setTarget( const QString & jid, bool update = true );
    void connect( const QString & jid, const QString & password, const QString & host = QString(), int port = -1, bool tls = true );
    void disconnect();

    // Pure text message.
    void sendMessage( const QString & stri );
    // Establishing pipe.
    bool createPipe( int portLocal, bool outgoing = true );

signals:
    void log( const QString & );
    void textmsg( const QString & );
private slots:
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




