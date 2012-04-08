
#include "connect.h"

CConnect::CConnect( CMainWnd * mainWnd )
{
    ui.setupUi( this );
    connect( ui.connect, SIGNAL(clicked()),        this, SLOT(accept()) );
    connect( ui.nickname, SIGNAL(returnPressed()), this, SLOT(accept()) );
}

CConnect::~CConnect()
{
}

void CConnect::setHost( const std::string & h )
{
    ui.host->setText( QString::fromStdString( h ) );
}

std::string CConnect::host() const
{
    return ui.host->text().toStdString();
}

void CConnect::setNickname( const std::string & nick )
{
    ui.nickname->setText( QString::fromStdString( nick ) );
}

std::string CConnect::nickname() const
{
    return ui.nickname->text().toStdString();
}
