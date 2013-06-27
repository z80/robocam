
#include "xmpp_video.h"
#include "rpc_call_interface.h"
#include <QXmppClient.h>
#include <QXmppRosterManager.h>
#include <QXmppCallManager.h>
#include <QXmppRpcManager.h>
#include <QXmppRtpChannel.h>
#include <opencv2/opencv.hpp>

class QXmppVideo::PD
{
public:
    PD ( QXmppVideo * video )
        : callInterface( video )
    {}

    ~PD() {}

    QXmppClient      * client;
    QXmppCallManager callManager;
    QXmppRpcManager  rpcManager;
    CallInterface    callInterface;
    QXmppCall        * call;
    cv::VideoCapture webcam;

    QImage           image;
    QString          jid;
    bool             acceptCall;
};






// https://en.wikipedia.org/wiki/YUV {
inline quint8 clamp(qint32 value)
{
    return (uchar) ((value > 255)? 255: ((value < 0)? 0: value));
}

inline quint8 med(quint8 v1, quint8 v2)
{
    return ((v1 + v2) >> 1);
}

inline quint8 rgb2y(quint8 r, quint8 g, quint8 b)
{
    return (( 66  * r + 129 * g + 25  * b + 128) >> 8) + 16;
}

inline quint8 rgb2u(quint8 r, quint8 g, quint8 b)
{
    return ((-38  * r - 74  * g + 112 * b + 128) >> 8) + 128;
}

inline quint8 rgb2v(quint8 r, quint8 g, quint8 b)
{
    return (( 112 * r - 94  * g - 18  * b + 128) >> 8) + 128;
}

inline qint32 y2uv(qint32 y, qint32 width)
{
    return (qint32) (((qint32) (y / width) >> 1) * width / 2.0 + (qint32) ((y % width) / 2.0));
}

inline qint32 yuv2r(quint8 y, quint8 u, quint8 v)
{
    Q_UNUSED(u)

    return ((298 * (y - 16) + 409 * (v - 128) + 128) >> 8);
}

inline qint32 yuv2g(quint8 y, quint8 u, quint8 v)
{
    return ((298 * (y - 16) - 100 * (u - 128) - 208 * (v - 128) + 128) >> 8);
}

inline qint32 yuv2b(quint8 y, quint8 u, quint8 v)
{
    Q_UNUSED(v)

    return ((298 * (y - 16) + 516 * (u - 128) + 128) >> 8);
}












QXmppVideo::QXmppVideo( QXmppClient * parent )
: QTimer( parent )
{
    pd             = new PD();
    pd->client     = parent;
    pd->acceptCall = true;
    pd->call       = 0;

    pd->client->addExtension( &pd->callManager );
    pd->client->addExtension( &pd->callManager );

    QTimer::setInterval( 33 );

    QObject::connect( this,
                      SIGNAL(timeout()),
                      this,
                      SLOT(xmppWriteFrame()) );

    QObject::connect( &pd->callManager,
                      SIGNAL(callReceived(QXmppCall *)),
                      this,
                      SLOT(callReceived(QXmppCall *)) );

    QObject::connect( &pd->callManager,
                      SIGNAL(callStarted(QXmppCall *)),
                      this,
                      SLOT(callStarted(QXmppCall *)) );
}

QXmppVideo::~QXmppVideo()
{
    delete pd;
}

void QXmppVideo::setTarget( const QString & jid )
{
    pd->jid = jid;
}

void QXmppVideo::setAcceptCall( bool en )
{
    pd->acceptCall = en;
}

void QXmppVideo::frame( QImage & image )
{
    image = pd->image;
}

