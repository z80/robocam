
#ifndef __HOST_ICE_THREAD_H_
#define __HOST_ICE_THREAD_H_

#include <IceE/Thread.h>
#include <IceE/Monitor.h>
#include <queue>
#include <map>
#include "host_ice.h"
#include "hdw.h"
#include "client.h"


class CServerGui;
class CMotoCtrl;
class CMotoCtrlEml;
class CMotoCtrlHdw;
class CCamCtrl;
class CCamCtrlEml;
class CCamCtrlHdw;

class CHostIceThread: public IceUtil::Thread
{
public:
    CHostIceThread( const std::string & listen  = "tcp -p 26001", 
                    const std::string & connect = "default -p 12345", 
                    const std::string & passwd  = "qwertyqwerty" );
    ~CHostIceThread();

    void shutdown();
    std::string lastError();
    std::string status() const;

    bool listen();
    bool connect( bool emulation = false );
    bool hdwAttached();

    void run();
protected:
    Ice::CommunicatorPtr             m_comm;
    Ice::ObjectAdapterPtr            m_adapter;
    IceUtil::Mutex                   m_mutex;
    IceUtil::Monitor<IceUtil::Mutex> m_semaphore;
    
    std::queue< std::string >        m_errors;
    
    std::string                      m_status;
    
    
    std::string m_listen;
    std::string m_connect;
    std::string m_passwd;

    IceUtil::Handle<CHostIce>           m_host;
    ::Hdw::CHdwPrx                      m_hdw;

    CMotoCtrl * m_moto;
    CCamCtrl  * m_cam;

    friend class CHostTray;
    friend class CHostIce;
    friend class CMotoViewIce;
    friend class CMotoCtrlIce;
    friend class CMotoSuperIce;
    friend class CCamViewIce;
    friend class CCamCtrlIce;
    friend class CCamSuperIce;
    friend class CCamCtrlEml;
    friend class CCamCtrlHdw;
    friend class CMotoCtrlEml;
    friend class CMotoCtrlHdw;
};

#endif

