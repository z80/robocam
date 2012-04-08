
#include "proxy.h"

#include "QsLog.h"

CProxy::CProxy( QObject * parent, const QString & listenHost, 
                              quint16 listenPort, 
                              const QString & connectHost, 
                              quint16 connectPort )
: QTcpServer( parent )
{
    m_clientHost = connectHost;
    m_clientPort = connectPort;
    connect( this, SIGNAL(newConnection()), this, SLOT(slotNewConnection()) );
    bool res = false;
    if ( listenHost.length() > 0 )
        res = listen( QHostAddress( listenHost ), listenPort );
    else
        res = listen( QHostAddress::Any, listenPort );

    QLOG_INFO() << "listen() result: " << ( res ? "true" : "false" );
}

CProxy::~CProxy()
{
    if ( isListening() )
        close();
}

bool CProxy::isListening() const
{
    bool res = QTcpServer::isListening();
    return res;
}

void CProxy::deleteLater()
{
    QTcpServer::deleteLater();
}

void CProxy::slotNewConnection()
{
    QTcpSocket * h;
    while ( h = nextPendingConnection() )
    {
        QLOG_INFO() << "new pending connection";
        connect( h, SIGNAL(readyRead()),    this, SLOT(slotHostDataAvailable()) );
        connect( h, SIGNAL(disconnected()), this, SLOT(slotDisconnected()) );
        QTcpSocket * c = new QTcpSocket( this );
        connect( c, SIGNAL(readyRead()), this, SLOT(slotClientDataAvailable()) );
        connect( c, SIGNAL(disconnected()), this, SLOT(slotDisconnected()) );
        c->connectToHost( m_clientHost, m_clientPort );
        m_hostKey.insert( h, c );
        m_clientKey.insert( c, h );
    }
}

void CProxy::slotDisconnected()
{
    QLOG_INFO() << "disconnected";
    QTcpSocket * s = qobject_cast<QTcpSocket *>( sender() );
    if ( s )
        removePair( s );
}

void CProxy::slotHostDataAvailable()
{
    QTcpSocket * from = qobject_cast<QTcpSocket *>( sender() );
    if ( from )
    {
        QTcpSocket * to = m_hostKey[ from ];
        if ( to )
        {
            qint64 available = from->bytesAvailable();
            m_buffer.resize( available );
            qint64 cnt = from->read( m_buffer.data(), available );
            to->write( m_buffer.data(), cnt );
        }
    }
}

void CProxy::slotClientDataAvailable()
{
    QTcpSocket * from = qobject_cast<QTcpSocket *>( sender() );
    if ( from )
    {
        QTcpSocket * to = m_clientKey[ from ];
        if ( to )
        {
            qint64 available = from->bytesAvailable();
            m_buffer.resize( available );
            qint64 cnt = from->read( m_buffer.data(), available );
            to->write( m_buffer.data(), cnt );
        }
    }
}

void CProxy::removePair( QTcpSocket * s )
{
    QHash<QTcpSocket*, QTcpSocket*>::iterator i = m_hostKey.find( s );
    if ( i != m_hostKey.end() )
    {
        QLOG_INFO() << "host pair removed";
        i.key()->deleteLater();
        QTcpSocket * c = i.value();
        c->deleteLater();
        m_hostKey.erase( i );

        i = m_clientKey.find( c );
        if ( i != m_clientKey.end() )
        {
            QLOG_INFO() << "appropriate client removed";
            m_clientKey.erase( i );
        }
    }
    else
    {
        i = m_clientKey.find( s );
        if ( i != m_clientKey.end() )
        {
            QLOG_INFO() << "client pair removed";
            i.key()->deleteLater();
            QTcpSocket * c = i.value();
            c->deleteLater();
            m_clientKey.erase( i );

            i = m_hostKey.find( c );
            if ( i != m_hostKey.end() )
            {
                QLOG_INFO() << "appropriate host removed";             
                m_hostKey.erase( i );
            }
        }
    }
}




