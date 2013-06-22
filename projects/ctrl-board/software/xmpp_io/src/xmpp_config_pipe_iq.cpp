

#include <QDomElement>

#include "QXmppConstants.h"
#include "QXmppUtils.h"

#include "xmpp_config_pipe_iq.h"


QXmppConfigPipeIq::QXmppConfigPipeIq()
    : QXmppIq()
{
    m_port = 22;
    m_listening = false;
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

void QXmppConfigPipeIq::setIsListening( bool en )
{
    m_listening = en;
}

bool QXmppConfigPipeIq::isListening() const
{
    return m_listening;
}

void QXmppConfigPipeIq::setId( int id )
{
    m_id = id;
}

int QXmppConfigPipeIq::id() const
{
    return m_id;
}

bool QXmppConfigPipeIq::isConfigPipeIq( const QDomElement & element )
{
    QDomElement queryElement = element.firstChildElement("query");
    QDomText t = queryElement.firstChildElement( "port" ).toText();
    return !t.isNull();
}

void QXmppConfigPipeIq::parseElementFromChild( const QDomElement & element )
{
    QDomElement queryElement = element.firstChildElement("query");
    m_port      = queryElement.firstChildElement( "port" ).text().toInt();
    m_listening = ( queryElement.firstChildElement( "listening" ).text().toInt() > 0 );
    m_id        = queryElement.firstChildElement( "id" ).text().toInt();
}

void QXmppConfigPipeIq::toXmlElementFromChild( QXmlStreamWriter * writer )
{
    writer->writeStartElement("query");
    writer->writeAttribute("xmlns", ns_version);

    helperToXmlAddTextElement(writer, "port",      QString( "%1" ).arg( m_port ) );
    helperToXmlAddTextElement(writer, "listening", QString( "%1" ).arg( m_listening ) );
    helperToXmlAddTextElement(writer, "id",        QString( "%1" ).arg( m_id ? 1 : 0 ) );

    writer->writeEndElement();
}


