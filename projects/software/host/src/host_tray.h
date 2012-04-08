
#ifndef __HOST_TRAY_H_
#define __HOST_TRAY_H_

#include <QtGui>
#include "host_ice.h"
#include "host_ice_thread.h"

class CHostTray: public QSystemTrayIcon
{
    Q_OBJECT
public:
    CHostTray( QObject * parent = 0 );
    ~CHostTray();

    static const QString & iniFileName();
private slots:
    void slotListen();
    void slotConnect();
    void slotQuit();
private:
    void loadSettings();
    void saveSettings();

    QMenu * m_menu;
    QAction * m_actionListen,
            * m_actionConnect, 
            * m_actionQuit;
    QString m_listen;
    QString m_connect;
    QString m_passwd;
    bool    m_emulation;
    ::IceUtil::Handle<CHostIceThread> m_host;

    static const QString g_iniFileName;
};

#endif


