
#ifndef __QXMPP_VIDEO_H_
#define __QXMPP_VIDEO_H_

#include <QTimer>
#include <QProcess>
#include <QXmppClient.h>
#include <QXmppRosterManager.h>
#include <QXmppCallManager.h>
#include <QXmppRtpChannel.h>
#include <opencv2/opencv.hpp>

#include "peer_abst.h"

class QXmppVideo: public QTimer
{
    Q_OBJECT
public:
    QXmppVideo( QXmppClient * parent );
    ~QXmppVideo();

    void setFrameHandler( PeerAbst::TFrameHandler handler );
    void frame( QImage & image );

private:
    // Methods for converting between RGB <=> YUV.
    quint8 clamp(qint32 value);
    quint8 med(quint8 v1, quint8 v2);
    quint8 rgb2y(quint8 r, quint8 g, quint8 b);
    quint8 rgb2u(quint8 r, quint8 g, quint8 b);
    quint8 rgb2v(quint8 r, quint8 g, quint8 b);
    qint32 y2uv(qint32 y, qint32 width);
    qint32 yuv2r(quint8 y, quint8 u, quint8 v);
    qint32 yuv2g(quint8 y, quint8 u, quint8 v);
    qint32 yuv2b(quint8 y, quint8 u, quint8 v);

    // Convertion between QXmpp <=> Qt image format.
    void imageToVideoFrame( const QImage & image, QXmppVideoFrame & frame );
    void videoFrameToImage( const QXmppVideoFrame & videoFrame );

private slots:
    void slotCall( const QString & jid );
    void slotEndCall();
    void audioModeChanged(QIODevice::OpenMode mode);
    void callConnected();
    void callFinished();
    void callReceived(QXmppCall *call);
    void callStarted(QXmppCall *call);
    void connected();
    void disconnected();
    void presenceChanged(const QString &bareJid, const QString &resource);
    void readFrames();
    void stateChanged(QXmppCall::State state);
    void videoModeChanged(QIODevice::OpenMode mode);
    void writeFrame();

private:
    QXmppClient      * m_client;
    QStringList      m_roster;
    QXmppCall        * m_call;
    QXmppCallManager m_callManager;
    cv::VideoCapture m_webcam;

    PeerAbst::TFrameHandler m_frameHandler;
    QImage                  m_image;
};

#endif



