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

#include "xmpp_tcp_proxy.h"
#include "xmpp_pipe_packet_iq.h"

#include "example_1_echoClient.h"

echoClient::echoClient(QObject *parent)
    : QXmppPeer(parent)
{
    QObject::connect( this, SIGNAL(message(const QString &)),
                      this, SLOT(messageReceived(const QString &)));

    QObject::connect( this, SIGNAL( connected() ),
                            SLOT( slotConnected() ) );

    QXmppPeer::connect( "out@xmpp", "12345", "localhost" );

    QXmppTcpProxy * proxy = new QXmppTcpProxy( 1 );
    this->addExtension( proxy );
    proxy->setPipe( 80, true );
}

echoClient::~echoClient()
{

}

void echoClient::messageReceived( const QString & stri )
{
    sendMessage( stri );
}

void echoClient::slotConnected()
{
    QXmppPacketIq packetIq;
    packetIq.setTo( "in@xmpp" );
    packetIq.setId( 1 );
    packetIq.setData( "123456" );
    sendPacket( packetIq );
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    echoClient client;
    //client.logger()->setLoggingType(QXmppLogger::StdoutLogging);
    //client.connectToServer("qxmpp.test1@qxmpp.org", "qxmpp123");

    return app.exec();
}
