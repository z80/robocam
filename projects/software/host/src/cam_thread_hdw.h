
#ifndef __CAM_THREAD_EML_H_
#define __CAM_THREAD_EML_H_

#include <QThread>
#include <QTimer>
#include <QMutex>

class CCamCtrlHdw;
class CHostIce;

class CCamThreadHdw: public QThread
{
    Q_OBJECT
public:
    CCamThreadHdw( QObject * owner, CCamCtrlHdw * camCtrl );
    ~CCamThreadHdw();

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
    CCamCtrlHdw * m_camCtrl;
};



#endif



