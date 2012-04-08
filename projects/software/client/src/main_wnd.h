
#ifndef __MAIN_WND_H_
#define __MAIN_WND_H_

#include <QtGui>
#include "ui_main_wnd.h"
#include "client_ice_thread.h"
#include "host.h"

class CClientList;
class CChat;
class CCamera;
class CMoto;

class CMainWnd: public QMainWindow
{
    Q_OBJECT
public:
    CMainWnd();
    ~CMainWnd();
    
    CClientIceThread * client();
    const std::string & clientId();

    void displayImage( const ::Types::TByteArray & data );

    void closeEvent( QCloseEvent * e );


private slots:
    void slotConnect();
    void slotQueryCtrl();
    void slotQuerySuper();

    // Callback m_client.
    void slotAcceptMessageCb();
    void slotAcceptClientListCb();
    void slotAcceptImageCb();
signals:
    void sigAcceptMessageCb();
    void sigAcceptClientListCb();
    void sigAcceptImageCb();

private:
    void loadSettings();
    void saveSettings();
    void setViewEnabled( bool en );
    void setCtrlEnabled( bool en );
    void setSuperEnabled( bool en );
    void hdwConnect();
    void hdwDisconnect();

    void acceptMessageCb( const std::string & stri );
    void acceptClientListCb( const std::vector<std::string> & clients, const std::string & driverNickname );
    void acceptImageCb( const ::Types::TByteArray & data );


    Ui_CMainWnd  ui;
    QDockWidget  * m_clientListDock;
    CClientList  * m_clientList;
    QDockWidget  * m_chatDock;
    CChat        * m_chat;
    
    CCamera      * m_camera;

    QDockWidget  * m_motoDock;
    CMoto        * m_moto;

    static const QString g_iniFileName;
    std::string  m_host;
    std::string  m_nickname;
    ::IceUtil::Handle<CClientIceThread> m_client;

    QMutex m_mutex;
    std::string m_msg;
    std::vector<std::string> m_clients;
    std::string m_driverNickname;
    ::Types::TByteArray m_imageData;
    QByteArray          m_imageBa;
    QImage              m_image;
    bool m_en;
    int m_dir1, m_dir2;
    double m_servo1, m_servo2;

};


#endif

