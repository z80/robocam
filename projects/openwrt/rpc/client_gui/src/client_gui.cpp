
#include "client_gui.h"
#include <QPaintEvent>
#include <vector>
#include <boost/bind.hpp>
#include <boost/bind/arg.hpp>
#include <boost/bind/placeholders.hpp>

const QString CClientGui::g_iniFileName = "client.ini";

CClientGui::CClientGui( QWidget * parent )
: QWidget( parent )
{
    ui.setupUi( this );

    // Чтобы файл появился.
    loadSettings();
    saveSettings();

    m_cameraCtrl = new CCameraCtrl( this );
    connectHost();

    connect( ui.setDeviceName, SIGNAL(clicked()), this, SLOT(slotSetDeviceName()) );
    connect( ui.open,          SIGNAL(clicked()), this, SLOT(slotOpen()) );
    connect( ui.isOpened,      SIGNAL(clicked()), this, SLOT(slotIsOpened()) );
    connect( ui.close,         SIGNAL(clicked()), this, SLOT(slotClose()) );
    connect( ui.initDevice,    SIGNAL(clicked()), this, SLOT(slotInitDevice()) );
    connect( ui.imageSize,     SIGNAL(clicked()), this, SLOT(slotImageSize()) );
    connect( ui.startCapture,  SIGNAL(clicked()), this, SLOT(slotStartCapture()) );
    connect( ui.stopCapture,   SIGNAL(clicked()), this, SLOT(slotStopCapture()) );
    connect( ui.acquire,       SIGNAL(clicked()), this, SLOT(slotAcquire()) );
    connect( ui.data,          SIGNAL(clicked()), this, SLOT(slotData()) );
    connect( ui.lastError,     SIGNAL(clicked()), this, SLOT(slotLastError()) );
    connect( ui.clearLog,      SIGNAL(clicked()), this, SLOT(slotClearLog()) );
}

CClientGui::~CClientGui()
{
    m_cameraCtrl->deleteLater();
}

void CClientGui::closeEvent( QCloseEvent * e )
{
}

void CClientGui::connectHost()
{
    m_cameraCtrl->shutdown();
    loadSettings();
    m_cameraCtrl->connect( m_host.toStdString() );
    log( QString( "%1 = connect( %2 )" ).arg( m_cameraCtrl->status().data() ).arg( m_host ) );
}

void CClientGui::loadSettings()
{
    QSettings set( g_iniFileName,  QSettings::IniFormat, this );
    m_host = set.value( "host", "default -p 26011 -h 192.168.1.1" ).toString();
}

void CClientGui::saveSettings()
{
    QSettings set( g_iniFileName,  QSettings::IniFormat, this );
    set.setValue( "host", m_host );
}

void CClientGui::slotSetDeviceName()
{
    m_cameraCtrl->setDeviceName( ui.cameraDev->text().toAscii().data() );
}

void CClientGui::slotOpen()
{
    QString stri = QString( "%1 = open()" ).arg( m_cameraCtrl->open() );
    log( stri );
}

void CClientGui::slotIsOpened()
{
    QString stri = QString( "%1 = isOpened()" ).arg( m_cameraCtrl->isOpened() );
    log( stri );
}

void CClientGui::slotClose()
{
    m_cameraCtrl->close();
    log( "close()" );
}

void CClientGui::slotInitDevice()
{
    int w = 640;
    int h = 480;
    std::string format = "yuyv";
    QString stri = QString( "%1 = initDevice()" ).arg( m_cameraCtrl->initDevice( format, w, h ) );
    log( stri );
}

void CClientGui::slotImageSize()
{
    m_cameraCtrl->imageSize( m_width, m_height, m_sz );
    QString stri = QString( "%1 x %2, %3" ).arg( m_width ).arg( m_height ).arg( m_sz );
    log( stri );
    m_yuyv.resize( m_sz );
    m_image = QImage( m_width, m_height, QImage::Format_RGB888 );
}

void CClientGui::slotStartCapture()
{
    QString stri = QString( "%1 = startCapture()" ).arg( m_cameraCtrl->startCapture() );
    log( stri );
}

void CClientGui::slotStopCapture()
{
    m_cameraCtrl->stopCapture();
    log( "stopCapture()" );
}

void CClientGui::slotAcquire()
{
    QString stri = QString( "%1 = acquire()" ).arg( m_cameraCtrl->acquire() );
    log( stri );
}

void CClientGui::slotData()
{
    const int cnt = 10240;
    std::vector<unsigned char> data;
    m_yuyv.clear();
    m_yuyv.reserve( m_sz );
    for ( int i=0; i<m_sz; i+=cnt )
    {
        data.clear();
        m_cameraCtrl->data( i, cnt, data );
        log( QString( "requested %1, got %2" ).arg( cnt ).arg( data.size() ) );
        for ( unsigned j=0; j<data.size(); j++ )
            m_yuyv.push_back( data[j] );
    }
    log( "data done" );
    QApplication::processEvents();
    // Build image.
    m_cameraCtrl->decodeYuyv( m_width, m_height, m_yuyv, m_raw );
    int ind = 0;
    for ( int y=0; y<m_height; y++ )
    {
        for ( int x=0; x<m_width; x++ )
        {
            int r = m_raw[ ind++ ];
            int g = m_raw[ ind++ ];
            int b = m_raw[ ind++ ];
            m_image.setPixel( x, y, qRgb( r, g, b ) );
        }
    }
    ui.image->setPixmap( QPixmap::fromImage( m_image ) );
}

void CClientGui::slotLastError()
{
    QString stri = m_cameraCtrl->lastError().data();
    log( stri );
}

void CClientGui::slotClearLog()
{
    ui.log->clear();
}

void CClientGui::log( const QString & stri )
{
    ui.log->append( stri );
}





