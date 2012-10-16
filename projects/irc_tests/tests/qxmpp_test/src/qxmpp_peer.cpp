
#include "qxmpp_peer.h"
#include "QXmppMessage.h"
#include "QXmppLogger.h"
#include <sstream>

QxmppPeer::QxmppPeer( QObject * parent )
{
    QXmppLogger::getLogger()->setLoggingType( QXmppLogger::SignalLogging );

    bool check;

    check = QObject::connect( QXmppLogger::getLogger(), SIGNAL(message(QXmppLogger::MessageType, const QString &)), 
                              this,                     SLOT(logMessage(QXmppLogger::MessageType, const QString &)) );

    check = QObject::connect( this, SIGNAL( connected() ), 
                                    SLOT( connected() ) );
    Q_ASSERT(check);

    check = QObject::connect( this, SIGNAL( disconnected() ), 
                                    SLOT( disconnected() ) );
    Q_ASSERT(check);

    check = QObject::connect( this, SIGNAL( error(QXmppClient::Error) ), 
                                    SLOT( error(QXmppClient::Error) ) );
    Q_ASSERT(check);

    check = QObject::connect(this, SIGNAL( messageReceived(QXmppMessage) ),
                                     SLOT( messageReceived(QXmppMessage) ) );
    Q_ASSERT(check);

    m_trManager = new QXmppTransferManager();
    addExtension( m_trManager );

    check = connect(this, SIGNAL( presenceReceived(QXmppPresence) ),
                    this, SLOT( trPresenceReceived(QXmppPresence) ) );
    Q_ASSERT(check);

    check = connect( m_trManager, SIGNAL(jobStarted(QXmppTransferJob*) ),
                     this, SLOT( trJobStarted(QXmppTransferJob*) ) );
    Q_ASSERT(check);

    check = connect( m_trManager, SIGNAL(fileReceived(QXmppTransferJob*) ),
                     this, SLOT( trFileReceived(QXmppTransferJob*) ) );
    Q_ASSERT(check);

    Q_UNUSED(check);
}

QxmppPeer::~QxmppPeer()
{
    m_trManager->deleteLater();
}

void QxmppPeer::setLogHandler( TLogHandler handler )
{
    m_logHandler = handler;
}

void QxmppPeer::setMessageHandler( TMessageHandler handler )
{
    m_messageHandler = handler;
}

void QxmppPeer::setInFileHandler( TInFileHandler handler )
{
    m_inFileHandler = handler;
}

void QxmppPeer::setAccFileHandler( TAccFileHandler handler )
{
    m_accFileHandler = handler;
}

void QxmppPeer::send( const std::string & jid, const std::string & stri )
{
    sendMessage( QString::fromStdString( jid ), QString::fromStdString( stri ) );
}

void QxmppPeer::sendFile( const std::string & jid, const std::string fileName, QIODevice * dev )
{
    if ( !dev->isOpen() )
    {
        bool res = dev->open( QIODevice::ReadOnly );
        if ( !res )
        {
            if ( !m_logHandler.empty() )
            {
                std::ostringstream out;
                out << "Error: failed to open QIODevice for reading";
                m_logHandler( out.str() );
            }
        }
    }
    QXmppTransferFileInfo info;
    info.setName( QString::fromStdString( fileName ) );
    info.setSize( dev->size() );
    QXmppTransferJob * job = m_trManager->sendFile( QString::fromStdString( jid ), dev, info );

    bool check;
    check = connect(job, SIGNAL( error(QXmppTransferJob::Error) ),
                    this, SLOT( trError(QXmppTransferJob::Error) ) );
    Q_ASSERT(check);

    check = connect(job, SIGNAL( finished() ),
                    this, SLOT( trFinished() ) );
    Q_ASSERT(check);

    check = connect(job, SIGNAL( progress(qint64,qint64) ),
                    this, SLOT( trProgress(qint64,qint64) ) );
    Q_ASSERT( check );

    Q_UNUSED( check );

    m_hash[ job ] = dev;
}

void QxmppPeer::connectHost( const std::string & jid, const std::string & password )
{
    /*QXmppConfiguration config;
    config.setJid( "z80@xmpp" );
    config.setPassword( "12345" );
    config.setHost( "10.8.0.1" );
    config.setStreamSecurityMode(QXmppConfiguration::TLSDisabled);
    connectToServer( config );*/
    connectToServer( jid.c_str(), password.c_str() );
}

bool QxmppPeer::isConnected() const
{
    bool res = QXmppClient::isConnected();
    return res;
}

void QxmppPeer::terminate()
{
    disconnectFromServer();
}

void QxmppPeer::logMessage( QXmppLogger::MessageType type, const QString & text )
{
    if ( !m_logHandler.empty() )
    {
        std::ostringstream out;
        out << "Log(" << type << "): ";
        out << text.toStdString();
        m_logHandler( out.str() );
    }
}

void QxmppPeer::connected()
{
    QXmppPresence pr;
    setClientPresence( pr );
    if ( !m_logHandler.empty() )
        m_logHandler( "Connected" );
}

void QxmppPeer::disconnected()
{
    if ( !m_logHandler.empty() )
        m_logHandler( "Disconnected" );
}

