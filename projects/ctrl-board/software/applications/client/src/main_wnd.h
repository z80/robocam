
#ifndef __MAIN_WND_H_
#define __MAIN_WND_H_

#include <QtGui>
#include "xmpp_io.h"
#include "xmpp_video.h"
#include "lua_machine.h"
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
    void slotShowFullLog();
    void slotConnected();
    void slotDisconnected();

    // Controls
    void slotStatus();
    void slotShutdown();
    void slotForward();
    void slotBackward();
    void slotLeft();
    void slotRight();
private:
	void log( const std::string & stri );

    Ui_MainWnd  ui;
	QXmppPeer * m_peer;
    QXmppVideo * m_video;

	static const std::string CONFIG_FILE;
	static const int         LOG_MAX;
	static const int         MOTO_TIME_MAX; // Due to big ping in the case of fast movements
	                                          // it is necessary to be ablt
	                                          // to set moto time explicitly.
    static const int MOTO1,
                     MOTO2,
                     MOTO3,
                     MOTO4;
    QImage m_img;
public slots:
	void slotSend( const QString & stri );
    void qxmppMessageReceived( const QString & );
};



#endif



