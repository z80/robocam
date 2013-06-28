
#ifndef __MAIN_WND_H_
#define __MAIN_WND_H_


#include <QtGui>
#include "ui_main_wnd.h"

#include "xmpp_io.h"
#include "xmpp_video.h"


class MainWnd: public QWidget
{
    Q_OBJECT
public:
    MainWnd( QWidget * parent = 0 );
    ~MainWnd();

private slots:
    void slotCall();
    void slotEndCall();
    void slotFrameReady();
private:
    Ui_MainWnd ui;
    QXmppPeer  * peer;
    QXmppVideo * video;
};



#endif


