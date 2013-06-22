
#include "xmpp_io.h"
#include "QXmppMessage.h"
#include "QXmppLogger.h"
#include "QXmppTransferManager.h"

class QXmppPeer::PD
{
public:
    PD() {}
    ~PD() {}

    QString targetJid;
    bool    targetUpdate;
};


QXmppPeer::QXmppPeer( QObject * parent )
    : QXmppClient( parent )
{
    pd = new PD();
    QXmppLogger::getLogger()->setLoggingType( QXmppLogger::SignalLogging );
    QObject::connect( QXmppLogger::getLogger(), SIGNAL(message(QXmppLogger::MessageType, const QString &)),
                      this,                     SLOT(qxmppLog( QXmppLogger::MessageType, const QString &)) );

    QObject::connect( this, SIGNAL( connected() ),
                              SLOT( qxmppConnected() ) );

    QObject::connect( this, SIGNAL( disconnected() ),
                              SLOT( qxmppDisconnected() ) );

    QObject::connect( this, SIGNAL( error(QXmppClient::Error) ),
                              SLOT( qxmppError(QXmppClient::Error) ) );

    QObject::connect(this, SIGNAL( messageReceived(QXmppMessage) ),
                             SLOT( qxmppMessageReceived(QXmppMessage) ) );
}

QXmppPeer::~QXmppPeer()
{
    delete pd;
}

void QXmppPeer::setTarget( const QString & jid, bool update )
{
    pd->targetJid    = jid;
    pd->targetUpdate = update;
}

void QXmppPeer::connect( const QString & jid, const QString & password, const QString & host, int port, bool tls )
{
    QXmppConfiguration conf;
    conf.setJid( jid );
    conf.setPassword( password );
    if ( host.size() > 0 )
        conf.setHost( host );
    if ( port > 0 )
        conf.setPort( port );
    conf.setAutoReconnectionEnabled( true );
    //conf.setUseNonSASLAuthentication( true );
    if ( tls )
        conf.setStreamSecurityMode( QXmppConfiguration::TLSEnabled );
    else
        conf.setStreamSecurityMode( QXmppConfiguration::TLSDisabled );

    connectToServer( conf );

}

void QXmppPeer::disconnect()
{
    disconnectFromServer();
}

void QXmppPeer::sendMessage( const QString & stri )
{
    QXmppClient::sendMessage( pd->targetJid, stri );
}

void QXmppPeer::qxmppLog( QXmppLogger::MessageType type, const QString & text )
{
    QString stri = QString( "Log(%1): %2" ).arg( type ).arg( text );
    emit log( stri );
}

void QXmppPeer::qxmppConnected()
{
    emit log( "connected" );
}

void QXmppPeer::qxmppDisconnected()
{
    emit log( "disconnected" );
}

void QXmppPeer::qxmppError( QXmppClient::Error e )
{
    QString stri = QString( "Error: %1" ).arg( e );
    emit log( stri );
}

void QXmppPeer::qxmppMessageReceived( const QXmppMessage & message )
{
    if ( pd->targetUpdate )
        pd->targetJid = message.from();
    QString stri = message.body();
    emit textmsg( stri );
}





