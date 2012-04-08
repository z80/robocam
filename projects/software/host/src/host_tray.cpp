
#include "host_tray.h"

const QString CHostTray::g_iniFileName = "host.ini";

CHostTray::CHostTray( QObject * parent )
: QSystemTrayIcon( parent )
{
    m_listen  = "tcp -p 26001";
    m_connect = "default -p 12345";
    m_passwd  = "qwertyqwerty";
    m_emulation = true;

    setIcon( QIcon( ":images/arrow.png" ) );
    setToolTip( "Hardware control host" );

    m_menu = new QMenu();
    m_menu->setTitle( "Menu" );
    m_menu->setTearOffEnabled( true );

    m_actionListen = new QAction( "Listen clients", m_menu );
    m_actionListen->setCheckable( true );
    connect( m_actionListen, SIGNAL(triggered()), this, SLOT(slotListen()) );
    m_menu->addAction( m_actionListen );

    m_actionConnect = new QAction( "Connect hardware", m_menu );
    m_actionConnect->setCheckable( true );
    connect( m_actionConnect, SIGNAL(triggered()), this, SLOT(slotConnect()) );
    m_menu->addAction( m_actionConnect );

    m_actionQuit = new QAction( "Quit", m_menu );
    connect( m_actionQuit, SIGNAL(triggered()), this, SLOT(slotQuit()) );
    m_menu->addAction( m_actionQuit );

    setContextMenu( m_menu );

    show();
}

CHostTray::~CHostTray()
{
    m_actionListen->setChecked( false );
    slotListen();
    hide();
}

const QString & CHostTray::iniFileName()
{
    return g_iniFileName;
}

void CHostTray::slotListen()
{
    if ( m_host )
    {
        saveSettings();
        bool started = m_host->isAlive();
        if ( started )
            m_host->shutdown();
    }
    if ( m_actionListen->isChecked() )
    {
        loadSettings();
        m_host = new CHostIceThread( m_listen.toStdString(), 
                                     m_connect.toStdString(), 
                                     m_passwd.toStdString() );
        if ( !m_host->listen() )
        {
            m_actionListen->setChecked( false );
            return;
        }
        m_actionConnect->setChecked( true );
        slotConnect();
    }
}

void CHostTray::slotConnect()
{
    if ( m_actionConnect->isChecked() )
    {
        bool res = m_host->connect( m_emulation );
        if ( !res )
            m_actionConnect->setChecked( false );
    }
    else
    {
        // Disconnection from hardware should be here.
    }
}

void CHostTray::slotQuit()
{
    hide();
    slotListen();
    QApplication::quit();
}

void CHostTray::loadSettings()
{
    QSettings set( g_iniFileName,  QSettings::IniFormat, this );
    m_listen  = set.value( "listen",  "tcp -p 26001 -t 5000" ).toString();
    m_connect = set.value( "connect", "default -p 12345 -t 5000" ).toString();
    m_passwd  = set.value( "passwd", "qwertyqwerty" ).toString();
    m_emulation = set.value( "emulation", true ).toBool();
}

void CHostTray::saveSettings()
{
    QSettings set( g_iniFileName,  QSettings::IniFormat, this );
    set.setValue( "listen",  m_listen );
    set.setValue( "connect", m_connect );
    set.setValue( "passwd",  m_passwd );
    set.setValue( "emulation", m_emulation );
}

