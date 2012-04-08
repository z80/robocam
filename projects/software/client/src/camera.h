
#ifndef __CAMERA_H_
#define __CAMERA_H_

#include <QtGui>
#include "ui_camera.h"
#include "host.h"

class CMainWnd;

class CCamera: public QWidget
{
    Q_OBJECT
public:
    CCamera( CMainWnd * mainWnd );
    ~CCamera();

    void setCtrlEnabled( bool en );
    void setSuperEnabled( bool en );
    void setImage( const QImage & img );
protected:
    void resizeEvent( QResizeEvent * e );
private slots:
    void slotSetPeriod( QAction * action );
    void slotSetResolution( QAction * action );
    void slotQueryImage();
private:
    void updatePixmap( const QPixmap & pm );
    Ui_CCamera ui;
    CMainWnd * m_mainWnd;
    QAction * actPeriodOff,
            * actPeriod30,
            * actPeriod10,
            * actPeriod3,
            * actPeriod1,
            * actPeriod03;
    QAction * actRes800x600,
            * actRes640x480,
            * actRes320x240,
            * actRes160x120;
    QGraphicsScene * m_scene;
    QGraphicsPixmapItem * m_item;
    // For acepting images when host timer is off.
    ::Types::TByteArray m_data;
};


#endif