void QXmppVideo::imageToVideoFrame( const QImage & image, QXmppVideoFrame & frame )
{
    QXmppVideoFrame videoFrame(2 * image.width() * image.height(),
                               image.size(),
                               2 * image.width(),
                               QXmppVideoFrame::Format_YUYV);

    const quint8 *iBits = (const quint8 *) image.bits();
    quint8 *oBits = (quint8 *) videoFrame.bits();

    for (qint32 i = 0; i < 3 * image.width() * image.height(); i += 6)
    {
        quint8 r1 = iBits[i];
        quint8 g1 = iBits[i + 1];
        quint8 b1 = iBits[i + 2];

        quint8 r2 = iBits[i + 3];
        quint8 g2 = iBits[i + 4];
        quint8 b2 = iBits[i + 5];

        // y1
        *oBits++ = rgb2y(r1, g1, b1);

        // u
        *oBits++ = rgb2u(med(r1, r2), med(g1, g2), med(b1, b2));

        // y2
        *oBits++ = rgb2y(r2, g2, b2);

        // v
        *oBits++ = rgb2v(med(r1, r2), med(g1, g2), med(b1, b2));
    }

    frame = videoFrame;
}

void QXmppVideo::videoFrameToImage( const QXmppVideoFrame & videoFrame )
{
    QImage & image = pd->image;
    image = QImage( videoFrame.size(), QImage::Format_RGB888 );

    qint32 width  = videoFrame.size().width();
    qint32 height = videoFrame.size().height();

    const quint8 *iBits = (const quint8 *) videoFrame.bits();
    quint8 *oBits = (quint8 *) image.bits();
    const quint8 *yp, *up, *vp;

    switch (videoFrame.pixelFormat())
    {
        case QXmppVideoFrame::Format_YUYV:
            for (qint32 i = 0; i < 2 * width * height; i += 4)
            {
                quint8 y1 = iBits[i];
                quint8 u  = iBits[i + 1];
                quint8 y2 = iBits[i + 2];
                quint8 v  = iBits[i + 3];

                // r1
                *oBits++ = clamp(yuv2r(y1, u, v));

                // g1
                *oBits++ = clamp(yuv2g(y1, u, v));

                // b1
                *oBits++ = clamp(yuv2b(y1, u, v));

                // r2
                *oBits++ = clamp(yuv2r(y2, u, v));

                // g2
                *oBits++ = clamp(yuv2g(y2, u, v));

                // b2
                *oBits++ = clamp(yuv2b(y2, u, v));
            }
        break;

        case QXmppVideoFrame::Format_YUV420P:
            yp = iBits;
            up = yp + width * height;
            vp = up + width * height / 4;

            for (qint32 i = 0; i < width * height; i++)
            {
                quint8 y = yp[i];
                quint8 u = up[y2uv(i, width)];
                quint8 v = vp[y2uv(i, width)];

                // r
                *oBits++ = clamp(yuv2r(y, u, v));

                // g
                *oBits++ = clamp(yuv2g(y, u, v));

                // b
                *oBits++ = clamp(yuv2b(y, u, v));
            }
        break;

        default:
        break;
    }
}

void QXmppVideo::call()
{
    // Call to contact as otherusername@server.org/resource
    pd->call = pd->callManager.call( pd->jid );

    QObject::connect(pd->call,
                     SIGNAL(connected()),
                     this,
                     SLOT(xmppCallConnected()));

    QObject::connect(pd->call,
                     SIGNAL(finished()),
                     this,
                     SLOT(xmppCallFinished()));

    QObject::connect(pd->call,
                     SIGNAL(stateChanged(QXmppCall::State)),
                     this,
                     SLOT(xmppCallStateChanged(QXmppCall::State)));

    QObject::connect(pd->call,
                     SIGNAL(audioModeChanged(QIODevice::OpenMode)),
                     this,
                     SLOT(xmppAudioModeChanged(QIODevice::OpenMode)));

    QObject::connect(pd->call,
                     SIGNAL(videoModeChanged(QIODevice::OpenMode)),
                     this,
                     SLOT(xmppVideoModeChanged(QIODevice::OpenMode)));
    QTimer::start();
}