void QxmppPeer::error( QXmppClient::Error err )
{
    if ( !m_logHandler.empty() )
    {
        std::ostringstream out;
        out << "Error: ";
        out << err;
        m_logHandler( out.str() );
    }
}

void QxmppPeer::messageReceived(const QXmppMessage& message)
{
    QString from = message.from();
    QString msg  = message.body();

    //sendPacket( QXmppMessage("", from, "Your message: " + msg) );
    if ( !m_messageHandler.empty() )
        m_messageHandler( from.toStdString(), msg.toStdString() );
}

/// A file transfer failed.
void QxmppPeer::trError( QXmppTransferJob::Error error )
{
    //qDebug() << "Transmission failed:" << error;
    if ( !m_logHandler.empty() )
    {
        std::ostringstream out;
        out << "Transmission failed: ";
        out << error;
        m_logHandler( out.str() );
    }
    QXmppTransferJob * job = qobject_cast<QXmppTransferJob *>( sender() );
    if ( job )
    {
        QHash<QXmppTransferJob *, QIODevice *>::iterator iter = m_hash.find( job );
        if ( iter != m_hash.end() )
        {
            QIODevice * device = iter.value();
            //device->deleteLater(); // It will be removed as job's child.
            m_hash.erase( iter );
        }
    }
}

/// A file transfer request was received.
void QxmppPeer::trFileReceived( QXmppTransferJob * job )
{

    if ( !m_logHandler.empty() )
    {
        std::ostringstream out;
        out << "Got transfer request from: ";
        out << job->jid().toStdString();
        m_logHandler( out.str() );
    }

    if ( m_inFileHandler.empty() )
    {
        job->abort();
        return;
    }
    std::string fileName = job->fileInfo().name().toStdString();
    QIODevice * device = m_inFileHandler( fileName );
    if ( !device )
        return;
    job->accept( device );

    bool check;
    Q_UNUSED(check);
    check = connect( job, SIGNAL( error(QXmppTransferJob::Error) ),
                     this, SLOT( trError(QXmppTransferJob::Error) ) );
    Q_ASSERT(check);

    check = connect(job, SIGNAL( finished() ),
                    this, SLOT( trFinished()) );
    Q_ASSERT(check);

    check = connect( job, SIGNAL( progress(qint64,qint64) ),
                     this, SLOT( trProgress(qint64,qint64) ) );
    Q_ASSERT(check);

    m_hash[ job ] = device;
}

void QxmppPeer::trJobStarted(QXmppTransferJob * job)
{
    if ( !m_logHandler.empty() )
    {
        std::ostringstream out;
        out << "Job started: ";
        out << job->jid().toStdString();
        m_logHandler( out.str() );
    }
}

/// A file transfer finished.
void QxmppPeer::trFinished()
{
    //qDebug() << "Transmission finished";
    if ( !m_logHandler.empty() )
    {
        std::ostringstream out;
        out << "Transmission finished";
        m_logHandler( out.str() );
    }
    QXmppTransferJob * job = qobject_cast<QXmppTransferJob *>( sender() );
    if ( job )
    {
        QHash<QXmppTransferJob *, QIODevice *>::iterator iter = m_hash.find( job );
        if ( iter != m_hash.end() )
        {
            std::string fileName = job->fileInfo().name().toStdString();
            QIODevice * device = iter.value();
            if ( !m_accFileHandler.empty() )
                m_accFileHandler( fileName, device );
            //device->deleteLater();
            m_hash.erase( iter );
        }
    }
}

/// A presence was received
void QxmppPeer::trPresenceReceived(const QXmppPresence &presence)
{
    //bool check;
    //Q_UNUSED(check);

    //const QLatin1String recipient("qxmpp.test2@gmail.com");

    //// if we are the recipient, or if the presence is not from the recipient,
    //// do nothing
    //if (QXmppUtils::jidToBareJid(configuration().jid()) == recipient ||
    //    QXmppUtils::jidToBareJid(presence.from()) != recipient ||
    //    presence.type() != QXmppPresence::Available)
    //    return;

    //// send the file and connect to the job's signals
    //QXmppTransferJob * job = transferManager->sendFile( presence.from(), "xmppClient.cpp" );

    //check = connect(job, SIGNAL( error(QXmppTransferJob::Error) ),
    //                this, SLOT( trError(QXmppTransferJob::Error) ) );
    //Q_ASSERT(check);

    //check = connect(job, SIGNAL( finished() ),
    //                this, SLOT( trFinished() ) );
    //Q_ASSERT(check);

    //check = connect(job, SIGNAL( progress(qint64,qint64) ),
    //                this, SLOT( trProgress(qint64,qint64) ) );
    //Q_ASSERT( check );
}

/// A file transfer has made progress.
void QxmppPeer::trProgress(qint64 done, qint64 total)
{
    //qDebug() << "Transmission progress:" << done << "/" << total;
    if ( !m_logHandler.empty() )
    {
        std::ostringstream out;
        out << "Transmission progress: ";
        out << done << " of " << total;
        m_logHandler( out.str() );
    }
}





