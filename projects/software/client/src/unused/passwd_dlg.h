
#ifndef __PASSWD_DLG_H__
#define __PASSWD_DLG_H__

#include "ui_passwd_dlg.h"

class CPasswdDlg: public ::QDialog
{
public:
    CPasswdDlg( QWidget * parent );
    ~CPasswdDlg();

    std::string passwd() const;
private:
    Ui_PasswdDlg ui;
};

#endif


