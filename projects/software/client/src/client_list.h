
#ifndef __CLIENT_LIST_H_
#define __CLIENT_LIST_H_

#include <QtGui>
#include "ui_client_list.h"

class CMainWnd;

class CClientList: public QWidget
{
    Q_OBJECT
public:
    CClientList( CMainWnd * mainWnd );
    ~CClientList();

    void setClientList( const std::vector<std::string> & list, const std::string & driverNickname );
private:
    Ui_CClientList ui;
};



#endif

