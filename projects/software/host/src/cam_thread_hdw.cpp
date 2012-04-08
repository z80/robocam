
#include "cam_thread_hdw.h"
#include "cam_ctrl_hdw.h"

CCamThreadHdw::CCamThreadHdw( QObject * owner, CCamCtrlHdw * camCtrl )
: QThread( owner ), 
  m_interval( 500 ), 
  m_active( false ), 
  m_camCtrl( camCtrl )
{
    m_timer = 0;
    QThread::start();
}

CCamThreadHdw::~CCamThreadHdw()
{
    this->quit();
    this->wait();
}

void CCamThreadHdw::start()
{
    QMutexLocker lock( &m_mut );
    m_active = true;
}

void CCamThreadHdw::stop()
{
    QMutexLocker lock( &m_mut );
    m_active = false;
}

void CCamThreadHdw::setInterval( int val )
{
    QMutexLocker lock( &m_mut );
    m_interval = val;
}

int CCamThreadHdw::interval() const
{
    QMutexLocker lock( &m_mut );
    return m_interval;
}

bool CCamThreadHdw::isActive() const
{
    QMutexLocker lock( &m_mut );
    return m_active;
}

void CCamThreadHdw::run()
{
    m_timer = new QTimer();
    m_timer->setSingleShot( false );
    m_timer->setInterval( m_interval );
    connect( m_timer, SIGNAL(timeout()),        this, SLOT(slotTimer()) );
    // Start beforehand.
    m_timer->start();
    m_timer->moveToThread( QApplication::instance()->thread() );
    //start();
    // Events loop.
    this->exec();
    // Finalization.
    m_timer->moveToThread( this );
    m_timer->deleteLater();
}

void CCamThreadHdw::slotTimer()
{
    QMutexLocker lock( &m_mut );
    if ( m_active )
    {
        m_camCtrl->postImage();
        if ( m_timer->interval() != m_interval )
            m_timer->setInterval( m_interval );
    }
}





