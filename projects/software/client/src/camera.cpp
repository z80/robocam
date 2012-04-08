
#include "camera.h"
#include "main_wnd.h"
#include "client_ice_thread.h"

CCamera::CCamera( CMainWnd * mainWnd )
: QWidget( mainWnd )
{
    m_mainWnd = mainWnd;
    ui.setupUi( this );

    QMenu * periodMenu = new QMenu();
    actPeriodOff = periodMenu->addAction( "Off" );
    actPeriod30  = periodMenu->addAction( "30s" );
    actPeriod10  = periodMenu->addAction( "10s" );
    actPeriod3   = periodMenu->addAction( "3s" );
    actPeriod1   = periodMenu->addAction( "1s" );
    actPeriod03  = periodMenu->addAction( "0.3s" );
    ui.imagePeriod->setMenu( periodMenu );
    connect( ui.imagePeriod, SIGNAL(triggered(QAction *)), this, SLOT(slotSetPeriod(QAction *)) );

    QMenu * resMenu = new QMenu();
    actRes800x600 = resMenu->addAction( "800x600" );
    actRes640x480 = resMenu->addAction( "640x480" );
    actRes320x240 = resMenu->addAction( "320x240" );
    actRes160x120 = resMenu->addAction( "160x120" );
    ui.imageRes->setMenu( resMenu );
    connect( ui.imageRes, SIGNAL(triggered(QAction *)), this, SLOT(slotSetResolution(QAction *)) );

    connect( ui.imageQuery, SIGNAL(clicked()), this, SLOT(slotQueryImage()) );

    m_scene = new QGraphicsScene( ui.view );
    m_scene->setBackgroundBrush( QBrush( Qt::gray ) );
    ui.view->setScene( m_scene );

    m_item = new QGraphicsPixmapItem( 0, m_scene );
    m_item->setPos( 0.0, 0.0 );
    m_item->setPixmap( QPixmap( ":/images/camera.png" ) );
}

CCamera::~CCamera()
{
}

void CCamera::setCtrlEnabled( bool en )
{
    ui.imageCtrl->setEnabled( en );
    ui.imageQuery->setEnabled( en );
    ui.imagePeriod->setEnabled( en );
    ui.imageRes->setEnabled( false );
}

void CCamera::setSuperEnabled( bool en )
{
    setCtrlEnabled( en );
    ui.imageSuper->setEnabled( en );
    ui.imageRes->setEnabled( en );
}

void CCamera::setImage( const QImage & img )
{
    QPixmap pm = QPixmap::fromImage( img );
    updatePixmap( pm );
}

void CCamera::resizeEvent( QResizeEvent * e )
{
    updatePixmap( m_item->pixmap() );
}

void CCamera::slotSetPeriod( QAction * action )
{
    CClientIceThread * c = m_mainWnd->client();
    if ( !c )
        return;
    ::Host::CCamPrx cam = c->cam();
    if ( !cam )
        return;
    if ( action == actPeriodOff )
        cam->setReceiveImages( false );
    else
    {
        if ( action == actPeriod30 )
            cam->setPeriod( 30.0 );
        else if ( action == actPeriod10 )
            cam->setPeriod( 10.0 );
        else if ( action == actPeriod3 )
            cam->setPeriod( 3.0 );
        else if ( action == actPeriod1 )
            cam->setPeriod( 1.0 );
        else if ( action == actPeriod03 )
            cam->setPeriod( 0.3 );
        cam->setReceiveImages( true );
    }
}

void CCamera::slotSetResolution( QAction * action )
{
    CClientIceThread * c = m_mainWnd->client();
    if ( !c )
        return;
    ::Host::CCamPrx cam = c->cam();
    if ( !cam )
        return;
    if ( action == actRes800x600 )
        cam->setResolution( 800, 600 );
    else if ( action == actRes640x480 )
        cam->setResolution( 640, 480 );
    else if ( action == actRes320x240 )
        cam->setResolution( 320, 240 );
    else if ( action == actRes160x120 )
        cam->setResolution( 160, 120 );
}

void CCamera::slotQueryImage()
{
    CClientIceThread * c = m_mainWnd->client();
    if ( !c )
        return;
    ::Host::CCamPrx cam = c->cam();
    if ( !cam )
        return;
    if ( cam->image( m_data ) )
        m_mainWnd->displayImage( m_data );
}

void CCamera::updatePixmap( const QPixmap & pm )
{
    QSizeF imgSz = pm.size();
    QSizeF wndSz = ui.view->size();

    qreal sc;
    if ( imgSz.width() * wndSz.height() > imgSz.height() * wndSz.width() )
        sc = wndSz.width() / imgSz.width();
    else
        sc = wndSz.height() / imgSz.height();

    m_scene->setSceneRect( QRectF( 0.0, 0.0, wndSz.width(), wndSz.height() ) );
    m_item->setPixmap( pm );
    m_item->setPos( 0.0, 0.0 );
    m_item->setScale( sc );
}


