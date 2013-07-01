
#include "capture_wgt.h"
#include "ui_capture_wgt.h"
#include "xmpp_video.h"
#include "brightness_wgt.h"



class CInitResource
{
public:
    CInitResource()
    {
        Q_INIT_RESOURCE( images );
    }

    ~CInitResource()
    {
        Q_CLEANUP_RESOURCE( images );
    }
};

class CaptureWgt::PD
{
public:
    PD()
    {
        static CInitResource resource;
    }

    ~PD() {}

    Ui_CaptureWgt ui;
    QXmppVideo * video;
    QImage        img;
    BrightnessWgt * brightness;

    QPointF imgAt;
    QPointF imgPos;
    QPointF markerPos;
    qreal   imgScale;
    bool flipX, 
         flipY;
    QSize imgSize;

    QList<QAction *> filterList;

    QGraphicsScene      * scene;
    QGraphicsPixmapItem * image;
    QGraphicsLineItem   * lineX1, 
                        * lineY1, 
                        * lineX2, 
                        * lineY2;

    void crossPos( CaptureWgt * owner, const QPointF & at );
};

void CaptureWgt::PD::crossPos( CaptureWgt * owner, const QPointF & at )
{
    QPointF imgAt = ui.view->mapToScene( at.x(), at.y() );
    qreal xx = ( imgAt.x() - imgPos.x() ) / imgScale;
    qreal yy = ( imgAt.y() - imgPos.y() ) / imgScale;
    this->imgAt = QPointF( xx, yy );
    if ( ui.laser->isChecked() )
        markerPos = QPointF( xx, yy );
    owner->emitMouseEvent();
}

CaptureWgt::CaptureWgt( QWidget * parent )
: QMainWindow( parent )
{
    pd = new PD();
    pd->ui.setupUi( this );

    pd->video = 0;
    pd->imgScale = 1.0;
    pd->flipX = false;
    pd->flipY = false;
    pd->ui.brightnessDw->setVisible( false );
    pd->brightness = new BrightnessWgt( this );
    pd->ui.brightnessDw->setWidget( pd->brightness );
    connect( pd->brightness, SIGNAL(rangeChanged(const QPointF &)), 
             this,           SLOT(slotBrightnessChanged(const QPointF &)) );
    connect( pd->ui.brightnessRange, SIGNAL(triggered()), 
             this,                   SLOT(slotBrightness()) );

    Ui_CaptureWgt & ui = pd->ui;
    connect( ui.capture,  SIGNAL(triggered()), this, SLOT(slotCapture()) );

    pd->scene = new QGraphicsScene( pd->ui.view );
    pd->scene->setBackgroundBrush( QBrush( Qt::gray ) );
    pd->ui.view->setScene( pd->scene );

    pd->image = new QGraphicsPixmapItem( 0, pd->scene );
    pd->image->setPos( 0.0, 0.0 );
    pd->lineX1 = new QGraphicsLineItem( pd->image, pd->scene );
    pd->lineY1 = new QGraphicsLineItem( pd->image, pd->scene );
    pd->lineX2 = new QGraphicsLineItem( pd->image, pd->scene );
    pd->lineY2 = new QGraphicsLineItem( pd->image, pd->scene );
    //pd->image->setPixmap( QPixmap( ":/images/camera.png" ) );

    connect( pd->ui.flipX, SIGNAL(triggered()), this, SLOT(slotFlipX()) );
    connect( pd->ui.flipY, SIGNAL(triggered()), this, SLOT(slotFlipY()) );

    ui.view->installEventFilter( this );

    // Действия соответствующие фильтрам.
    pd->filterList << ui.equalizeHist;
    pd->filterList << ui.fullContrast;
    pd->filterList << ui.sobel;
    pd->filterList << ui.median;
    pd->filterList << ui.timeSmooth;
    pd->filterList << ui.highPass;
    pd->filterList << ui.surface;
    pd->filterList << ui.brightnessRange;
    for ( int i=0; i<pd->filterList.size(); i++ )
    {
        QAction * a = pd->filterList[i];
        connect( a, SIGNAL(triggered()), this, SLOT(slotFilter()) );
    }

    connect( ui.pixmap, SIGNAL(triggered()), this, SLOT(slotSavePixmap()) );
}

