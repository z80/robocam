
#include <QtGui>
#include "wgt.h"

int main( int argc, char * argv[] )
{
    QApplication app( argc, argv );
    Wgt * w = new Wgt();
    w->show();
    int res = app.exec();
    return res;
}

