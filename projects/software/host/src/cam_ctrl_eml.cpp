
#include "cam_ctrl_eml.h"
#include "cam_thread_eml.h"
#include "host_ice_thread.h"
#include "host_ice.h"
#include <QtCore>

CCamCtrlEml::CCamCtrlEml( CHostIceThread * owner )
: CCamCtrl( owner )
{
	m_open = false;

    const QString path = "images";
    QDir d( path );
    QStringList filters;
    filters << "*.png";
    m_files = d.entryList( filters, QDir::Files | QDir::Readable, QDir::Name | QDir::IgnoreCase );
    for ( int i=0; i<m_files.size(); i++ )
        m_files[i] = QString( "%1/%2" ).arg( path ).arg( m_files.at( i ) );
    m_fileIndex = 0;
    m_camThread = new CCamThreadEml( 0, this );
}

CCamCtrlEml::~CCamCtrlEml()
{
    m_camThread->deleteLater();
}

bool CCamCtrlEml::isOpen()
{
    qDebug( "%s = CCamCtrl::isOpen()", m_open ? "true" : "false" );
	return m_open;
}

void CCamCtrlEml::setResolution( ::Ice::Int & width, ::Ice::Int & height )
{
}

void CCamCtrlEml::resolution( ::Ice::Int & width, ::Ice::Int & height )
{
    width  = m_img.size().width();
    height = m_img.size().height();
    qDebug( "CCamCtrl::resolution( %i, %i )", width, height );
}

::Ice::Double CCamCtrlEml::period()
{
    double res = static_cast<qreal>( m_camThread->interval() ) / 1000.0;
    qDebug( "%4.3f = CCamCtrl::period()", res );
	return res;
}

bool CCamCtrlEml::image( ::Types::TByteArray & data )
{
    QMutexLocker lock( & m_mut );

    int & ind = m_fileIndex;
    QStringList & l = m_files;

    if ( l.size() < 1 )
        return false;
    QString fileName = l.at( ind++ );
    ind %= l.size();
    m_img.load( fileName, "PNG" );

    bool res = !m_img.isNull();
    if ( res )
    {
        m_imgArray.clear();
        QBuffer b( &m_imgArray );
        b.open( QIODevice::WriteOnly );
        m_img.save( &b, "PNG" );
        b.close();
        data.clear();
        data.reserve( m_imgArray.size() );
        Ice::Byte * orig = reinterpret_cast<Ice::Byte *>( m_imgArray.data() );
        for ( int i=0; i<m_imgArray.size(); i++ )
            data.push_back( orig[i] );
    }
    qDebug( "%s = CCamCtrl::image()", res ? "true" : "false" );
	return res;
}

void CCamCtrlEml::setReceiveImages(bool en)
{
    qDebug( "CCamCtrl::setReceiveImages( %s )", en ? "true" : "false" );
    if ( en )
        m_camThread->start();
    else
        m_camThread->stop();
}

bool CCamCtrlEml::receiveImages()
{
    bool res = m_camThread->isActive();
    qDebug( "%s = CCamCtrl::receiveImages()", res ? "true" : "false" );
	return res;
}

::std::string CCamCtrlEml::deviceName()
{
    ::std::string stri = "/dev/video0";
    qDebug( "%s = CCamCtrl::deviceName()", stri.data() );
	return stri;
}

void CCamCtrlEml::setPeriod(::Ice::Double value)
{
    qDebug( "CCamCtrl::setPeriod( %4.3f )", value );
    m_camThread->setInterval( static_cast<int>( value * 1000.0 ) );
}

void CCamCtrlEml::setDeviceName(const ::std::string& stri)
{
    qDebug( "CCamCtrl::setDeviceName( %s )", stri.data() );
}

bool CCamCtrlEml::open()
{
    m_open = true;
    qDebug( "%s = CCamCtrl::open()", m_open ? "true" : "false" );
	return m_open;
}

void CCamCtrlEml::close()
{
    qDebug( "CCamCtrl::close()" );
	m_open = false;
}

void CCamCtrlEml::postImage()
{
    QMutexLocker lock( &m_mut );
    if ( ( m_owner->m_host->clientCnt() > 0 ) && ( m_files.size() > 0 ) )
    {
        int & ind = m_fileIndex;
        QStringList & l = m_files;
        QByteArray & ia = m_imgArray;
        ::Types::TByteArray & ba = m_byteArray;

        QString fileName = l.at( ind++ );
        ind %= l.size();
        m_img.load( fileName, "PNG" );

        m_imgArray.clear();
        QBuffer b( &ia );
        b.open( QIODevice::WriteOnly );
        m_img.save( &b, "PNG" );
        b.close();

        ba.clear();
        ba.reserve( ia.size() );
        Ice::Byte * orig = reinterpret_cast<Ice::Byte *>( ia.data() );;
        for ( int i=0; i<ia.size(); i++ )
            ba.push_back( orig[i] );

        m_owner->m_host->postImage( ba );
    }
}



