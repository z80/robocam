
#include "QXmppIq.h"

class QXmppConfigPipeIq: public QXmppIq
{
public:
    QXmppConfigPipeIq();
    ~QXmppConfigPipeIq();

    void setPort( int arg );
    int port() const;

    void setIsListening( bool en );
    bool isListening() const;

    void setId( int id );
    int id() const;

    static bool isConfigPipeIq( const QDomElement & element );
protected:
    void parseElementFromChild( const QDomElement & element );
    void toXmlElementFromChild( QXmlStreamWriter * writer );
private:
    int  m_port;
    bool m_listening;
    int  m_id;
};



