
#ifndef __QXMPP_PEER_H_
#define __QXMPP_PEER_H_

#include "QXmppClient.h"
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
    QxmppPeer( QObject * parent = 0 );
    ~QxmppPeer();

    bool connect( const std::string & jid, const std::string & password );
    bool isConnected() const;
    void send( const std::string & jid, const std::string & stri );

public slots:
    void connected();
    void disconnected();
    void error( QXmppClient::Error );
    void messageReceived( const QXmppMessage & );

private:

};


#endif

