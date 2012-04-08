
#include <IceE/IceE.h>
#include "host_ice.h"
#include "host_ice_thread.h"
#include "client.h"
#include <sstream>
#include <iostream>

#include <QString>
#include <QCryptographicHash>

#include "QsLog.h"

CHostIce::CClientDesc::CClientDesc()
{
}

CHostIce::CClientDesc::~CClientDesc()
{

}

CHostIce::CClientDesc::CClientDesc( const CHostIce::CClientDesc & inst )
{
    *this = inst;
}

CHostIce::CClientDesc::CClientDesc( const std::string & nickname, const ::Client::CClientPrx & client )
{
    this->nickname = nickname;
    this->client   = client;
    this->access   = TView;
}

const CHostIce::CClientDesc & CHostIce::CClientDesc::operator=( const CHostIce::CClientDesc & inst )
{
    if ( this != &inst )
    {
        nickname = inst.nickname;
        client   = inst.client;
        access   = inst.access;
    }
    return *this;
}






CHostIce::CHostIce( CHostIceThread * owner )
: ::Host::CHost()
{
    m_owner = owner;
    m_motoView  = new CMotoViewIce(  owner );
    m_motoViewPrx = ::Host::CMotoPrx::uncheckedCast( 
             m_owner->m_adapter->addWithUUID( m_motoView ) );

    m_motoCtrl  = new CMotoCtrlIce(  owner );
    m_motoCtrlPrx = ::Host::CMotoPrx::uncheckedCast( 
             m_owner->m_adapter->addWithUUID( m_motoCtrl ) );

    m_motoSuper = new CMotoSuperIce( owner );
    m_motoSuperPrx = ::Host::CMotoPrx::uncheckedCast( 
             m_owner->m_adapter->addWithUUID( m_motoSuper ) );

    m_camView   = new CCamViewIce(   owner );
    m_camViewPrx = ::Host::CCamPrx::uncheckedCast( 
             m_owner->m_adapter->addWithUUID( m_camView ) );

    m_camCtrl   = new CCamCtrlIce(   owner );
    m_camCtrlPrx = ::Host::CCamPrx::uncheckedCast( 
             m_owner->m_adapter->addWithUUID( m_camCtrl ) );

    m_camSuper  = new CCamSuperIce( owner );
    m_camSuperPrx = ::Host::CCamPrx::uncheckedCast( 
             m_owner->m_adapter->addWithUUID( m_camSuper ) );
}

CHostIce::~CHostIce()
{
}

bool CHostIce::registerClient( const ::Client::CClientPrx & client, const std::string & nickname, std::string & idOrErrMsg, const ::Ice::Current & c )
{
    IceUtil::Mutex::Lock lock( m_mut );
    QLOG_TRACE() << "registerClient( " << QString::fromUtf8( nickname.data(), nickname.size() ) << " )";
    try
    {
        //client->cam( c.ctx );
        //client->ice_id( c.ctx );

        if ( !nicknameUnique( nickname ) )
        {
            std::ostringstream msg;
            msg << "ERROR: \"" << nickname << "\" is aready in use";
            QLOG_TRACE() << QString::fromUtf8( msg.str().data(), msg.str().size() );
            idOrErrMsg = msg.str();
            return false;
        }
        std::string id = clientId( nickname, client );
        if ( hasClient( id ) )
        {
            std::ostringstream msg;
            msg << "ERROR: your client id is \"" << id << "\", it is aready in use. Failed to add client.";
            QLOG_TRACE() << QString::fromUtf8( msg.str().data(), msg.str().size() );
            idOrErrMsg = msg.str();
            return false;
        }
        QLOG_TRACE() << "Assigned id: " << QString::fromStdString( id );
        CClientDesc cd( nickname, client );
        idOrErrMsg = id;
        addClient( id, cd );
        validateClientList( c );
        sendClientList( c );
        return true;
    }
    catch( const Ice::Exception & ex )
    {
        QLOG_TRACE() << "Exception: " << ex.toString().c_str();
        idOrErrMsg = ex.toString().c_str();
        fprintf(stderr, "%s\n", ex.toString().c_str());
    }
    return false;
}

