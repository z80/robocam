
#ifndef __CLIENT_GUI_H_
#define __CLIENT_GUI_H_

#include <QtGui>
#include "ui_client_gui.h"
#include "client_ice_thread.h"
#include "host.h"

class CCarCtrl;

class CClientGui: public QWidget
{
    Q_OBJECT
public:
    CClientGui( QWidget * parent = 0 );
    ~CClientGui();

    void closeEvent( QCloseEvent * e );

private slots:
    void slotConnect();
    void slotMotoEn();
    void slotServoEn();
    void slotMoto();
    void slotServo();
    void slotQueryCtrl();
    void slotQuerySuper();
    void slotSend();
    
    // Callback m_client.
    void slotAcceptMessageCb();
    void slotAcceptClientListCb();
    void slotMotoEnCb();
    void slotMotoCb();
    void slotServoEnCb();
    void slotServoCb();
    void slotAcceptImageCb();
signals:
    void sigAcceptMessageCb();
    void sigAcceptClientListCb();
    void sigMotoEnCb();
    void sigMotoCb();
    void sigServoEnCb();
    void sigServoCb();
    void sigAcceptImageCb();
private:
    void connect();
    void disconnect();
    void loadSettings();
    void saveSettings();
    void setMotoCtrlEnabled( bool en );
    void setMotoSuperEnabled( bool en );
    void setCamCtrlEnabled( bool en );
    void setCamSuperEnabled( bool en );
    void setChatEnabled( bool en );
    // Callback on m_client.
    void acceptMessageCb( const std::string & stri );
    void acceptClientListCb( const std::vector<std::string> & clients, const std::string & driverNickname );
    void motoEnCb( bool en );
    void motoCb( int dir1, int dir2 );
    void servoEnCb( bool en );
    void servoCb( double servo1, double servo2 );
    void acceptImageCb( const ::Types::TByteArray & data );

    static const QString g_iniFileName;
    QString      m_host;
    ::IceUtil::Handle<CClientIceThread> m_client;

    Ui_ClientGui ui;

    // callback m_client.
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

