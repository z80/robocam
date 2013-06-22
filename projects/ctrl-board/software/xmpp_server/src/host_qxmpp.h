
#ifndef __HOST_QXMPP_H_
#define __HOST_QXMPP_H_

#include <string>

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