void QXmppVideo::endCall()
{
    QTimer::stop();
    if ( pd->call )
    {
        // Hangup call.
        pd->call->hangup();

        QObject::disconnect(pd->call,
                            SIGNAL(connected()),
                            this,
                            SLOT(xmppCallConnected()));

        QObject::disconnect(pd->call,
                            SIGNAL(finished()),
                            this,
                            SLOT(xmppCallFinished()));

        QObject::disconnect(pd->call,
                            SIGNAL(stateChanged(QXmppCall::State)),
                            this,
                            SLOT(xmppCallStateChanged(QXmppCall::State)));

        QObject::disconnect(pd->call,
                            SIGNAL(audioModeChanged(QIODevice::OpenMode)),
                            this,
                            SLOT(xmppAudioModeChanged(QIODevice::OpenMode)));

        QObject::disconnect(pd->call,
                            SIGNAL(videoModeChanged(QIODevice::OpenMode)),
                            this,
                            SLOT(xmppVideoModeChanged(QIODevice::OpenMode)));

        pd->call = 0;
    }
}

void QXmppVideo::invokeCall()
{
    QXmppRemoteMethodResult method = pd->rpcManager.callRemoteMethod( pd->jid, "CallInterface.call" );
}

void QXmppVideo::invokeEndCall()
{
    QXmppRemoteMethodResult method = pd->rpcManager.callRemoteMethod( pd->jid, "CallInterface.endCall" );
}

void QXmppVideo::xmppAudioModeChanged(QIODevice::OpenMode mode)
{
    /*
    QXmppRtpAudioChannel *channel = pd->call->audioChannel();

    // prepare audio format
    QAudioFormat format;

    format.setFrequency(channel->payloadType().clockrate());
    format.setChannels(channel->payloadType().channels());
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);

    // the size in bytes of the audio buffers to/from sound devices
    // 160 ms seems to be the minimum to work consistently on Linux/Mac/Windows
    const int bufferSize = (format.frequency() * format.channels() * (format.sampleSize() / 8) * 160) / 1000;
    qDebug() << "bufferSize" << bufferSize;

    if ( mode & QIODevice::ReadOnly )
    {
        // initialise audio output
        QAudioOutput *audioOutput = new QAudioOutput( format, this );

        audioOutput->setBufferSize( bufferSize );
        audioOutput->start( channel );
    }

    if ( mode & QIODevice::WriteOnly )
    {
        // initialise audio input
        QAudioInput * audioInput = new QAudioInput(format, this);

        audioInput->setBufferSize( bufferSize );
        audioInput->start( channel );
    }
    */
}

void QXmppVideo::xmppCallConnected()
{
    // Only caller or receiver can start a video call, but not both
    // at same time.
    if ( pd->call->direction() == QXmppCall::OutgoingDirection)
        pd->call->startVideo();
}

void QXmppVideo::xmppCallFinished()
{
    if ( pd->call->direction() == QXmppCall::OutgoingDirection)
        pd->call->stopVideo();
}

void QXmppVideo::xmppCallReceived(QXmppCall *call)
{
    pd->call = call;

    QObject::connect(pd->call,
                     SIGNAL(connected()),
                     this,
                     SLOT(xmppCallConnected()));

    QObject::connect(pd->call,
                     SIGNAL(finished()),
                     this,
                     SLOT(xmppCallFinished()));

    QObject::connect(pd->call,
                     SIGNAL(stateChanged(QXmppCall::State)),
                     this,
                     SLOT(xmppCallStateChanged(QXmppCall::State)));

    QObject::connect(pd->call,
                     SIGNAL(audioModeChanged(QIODevice::OpenMode)),
                     this,
                     SLOT(xmppAudioModeChanged(QIODevice::OpenMode)));

    QObject::connect(pd->call,
                     SIGNAL(videoModeChanged(QIODevice::OpenMode)),
                     this,
                     SLOT(xmppVideoModeChanged(QIODevice::OpenMode)));

    if ( pd->acceptCall )
        // Accept call.
        call->accept();
    else
        // Cancel call.
        call->hangup();
}

void QXmppVideo::xmppCallStarted(QXmppCall *call)
{
    pd->call = call;
}

void QXmppVideo::xmppReadFrames()
{
    bool captured = false;
    foreach ( QXmppVideoFrame frame, pd->call->videoChannel()->readFrames() )
    {
        if (!frame.isValid())
            continue;

        this->videoFrameToImage( frame );
        captured = true;

    }
    if ( captured )
        emit frameReady();
}

