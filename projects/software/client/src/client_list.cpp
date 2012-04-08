
#include "client_list.h"
#include "main_wnd.h"

CClientList::CClientList( CMainWnd * mainWnd )
: QWidget( mainWnd )
{
    ui.setupUi( this );
}

CClientList::~CClientList()
{
}

void CClientList::setClientList( const std::vector<std::string> & list, const std::string & driverNickname )
{
    ui.ctrlBy->setText( QString::fromStdString( driverNickname ) );
    ui.list->clear();
    for ( unsigned i=0; i<list.size(); i++ )
        ui.list->addItem( QString::fromStdString( list.at( i ) ) );
}


