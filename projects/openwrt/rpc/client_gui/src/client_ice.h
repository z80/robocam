
#ifndef __CLIENT_ICE_H_
#define __CLIENT_ICE_H_

#include "interface.h"
#include "IceE/IceE.h"
#include "IceE/Mutex.h"
#include "IceE/Thread.h"
#include "IceE/Monitor.h"
#include <queue>

class CCameraCtrl;

class CClientIce: public IceUtil::Thread
{
public:
    CClientIce( CCameraCtrl * owner );
    ~CClientIce();

    void run();
    void shutdown();

    std::string  status();
    std::string  lastError();
protected:
    CCameraCtrl * m_owner;
    std::string m_server;
    // Статус при соединении/отсоединении.
    std::string m_status;
    // Сообщения об ошибках.
    std::queue< std::string >        m_errors;
    IceUtil::Mutex                   m_mutex;
    IceUtil::Monitor<IceUtil::Mutex> m_semaphore;
    // Объекты Ice.
    Ice::PropertiesPtr    m_props;
    Ice::CommunicatorPtr  m_comm;
    // Прокси интерфейса.
    Demo::CameraPrx       m_camera;

    friend class CCameraCtrl;
};


#endif

