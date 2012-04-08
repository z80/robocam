
#ifndef __CHAT_H_
#define __CHAT_H_

#include <QtGui>
#include "ui_chat.h"

class CMainWnd;

class CChat: public QWidget
{
    Q_OBJECT
public:
    CChat( CMainWnd * mainWnd );
    ~CChat();

    void postMessage( const std::string & stri );

    void contextMenuEvent( QContextMenuEvent * e );
private slots:
    void slotSend();
    void slotClear();
private:
    Ui_CChat ui;
    CMainWnd * m_mainWnd;
    QMenu    * m_menu;
    QAction  * m_clear;
};



#endif




