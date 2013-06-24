

#ifndef __XMPP_CONFIG_PIPE_IQ_H_
#define __XMPP_CONFIG_PIPE_IQ_H_


#include "QXmppIq.h"

class QXmppConfigPipeIq: public QXmppIq
{
public:
    QXmppConfigPipeIq();
    ~QXmppConfigPipeIq();

    void setPort( int arg );
    int  port() const;

    void setHost( const QString & stri );
    const QString & host() const;

    void setId( int id );
    int  id() const;

    static bool isConfigPipeIq( const QDomElement & element, int id );
protected:
    void parseElementFromChild( const QDomElement & element );
    void toXmlElementFromChild( QXmlStreamWriter * writer ) const;
private:
    int     m_port;
    QString m_host;
    int     m_id;
};


#endif

