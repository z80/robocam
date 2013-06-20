
#include "qxmpp_video.h"
#include <QtGui>
//#include <QAudioInput>
//#include <QAudioOutput>
//#include <QtMultimedia>

QXmppVideo::QXmppVideo( QXmppClient * parent )
    : QTimer( parent ),
      m_client( parent )
{
    m_call = 0;

    // Add the extention for Jingle (Voice/Video calls).
    m_client->addExtension( &m_callManager );

    this->setInterval( 33 );

    QObject::connect( this,
                      SIGNAL(timeout()),
                      this,
                      SLOT(writeFrame()) );

    QObject::connect( m_client,
                      SIGNAL(connected()),
                      this,
                      SLOT(connected()) );

    QObject::connect( m_client,
                      SIGNAL(disconnected()),
                      this,
                      SLOT(disconnected()) );

    QObject::connect( &m_client->rosterManager(),
                     SIGNAL(presenceChanged(const QString &, const QString &)),
                     this,
                     SLOT(presenceChanged(const QString &, const QString &)) );

    QObject::connect( &m_callManager,
                      SIGNAL(callReceived(QXmppCall *)),
                      this,
                      SLOT(callReceived(QXmppCall *)) );

    QObject::connect( &m_callManager,
                      SIGNAL(callStarted(QXmppCall *)),
                      this,
                      SLOT(callStarted(QXmppCall *)) );
}

QXmppVideo::~QXmppVideo()
{

}

void QXmppVideo::setFrameHandler( PeerAbst::TFrameHandler handler )
{
    m_frameHandler = handler;
}

void QXmppVideo::frame( QImage & image )
{
    image = m_image;
}

// https://en.wikipedia.org/wiki/YUV {
inline quint8 QXmppVideo::clamp(qint32 value)
{
    return (uchar) ((value > 255)? 255: ((value < 0)? 0: value));
}

inline quint8 QXmppVideo::med(quint8 v1, quint8 v2)
{
    return ((v1 + v2) >> 1);
}

inline quint8 QXmppVideo::rgb2y(quint8 r, quint8 g, quint8 b)
{
    return (( 66  * r + 129 * g + 25  * b + 128) >> 8) + 16;
}

inline quint8 QXmppVideo::rgb2u(quint8 r, quint8 g, quint8 b)
{
    return ((-38  * r - 74  * g + 112 * b + 128) >> 8) + 128;
}

inline quint8 QXmppVideo::rgb2v(quint8 r, quint8 g, quint8 b)
{
    return (( 112 * r - 94  * g - 18  * b + 128) >> 8) + 128;
}

inline qint32 QXmppVideo::y2uv(qint32 y, qint32 width)
{
    return (qint32) (((qint32) (y / width) >> 1) * width / 2.0 + (qint32) ((y % width) / 2.0));
}

inline qint32 QXmppVideo::yuv2r(quint8 y, quint8 u, quint8 v)
{
    Q_UNUSED(u)

    return ((298 * (y - 16) + 409 * (v - 128) + 128) >> 8);
}

inline qint32 QXmppVideo::yuv2g(quint8 y, quint8 u, quint8 v)
{
    return ((298 * (y - 16) - 100 * (u - 128) - 208 * (v - 128) + 128) >> 8);
}

inline qint32 QXmppVideo::yuv2b(quint8 y, quint8 u, quint8 v)
{
    Q_UNUSED(v)

    return ((298 * (y - 16) + 516 * (u - 128) + 128) >> 8);
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
        *oBits++ = this->rgb2y(r1, g1, b1);

        // u
        *oBits++ = this->rgb2u(this->med(r1, r2), this->med(g1, g2), this->med(b1, b2));

        // y2
        *oBits++ = this->rgb2y(r2, g2, b2);

        // v
        *oBits++ = this->rgb2v(this->med(r1, r2), this->med(g1, g2), this->med(b1, b2));
    }

    frame = videoFrame;
}

