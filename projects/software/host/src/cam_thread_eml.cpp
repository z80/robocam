
#include "cam_thread_eml.h"
#include "cam_ctrl_eml.h"

CCamThreadEml::CCamThreadEml( QObject * owner, CCamCtrlEml * camCtrl )
: QThread( 0 ), 
  m_interval( 500 ), 
  m_active( false ), 
  m_camCtrl( camCtrl )
{
    m_timer = 0;
    QThread::start();
}

CCamThreadEml::~CCamThreadEml()
{
    this->quit();
    this->wait();
}

void CCamThreadEml::start()
{
    QMutexLocker lock( &m_mut );
    m_active = true;
}

void CCamThreadEml::stop()
{
    QMutexLocker lock( &m_mut );
    m_active = false;
}

void CCamThreadEml::setInterval( int val )
{
    QMutexLocker lock( &m_mut );
    m_interval = val;
}

int CCamThreadEml::interval() const
{
    QMutexLocker lock( &m_mut );
    return m_interval;
}

bool CCamThreadEml::isActive() const
{
    QMutexLocker lock( &m_mut );
    return m_active;
}

void CCamThreadEml::run()
{
    m_timer = new QTimer();
    m_timer->setInterval( m_interval );
    m_timer->setSingleShot( false );
    // Start beforehand.
    connect( m_timer, SIGNAL(timeout()),        this, SLOT(slotTimer()) );
    m_timer->start();
    m_timer->moveToThread( QApplication::instance()->thread() );
    //start();
    // Events loop.
    this->exec();
    // Finalization.
    m_timer->moveToThread( this );
    m_timer->deleteLater();
}

void CCamThreadEml::slotTimer()
{
    QMutexLocker lock( &m_mut );
    if ( m_active )
    {
        m_camCtrl->postImage();
        if ( m_timer->interval() != m_interval )
            m_timer->setInterval( m_interval );
    }
}





