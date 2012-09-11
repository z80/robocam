
#ifndef __XMPP_PEER_H_
#define __XMPP_PEER_H_

#include <string>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>
#include <boost/function.hpp>
#include "client.h"
#include "messagesessionhandler.h"
#include "messageeventhandler.h"
#include "messagehandler.h"
//#include "message.h"
#include "connectionlistener.h"
#include "registrationhandler.h"
#include "registration.h"
#include "siprofileft.h"
#include "siprofilefthandler.h"
//#include "bytestreamdatahandler.h"
//#include "socks5bytestreamserver.h"

class XmppPeer: public gloox::MessageSessionHandler,
                public gloox::MessageEventHandler,
                public gloox::MessageHandler,
                public gloox::ConnectionListener,
                public gloox::LogHandler,
                public gloox::RegistrationHandler/*,
                public gloox::SIProfileFTHandler,
                public gloox::BytestreamDataHandler*/

{
public:
    typedef boost::function<void (const std::string &, const std::string &)> TMessageHandler;
    typedef boost::function<void (const std::string &)> TLogHandler;

    XmppPeer();
    ~XmppPeer();

    void setMessageHandler( TMessageHandler handler );
    void setLogHandler( TLogHandler handler );
    void setHost( const std::string & host = "10.8.0.1", int port = 5222 );
    void setNick( const std::string & jid  = "peer", const std::string & password = "" );
    void setRegistering( bool reg = false );
    bool connect();
    bool isConnected() const;
    void terminate();
    bool send( const std::string & to, const std::string & msg );

    const std::string lastError() const;

    // Reimplementing virtual methods...
    virtual void onConnect();
    virtual void onDisconnect( gloox::ConnectionError e );
    virtual bool onTLSConnect( const gloox::CertInfo & info );
    virtual void handleMessage( const gloox::Message & msg, gloox::MessageSession * s );
    virtual void handleMessageEvent( const gloox::JID & from, gloox::MessageEventType type );
    virtual void handlerChatState( const gloox::JID & from, gloox::ChatStateType type );
    virtual void handleMessageSession( gloox::MessageSession * s );
    virtual void handleRegistrationFields( const gloox::JID & from, int fields, std::string instructions );
    virtual void handleRegistrationResult( const gloox::JID & from, gloox::RegistrationResult result );
    virtual void handleAlreadyRegistered( const gloox::JID & from );
    virtual void handleDataForm( const gloox::JID & from, const gloox::DataForm& form );
    virtual void handleOOB( const gloox::JID & from, const gloox::OOB & oob );
    virtual void handleLog( gloox::LogLevel level, gloox::LogArea area, const std::string & msg );

private:
    void run();

    // Client desc.
    std::string m_jid,
                m_password,
                m_host,
                m_lastError;
    int         m_port;
    bool        m_connected, 
                m_doRegister;

    TMessageHandler m_messageHandler;
    TLogHandler     m_logHandler;

    boost::thread         m_thread;
    mutable boost::mutex m_mutex;
    boost::condition      m_cond;
    gloox::MessageSession * m_session;
    gloox::Client         * m_client;
    gloox::Registration   * m_reg;
    /*
    gloox::SIProfileFT* f;
    gloox::Bytestream* m_bs;
    gloox::SOCKS5BytestreamServer* m_server;
    */
};


#endif





