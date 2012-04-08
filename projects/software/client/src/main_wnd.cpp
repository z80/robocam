
#include "main_wnd.h"
#include "connect.h"
#include "client_list.h"
#include "chat.h"
#include "camera.h"
#include "moto.h"
#include "sudo.h"

#include <boost/bind.hpp>
#include <boost/bind/arg.hpp>
#include <boost/bind/placeholders.hpp>

const QString CMainWnd::g_iniFileName = "client.ini";

CMainWnd::CMainWnd()
: QMainWindow()
{
    ui.setupUi( this );

    connect( ui.actionConnect,  SIGNAL(triggered()), this, SLOT(slotConnect()) );
    connect( ui.actionCtrl,     SIGNAL(triggered()), this, SLOT(slotQueryCtrl()) );
    connect( ui.actionSudoctrl, SIGNAL(triggered()), this, SLOT(slotQuerySuper()) );

    QObject::connect( this, SIGNAL(sigAcceptMessageCb()),    this, SLOT(slotAcceptMessageCb()) );
    QObject::connect( this, SIGNAL(sigAcceptClientListCb()), this, SLOT(slotAcceptClientListCb()) );
    QObject::connect( this, SIGNAL(sigAcceptImageCb()),      this, SLOT(slotAcceptImageCb()) );

    m_clientList = new CClientList( this );
    m_clientListDock = new QDockWidget( "Client list", this );
    connect( ui.actionClientlist, SIGNAL(toggled(bool)), m_clientListDock, SLOT(setVisible(bool)) );
    connect( m_clientListDock, SIGNAL(visibilityChanged(bool)), ui.actionClientlist, SLOT(setChecked(bool)) );
    m_clientListDock->setAllowedAreas( Qt::LeftDockWidgetArea | 
                                       Qt::RightDockWidgetArea );
    m_clientListDock->setWidget( m_clientList );
    addDockWidget(Qt::RightDockWidgetArea, m_clientListDock );
    m_clientListDock->setVisible( false );

    m_chat = new CChat( this );
    m_chatDock = new QDockWidget( "Chat", this );
    connect( ui.actionChat, SIGNAL(toggled(bool)), m_chatDock, SLOT(setVisible(bool)) );
    connect( m_chatDock, SIGNAL(visibilityChanged(bool)), ui.actionChat, SLOT(setChecked(bool)) );
    m_chatDock->setAllowedAreas( Qt::LeftDockWidgetArea | 
                                 Qt::RightDockWidgetArea );
    m_chatDock->setWidget( m_chat );
    addDockWidget(Qt::LeftDockWidgetArea, m_chatDock );
    m_chatDock->setVisible( false );
    
    m_camera = new CCamera( this );
    setCentralWidget( m_camera );
    //connect( ui.actionCamera, SIGNAL(toggled(bool)), m_camera, SLOT(setEnabled(bool)) );
    //connect( m_chatDock, SIGNAL(visibilityChanged(bool)), ui.actionCamera, SLOT(setChecked(bool)) );

    m_moto = new CMoto( this );
    m_motoDock = new QDockWidget( "Moto", this );
    connect( ui.actionMoto, SIGNAL(toggled(bool)), m_motoDock, SLOT(setVisible(bool)) );
    connect( m_motoDock, SIGNAL(visibilityChanged(bool)), ui.actionMoto, SLOT(setChecked(bool)) );
    m_motoDock->setAllowedAreas( Qt::BottomDockWidgetArea | 
                                 Qt::TopDockWidgetArea );
    m_motoDock->setWidget( m_moto );
    addDockWidget(Qt::BottomDockWidgetArea, m_motoDock );
    m_motoDock->setVisible( false );

    loadSettings();
    setSuperEnabled( false );
}

CMainWnd::~CMainWnd()
{
}

void CMainWnd::closeEvent( QCloseEvent * e )
{
    hdwDisconnect();
    saveSettings();
}


CClientIceThread * CMainWnd::client()
{
    return m_client.get();
}

const std::string & CMainWnd::clientId()
{
    return m_client->clientId();
}

void CMainWnd::slotConnect()
{
    if ( ui.actionConnect->isChecked() )
        hdwConnect();
    else
        hdwDisconnect();
}

void CMainWnd::slotQueryCtrl()
{
    if ( ui.actionCtrl->isChecked() )
    {
        if ( ui.actionSudoctrl->isChecked() )
        {
            ui.actionSudoctrl->setChecked( false );
            m_client->releaseCtrl();
            setSuperEnabled( false );
        }
        if( m_client->queryCtrl() )
            setCtrlEnabled( true );
        else
            ui.actionSudoctrl->setChecked( false );
    }
    else
    {
        m_client->releaseCtrl();
        setCtrlEnabled( false );
        m_client->queryView();
        setViewEnabled( true );
    }
}

