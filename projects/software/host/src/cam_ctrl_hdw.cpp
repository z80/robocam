
#include "cam_ctrl_hdw.h"
#include "cam_thread_hdw.h"
#include "host_ice_thread.h"
#include "host_ice.h"
#include "hdw.h"
#include <QtCore>

class CSleep: public QThread
{
public:
    static void sleep( quint32 ms )
    {
        QThread::msleep( ms );
    }
};

CCamCtrlHdw::CCamCtrlHdw( CHostIceThread * owner, Hdw::CHdwPrx hdwPrx )
: CCamCtrl( owner )
{
    m_width  = 176;
    m_height = 144;

    m_inProgress = false;
    m_camPrx    = hdwPrx->cam();
	m_camThread = new CCamThreadHdw( 0, this );

    bool res = false;
    if ( !( res = m_camPrx->isOpen() ) )
        res = m_camPrx->open();
    if ( m_camPrx->isOpen() )
    {
        caps();
        m_camPrx->close();
    }
}

CCamCtrlHdw::~CCamCtrlHdw()
{
    if ( m_camPrx )
        m_camPrx->stopCapture();
    m_camThread->deleteLater();
    m_camPrx->close();
}

bool CCamCtrlHdw::isOpen()
{
    return m_camPrx->isOpen();
}

void CCamCtrlHdw::setResolution( ::Ice::Int & width, ::Ice::Int & height )
{
    QMutexLocker lock( &m_mut );
    m_width  = width;
    m_height = height;
    if ( m_camPrx->isOpen() )
        m_camPrx->close();
}

void CCamCtrlHdw::resolution( ::Ice::Int & width, ::Ice::Int & height )
{
    ::Ice::Int bufferSize;
    m_camPrx->imageSize( width, height, bufferSize );
}

::Ice::Double CCamCtrlHdw::period()
{
    return static_cast<qreal>( m_camThread->interval() ) / 1000.0;
}

bool CCamCtrlHdw::image( ::Types::TByteArray & data )
{
    acquireImage();

    QMutexLocker lock( &m_mut );
    bool res = !m_img.isNull();
    if ( res )
    {
        data.clear();
        data.reserve( m_sendArray.size() );
        for ( unsigned i=0; i<m_sendArray.size(); i++ )
            data.push_back( m_sendArray.at( i ) );
    }
    qDebug( "%s = CCamCtrl::image()", res ? "true" : "false" );
	return res;
}

void CCamCtrlHdw::setReceiveImages(bool en)
{
    qDebug( "CCamCtrl::setReceiveImages( %s )", en ? "true" : "false" );
    if ( en )
        m_camThread->start();
    else
        m_camThread->stop();
}

bool CCamCtrlHdw::receiveImages()
{
    bool res = m_camThread->isActive();
    qDebug( "%s = CCamCtrl::receiveImages()", res ? "true" : "false" );
	return res;
}

::std::string CCamCtrlHdw::deviceName()
{
	return m_deviceName;
}

void CCamCtrlHdw::setPeriod(::Ice::Double value)
{
    qDebug( "CCamCtrl::setPeriod( %4.3f )", value );
    m_camThread->setInterval( static_cast<int>( value * 1000.0 ) );
}

void CCamCtrlHdw::setDeviceName(const ::std::string& stri)
{
    m_camPrx->setDeviceName( stri );
    m_deviceName = stri;
}

bool CCamCtrlHdw::open()
{
	return m_camPrx->open();
}

void CCamCtrlHdw::close()
{
    m_camPrx->close();
}

