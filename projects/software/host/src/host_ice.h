
#ifndef __HOST_ICE_H_
#define __HOST_ICE_H_

#include "host.h"
#include "moto_view_ice.h"
#include "moto_ctrl_ice.h"
#include "moto_super_ice.h"
#include "cam_view_ice.h"
#include "cam_ctrl_ice.h"
#include "cam_super_ice.h"
class CHostIceThread;

class CHostIce: public ::Host::CHost
{
public:
    enum TAccess { TView, TCtrl, TSuper };
    class CClientDesc
    {
    public:
        CClientDesc();
        ~CClientDesc();
        CClientDesc( const CClientDesc & inst );
        CClientDesc( const std::string & nickname, const ::Client::CClientPrx & client );
        const CClientDesc & operator=( const CClientDesc & inst );

        std::string          nickname;
        ::Client::CClientPrx client;
        TAccess              access;
    };


    CHostIce( CHostIceThread * host );
    ~CHostIce();

    bool registerClient( const ::Client::CClientPrx & client, const std::string & nickname, std::string & idOrErrMsg, const ::Ice::Current & c = ::Ice::Current() );
    void removeClient( const std::string & id, const ::Ice::Current & c = ::Ice::Current() );
    void postMessage( const std::string & id, const ::std::string & stri, const ::Ice::Current & c = ::Ice::Current() );

    bool queryCtrl( const std::string & id, const ::Ice::Current & c = ::Ice::Current() );
    bool querySuper( const std::string & id, const ::std::string&, const ::Ice::Current & c = ::Ice::Current() );
    void releaseCtrl( const std::string & id, const ::Ice::Current & c = ::Ice::Current() );
    ::Host::CCamPrx cam( const std::string & id, const ::Ice::Current & c= ::Ice::Current() );
    ::Host::CMotoPrx moto( const std::string & id, const ::Ice::Current & c= ::Ice::Current() );

    void postImage( const ::Types::TByteArray & data, const ::Ice::Current & c= ::Ice::Current() );
    int clientCnt() const;
protected:
    ::IceUtil::Mutex m_mut; // All public functions should be locked with mutex because they are called potentially from two threads.
    CHostIceThread * m_owner;
    ::Host::CMotoPtr  m_motoView;
    ::Host::CMotoPtr  m_motoCtrl;
    ::Host::CMotoPtr m_motoSuper;
    ::Host::CCamPtr   m_camView;
    ::Host::CCamPtr   m_camCtrl;
    ::Host::CCamPtr  m_camSuper;
    ::Host::CMotoPrx m_motoViewPrx;
    ::Host::CMotoPrx m_motoCtrlPrx;
    ::Host::CMotoPrx m_motoSuperPrx;
    ::Host::CCamPrx m_camViewPrx;
    ::Host::CCamPrx m_camCtrlPrx;
    ::Host::CCamPrx m_camSuperPrx;
private:
    bool nicknameUnique( const std::string & nickname ) const;
    std::string clientId( const std::string & nickname, const ::Client::CClientPrx & client );
    void addClient( const std::string & id, const CClientDesc & client );
    void remClient( const std::string & id );
    bool hasClient( const std::string & id ) const;
    bool client( const std::string & id, CClientDesc & client ) const;
    void updateClient( const std::string & id, const CClientDesc & client );
    void validateClientList( const ::Ice::Current & c = ::Ice::Current() );
    void sendClientList( const ::Ice::Current & c );

    typedef std::map<std::string, CClientDesc>                  TClients;
    typedef std::map<std::string, CClientDesc>::iterator        TClientsIter;
    typedef std::map<std::string, CClientDesc>::const_iterator TClientsConstIter;
    TClients m_clients;
};

#endif


