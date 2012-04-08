
#ifndef __CONNECT_H_
#define __CONNECT_H_

#include <QtGui>
#include "ui_connect.h"

class CMainWnd;

class CConnect: public QDialog
{
    Q_OBJECT
public:
    CConnect( CMainWnd * mainWnd );
    ~CConnect();

    void setHost( const std::string & h );
    std::string host() const;
    void setNickname( const std::string & nick );
    std::string nickname() const;
private:
    Ui_CConnect ui;
};


#endif


