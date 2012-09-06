
#ifndef __WGT_H_
#define __WGT_H_

#include <QtGui>
#include "ui_wgt.h"
#include "irc_peer.h"

class Wgt: public QWidget
{
    Q_OBJECT
public:
   Wgt( QWidget * parent = 0 );
   ~Wgt();
   
   void log( const QString & stri );
signals:
    void sigLog( const QString & stri );
private slots:
    void connectHost();
    void join();
    void channelList();
    void clientList();
    void isConnected();
    void isJoined();
    void send();
    void status();
    void clear();
    void slotLog( const QString & stri );
public:
    // Message and event handlers...
    void messageHandler( const std::string & client, const std::string & stri );
private:
    Ui_Wgt ui;
    IrcPeer irc;
};


#endif




