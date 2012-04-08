
#ifndef __MOTO_H_
#define __MOTO_H_

#include <QtGui>
#include "ui_moto.h"

class CMainWnd;

class CMoto: public QWidget
{
    Q_OBJECT
public:
    CMoto( CMainWnd * mainWnd );
    ~CMoto();

    void setCtrlEnabled( bool en );
    void setSuperEnabled( bool en );
protected:
    void keyPressEvent( QKeyEvent * e );
    void keyReleaseEvent( QKeyEvent * e );
private slots:
    void slotMoto();
    void slotServoChanged( QPointF newValue, bool mouseDown );
    void slotOpen();
    void slotMotoEn();
    void slotServoEn();
private:
    Ui_CMoto ui;
    CMainWnd * m_mainWnd;
};



#endif

