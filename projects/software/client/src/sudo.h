
#ifndef __SUDO_H_
#define __SUDO_H_

#include <QtGui>
#include "ui_sudo.h"

class CMainWnd;

class CSudo: public QDialog
{
public:
    CSudo( CMainWnd * mainWnd );
    ~CSudo();

    std::string passwd() const;
private:
    Ui_CSudo ui;
};




#endif



