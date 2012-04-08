
#include "chat.h"
#include "main_wnd.h"

CChat::CChat( CMainWnd * mainWnd )
: QWidget( mainWnd ), 
  m_mainWnd( mainWnd )
{
    ui.setupUi( this );
    m_menu = new QMenu( "Context menu", this );
    m_clear = m_menu->addAction( "Clear" );
    connect( ui.send, SIGNAL(clicked()),       this, SLOT(slotSend()) );
    connect( ui.msg,  SIGNAL(returnPressed()), this, SLOT(slotSend()) );
    connect( m_clear, SIGNAL(triggered()),     this, SLOT(slotClear()) );
}

CChat::~CChat()
{
}

void CChat::contextMenuEvent( QContextMenuEvent * e )
{
    m_menu->popup( e->globalPos() );
}

void CChat::postMessage( const std::string & stri )
{
    ui.history->append( QString::fromUtf8( stri.data(), stri.size() ) );
}

void CChat::slotSend()
{
    //std::string stri = ui.msg->text().toStdString();
    QByteArray ba = ui.msg->text().toUtf8();
    std::string stri( ba.data(), ba.size() ) ;
    ui.msg->clear();
    m_mainWnd->client()->host()->postMessage( m_mainWnd->clientId(), stri );
}

void CChat::slotClear()
{
    ui.history->clear();
}




