
#ifndef __CAPTURE_WGT_H_
#define __CAPTURE_WGT_H_

#include <QtGui>
#include "capture.h"

class QXmppVideo;

class CaptureWgt: public QMainWindow
{
    Q_OBJECT
public:
    CaptureWgt( QWidget * parent = 0 );
    virtual ~CaptureWgt();
    
    void setVideo( QXmppVideo * video );
    bool eventFilter( QObject * o, QEvent * e );
signals:
    void mouseEvent( const QPointF & at );
protected:
    void resizeEvent( QResizeEvent * e );
    void showEvent( QShowEvent * w );
public slots:
    void slotCapture();

    void slotFilter();
    void slotPixmap();
    void slotFrame();
    void slotBrightness();
    void slotBrightnessChanged( const QPointF & range );
    void slotFlipX();
    void slotFlipY();
protected:
    void emitMouseEvent();
public:
    QString savePixmap( const QString & stri );
    void image( QImage & img );
    bool isMarker() const;
    const QPointF & marker() const;
private:
    void listDevices();
    void listResolutions();
    void updatePixmap( const QImage & img = QImage() );
    void drawArrow();
    
    class PD;
    friend class PD;
    PD * pd;
};


#endif



