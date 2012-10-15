
#ifndef __FSW_PROCESS_H_
#define __FSW_PROCESS_H_

#include <QtGui>
#include "lua.hpp"
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>

extern "C" int luaopen_luafsw( lua_State * L );

class PeerAbst;

class FswProcess: public QProcess
{
	Q_OBJECT
public:
	FswProcess();
	~FswProcess();

	void setCommand( const QString & stri );
	void setPeer( PeerAbst * peer );
	void setSendFileName( const QString & fileName );
	void setInterval( int i );
	void setLoop( bool en );
	void start();
	void stop();
	bool isRunning() const;

signals:
    void sigTimeout();
private slots:
    void slotError( QProcess::ProcessError );
	void slotTimeout();
	void slotStateChanged( QProcess::ProcessState );
private:
	void threadProc();
	QString m_command;
	QStringList m_args;
	QString m_fileName;
	int m_interval;
	bool m_loop,
	     m_stop,
	     m_running;
	PeerAbst * m_peer;
	boost::thread m_thread;
	mutable boost::mutex m_mutex;

	static const int CHECK_TIMEOUT;
};


#endif


