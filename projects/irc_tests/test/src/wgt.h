
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
private slots:
    void connectHost();
    void join();
    void channeList();
    void clientList();
    void isConnected();
    void isJoined();
    void listChannels();
    void listClients();
    void status();
    void clear();
public:
    // Message and event handlers...
private:
    Ui_Wgt ui;
    IrcPeer irc;
};


#endif




