
#include "brightness_wgt.h"

class BrightnessWgt::PD
{
public:
    PD() {}
    ~PD() {}

    QPointF range;
    QPointF refPoint;
    static const qreal wheelStep;
    static const int MARGIN;
    static const int BRIGHTNESS_MAX;
};

const qreal BrightnessWgt::PD::wheelStep = 1.1;
const int   BrightnessWgt::PD::MARGIN    = 3;
const int   BrightnessWgt::PD::BRIGHTNESS_MAX = 255;

BrightnessWgt::BrightnessWgt( QWidget * parent )
: QWidget( parent )
{
    pd = new PD();
    pd->range = QPointF( 0.0, 255.0 );
    setMinimumSize( 32, 128 );
}

BrightnessWgt::~BrightnessWgt()
{
    delete pd;
}

void BrightnessWgt::setRange( const QPointF & range )
{
    qreal vmin = ( range.x() < range.y() ) ? range.x() : range.y();
    qreal vmax = ( range.x() > range.y() ) ? range.x() : range.y();
    pd->range = QPointF( vmin, vmax );
    update();
}

QPointF BrightnessWgt::range()
{
    return pd->range;
}

void BrightnessWgt::paintEvent( QPaintEvent * e )
{
    QWidget::paintEvent( e );

    QPainter p( this );
    QPen pen;
    pen.setColor( QColor( Qt::blue ) );
    QLinearGradient linearGrad( QPointF( PD::MARGIN, PD::MARGIN ), 
                                QPointF( width() - 2*PD::MARGIN, 
                                         height() - 2*PD::MARGIN ) );
    linearGrad.setColorAt( 0, Qt::white );
    linearGrad.setColorAt( 1, Qt::black );
    QBrush brush( linearGrad );
    brush.setColor( QColor( Qt::lightGray ) );

    QSize sz = size();
    QRect r( PD::MARGIN, PD::MARGIN, 
             width() - 3*PD::MARGIN, 
             height() - 3*PD::MARGIN );
    
    // Рамка.
    p.setPen( pen );
    p.setBrush( brush );
    p.drawRect( r );
    // Стрелочка.
    int s = height() - 4 * PD::MARGIN;
    int vmin = PD::MARGIN + ( s - s * pd->range.y() / PD::BRIGHTNESS_MAX );
    int vmax = PD::MARGIN + ( s - s * pd->range.x() / PD::BRIGHTNESS_MAX );
    QPen apen;
    apen.setColor( QColor( Qt::blue ) );
    apen.setWidth( 3 );
    //QBrush abrush();
    p.setPen( apen );
    p.setBrush( Qt::NoBrush );
    p.drawRect( 2*PD::MARGIN, vmin, width() - 5*PD::MARGIN, vmax - vmin );
}

void BrightnessWgt::wheelEvent( QWheelEvent * e )
{
    qreal step = ( e->delta() > 0 ) ? PD::wheelStep : (1.0/PD::wheelStep);
    qreal middle = static_cast<qreal>( pd->range.x() + pd->range.y() ) * 0.5;
    qreal width2 = static_cast<qreal>( pd->range.y() - pd->range.x() ) * 0.5;
    width2 *= step;
    qreal vmin = middle - width2;
    qreal vmax = middle + width2;
    vmin = ( vmin >= 0.0 ) ? vmin : 0.0;
    vmax = ( vmax <= static_cast<qreal>( PD::BRIGHTNESS_MAX ) ) ? vmax : static_cast<qreal>( PD::BRIGHTNESS_MAX );
    pd->range = QPointF( vmin, vmax );

    update();
    emit rangeChanged( pd->range );
}

//void BrightnessWgt::dragMoveEvent( QDragMoveEvent * e )
//{
//}

void BrightnessWgt::mouseMoveEvent( QMouseEvent * e )
{
    QPointF pt = e->pos();
    qreal dh = pd->refPoint.y() - pt.y();
    pd->refPoint = pt;

    qreal s = static_cast<qreal>( height() - 4 * PD::MARGIN );
    qreal disp = static_cast<qreal>( PD::BRIGHTNESS_MAX ) * dh / s;
    qreal vmin = pd->range.x() + disp;
    qreal vmax = pd->range.y() + disp;
    pd->range = QPointF( vmin, vmax );

    update();
    emit rangeChanged( pd->range );
}

void BrightnessWgt::mousePressEvent( QMouseEvent * e )
{
    pd->refPoint = e->posF();
}




