
#ifndef __FSW_PROCESS_H_
#define __FSW_PROCESS_H_

#include <QtGui>
#include "lua.hpp"

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

private slots:
	void timeout();
	void slotFinished( int exitCode, QProcess::ExitStatus exitStatus );
private:
	QString m_command;
	QStringList m_args;
	QString m_fileName;
	int m_interval;
	bool m_loop,
	     m_stop,
	     m_running;
	PeerAbst * m_peer;

	static const int CHECK_TIMEOUT;
};


#endif