void CHostIce::removeClient( const std::string & id, const ::Ice::Current & c )
{
    IceUtil::Mutex::Lock lock( m_mut );

    QLOG_TRACE() << "removeClient( " << QString::fromStdString( id ) << " )";
    remClient( id );
    sendClientList( c );
}

void CHostIce::postMessage( const std::string & id, const ::std::string & stri, const ::Ice::Current & c )
{
    IceUtil::Mutex::Lock lock( m_mut );
    
    CClientDesc cd;
    if ( !client( id, cd ) )
        return;
    std::ostringstream msg;
    msg << cd.nickname << ": \'" << stri << "\'";
    QLOG_TRACE() << "postMessage( " << QString::fromUtf8( msg.str().data(), msg.str().size() ) << " )";
    
    bool sendList = false;
    for ( TClientsIter j = m_clients.begin();
          j != m_clients.end();
          j++ )
    {
        Client::CClientPrx client = j->second.client;
        try
        {
            client->chat()->acceptMessage( msg.str() );
        }
        catch ( Ice::Exception & )
        {
            sendList = true;
        }
    }
    if ( sendList )
    {
        validateClientList( c );
        sendClientList( c );
    }
}

bool CHostIce::queryCtrl( const std::string & id, const ::Ice::Current & c )
{
    IceUtil::Mutex::Lock lock( m_mut );
    QLOG_TRACE() << "queryCtrl( "  << QString::fromStdString( id ) << " )";

    CClientDesc cd;
    if ( !client( id, cd ) )
        return false;
    
    for ( TClientsConstIter i = m_clients.begin();
          i != m_clients.end();
          i++ )
    {
        const CClientDesc & cd = i->second;
        if ( cd.access != TView )
        {
            QLOG_TRACE() << "query refused";
            return false;
        }
    }
    QLOG_TRACE() << "query granted";
    cd.access = TCtrl;
    updateClient( id, cd );
    validateClientList( c );
    sendClientList( c );
    return true;
}

bool CHostIce::querySuper( const std::string & id, const ::std::string & passwd, const ::Ice::Current & c )
{
    IceUtil::Mutex::Lock lock( m_mut );
    QLOG_TRACE() << "querySuper( "  << QString::fromStdString( id ) << " )";
    
    if ( m_owner->m_passwd != passwd )
    {
        QLOG_TRACE() << "wrong password";
        return false;
    }

    CClientDesc cd;
    if ( !client( id, cd ) )
        return false;
    
    bool modified;
    do {
        modified = false;
        for ( TClientsIter i = m_clients.begin();
              i != m_clients.end();
              i++ )
        {
            if ( id != i->first )
            {
                CClientDesc & cd = i->second;
                if ( cd.access != TView )
                {
                    cd.access = TView;
                    modified = true;
                }
            }
        }
    } while ( modified );
    
    QLOG_TRACE() << "super privilegies granted";
    cd.access = TSuper;
    updateClient( id, cd );
    validateClientList( c );
    sendClientList( c );
    return true;
}

void CHostIce::releaseCtrl( const std::string & id, const ::Ice::Current & c )
{
    IceUtil::Mutex::Lock lock( m_mut );
    QLOG_TRACE() << "releaseCtrl( "  << QString::fromStdString( id ) << " )";
    
    CClientDesc cd;
    if ( !client( id, cd ) )
        return;
    
    cd.access = TView;
    updateClient( id, cd );
    validateClientList( c );
    sendClientList( c );
}

::Host::CCamPrx CHostIce::cam( const std::string & id, const ::Ice::Current & c )
{
    IceUtil::Mutex::Lock lock( m_mut );
    
    CClientDesc cd;
    if ( !client( id, cd ) )
        return 0;

    switch ( cd.access )
    {
    case TSuper:
        return m_camSuperPrx;
    case TCtrl:
        return m_camCtrlPrx;
    }
    return m_camViewPrx;
}

