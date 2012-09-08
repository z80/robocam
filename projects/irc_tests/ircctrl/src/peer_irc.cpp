
#include "peer_irc.h"
#include "irc_peer.h"
#include <boost/bind.hpp>
#include <boost/bind/placeholders.hpp>

#include <boost/property_tree/ini_parser.hpp>
//#include <boost/property_tree/xml_parser.hpp>
//#include <boost/property_tree/json_parser.hpp>
//#include <boost/property_tree/info_parser.hpp>
#include <boost/foreach.hpp>


class PeerIrc::PD
{
public:
	PD( PeerIrc * owner );
	~PD();

	void messageHandler( const std::string & from, const std::string & cmd );

	PeerIrc * peer;
	IrcPeer irc;
	std::string host;
	int         port;
	std::string chan;
	std::string self;
	std::string target;
	bool        updateTarget;
};

PeerIrc::PD::PD( PeerIrc * owner )
	: peer( owner )
{
}

PeerIrc::PD::~PD()
{
}

void PeerIrc::PD::messageHandler( const std::string & from, const std::string & cmd )
{
	if ( updateTarget )
		target = from;
	peer->invokeCmd( cmd );
}

PeerIrc::PeerIrc( const std::string & iniFile, PeerAbst::TInit init )
: PeerAbst( init )
{
	pd = new PD( this );

	pd->host         = "213.171.43.24";
	pd->port         = 80;
	pd->chan         = "#solar_cam_rpi";
	pd->self         = "identity";
	pd->target       = "#solar_cam_rpi";
	pd->updateTarget = true;
	boost::property_tree::ptree config;
	try
	{
		boost::property_tree::read_ini( iniFile, config );
		const boost::property_tree::ptree & sect = config.get_child( "main" );
		pd->host = sect.get<std::string>( "host", "213.171.43.24" );
		pd->port = sect.get( "port", 80 );
		pd->chan = sect.get<std::string>( "chan", "#solar_cam_rpi" );
		pd->self = sect.get<std::string>( "self", "identity" );
		pd->target = sect.get<std::string>( "target", "#solar_cam_rpi" );
		pd->updateTarget = sect.get<bool>( "update_target", true );
	}
	catch ( boost::property_tree::ini_parser_error & error )
	{
		std::cout << error.message() << ": " << error.filename() << ", line "
			<< error.line() << std::endl;
	}

	connect();
}

PeerIrc::~PeerIrc()
{
	terminate();
	delete pd;
}

bool PeerIrc::connect()
{
	pd->irc.setMessageHandler( boost::bind( &PeerIrc::PD::messageHandler, pd, _1, _2 ) );
	pd->irc.setNick( pd->self );
	pd->irc.setHost( pd->host, pd->port );
	bool res = pd->irc.connect( pd->host, pd->port );
	if ( res )
		res = pd->irc.join( pd->chan );
	return true;
}

void PeerIrc::terminate()
{
	pd->irc.terminate( "Just disconnect" );
}

bool PeerIrc::isConnected()
{
	bool res = pd->irc.isConnected();
	if ( res )
		res = pd->irc.isJoined();
	return res;
}

bool PeerIrc::send( const std::string & cmd )
{
	bool res = pd->irc.send( pd->target, cmd );
	return res;
}

std::string PeerIrc::lastError() const
{
	return pd->irc.lastError();
}


