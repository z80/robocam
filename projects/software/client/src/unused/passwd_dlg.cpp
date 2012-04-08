
#include "passwd_dlg.h"

CPasswdDlg::CPasswdDlg( QWidget * parent )
: QDialog( parent )
{
    ui.setupUi( this );
    connect( ui.ok, SIGNAL(clicked()), this, SLOT(accept()) );
}

CPasswdDlg::~CPasswdDlg()
{
}

std::string CPasswdDlg::passwd() const
{
    return ui.passwd->text().toStdString();
}



