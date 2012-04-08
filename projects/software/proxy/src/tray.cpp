
#include "tray.h"

const QString CTray::g_iniFileName = "proxy.ini";

CTray::CTray( QObject * parent )
: QSystemTrayIcon( parent )
{
    m_proxy = 0;
    m_listenHost  = "";
    m_connectHost = "10.8.0.2";
    m_listenPort  = 26001;
    m_connectPort = 26001;

    setIcon( QIcon( ":images/arrow.png" ) );
    setToolTip( "Internetwork proxy" );

    m_menu = new QMenu();
    m_menu->setTitle( "Menu" );
    m_menu->setTearOffEnabled( true );

    m_actionListen = new QAction( "Listen clients", m_menu );
    m_actionListen->setCheckable( true );
    connect( m_actionListen, SIGNAL(triggered()), this, SLOT(slotListen()) );
    m_menu->addAction( m_actionListen );

    m_actionQuit = new QAction( "Quit", m_menu );
    connect( m_actionQuit, SIGNAL(triggered()), this, SLOT(slotQuit()) );
    m_menu->addAction( m_actionQuit );

    setContextMenu( m_menu );
    
    loadSettings();

    show();
}

CTray::~CTray()
{
    if ( m_proxy )
        m_proxy->deleteLater();
}

const QString & CTray::iniFileName()
{
    return g_iniFileName;
}

void CTray::slotListen()
{
    if ( m_proxy )
        m_proxy->deleteLater();
    if ( m_actionListen->isChecked() )
    {
        loadSettings();
        m_proxy = new CProxy( this, m_listenHost, m_listenPort, m_connectHost, m_connectPort );
        if ( !m_proxy->isListening() )
        {
            m_proxy->deleteLater();
            m_proxy = 0;
            m_actionListen->setChecked( false );
            setToolTip( "Idle" );
        }
        else
            setToolTip( "Listening" );
    }
}

void CTray::slotQuit()
{
    hide();
    saveSettings();
    QApplication::quit();
}

void CTray::loadSettings()
{
    QSettings set( g_iniFileName,  QSettings::IniFormat, this );
    m_listenHost  = set.value( "listenHost",  "" ).toString();
    m_connectHost = set.value( "connectHost", "localhost" ).toString();
    m_listenPort  = set.value( "listenPort",  "1234" ).toInt();
    m_connectPort = set.value( "connectPort", "26001" ).toInt();
}

void CTray::saveSettings()
{
    QSettings set( g_iniFileName,  QSettings::IniFormat, this );
    set.setValue( "listenHost",  m_listenHost );
    set.setValue( "connectHost", m_connectHost );
    set.setValue( "listenPort",  m_listenPort );
    set.setValue( "connectPort", m_connectPort );
}

