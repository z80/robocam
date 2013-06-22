
#include <QtGui>
#include "host_qxmpp.h"

static const char serverConfig[] = "server.ini";

int main( int argc, char ** argv )
{
    QCoreApplication a( argc, argv );
    // XMPP server initalization.
    HostQxmpp host;
    bool result = host.listen( serverConfig );
    Q_ASSERT( result );
    int res = a.exec();
    return res;
}