CaptureWgt::~CaptureWgt()
{
    delete pd;
}

void CaptureWgt::setVideo( QXmppVideo * video )
{
    if ( pd->video )
        disconnect( pd->video, SIGNAL(frameReady()), this, SLOT(slotFrameReady()) );
    pd->video = video;
    connect( pd->video, SIGNAL(frameReady()), this, SLOT(slotFrameReady()) );
}

bool CaptureWgt::eventFilter( QObject * o, QEvent * e )
{
    if ( e->type() == QEvent::MouseButtonPress )
    {
        QMouseEvent * m = reinterpret_cast<QMouseEvent *>( e );
        pd->crossPos( this, m->posF() );
    }
    return false;
}

void CaptureWgt::resizeEvent( QResizeEvent * e )
{
    QSizeF sz = pd->ui.view->size();
    pd->ui.view->setSceneRect( 0.0, 0.0, sz.width() - 10, sz.height() - 10 );
    updatePixmap();
}

void CaptureWgt::showEvent( QShowEvent * w )
{
    resizeEvent( 0 );
}

void CaptureWgt::slotCapture()
{
    Ui_CaptureWgt & ui = pd->ui;
    bool en = ui.capture->isChecked();
    
    if ( en )
        pd->video->invokeCall();
    else
        pd->video->invokeEndCall();
}

void CaptureWgt::slotFilter()
{
    QObject * o = sender();
    QAction * a = qobject_cast<QAction *>( o );
    QString name;
    if ( a == pd->ui.equalizeHist )
        name = "equalizeHist";
    else if ( a == pd->ui.fullContrast )
        name = "fullContrast";
    else if ( a == pd->ui.sobel )
        name = "sobel";
    else if ( a == pd->ui.median )
        name = "median";
    else if ( a == pd->ui.timeSmooth )
        name = "timeSmooth";
    else if ( a == pd->ui.highPass )
        name = "highPass";
    else if ( a == pd->ui.surface )
        name = "surfaceSubtract";
    else if ( a == pd->ui.brightnessRange )
        name = "brightnessRange";
    bool checked = a->isChecked();
    // Here it should be processing setup.
}

void CaptureWgt::slotSavePixmap()
{
    QFileDialog d( this );
    d.setWindowTitle( "Save pixmap as" );
    d.setNameFilter( "PNG files (*.png)" );
    d.setFileMode( QFileDialog::AnyFile );
    d.setAcceptMode( QFileDialog::AcceptSave );
    d.setOptions( 0 );
    if ( d.exec() )
    {
        QStringList fileNames = d.selectedFiles();
        if ( fileNames.size() < 1 )
            return;
        QString fileName = fileNames.at( 0 );
        savePixmap( fileName );
    }
}

void CaptureWgt::slotFrameReady()
{
    pd->video->frame( pd->img );
    updatePixmap();
}

void CaptureWgt::slotBrightness()
{
    pd->ui.brightnessDw->setVisible( pd->ui.brightnessRange->isChecked() );
}

void CaptureWgt::slotBrightnessChanged( const QPointF & range )
{
    //pd->cap->setBrightnessRange( range );
}

void CaptureWgt::slotFlipX()
{
    pd->flipX = pd->ui.flipX->isChecked();
}

void CaptureWgt::slotFlipY()
{
    pd->flipY = pd->ui.flipY->isChecked();
}

void CaptureWgt::emitMouseEvent()
{
    emit mouseEvent( pd->imgAt );
}

QString CaptureWgt::savePixmap( const QString & stri )
{
    QString fileName = stri;
    if ( !fileName.endsWith( ".png", Qt::CaseInsensitive ) )
        fileName.append( ".png" );
    
    QImage pm;
    image( pm );
    pm.save( fileName, "PNG", 100 );
    return fileName;
}

