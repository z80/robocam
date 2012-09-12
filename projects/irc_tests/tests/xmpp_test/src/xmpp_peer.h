
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
#include "stanza.h"
#include "connectionlistener.h"
#include "registrationhandler.h"
#include "registration.h"
#include "siprofileft.h"
#include "siprofilefthandler.h"
#include "inbandbytestream.h"
#include "inbandbytestreammanager.h"
#include "inbandbytestreamhandler.h"
#include "inbandbytestreamdatahandler.h"


class XmppPeer: public gloox::MessageSessionHandler,
                public gloox::MessageEventHandler,
                public gloox::MessageHandler,
                public gloox::ConnectionListener,
                public gloox::LogHandler,
                public gloox::RegistrationHandler, 
                public gloox::InBandBytestreamHandler,
                public gloox::InBandBytestreamDataHandler

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
    bool connect();
    bool registerClient();
    bool isConnected() const;
    void terminate();
    bool send( const std::string & to, const std::string & msg );
    // File io.
    void setPieceSize( int bytes = 2048 );
    void sendFile( const std::string & to, const char * data, int sz );
    bool isFileFinished() const;
    bool isFileSucceeded() const;
    void reserveFileBuffer( int size );

    const std::string lastError() const;

    // Reimplementing virtual methods...
    virtual void onConnect();
    virtual void onDisconnect( gloox::ConnectionError e );
    virtual bool onTLSConnect( const gloox::CertInfo & info );
    virtual void handleMessage( gloox::Stanza * stanza, gloox::MessageSession * );
    virtual void handleMessageEvent( const gloox::JID & from, gloox::MessageEventType type );
    virtual void handlerChatState( const gloox::JID & from, gloox::ChatStateType type );
    virtual void handleMessageSession( gloox::MessageSession * s );
    virtual void handleRegistrationFields( const gloox::JID & from, int fields, std::string instructions );
    virtual void handleRegistrationResult( const gloox::JID & from, gloox::RegistrationResult result );
    virtual void handleAlreadyRegistered( const gloox::JID & from );
    virtual void handleDataForm( const gloox::JID & from, const gloox::DataForm& form );
    virtual void handleOOB( const gloox::JID & from, const gloox::OOB & oob );
    virtual void handleLog( gloox::LogLevel level, gloox::LogArea area, const std::string & msg );

    // InBand data io.
    virtual bool handleIncomingInBandBytestream( const gloox::JID & from, gloox::InBandBytestream * ibb );
    virtual void handleOutgoingInBandBytestream( const gloox::JID & to,   gloox::InBandBytestream * ibb );
    virtual void handleInBandBytestreamError( const gloox::JID& /*remote*/, gloox::StanzaError /*se*/ );
    virtual void handleInBandData( const std::string& data, const std::string& sid );
    virtual void handleInBandError( const std::string& /*sid*/, const gloox::JID& /*remote*/, gloox::StanzaError /*se*/ );
    virtual void handleInBandClose( const std::string& /*sid*/, const gloox::JID& /*from*/ );

private:
    void run( bool reg );

    // Client desc.
    std::string m_jid,
                m_password,
                m_host,
                m_lastError;
    int         m_port;
    bool        m_connected, 
                m_registered, 
                m_doRegister;

    TMessageHandler m_messageHandler;
    TLogHandler     m_logHandler;

    boost::thread         m_thread;
    mutable boost::mutex  m_mutex;
    boost::condition      m_cond;
    gloox::MessageSession * m_session;
    gloox::Client         * m_client;
    gloox::Registration   * m_reg;

    gloox::InBandBytestreamManager * m_ibbManager;
    gloox::InBandBytestream        * m_ibb;
    gloox::MessageSession          * m_fileSession;
    int m_filePieceSize;
    bool m_isFileFinished,
         m_isFileSucceeded;
    const char * m_fileData;
    int    m_fileSize, 
           m_filePointer;
    std::basic_string<char> m_fileReceived;
};


#endif





