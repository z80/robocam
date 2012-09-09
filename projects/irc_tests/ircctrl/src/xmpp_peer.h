
#ifndef __XMPP_PEER_H_
#define __XMPP_PEER_H_

#include <string>
#include <boost/thread.hpp>
#include <boost/function.hpp>
#include "messagesessionhandler.h"
#include "messageeventhandler.h"
#include "connectionlistener.h"
#include "message.h"

class XmppPeer: public MessageSessionHandler,
                 public MessageEventHandler,
                 public MessageHandler,
                 public ConnectionListener,
                 public LogHandler

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
	virtual void handleLog( LogLevel level, LogArea area, const std::string & msg );

private:
	void run();

	// Client desc.
	std::string m_jid,
	            m_password,
	            m_host,
	            m_lastError;
	int        m_port;
	bool       m_connected;

	TMessageHandler m_messageHandler;
	TLogHandler     m_logHandler;

	boost::thread    m_thread;
	boost::mutex     m_mutex;
	boost::condition m_cond;
	MessageSession * m_session;
	Client         * m_client;
};


#endif





