
#ifndef __XMPP_VIDEO_H_
#define __XMPP_VIDEO_H_

#include <QtGui>
#include <QXmppClient.h>
#include <QXmppRosterManager.h>
#include <QXmppCallManager.h>
#include <QXmppRtpChannel.h>
#include "QXmppMessage.h"

class QXmppVideo: public QTimer
{
    Q_OBJECT
public:
    QXmppVideo( QXmppClient * parent );
    ~QXmppVideo();

    void setTarget( const QString & jid );
    void setAcceptCall( bool en );
    void frame( QImage & image );
public slots:
    void call();
    void endCall();
    void setFps();

    void invokeCall();
    void invokeEndCall();
    void invokeSetFps( qreal fps );

signals:
    void frameReady();
private:
    // Convertion between QXmpp <=> Qt image format.
    void imageToVideoFrame( const QImage & image, QXmppVideoFrame & frame );
    void videoFrameToImage( const QXmppVideoFrame & videoFrame );
private slots:
    void xmppMessageReceived( const QXmppMessage & msg );
    void xmppAudioModeChanged(QIODevice::OpenMode mode);
    void xmppCallConnected();
    void xmppCallFinished();
    void xmppCallReceived(QXmppCall *call);
    void xmppCallStarted(QXmppCall *call);
    void xmppReadFrames();
    void xmppCallStateChanged(QXmppCall::State state);
    void xmppVideoModeChanged(QIODevice::OpenMode mode);
    void xmppWriteFrame();

private:
    class PD;
    PD * pd;
};



#endif


