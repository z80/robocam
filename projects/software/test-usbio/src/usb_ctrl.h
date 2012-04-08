
#ifndef __USB_CTRL_H_
#define __USB_CTRL_H_

#include <QtGui>
#include "ui_usb_ctrl.h"

class CMotorsCtrl;

class CUsbCtrl: public QWidget
{
    Q_OBJECT
public:
    CUsbCtrl( QWidget * parent = 0 );
    ~CUsbCtrl();

private slots:
    void open();
    void motoEnChanged();
    void servoEnChanged();
    void motoChanged();
    void servoChanged();
private:
    void log( const QString & stri );
    void out();
    Ui_MotoCtrl ui;
    CMotorsCtrl * io;
};



#endif


