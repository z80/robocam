



#include <QDomElement>

#include "QXmppConstants.h"
#include "QXmppUtils.h"

#include "xmpp_config_pipe_iq.h"


QXmppConfigPipeIq::QXmppConfigPipeIq()
    : QXmppIq()
{
    m_id = -1;
    m_port = 22;
    m_host = "localhost";
}

QXmppConfigPipeIq::~QXmppConfigPipeIq()
{

}

void QXmppConfigPipeIq::setPort( int arg )
{
    m_port = arg;
}

int QXmppConfigPipeIq::port() const
{
    return m_port;
}

void QXmppConfigPipeIq::setHost( const QString & stri )
{
    m_host = stri;
}

const QString & QXmppConfigPipeIq::host() const
{
    return m_host;
}

void QXmppConfigPipeIq::setId( int id )
{
    m_id = id;
}

int QXmppConfigPipeIq::id() const
{
    return m_id;
}

bool QXmppConfigPipeIq::isConfigPipeIq( const QDomElement & element, int id )
{
    QDomElement queryElement = element.firstChildElement("query");
    int ind = queryElement.firstChildElement( "id" ).text().toInt();
    if ( ind != id )
        return false;
    QString t = queryElement.firstChildElement( "port" ).text();
    return ( t.size() > 0 );
}

void QXmppConfigPipeIq::parseElementFromChild( const QDomElement & element )
{
    QDomElement queryElement = element.firstChildElement("query");
    m_port = queryElement.firstChildElement( "port" ).text().toInt();
    m_host = queryElement.firstChildElement( "host" ).text();
    m_id   = queryElement.firstChildElement( "id" ).text().toInt();
}

void QXmppConfigPipeIq::toXmlElementFromChild( QXmlStreamWriter * writer ) const
{
    writer->writeStartElement("query");
    writer->writeAttribute("xmlns", "netpacket" );

    helperToXmlAddTextElement(writer, "port", QString( "%1" ).arg( m_port ) );
    helperToXmlAddTextElement(writer, "host", QString( "%1" ).arg( m_host ) );
    helperToXmlAddTextElement(writer, "id",   QString( "%1" ).arg( m_id ) );

    writer->writeEndElement();
}

