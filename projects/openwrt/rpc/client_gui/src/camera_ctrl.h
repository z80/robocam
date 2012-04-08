
#ifndef __CAR_CTRL_H_
#define __CAR_CTRL_H_

#include <QtGui>
#include "interface.h"

class CClientIce;

class CCameraCtrl: public QObject
{
    Q_OBJECT
public:
    CCameraCtrl( QObject * parent = 0 );
    ~CCameraCtrl();

    bool connect( const std::string & host = "default -p 26011 -h 192.168.1.1" );
    void shutdown();
    std::string status();

    void setDeviceName( const std::string & stri );
    bool open();
    void close();
    bool isOpened();
    bool initDevice( const std::string & format, int width, int height );
    void imageSize( int & width, int & height, int & sz );
    bool startCapture();
    void stopCapture();
    bool started();
    bool acquire();
    void data( int from, int sz, std::vector<unsigned char> & res );
    std::string lastError();

    static void decodeYuyv( int w, int h, const std::vector<unsigned char> & yuyv, std::vector<unsigned char> & data );
signals:
    void sigMessage( const QString & stri );

private:
    class PD;
    PD * pd;
};


#endif