void CaptureWgt::image( QImage & img )
{
    QTransform tr;
    qreal scX, scY, trX, trY;
    if ( pd->flipY )
    {
        scX = -1.0;
        trX = static_cast<qreal>( pd->img.width() );
    }
    else
    {
        scX = 1.0;
        trX = 0.0;
    }
    if ( pd->flipX )
    {
        scY = -1.0;
        trY = static_cast<qreal>( pd->img.height() );
    }
    else
    {
        scY = 1.0;
        trY = 0.0;
    }
    tr.scale( scX, scY );
    tr.translate( trX, trY );
    QImage image = pd->img.transformed( tr, Qt::SmoothTransformation );
    img = image;
}

bool CaptureWgt::isMarker() const
{
    bool en = pd->ui.laser->isChecked();
    return en;
}

const QPointF & CaptureWgt::marker() const
{
    return pd->imgAt;
}


void CaptureWgt::updatePixmap()
{
    if ( pd->img.isNull() )
        return;
    Ui_CaptureWgt & ui = pd->ui;
    QSizeF imgSz = pd->img.size();
    QSizeF wndSz = ui.view->size();
    
    qreal sc;
    qreal x, y;
    if ( imgSz.width() * wndSz.height() > imgSz.height() * wndSz.width() )
    {
        sc = wndSz.width() / imgSz.width();
        x = 0.0;
        y = ( static_cast<qreal>( wndSz.height() ) - 
              static_cast<qreal>( imgSz.height() ) * sc ) * 0.5;
    }
    else
    {
        sc = wndSz.height() / imgSz.height();
        x = ( static_cast<qreal>( wndSz.width() ) - 
              static_cast<qreal>( imgSz.width() ) * sc ) * 0.5;
        y = 0.0;
    }
    pd->imgPos = QPointF( x, y );
    pd->imgScale = sc;
    




    pd->scene->setSceneRect( QRectF( 0.0, 0.0, wndSz.width(), wndSz.height() ) );
    pd->image->setPixmap( QPixmap::fromImage( pd->img ) );

    QTransform scaleX;
    if ( pd->flipX )
    {
        scaleX.scale( 1.0, -1.0 );
        scaleX.translate( 0.0, -static_cast<qreal>( imgSz.height() ) );
    }
    QTransform scaleY;
    if ( pd->flipY )
    {
        scaleY.scale( -1.0, 1.0 );
        scaleY.translate( -static_cast<qreal>( imgSz.width() ), 0.0 );
    }
    QTransform scale;
    scale.scale( sc, sc );
    QTransform tran;
    tran.translate( x, y );

    tran = scaleX * scaleY * scale * tran;
    pd->image->setTransform( tran );

    bool lineVisible = ( ( ui.laser->isChecked() ) && ( !pd->markerPos.isNull() ) );
    pd->lineX1->setVisible( lineVisible );
    pd->lineY1->setVisible( lineVisible );
    pd->lineX2->setVisible( lineVisible );
    pd->lineY2->setVisible( lineVisible );
    if ( lineVisible )
    {
        qreal w = static_cast<qreal>( pd->img.size().width() );
        qreal h = static_cast<qreal>( pd->img.size().height() );
        qreal xx = static_cast<qreal>( pd->markerPos.x() );
        if ( pd->flipY )
            xx = w - xx;
        qreal yy = static_cast<qreal>( pd->markerPos.y() );
        if ( pd->flipX )
            yy = h - yy;
        QPen penW( Qt::white );
        pd->lineX1->setPen( penW );
        pd->lineY1->setPen( penW );
        pd->lineX1->setLine( 0, yy, w, yy );
        pd->lineY1->setLine( xx, 0, xx, h );

        QPen penB( Qt::black );
        pd->lineX2->setPen( penB );
        pd->lineY2->setPen( penB );
        xx+=1.5;
        yy+=1.5;
        pd->lineX2->setLine( 0, yy, w, yy );
        pd->lineY2->setLine( xx, 0, xx, h );
    }

    drawArrow();
}






