
#ifndef __QXMPP_PACKET_IQ_H_
#define __QXMPP_PACKET_IQ_H_

#include "QXmppIq.h"

class QXmppPacketIq: public QXmppIq
{
public:
    QXmppPacketIq();
    ~QXmppPacketIq();

    void setId( int id );
    int id() const;

    void setData( const QByteArray & stri );
    const QByteArray & data() const;

    static bool isPacketIq( const QDomElement & element, int id );
protected:
    void parseElementFromChild( const QDomElement & element );
    void toXmlElementFromChild( QXmlStreamWriter * writer ) const;
private:
    QByteArray         m_stri;
    mutable QByteArray m_stri64;

    int        m_id;
};


#endif