void QXmppVideo::videoFrameToImage( const QXmppVideoFrame & videoFrame )
{
    QImage & image = m_image;
    image = QImage(videoFrame.size(), QImage::Format_RGB888);

    qint32 width = videoFrame.size().width();
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
                *oBits++ = this->clamp(this->yuv2r(y1, u, v));

                // g1
                *oBits++ = this->clamp(this->yuv2g(y1, u, v));

                // b1
                *oBits++ = this->clamp(this->yuv2b(y1, u, v));

                // r2
                *oBits++ = this->clamp(this->yuv2r(y2, u, v));

                // g2
                *oBits++ = this->clamp(this->yuv2g(y2, u, v));

                // b2
                *oBits++ = this->clamp(this->yuv2b(y2, u, v));
            }
        break;

        case QXmppVideoFrame::Format_YUV420P:
            yp = iBits;
            up = yp + width * height;
            vp = up + width * height / 4;

            for (qint32 i = 0; i < width * height; i++)
            {
                quint8 y = yp[i];
                quint8 u = up[this->y2uv(i, width)];
                quint8 v = vp[this->y2uv(i, width)];

                // r
                *oBits++ = this->clamp(this->yuv2r(y, u, v));

                // g
                *oBits++ = this->clamp(this->yuv2g(y, u, v));

                // b
                *oBits++ = this->clamp(this->yuv2b(y, u, v));
            }
        break;

        default:
        break;
    }
}










void QXmppVideo::slotCall( const QString & jid )
{
    // Call to contact as otherusername@server.org/resource
    this->m_call = this->m_callManager.call( jid );

    QObject::connect(this->m_call,
                     SIGNAL(connected()),
                     this,
                     SLOT(callConnected()));

    QObject::connect(this->m_call,
                     SIGNAL(finished()),
                     this,
                     SLOT(callFinished()));

    QObject::connect(this->m_call,
                     SIGNAL(stateChanged(QXmppCall::State)),
                     this,
                     SLOT(stateChanged(QXmppCall::State)));

    QObject::connect(this->m_call,
                     SIGNAL(audioModeChanged(QIODevice::OpenMode)),
                     this,
                     SLOT(audioModeChanged(QIODevice::OpenMode)));

    QObject::connect(this->m_call,
                     SIGNAL(videoModeChanged(QIODevice::OpenMode)),
                     this,
                     SLOT(videoModeChanged(QIODevice::OpenMode)));
}

void QXmppVideo::slotEndCall()
{
    if ( this->m_call )
    {
        // Hangup call.
        this->m_call->hangup();

        QObject::disconnect(this->m_call,
                            SIGNAL(connected()),
                            this,
                            SLOT(callConnected()));

        QObject::disconnect(this->m_call,
                            SIGNAL(finished()),
                            this,
                            SLOT(callFinished()));

        QObject::disconnect(this->m_call,
                            SIGNAL(stateChanged(QXmppCall::State)),
                            this,
                            SLOT(stateChanged(QXmppCall::State)));

        QObject::disconnect(this->m_call,
                            SIGNAL(audioModeChanged(QIODevice::OpenMode)),
                            this,
                            SLOT(audioModeChanged(QIODevice::OpenMode)));

        QObject::disconnect(this->m_call,
                            SIGNAL(videoModeChanged(QIODevice::OpenMode)),
                            this,
                            SLOT(videoModeChanged(QIODevice::OpenMode)));

        this->m_call = 0;
    }
}

