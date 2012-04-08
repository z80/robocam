
#ifndef __CLIENT_ICE_THREAD_H_
#define __CLIENT_ICE_THREAD_H_

#include "IceE/IceE.h"
#include "IceE/Mutex.h"
#include "IceE/Thread.h"
#include "IceE/Monitor.h"
#include <queue>
#include "client.h"
#include "host.h"
#include "client_ice.h"
#include "chat_ice.h"
#include "moto_ice.h"
#include "cam_ice.h"
#include <boost/function.hpp>
class CClientGui;

class CClientIceThread: public IceUtil::Thread
{
public:
	// Chat callback functionality.
    typedef boost::function< void ( const std::vector<std::string> &, 
                                    const std::string & ) > TAcceptClientListCb;
    typedef boost::function< void ( const std::string & ) > TAcceptMessageCb;
    // Moto callback functionality.
    typedef boost::function< void ( bool ) >           TMotoEnCb;
    typedef boost::function< void ( int, int ) >       TMotoCb;
    typedef boost::function< void ( bool ) >           TServoEnCb;
    typedef boost::function< void ( double, double ) > TServoCb;
    // Camera callback functionality.
    typedef boost::function< void ( const ::Types::TByteArray & ) > TAcceptImageCb;

    CClientIceThread( const std::string & host,
                      const std::string & clientName = "anonimous" );
    ~CClientIceThread();

    void run();
    bool connect();
    void shutdown();

    std::string  status();
    const std::string & clientId() const;
    std::string  lastError();
    
    bool queryView();
    bool queryCtrl();
    bool querySuper( const std::string & stri );
    void releaseCtrl();
    ::Host::CHostPrx host();
    ::Host::CMotoPrx moto();
    ::Host::CCamPrx  cam();

    
    // ���������� �������.
    void setAcceptClientListCb( const TAcceptClientListCb & value );
    void setAcceptMessageCb( const TAcceptMessageCb & value );
    void setMotoEnCb( const TMotoEnCb & value );
    void setMotoCb( const TMotoCb & value );
    void setServoEnCb( const TServoEnCb & value );
    void setServoCb( const TServoCb & value );
    void setAcceptImageCb( const TAcceptImageCb & value );
protected:
    std::string m_host;
    // ������ ��� ����������/������������.
    std::string m_status;
    // ��������� �� �������.
    std::queue< std::string >        m_errors;
    IceUtil::Mutex                   m_mutex;
    IceUtil::Monitor<IceUtil::Mutex> m_semaphore;
    // ������� Ice.
    Ice::CommunicatorPtr  m_comm;
    Ice::ObjectAdapterPtr m_adapter;
    // ������.
    ::IceInternal::Handle<CClientIce>      m_client;
    std::string                            m_clientNickname;
    std::string                            m_clientId;
    // ������ ���������� Host, ���������� ��� ����������.
    ::Host::CHostPrx m_hostPrx;
    ::Host::CMotoPrx m_motoPrx;
    ::Host::CCamPrx  m_camPrx;

    // Callback ������� ����������������� ����������.
    TAcceptClientListCb m_acceptClientListCb;
    TAcceptMessageCb    m_acceptMessageCb;
    TMotoEnCb           m_motoEnCb;
    TMotoCb             m_motoCb;
    TServoEnCb          m_servoEnCb;
    TServoCb            m_servoCb;
    TAcceptImageCb      m_acceptImageCb;

    friend class CClientGui;
    friend class CClientIce;
    friend class CChatIce;
    friend class CMotoIce;
    friend class CCamIce;
};


#endif

