
#ifndef __XMPP_MSG_PIPE_H_
#define __XMPP_MSG_PIPE_H_

#include <QtCore>
#include "QXmppClient.h"
#include "QXmppMessage.h"

class QXmppMsgPipe: public QObject
{
    Q_OBJECT
public:
    QXmppMsgPipe( QXmppClient * client, int id = -1 );
    ~QXmppMsgPipe();

    void setInPipe( int id = -1 );
    void setOutPipe( const QString & jidDest, int localPort, int remotePort = -1, const QString & remoteHost = QString(), int id = -1 );
    void clearPipe();

private slots:
    void qxmppMessageReceived( const QXmppMessage & );
    void serverNewConnection();
    void socketReadyRead();


private:
    class PD;
    PD * pd;
};



#endif







