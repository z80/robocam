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
#include "example_1_echoClient.h"

echoClient::echoClient(QObject *parent)
    : QXmppPeer(parent)
{
    QObject::connect( this, SIGNAL(textmsg(const QString &)),
                      this, SLOT(messageReceived(const QString &)));

    QObject::connect( this, SIGNAL( connected() ),
                            SLOT( slotConnected() ) );

    QXmppPeer::connect( "out@xmpp", "12345", "localhost" );

    QXmppMsgPipe * proxy = new QXmppMsgPipe( this, 1 );
    proxy->setOutPipe( "in@xmpp", 1234, 22, "localhost" );
}

echoClient::~echoClient()
{

}

void echoClient::messageReceived( const QString & stri )
{
    //sendMessage( stri );
}

void echoClient::slotConnected()
{
    /*
    QXmppConfigPipeIq configIq;
    configIq.setTo( "in@xmpp" );
    configIq.setId( 1 );
    configIq.setPort( 22 );
    configIq.setHost( "localhost" );
    sendPacket( configIq );


    QXmppPacketIq packetIq;
    packetIq.setTo( "in@xmpp" );
    packetIq.setId( 1 );
    packetIq.setData( "123456" );
    sendPacket( packetIq );
    */
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    echoClient client;
    //client.logger()->setLoggingType(QXmppLogger::StdoutLogging);
    //client.connectToServer("qxmpp.test1@qxmpp.org", "qxmpp123");

    return app.exec();
}
