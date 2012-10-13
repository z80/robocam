
#ifndef __MAIN_WND_H_
#define __MAIN_WND_H_

#include <QtGui>
#include "peer_qxmpp.h"
#include "ui_main_wnd.h"

class MainWnd: public QMainWindow
{
	Q_OBJECT
public:
	MainWnd( QWidget * parent = 0 );
	~MainWnd();

signals:
    void sigLog( const QString & );
private slots:
    void slotLog( const QString & );
public:
	int print( lua_State * L );
private:
	void init( lua_State * L );
	QIODevice * inFileHandler( const std::string & fileName );
	void accFileHandler( const std::string & fileName, QIODevice * file );
	void log( const std::string & stri );

	Ui_MainWnd ui;
	PeerQxmpp * m_peer;

	static const std::string CONFIG_FILE;
};



#endif