bool CCamCtrlHdw::acquireImage()
{
    QMutexLocker lock( &m_mut );
    m_inProgress = true;

    if ( !m_camPrx->isOpen() )
    {
        if ( m_camPrx->open() )
        {
            caps();
            if ( !m_camPrx->initDevice( true, m_fourcc, m_width, m_height, 7 ) )
            {
                m_camPrx->close();
                qDebug( "initDevice() failed" );
                debug();
                return false;
            }
            m_camPrx->imageSize( m_width, m_height, m_rawSz );
            m_dec = CDec( m_width, m_height );
            m_raw.resize( m_rawSz );
            m_img = QImage( m_width, m_height, QImage::Format_RGB888 );

            if ( !m_camPrx->startCapture() )
            {
                qDebug( "startCapture() failed" );
                debug();
                return false;
            }
            CSleep::sleep( 1000 );
        }
        else
        {
            qDebug( "open() failed" );
            debug();
            return false;
        }
    }
    const int attempts = 5;
    int tries = attempts;
    while ( tries > 0 )
    {
        if ( m_camPrx->acquire() )
            break;
        tries--;
        CSleep::sleep( 300 );
    }
    if ( tries == 0 )
    {
        std::string err = m_camPrx->lastError();
        m_camPrx->stopCapture();
        m_camPrx->close();
        qDebug( "acquire() failed" );
        debug();
        return false;
    }
    //CSleep::sleep( 50 );

    const int cnt = 102400;
    std::vector<unsigned char> data;
    m_raw.clear();
    m_raw.reserve( m_rawSz );
    for ( int i=0; i<m_rawSz; i+=cnt )
    {
        data.clear();
        m_camPrx->data( i, cnt, data );
        //log( QString( "requested %1, got %2" ).arg( cnt ).arg( data.size() ) );
        for ( unsigned j=0; j<data.size(); j++ )
            m_raw.push_back( data[j] );
    }
    if ( !m_camPrx->release() )
    {
        std::string err = m_camPrx->lastError();
        m_camPrx->stopCapture();
        m_camPrx->close();
        qDebug( "release() failed" );
        debug();
        return false;
    }

    if ( m_raw.size() >= static_cast<unsigned>( m_rawSz ) )
    {
        //log( "data done" );
        // Build image.
        if ( !m_dec.decodeYuyv( m_raw, m_img ) )
            return false;
    }
    else
        return false;

    if ( !m_dec.encodePng( m_img, m_sendArray ) )
        return false;

    return true;
}

void CCamCtrlHdw::postImage()
{
    try
    {
        if ( m_owner->m_host->clientCnt() > 0 )
        {
            // Capture image from camera.
            if ( acquireImage() )
            {
                QMutexLocker lock( &m_mut );
                // Distributing image among connected clients.
                m_owner->m_host->postImage( m_sendArray );
            }
        }
        else
        {
            QMutexLocker lock( &m_mut );
            if ( m_inProgress )
            {
                if ( m_camPrx->isOpen() )
                    m_camPrx->close();
                m_inProgress = false;
            }
        }
    }
    catch ( ::Ice::Exception & /*ex*/ )
    {

    }
}

void CCamCtrlHdw::caps()
{
    std::vector<std::string> cap, info;
    std::vector<bool> en;
    if ( m_camPrx->capabilities( cap, en, info ) )
    {
        for ( unsigned i=0; i<info.size(); i++ )
            qDebug( "%s", info.at( i ).data() );
        for ( unsigned i=0; i<cap.size(); i++ )
            qDebug( "%s: %s", cap.at( i ).data(), en.at( i ) ? "true" : "false" );
    }
    else
    {
        if ( info.size() > 0 )
            qDebug( "%s", info.at( 0 ).data() );
    }

    ::Types::TStringArray fmt;
    ::Types::TLongArray   fourcc;
    if ( m_camPrx->formats( fmt, fourcc ) )
    {
        if ( fourcc.size() > 0 )
            m_fourcc = fourcc.at( 0 );
        for ( unsigned i=0; i<fmt.size(); i++ )
            qDebug( "%s", fmt.at( i ).data() );
    }
}

void CCamCtrlHdw::debug()
{
    while ( true )
    {
        std::string err = m_camPrx->lastError();
        if ( err.size() > 0 )
            qDebug( "%s", err.data() );
        else
            break;
    }
}


