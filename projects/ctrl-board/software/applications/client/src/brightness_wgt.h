
#ifndef __BRIGHTNESS_WGT_H_
#define __BRIGHTNESS_WGT_H_

#include <QtGui>

class BrightnessWgt: public QWidget
{
    Q_OBJECT
public:
    BrightnessWgt( QWidget * parent = 0 );
    virtual ~BrightnessWgt();
    
    void setRange( const QPointF & range );
    QPointF range();
    
protected:
    // Рисование виджета.
    void paintEvent( QPaintEvent * e );
    void wheelEvent( QWheelEvent * e );
    //void dragMoveEvent( QDragMoveEvent * e );
    void mouseMoveEvent( QMouseEvent * e );
    void mousePressEvent( QMouseEvent * e );
    
signals:
    void rangeChanged( const QPointF & );
private:
    class PD;
    PD * pd;
    QPointF m_range;
};


#endif