void QXmppVideo::audioModeChanged( QIODevice::OpenMode mode )
{
    /*
    QXmppRtpAudioChannel *channel = this->m_call->audioChannel();

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

void QXmppVideo::callConnected()
{
    // Only caller or receiver can start a video call, but not both
    // at same time.
    if (this->m_call->direction() == QXmppCall::OutgoingDirection)
        this->m_call->startVideo();
}

void QXmppVideo::callFinished()
{
    if (this->m_call->direction() == QXmppCall::OutgoingDirection)
        this->m_call->stopVideo();
}

void QXmppVideo::callReceived(QXmppCall *call)
{
    this->m_call = call;

    QObject::connect(this->m_call,
                     SIGNAL(connected()),
                     this,
                     SLOT(callConnected()));

    QObject::connect(this->m_call,
                     SIGNAL(finished()),
                     this,
                     SLOT(callFinished()));

    QObject::connect(this->m_call,
                     SIGNAL(stateChanged(QXmppCall::State)),
                     this,
                     SLOT(stateChanged(QXmppCall::State)));

    QObject::connect(this->m_call,
                     SIGNAL(audioModeChanged(QIODevice::OpenMode)),
                     this,
                     SLOT(audioModeChanged(QIODevice::OpenMode)));

    QObject::connect(this->m_call,
                     SIGNAL(videoModeChanged(QIODevice::OpenMode)),
                     this,
                     SLOT(videoModeChanged(QIODevice::OpenMode)));

    // Accept call.
    call->accept();
    // Cancel call.
    //call->hangup();
}

void QXmppVideo::callStarted(QXmppCall *call)
{
    this->m_call = call;
}

void QXmppVideo::connected()
{
    // Update user status.
    this->m_client->clientPresence().setType(QXmppPresence::Available);
}

void QXmppVideo::disconnected()
{
    this->m_roster.clear();
}

void QXmppVideo::presenceChanged(const QString &bareJid, const QString &resource)
{
    // Get contacts list.
    QStringList roster = this->m_client->rosterManager().getRosterBareJids();

    if (!roster.contains(bareJid))
        return;

    QXmppPresence presence = this->m_client->rosterManager().getPresence(bareJid, resource);
    QString jid = bareJid + "/" + resource;

    // Only show connected friends.
    if (presence.status().type() == QXmppPresence::Status::Online)
    {
        if (!this->m_roster.contains(jid))
            this->m_roster << jid;
    }
    else
    {
        if (this->m_roster.contains(jid))
            this->m_roster.removeAll(jid);
    }
}

void QXmppVideo::readFrames()
{
    foreach (QXmppVideoFrame frame, this->m_call->videoChannel()->readFrames())
    {
        if (!frame.isValid())
            continue;

        this->videoFrameToImage(frame);

        if ( !m_frameHandler.empty() )
            m_frameHandler();
        //emit frame( image );
        //this->lblIncomingFrame->setPixmap(QPixmap::fromImage(image));
    }
}

void QXmppVideo::stateChanged(QXmppCall::State state)
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

void QXmppVideo::videoModeChanged(QIODevice::OpenMode mode)
{
    if (mode & QIODevice::ReadOnly)
    {
        QXmppVideoFormat videoFormat;

        // Open the webcam.
        this->m_webcam.open( 0 );

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
        videoFormat.setFrameSize(QSize(this->m_webcam.get(CV_CAP_PROP_FRAME_WIDTH),
                                       this->m_webcam.get(CV_CAP_PROP_FRAME_HEIGHT)));

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

        videoFormat.setPixelFormat(QXmppVideoFrame::Format_YUYV);

        // Change default Encoder Format.
        this->m_call->videoChannel()->setEncoderFormat(videoFormat);

        if (!this->isActive())
        {
            QObject::connect( this,
                              SIGNAL(timeout()),
                              this,
                              SLOT(writeFrame()));

            QObject::connect( this,
                              SIGNAL(timeout()),
                              this,
                              SLOT(readFrames()));

            this->start();
        }
    }
    else if (mode == QIODevice::NotOpen)
    {
        this->m_webcam.release();

        QObject::disconnect( this,
                             SIGNAL(timeout()),
                             this,
                             SLOT(writeFrame()) );

        QObject::disconnect( this,
                             SIGNAL(timeout()),
                             this,
                             SLOT(readFrames()) );

        this->stop();
    }
}

void QXmppVideo::writeFrame()
{
    if (!this->m_call)
        return;

    cv::Mat mat;

    this->m_webcam >> mat;

    QImage imageBGR((const uchar *)mat.data, mat.cols, mat.rows, QImage::Format_RGB888);

    // OpenCV swaps Red and Blue components.
    QImage imageRGB = imageBGR.rgbSwapped();

    QSize encoderFrameSize = this->m_call->videoChannel()->encoderFormat().frameSize();

    if (imageRGB.size() != encoderFrameSize)
        imageRGB = imageRGB.scaled(encoderFrameSize);

    QXmppVideoFrame frame;
    this->imageToVideoFrame( imageRGB, frame );

    this->m_call->videoChannel()->writeFrame(frame);

    //this->lblOutgoingFrame->setPixmap(QPixmap::fromImage(imageRGB));
}










