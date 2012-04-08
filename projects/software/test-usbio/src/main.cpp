

#include <QtGui>
#include "usb_ctrl.h"

int main( int argc, char * argv[] )
{
    QApplication::setColorSpec( QApplication::CustomColor );
    QApplication a( argc, argv );

    CUsbCtrl * lc = new CUsbCtrl();
    lc->show();

    int ret = a.exec();

    return ret;
}











