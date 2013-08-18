
#ifndef __CAPTURE_WGT_H_
#define __CAPTURE_WGT_H_

#include <QtGui>

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
    void slotResolution();
    void slotSettings();

    void slotSavePixmap();
    void slotFrameReady();
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
    void updatePixmap();
    void brightnessRange();
    
    class PD;
    friend class PD;
    PD * pd;
};


#endif



