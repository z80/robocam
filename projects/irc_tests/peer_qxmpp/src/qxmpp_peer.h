
#ifndef __QXMPP_PEER_H_
#define __QXMPP_PEER_H_

#include <QtGui>
#include "QXmppClient.h"
#include "QXmppTransferManager.h"

#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/bind/placeholders.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>

class QxmppPeer: public QXmppClient
{
    Q_OBJECT
public:
    typedef boost::function<void (const std::string &)> TLogHandler;
    typedef boost::function<void (const std::string &, const std::string &)> TMessageHandler;
    typedef boost::function<QIODevice * (const std::string &)> TInFileHandler;
    typedef boost::function<void (const std::string &, QIODevice * )> TAccFileHandler;

    QxmppPeer( QObject * parent = 0 );
    ~QxmppPeer();

    void setLogHandler( TLogHandler handler );
    void setMessageHandler( TMessageHandler handler );
    void setInFileHandler( TInFileHandler handler );
    void setAccFileHandler( TAccFileHandler handler );

    void connectHost( const std::string & jid, const std::string & password, const std::string & host = std::string(), int port = -1, bool tls = true );
    bool isConnected() const;
    void terminate();
    void send( const std::string & jid, const std::string & stri );
    //void sendFile( const std::string & jid, const std::string & fileName );
    void sendFile( const std::string & jid, const std::string & fileName, QIODevice * dev );
signals:
    void sigSendFile(const QString &, const QString &, QIODevice *);
public slots:
    void logMessage( QXmppLogger::MessageType type, const QString & text );
    void connected();
    void disconnected();
    void error( QXmppClient::Error );
    void messageReceived( const QXmppMessage & );
    // File transfer slots.
    void slotSendFile( const QString & jid, const QString & fileName, QIODevice * dev );
    void trError(QXmppTransferJob::Error error);
    void trFileReceived(QXmppTransferJob *job);
    void trJobStarted(QXmppTransferJob * job);
    void trFinished();
    void trPresenceReceived(const QXmppPresence &presence);
    void trProgress(qint64 done, qint64 total);

private:
    TLogHandler     m_logHandler;
    TMessageHandler m_messageHandler;
    TInFileHandler    m_inFileHandler;
    TAccFileHandler   m_accFileHandler;
    QXmppTransferManager * m_trManager;
    QHash<QXmppTransferJob *, QIODevice *> m_hash;
};


#endif

