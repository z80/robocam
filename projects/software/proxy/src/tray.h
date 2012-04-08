
#ifndef __TRAY_H_
#define __TRAY_H_

#include <QtGui>
#include "proxy.h"

class CTray: public QSystemTrayIcon
{
    Q_OBJECT
public:
    CTray( QObject * parent = 0 );
    ~CTray();

    static const QString & iniFileName();
private slots:
    void slotListen();
    void slotQuit();
private:
    void loadSettings();
    void saveSettings();

    QMenu * m_menu;
    QAction * m_actionListen,
            * m_actionQuit;
    QString m_listenHost;
    QString m_connectHost;
    quint16 m_listenPort;
    quint16 m_connectPort;

    CProxy * m_proxy;

    static const QString g_iniFileName;
};

#endif


