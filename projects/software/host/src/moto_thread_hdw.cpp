
#include "moto_thread_hdw.h"
#include "moto_ctrl_hdw.h"
#include <QtGui>

CMotoThreadHdw::CMotoThreadHdw( QObject * owner, CMotoCtrlHdw * motoCtrl )
: QThread( owner ), 
  m_interval( 3000 ),
  m_active( false ), 
  m_motoCtrl( motoCtrl )
{
    m_timer = 0;
    QThread::start();
}

CMotoThreadHdw::~CMotoThreadHdw()
{
    this->quit();
    this->wait();
}

void CMotoThreadHdw::start()
{
    QMutexLocker lock( &m_mut );
    m_active = true;
}

void CMotoThreadHdw::stop()
{
    QMutexLocker lock( &m_mut );
    m_active = false;
}

void CMotoThreadHdw::setInterval( int val )
{
    QMutexLocker lock( &m_mut );
    m_interval = val;
}

int CMotoThreadHdw::interval() const
{
    QMutexLocker lock( &m_mut );
    return m_interval;
}

bool CMotoThreadHdw::isActive() const
{
    QMutexLocker lock( &m_mut );
    return m_active;
}

void CMotoThreadHdw::run()
{
    m_timer = new QTimer();
    m_timer->setInterval( m_interval );
    connect( m_timer, SIGNAL(timeout()),        this, SLOT(slotTimer()) );
    // Start beforehand.
    m_timer->start();
    start();
    m_timer->moveToThread( QApplication::instance()->thread() );
    // Events loop.
    this->exec();
    // Finalization.
    m_timer->moveToThread( this );
    m_timer->deleteLater();
}

void CMotoThreadHdw::slotTimer()
{
    QMutexLocker lock( &m_mut );
    if ( m_active )
    {
        m_motoCtrl->checkPowerState();
        if ( m_timer->interval() != m_interval )
            m_timer->setInterval( m_interval );
    }
}





