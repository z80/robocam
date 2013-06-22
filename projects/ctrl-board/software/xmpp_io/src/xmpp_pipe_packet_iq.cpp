


#include <QDomElement>

#include "QXmppConstants.h"
#include "QXmppUtils.h"

#include "xmpp_pipe_packet_iq.h"

QXmppPacketIq::QXmppPacketIq()
    : QXmppIq()
{
    m_id = 0;
}

QXmppPacketIq::~QXmppPacketIq()
{

}

void QXmppPacketIq::setId( int id )
{
    m_id = id;
}

int QXmppPacketIq::id() const
{
    return m_id;
}

void QXmppPacketIq::setData( const QByteArray & stri )
{
    m_stri = stri;
}

const QByteArray & QXmppPacketIq::data() const
{
    return m_stri;
}

bool QXmppPacketIq::isPacketIq( const QDomElement & element, int id )
{
    QDomElement queryElement = element.firstChildElement("query");
    int ind = queryElement.firstChildElement( "id" ).text().toInt();
    if ( ind != id )
        return false;
    QString t = queryElement.firstChildElement( "data" ).text();
    return (t.size() > 0);
}

void QXmppPacketIq::parseElementFromChild( const QDomElement & element )
{
    QDomElement queryElement = element.firstChildElement("query");
    m_id      = queryElement.firstChildElement( "id" ).text().toInt();
    m_stri64  = queryElement.firstChildElement( "data" ).text().toAscii();
    m_stri    = QByteArray::fromBase64( m_stri64 );
}

void QXmppPacketIq::toXmlElementFromChild( QXmlStreamWriter * writer ) const
{
    writer->writeStartElement("query");
    writer->writeAttribute("xmlns", "netpacket" );

    helperToXmlAddTextElement(writer, "id",   QString( "%1" ).arg( m_id ) );
    m_stri64 = m_stri.toBase64();
    helperToXmlAddTextElement(writer, "data", QString::fromAscii( m_stri64 ) );

    writer->writeEndElement();
}





