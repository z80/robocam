

#ifndef __TEST_BIN_
#define __TEST_BIN_

#include <QtGui>
#include "client_gui.h"

int main( int argc, char * argv[] )
{
    //QApplication::setColorSpec( QApplication::CustomColor );
    QApplication a( argc, argv );

    CClientGui * c = new CClientGui();
    c->show();

    int ret = a.exec();

    return ret;
}



#endif








