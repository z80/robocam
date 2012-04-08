
#ifndef __MOTO_THREAD_HDW_H_
#define __MOTO_THREAD_HDW_H_

#include <QThread>
#include <QTimer>
#include <QMutex>

class CMotoCtrlHdw;
class CHostIce;

class CMotoThreadHdw: public QThread
{
    Q_OBJECT
public:
    CMotoThreadHdw( QObject * owner, CMotoCtrlHdw * motoCtrl );
    ~CMotoThreadHdw();

    void start();
    void stop();
    void setInterval( int val );
    int  interval() const;
    bool isActive() const;

    void run();
private slots:
    void slotTimer();
private:
    mutable QMutex m_mut;
    int        m_interval;
    bool       m_active;
    QTimer      * m_timer;
    CMotoCtrlHdw * m_motoCtrl;
};



#endif



