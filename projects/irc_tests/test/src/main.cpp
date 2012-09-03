
#include <QtGui>
#include "irc_peer.h"

int main( int argc char * argv[] )
{
    QApplication app( argc, argv );
    QWidget * w = new QWidget();
    int res = app.exec();
    return res;
}

