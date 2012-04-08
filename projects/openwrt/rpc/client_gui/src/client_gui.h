
#ifndef __CLIENT_GUI_H_
#define __CLIENT_GUI_H_

#include <QtGui>
#include "ui_client_gui.h"
#include "camera_ctrl.h"

class CCarCtrl;

class CClientGui: public QWidget
{
    Q_OBJECT
public:
    CClientGui( QWidget * parent = 0 );
    ~CClientGui();

    void closeEvent( QCloseEvent * e );

private slots:
    void slotSetDeviceName();
    void slotOpen();
    void slotIsOpened();
    void slotClose();
    void slotInitDevice();
    void slotImageSize();
    void slotStartCapture();
    void slotStopCapture();
    void slotAcquire();
    void slotData();
    void slotLastError();
    void slotClearLog();
private:
    void connectHost();
    void loadSettings();
    void saveSettings();
    void log( const QString & stri );
    static const QString g_iniFileName;

    QString      m_host;
    CCameraCtrl  * m_cameraCtrl;
    Ui_ClientGui ui;
    int m_width, m_height, m_sz;
    std::vector<unsigned char> m_yuyv;
    std::vector<unsigned char> m_raw;
    QImage m_image;
};

#endif

