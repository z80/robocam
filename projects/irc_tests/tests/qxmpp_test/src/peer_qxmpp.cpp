
#include "peer_qxmpp.h"
#include "qxmpp_peer.h"
#include <iostream>
#include <boost/bind.hpp>
#include <boost/bind/placeholders.hpp>

#include <boost/property_tree/ini_parser.hpp>
//#include <boost/property_tree/xml_parser.hpp>
//#include <boost/property_tree/json_parser.hpp>
//#include <boost/property_tree/info_parser.hpp>
#include <boost/foreach.hpp>

class PeerQxmpp::PD
{
public:
    PD() {}
    ~PD() {}

    void messageHandler( const std::string & from, const std::string & msg );
    void logHandler( const std::string & msg );

    QxmppPeer peer;
    std::stringbuf jidSelf, 
                   jidDest;
    bool updateTarget;

};



