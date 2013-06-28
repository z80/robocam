/*
 * Copyright (C) 2008-2012 The QXmpp developers
 *
 * Author:
 *	Manjeet Dahiya
 *
 * Source:
 *	http://code.google.com/p/qxmpp
 *
 * This file is a part of QXmpp library.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 */


#include <QCoreApplication>

#include "QXmppLogger.h"
#include "QXmppMessage.h"

#include "xmpp_msg_pipe.h"
#include "xmpp_video.h"

#include "example_1_echoClient.h"

echoClient::echoClient(QObject *parent)
    : QXmppPeer(parent)
{
    QObject::connect( this, SIGNAL(textmsg(const QString &)),
                      this, SLOT(messageReceived(const QString &)) );

    QXmppPeer::connect( "in@xmpp", "12345", "localhost" );

    QXmppMsgPipe * proxy = new QXmppMsgPipe( this, 1 );
    proxy->setInPipe();

    QXmppVideo * video = new QXmppVideo( this );
    video->setTarget( "out@xmpp" );
}

echoClient::~echoClient()
{

}

void echoClient::messageReceived( const QString & stri )
{
    //sendMessage( stri );
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    echoClient client;
    //client.logger()->setLoggingType(QXmppLogger::StdoutLogging);
    //client.connectToServer("qxmpp.test1@qxmpp.org", "qxmpp123");

    return app.exec();
}
