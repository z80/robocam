
#include "peer_qxmpp.h"
#include "qxmpp_peer.h"
#include <iostream>
#include <sstream>
#include <boost/bind.hpp>
#include <boost/bind/placeholders.hpp>

#include <boost/property_tree/ini_parser.hpp>
//#include <boost/property_tree/xml_parser.hpp>
//#include <boost/property_tree/json_parser.hpp>
//#include <boost/property_tree/info_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>

class PeerDesc
{
public:
    PeerDesc( PeerQxmpp * parent );
    ~PeerDesc();
    PeerDesc( const PeerDesc &);
    const PeerDesc & operator=(const PeerDesc &);

    void messageHandler( const std::string & from, const std::string & msg );
    void logHandler( const std::string & msg );

    PeerQxmpp * self;
    QxmppPeer * peer;
    std::string jidDest;
    bool updateDest;
};

PeerDesc::PeerDesc( PeerQxmpp * parent )
: self( parent )
{
}

PeerDesc::~PeerDesc()
{
}

PeerDesc::PeerDesc( const PeerDesc & inst )
{
    *this = inst;
}

const PeerDesc & PeerDesc::operator=( const PeerDesc & inst )
{
    if ( this != &inst )
    {
        self       = inst.self;
        peer       = inst.peer;
        jidDest    = inst.jidDest;
        updateDest = inst.updateDest;
    }
    return *this;
}

void PeerDesc::messageHandler( const std::string & from, const std::string & msg )
{
    if ( updateDest )
        jidDest = from;
    self->invokeCmd( msg );
}

void PeerDesc::logHandler( const std::string & msg )
{
    //std::ostringstream out;
    //out << "print( [[" << msg << "]] )";
    //self->invokeCmd( out.str() );
	qDebug() << msg.c_str();
}






class PeerQxmpp::PD
{
public:
    PD();
    ~PD();

    // Here it should be several peers to protect from XMPP server being down.
    std::string iniFile;
    std::list<PeerDesc *> peers;
};

PeerQxmpp::PD::PD()
{
}

PeerQxmpp::PD::~PD()
{
    for ( std::list<PeerDesc*>::iterator i=peers.begin(); i!=peers.end(); i++ )
    {
        PeerDesc * p = *i;
        p->peer->deleteLater();
        delete p;
    }
    peers.clear();
}

PeerQxmpp::PeerQxmpp( const std::string & iniFile, PeerAbst::TInit init )
: PeerAbst( init )
{
	pd = new PD();
	pd->iniFile = iniFile;

	connect();
}

PeerQxmpp::~PeerQxmpp()
{
    delete pd;
}

void PeerQxmpp::connect()
{
    for ( std::list<PeerDesc*>::iterator i=pd->peers.begin(); i!=pd->peers.end(); i++ )
    {
        PeerDesc * p = *i;
        p->peer->deleteLater();
        delete p;
    }
    pd->peers.clear();

	boost::property_tree::ptree config;
	try
	{
		boost::property_tree::read_ini( pd->iniFile, config );

		//const boost::property_tree::ptree & sect = config.get_child( "main" );
        for ( boost::property_tree::ptree::iterator i=config.begin(); i!=config.end(); i++ )
        {
            std::string key = i->first;
            boost::property_tree::ptree sect = config.get_child( key );
            PeerDesc * p = new PeerDesc( this );
		    p->jidDest           = sect.get<std::string>( "jid_dest", "bashkirov.sergey@gmail.com" );
		    p->updateDest        = sect.get<bool>( "update_dest", true );
		    std::string jidSelf  = sect.get<std::string>( "jid_self", "litedictteam@gmail.com" );
            std::string password = sect.get<std::string>( "password", "12345" );
            std::string host     = sect.get<std::string>( "host", "" );
            int         port     = sect.get<int>( "port", -1 );
            bool        tls      = sect.get<bool>( "tls", true );
            QxmppPeer * peer = new QxmppPeer();
            p->peer = peer;

            peer->setMessageHandler( boost::bind( &PeerDesc::messageHandler, p, _1, _2 ) );
            peer->setLogHandler( boost::bind( &PeerDesc::logHandler, p, _1 ) );
            peer->setInFileHandler( boost::bind<QIODevice *>( &PeerAbst::inFile, this, _1 ) );
            peer->setAccFileHandler( boost::bind( &PeerAbst::accFile, this, _1, _2 ) );
            peer->connectHost( jidSelf, password, host, port, tls );
            pd->peers.push_back( p );
        }
	}
	catch ( boost::property_tree::ini_parser_error & error )
	{
		std::cout << error.message() << ": " << error.filename() << ", line "
			<< error.line() << std::endl;
	}
}

bool PeerQxmpp::isConnected()
{
    for ( std::list<PeerDesc*>::iterator i=pd->peers.begin(); i!=pd->peers.end(); i++ )
    {
        PeerDesc * p = *i;
        if( p->peer->isConnected() )
            return true;
    }
    return false;
}

bool PeerQxmpp::send( const std::string & cmd )
{
    for ( std::list<PeerDesc*>::iterator i=pd->peers.begin(); i!=pd->peers.end(); i++ )
    {
        PeerDesc * p = *i;
        if ( p->peer->isConnected() )
        {
            p->peer->send( p->jidDest, cmd );
            return true;
        }
    }
    return false;
}

bool PeerQxmpp::sendFile( const std::string & fileName, QIODevice * file )
{
    for ( std::list<PeerDesc*>::iterator i=pd->peers.begin(); i!=pd->peers.end(); i++ )
    {
        PeerDesc * p = *i;
        if ( p->peer->isConnected() )
        {
            p->peer->sendFile( p->jidDest, fileName, file );
            return true;
        }
    }
    return false;
}