void CMainWnd::slotQuerySuper()
{
    if ( ui.actionSudoctrl->isChecked() )
    {
        if ( ui.actionCtrl->isChecked() )
        {
            ui.actionCtrl->setChecked( false );
            m_client->releaseCtrl();
            setCtrlEnabled( false );
        }
        CSudo s( this );
        if ( s.exec() == QDialog::Accepted )
        {
            std::string passwd = s.passwd();
            if ( m_client->querySuper( passwd ) )
                setSuperEnabled( true );
            else
                ui.actionSudoctrl->setChecked( false );
        }
    }
    else
    {
        m_client->releaseCtrl();
        setSuperEnabled( false );
        m_client->queryView();
        setViewEnabled( true );
    }
}

void CMainWnd::slotAcceptMessageCb()
{
    QMutexLocker lock( &m_mutex );
    m_chat->postMessage( m_msg );
}

void CMainWnd::slotAcceptClientListCb()
{
    QMutexLocker lock( &m_mutex );
    m_clientList->setClientList( m_clients, m_driverNickname );
}

void CMainWnd::slotAcceptImageCb()
{
    QMutexLocker lock( &m_mutex );
    m_imageBa.clear();
    m_imageBa.resize( m_imageData.size() );
    ::Ice::Byte * d = reinterpret_cast< ::Ice::Byte * >( m_imageBa.data() );
    for ( unsigned i=0; i<m_imageData.size(); i++ )
        d[i] = m_imageData.at( i );
    QBuffer b( &m_imageBa );
    b.open( QIODevice::ReadOnly );
    m_image.load( &b, "PNG" );
    m_camera->setImage( m_image );
}

void CMainWnd::displayImage( const ::Types::TByteArray & data )
{
    m_mutex.lock();
    m_imageData = data;
    m_mutex.unlock();

    slotAcceptImageCb();
}

void CMainWnd::loadSettings()
{
    QSettings set( g_iniFileName,  QSettings::IniFormat, this );
    m_host     = set.value( "host", "tcp -p 26001 -h localhost" ).toString().toStdString();
    m_nickname = set.value( "nickname", "anonimous" ).toString().toStdString();
}

void CMainWnd::saveSettings()
{
    QSettings set( g_iniFileName,  QSettings::IniFormat, this );
    set.setValue( "host",     QString::fromStdString( m_host ) );
    set.setValue( "nickname", QString::fromStdString( m_nickname ) );
}

void CMainWnd::setViewEnabled( bool en )
{
    m_chatDock->setEnabled( en );
    m_clientList->setEnabled( en );

    ui.actionCtrl->setEnabled( en ); 
    ui.actionSudoctrl->setEnabled( en );
}

void CMainWnd::setCtrlEnabled( bool en )
{
    setViewEnabled( en );
    m_camera->setCtrlEnabled( en );
    m_moto->setCtrlEnabled( en );
}

void CMainWnd::setSuperEnabled( bool en )
{
    setViewEnabled( en );
    m_camera->setSuperEnabled( en );
    m_moto->setSuperEnabled( en );
}

void CMainWnd::hdwConnect()
{
    CConnect c( this );
    c.setHost( m_host );
    c.setNickname( m_nickname );
    if ( c.exec() == QDialog::Accepted )
    {
        m_host = c.host();
        m_nickname = c.nickname();
        m_client = new CClientIceThread( m_host, m_nickname );
        // Assigning callback functions.
        m_client->setAcceptMessageCb( boost::bind( &CMainWnd::acceptMessageCb, this, _1 ) );
        m_client->setAcceptClientListCb( boost::bind( &CMainWnd::acceptClientListCb, this, _1, _2 ) );
        m_client->setAcceptImageCb( boost::bind( &CMainWnd::acceptImageCb, this, _1 ) );

        // Executing message thread
        if ( !m_client->connect() )
        {
            ui.actionConnect->setChecked( false );
            QMessageBox::warning( this, "Host unreachable", QString( "Failed to connect to host\n %1" ).arg( QString::fromStdString( m_client->clientId() ) ) );
            hdwDisconnect();
            return;
        }
        if ( m_client->queryView() )
            setViewEnabled( true );
    }
    else
        ui.actionConnect->setChecked( false );
}

void CMainWnd::hdwDisconnect()
{
    if ( m_client )
    {
        if( m_client->status() == "connected" )
            m_client->shutdown();
        m_client = 0;
    }
    setViewEnabled( false );
    setCtrlEnabled( false );
}

void CMainWnd::acceptMessageCb( const std::string & stri )
{
    QMutexLocker lock( &m_mutex );
    m_msg = stri;
    emit sigAcceptMessageCb();
}

void CMainWnd::acceptClientListCb( const std::vector<std::string> & clients, const std::string & driverNickname )
{
    QMutexLocker lock( &m_mutex );
    m_clients = clients;
    m_driverNickname = driverNickname;
    emit sigAcceptClientListCb();
}

void CMainWnd::acceptImageCb( const ::Types::TByteArray & data )
{
    QMutexLocker lock( &m_mutex );
    m_imageData = data;
    emit sigAcceptImageCb();
}








