
#include "sudo.h"
#include "main_wnd.h"

CSudo::CSudo( CMainWnd * mainWnd )
: QDialog( mainWnd )
{
    ui.setupUi( this );
    connect( ui.submit, SIGNAL(clicked()),       this, SLOT(accept()) );
    connect( ui.passwd, SIGNAL(returnPressed()), this, SLOT(accept()) );
}

CSudo::~CSudo()
{
}


std::string CSudo::passwd() const
{
    return ui.passwd->text().toStdString();
}