void QXmppVideo::xmppCallStateChanged(QXmppCall::State state)
{
    /*switch (state)
    {
        case QXmppCall::ConnectingState:
            this->stbStatusBar->showMessage("Connecting Call");
        break;

        case QXmppCall::ActiveState:
            this->stbStatusBar->showMessage("Active Call");
        break;

        case QXmppCall::DisconnectingState:
            this->stbStatusBar->showMessage("Disconnecting Call");
        break;

        case QXmppCall::FinishedState:
            this->stbStatusBar->showMessage("Finished Call");
        break;

        default:
            this->stbStatusBar->showMessage("");
        break;
    }*/
}

void QXmppVideo::xmppVideoModeChanged(QIODevice::OpenMode mode)
{
    if (mode & QIODevice::ReadOnly)
    {
        QXmppVideoFormat videoFormat;

        // Open the webcam.
        pd->webcam.open( 0 );

        // QXmpp uses this defaults formats for Encoder/Decoder:
        //
        // Default Decoder Format
        // {
        //     frameRate =  15
        //     frameSize =  QSize(320, 240)
        //     pixelFormat =  18
        // }
        //
        // Default Encoder Format
        // {
        //     frameRate =  15
        //     frameSize =  QSize(320, 240)
        //     pixelFormat =  21
        // }

        videoFormat.setFrameRate(30);
        videoFormat.setFrameSize(QSize( pd->webcam.get( CV_CAP_PROP_FRAME_WIDTH ),
                                        pd->webcam.get( CV_CAP_PROP_FRAME_HEIGHT ) ) );

        // QXmpp allow the following pixel formats for video encoding:
        //
        // PixelFormat
        // {
        //     Format_Invalid = 0,
        //     Format_RGB32 = 3,
        //     Format_RGB24 = 4,
        //     Format_YUV420P = 18,
        //     Format_UYVY = 20,
        //     Format_YUYV = 21
        // }
        //
        // QXmpp can be compiled with Vp8 and Theora support.
        // The encoding formats supported by this codecs are:
        //
        // Vpx    -> QXmppVideoFrame::Format_YUYV
        //
        // Theora -> QXmppVideoFrame::Format_YUV420P
        //           QXmppVideoFrame::Format_YUYV

        videoFormat.setPixelFormat( QXmppVideoFrame::Format_YUYV );

        // Change default Encoder Format.
        pd->call->videoChannel()->setEncoderFormat( videoFormat );

        if (!this->isActive())
        {
            QObject::connect( this,
                              SIGNAL( timeout() ),
                              this,
                              SLOT( xmppWriteFrame()) );

            QObject::connect( this,
                              SIGNAL( timeout() ),
                              this,
                              SLOT( xmppReadFrames() ) );

            this->start();
        }
    }
    else if ( mode == QIODevice::NotOpen )
    {
        pd->webcam.release();

        QObject::disconnect( this,
                             SIGNAL( timeout() ),
                             this,
                             SLOT( xmppWriteFrame() ) );

        QObject::disconnect( this,
                             SIGNAL( timeout() ),
                             this,
                             SLOT( xmppReadFrames() ) );

        this->stop();
    }
}

void QXmppVideo::xmppWriteFrame()
{
    if (!pd->call)
        return;

    cv::Mat mat;

    pd->webcam >> mat;

    QImage imageBGR((const uchar *)mat.data, mat.cols, mat.rows, QImage::Format_RGB888);

    // OpenCV swaps Red and Blue components.
    QImage imageRGB = imageBGR.rgbSwapped();

    QSize encoderFrameSize = pd->call->videoChannel()->encoderFormat().frameSize();

    if ( imageRGB.size() != encoderFrameSize )
        imageRGB = imageRGB.scaled( encoderFrameSize );

    QXmppVideoFrame frame;
    this->imageToVideoFrame( imageRGB, frame );

    pd->call->videoChannel()->writeFrame( frame );
}



