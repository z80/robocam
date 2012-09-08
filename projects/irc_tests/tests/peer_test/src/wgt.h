
#ifndef __WGT_H_
#define __WGT_H_

#include <QtGui>
#include "ui_wgt.h"
#include "peer_irc.h"

class Wgt: public QWidget
{
    Q_OBJECT
public:
   Wgt( QWidget * parent = 0 );
   ~Wgt();
   
   void init( lua_State * L );
   void log( const QString & stri );
signals:
    void sigLog( const QString & stri );
private slots:
	void isConnected();
	void send();
	void invoke();
    void clear();
    void slotLog( const QString & stri );
public:
private:
    Ui_Wgt ui;
    PeerIrc * irc;
};


#endif




