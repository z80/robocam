

#include <QtGui>
#include "main_wnd.h"

int main( int argc, char * argv[] )
{
    //QApplication::setColorSpec( QApplication::CustomColor );
    QApplication a( argc, argv );

    CMainWnd * c = new CMainWnd();
    c->show();

    int ret = a.exec();

    return ret;
}









