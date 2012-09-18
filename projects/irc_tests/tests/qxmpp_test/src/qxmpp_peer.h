
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

class QxmppPeer: QXmppClient
{
    Q_OBJECT
public:
    typedef boost::function<void (const std::string &)> TLogHandler;
    typedef boost::function<void (const std::string &, const std::string &)> TMessageHandler;
    typedef boost::function<void (const std::string &, QBuffer &)> TFileHandler;

    QxmppPeer( QObject * parent = 0 );
    ~QxmppPeer();

    void setLogHandler( TLogHandler handler );
    void setMessageHandler( TMessageHandler handler );
    void setFileHandler( TFileHandler handler );

    void connectHost( const std::string & jid, const std::string & password );
    bool isConnected() const;
    void terminate();
    void send( const std::string & jid, const std::string & stri );
    //void sendFile( const std::string & jid, const std::string & fileName );
    void sendFile( const std::string & jid, const std::string fileName, QIODevice * dev );

public slots:
    void connected();
    void disconnected();
    void error( QXmppClient::Error );
    void messageReceived( const QXmppMessage & );
    // File transfer slots.
    void trError(QXmppTransferJob::Error error);
    void trFileReceived(QXmppTransferJob *job);
    void trFinished();
    void trPresenceReceived(const QXmppPresence &presence);
    void trProgress(qint64 done, qint64 total);

private:
    TLogHandler     m_logHandler;
    TMessageHandler m_messageHandler;
    TFileHandler    m_fileHandler;
    QXmppTransferManager * m_trManager;
    QHash<QXmppTransferJob *, QBuffer *> m_hash;
};


#endif

