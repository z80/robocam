
#ifndef __HOST_QXMPP_H_
#define __HOST_QXMPP_H_

#include "QXmppServer.h"
#include "QXmppPasswordChecker.h"

class HostQxmpp
{
public:
    HostQxmpp();
    ~HostQxmpp();

    bool listen( const std::string & configFile );
private:
    class PD;
    PD * pd;
};




#endif



