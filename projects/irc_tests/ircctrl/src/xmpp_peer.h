
#ifndef __XMPP_PEER_H_
#define __XMPP_PEER_H_

#include <string>
#include <boost/thread.hpp>
#include <boost/function.hpp>
#include "messagesessionhandler.h"
#include "messageeventhandler.h"
#include "connectionlistener.h"
#include "registrationhandler.h"
#include "siprofileft.h"
#include "siprofilefthandler.h"
#include "bytestreamdatahandler.h"
#include "socks5bytestreamserver.h"
#include "message.h"

class XmppPeer: public MessageSessionHandler,
                public MessageEventHandler,
                public MessageHandler,
                public ConnectionListener,
                public LogHandler, 
                public RegistrationHandler, 
                public SIProfileFTHandler/*, 
                public BytestreamDataHandler*/

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
    virtual void onDisconnect( ConnectionError e );
    virtual bool onTLSConnect( const CertInfo & info );
    virtual void handleMessage( const Message & msg, MessageSession * s );
    virtual void handleMessageEvent( const & JID & from, MessageEventType type );
    virtual void handlerChatState( const JID & from, ChatStateType type );
    virtual void handleMessageSession( MessageSession * s );
    virtual void handleRegistrationFields( const JID & from, int fields, std::string instructions )
    virtual void handleRegistrationResult( const JID & from, RegistrationResult result )
    virtual void handleAlreadyRegistered( const JID & from )
    virtual void handleDataForm( const JID & from, const DataForm& form )
    virtual void handleOOB( const JID & from, const OOB & oob )
    virtual void handleLog( LogLevel level, LogArea area, const std::string & msg );

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

    boost::thread    m_thread;
    boost::mutex     m_mutex;
    boost::condition m_cond;
    MessageSession * m_session;
    Client         * m_client;
    Registration   * m_reg;
    /*
    SIProfileFT* f;
    Bytestream* m_bs;
    SOCKS5BytestreamServer* m_server;
    */
};


#endif