::Host::CMotoPrx CHostIce::moto( const std::string & id, const ::Ice::Current & c )
{
    IceUtil::Mutex::Lock lock( m_mut );
    
    CClientDesc cd;
    if ( !client( id, cd ) )
        return 0;

    switch ( cd.access )
    {
    case TSuper:
        return m_motoSuperPrx;
    case TCtrl:
        return m_motoCtrlPrx;
    }
    return m_motoViewPrx;
}

void CHostIce::postImage( const ::Types::TByteArray & data, const ::Ice::Current & c )
{
    IceUtil::Mutex::Lock lock( m_mut );
    
    bool sendList = false;
    for( TClientsIter i = m_clients.begin();
         i != m_clients.end();
         i++ )
    {
        Client::CClientPrx & client = i->second.client;
        try
        {
            client->cam()->acceptImage( data, c.ctx );
        }
        catch ( Ice::Exception & )
        {
            sendList = true;
        }
    }

    if ( sendList )
    {
        validateClientList( c );
        sendClientList( c );
    }
}

int CHostIce::clientCnt() const
{
    IceUtil::Mutex::Lock lock( m_mut );
    return static_cast<int>( m_clients.size() );
}









bool CHostIce::nicknameUnique( const std::string & nickname ) const
{
    for( TClientsConstIter i = m_clients.begin();
         i != m_clients.end();
         i++ )
    {
        if ( i->second.nickname == nickname )
            return false;
    }
    return true;
}

std::string CHostIce::clientId( const std::string & nickname, const ::Client::CClientPrx & client )
{
    QCryptographicHash hash( QCryptographicHash::Sha1 );
    hash.addData( QString::fromStdString( nickname ).toAscii() );
    hash.addData( QString::fromStdString( client->ice_id() ).toAscii() );
    QString stri( hash.result().toHex() );
    std::string id = stri.toStdString();
    return id;
}

bool CHostIce::hasClient( const std::string & id ) const
{
    TClientsConstIter i = m_clients.find( id );
    return ( i != m_clients.end() );
}

void CHostIce::addClient( const std::string & id, const CClientDesc & client )
{
    if ( !hasClient( id ) )
        m_clients.insert( std::pair<std::string, CClientDesc>( id, client ) );
}

bool CHostIce::client( const std::string & id, CClientDesc & client ) const
{
    TClientsConstIter i = m_clients.find( id );
    bool res = (i != m_clients.end());
    if ( res )
        client = i->second;
    return res;
}

void CHostIce::remClient( const std::string & id )
{
    TClientsIter i = m_clients.find( id );
    if (i != m_clients.end())
        m_clients.erase( i );
}

void CHostIce::updateClient( const std::string & id, const CClientDesc & client )
{
    TClientsIter i = m_clients.find( id );
    bool res = (i != m_clients.end());
    if ( res )
        m_clients.erase( i );
    m_clients.insert( std::pair< std::string, CClientDesc >( id, client ) );
}

void CHostIce::validateClientList( const ::Ice::Current & c )
{
    std::list<TClientsIter> removeList;
    for ( TClientsIter i = m_clients.begin();
          i != m_clients.end();
          i++ )
    {
        Client::CClientPrx & client = i->second.client;
        try
        {
            client->ice_ping( c.ctx );
        }
        catch ( Ice::Exception & )
        {
            QLOG_TRACE() << "ping failed, removing client "  << QString::fromStdString( i->first );
            removeList.push_back( i );
        }
    }
    for ( std::list<TClientsIter>::iterator i=removeList.begin();
          i!=removeList.end();
          i++ )
          m_clients.erase( *i );

}

void CHostIce::sendClientList( const ::Ice::Current & c )
{
    ::Types::TStringArray l;
    std::string driverNickname = std::string();
    for ( TClientsConstIter i=m_clients.begin(); i!=m_clients.end(); i++ )
    {
        l.push_back( i->second.nickname );
        if ( i->second.access != TView )
            driverNickname = i->second.nickname;
    }
    for ( TClientsIter i=m_clients.begin(); i!=m_clients.end(); i++ )
    {
        Client::CClientPrx & client = i->second.client;
        client->chat()->acceptClientList( l, driverNickname, c.ctx );
    }
}





