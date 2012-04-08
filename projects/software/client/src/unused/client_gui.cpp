
#include "client_gui.h"
#include "passwd_dlg.h"
#include <QPaintEvent>
#include <vector>

#include <boost/bind.hpp>
#include <boost/bind/arg.hpp>
#include <boost/bind/placeholders.hpp>

const QString CClientGui::g_iniFileName = "client.ini";

CClientGui::CClientGui( QWidget * parent )
: QWidget( parent )
{
    m_host = "host_ice: default -p 26001";
    ui.setupUi( this );
    loadSettings();
    setMotoSuperEnabled( false );
    setCamSuperEnabled( false );
    setChatEnabled( false );

    QObject::connect( ui.connect, SIGNAL(clicked()),       this, SLOT(slotConnect()) );
    QObject::connect( ui.message, SIGNAL(returnPressed()), this, SLOT(slotSend()) );
    QObject::connect( ui.send,    SIGNAL(clicked()),       this, SLOT(slotSend()) );

    QObject::connect( this,        SIGNAL(sigAcceptMessageCb()), this, SLOT(slotAcceptMessageCb()) );
    QObject::connect( this,        SIGNAL(sigAcceptClientListCb()), this, SLOT(slotAcceptClientListCb()) );
    QObject::connect( this,        SIGNAL(sigMotoEnCb()),        this, SLOT(slotMotoEnCb()) );
    QObject::connect( this,        SIGNAL(sigMotoCb()),          this, SLOT(slotMotoCb()) );
    QObject::connect( this,        SIGNAL(sigServoEnCb()),       this, SLOT(slotServoEnCb()) );
    QObject::connect( this,        SIGNAL(sigServoCb()),         this, SLOT(slotServoCb()) );
    QObject::connect( this,        SIGNAL(sigAcceptImageCb()),   this, SLOT(slotAcceptImageCb()) );

    QObject::connect( ui.motoEn,   SIGNAL(clicked()),            this, SLOT(slotMotoEn()) );
    QObject::connect( ui.servoEn,  SIGNAL(clicked()),            this, SLOT(slotServoEn()) );
    QObject::connect( ui.left,     SIGNAL(pressed()),            this, SLOT(slotMoto()) );
    QObject::connect( ui.left,     SIGNAL(released()),           this, SLOT(slotMoto()) );
    QObject::connect( ui.right,    SIGNAL(pressed()),            this, SLOT(slotMoto()) );
    QObject::connect( ui.right,    SIGNAL(released()),           this, SLOT(slotMoto()) );
    QObject::connect( ui.fwd,      SIGNAL(pressed()),            this, SLOT(slotMoto()) );
    QObject::connect( ui.fwd,      SIGNAL(released()),           this, SLOT(slotMoto()) );
    QObject::connect( ui.bwd,      SIGNAL(pressed()),            this, SLOT(slotMoto()) );
    QObject::connect( ui.bwd,      SIGNAL(released()),           this, SLOT(slotMoto()) );
    QObject::connect( ui.servoSl1,   SIGNAL(valueChanged(int)),  this, SLOT(slotServo()) );
    QObject::connect( ui.servoSl2,   SIGNAL(valueChanged(int)),  this, SLOT(slotServo()) );
    QObject::connect( ui.queryCtrl,  SIGNAL(clicked()),          this, SLOT(slotQueryCtrl()) );
    QObject::connect( ui.querySuper, SIGNAL(clicked()),          this, SLOT(slotQuerySuper()) );
}

CClientGui::~CClientGui()
{
}

void CClientGui::closeEvent( QCloseEvent * e )
{
    saveSettings();
}

void CClientGui::slotConnect()
{
    if ( ui.connect->isChecked() )
        connect();
    else
        disconnect();
}

void CClientGui::slotMotoEn()
{
    m_client->m_motoPrx->setMotoEn( ui.motoEn->isChecked() );
}

void CClientGui::slotServoEn()
{
    m_client->m_motoPrx->setMotoEn( ui.servoEn->isChecked() );
}

void CClientGui::slotMoto()
{
    int dir1, dir2;
    if ( ui.fwd->isDown() )
    {
        dir1 = dir2 = 1;
        if ( ui.left->isChecked() )
            dir1 = 0;
        if ( ui.right->isChecked() )
            dir2 = 0;
    }
    else if ( ui.bwd->isDown() )
    {
        dir1 = dir2 = -1;
        if ( ui.left->isChecked() )
            dir1 = 0;
        if ( ui.right->isChecked() )
            dir2 = 0;
    }
    else if ( ui.left->isDown() )
    {
        dir1 = 0;
        dir2 = 1;
    }
    else if ( ui.right->isDown() )
    {
        dir1 = 1;
        dir2 = 0;
    }
    else
    {
        dir1 = dir2 = 0;
    }

    m_client->m_motoPrx->setMoto( dir1, dir2, 30.0 );
}

void CClientGui::slotServo()
{
    double servo1 = static_cast<double>( ui.servoSl1->value() );
    double servo2 = static_cast<double>( ui.servoSl2->value() );
    m_client->m_motoPrx->setServo( servo1, servo2 );
}

void CClientGui::slotQueryCtrl()
{
    if ( ui.queryCtrl->isChecked() )
    {
        ui.querySuper->setChecked( false );
        bool res = m_client->queryCtrl();
        if ( !res )
            ui.queryCtrl->setChecked( false );
        else
        {
            setMotoCtrlEnabled( true );
            setCamCtrlEnabled( true );
        }
    }
    else
    {
        setMotoCtrlEnabled( false );
        setCamCtrlEnabled( false );
        m_client->releaseCtrl();
    }
}

void CClientGui::slotQuerySuper()
{
    if ( ui.querySuper->isChecked() )
    {
        ui.queryCtrl->setChecked( false );
        CPasswdDlg dlg( this );
        if ( dlg.exec() == QDialog::Accepted )
        {
            std::string stri = dlg.passwd();
            bool res = false;
            try
            {
                if ( m_client.get() )
                    res = m_client->querySuper( stri );
            }
            catch ( ::Ice::Exception & exc )
            {
                setWindowTitle( QString::fromStdString( exc.toString() ) );
            }
            if ( !res )
                ui.querySuper->setChecked( false );
            else
            {
                setMotoSuperEnabled( true );
                setCamSuperEnabled( true );
            }

        }
    }
    else
    {
        setMotoSuperEnabled( false );
        setCamSuperEnabled( false );
        m_client->releaseCtrl();
    }
}

void CClientGui::slotSend()
{
    QString text = ui.message->text();
    ui.message->clear();
    m_client->m_hostPrx->postMessage( m_client->m_clientId, text.toStdString() );
}

void CClientGui::slotAcceptMessageCb()
{
    QMutexLocker lock( &m_mutex );
    ui.chat->append( QString::fromStdString( m_msg ) );
}

void CClientGui::slotAcceptClientListCb()
{
    QMutexLocker lock( &m_mutex );
    ui.clientList->clear();
    for ( unsigned i=0; i<m_clients.size(); i++ )
        ui.clientList->addItem( QString::fromStdString( m_clients.at( i ) ) );
    ui.driverNickname->setText( QString::fromStdString( m_driverNickname ) );
}

void CClientGui::slotMotoEnCb()
{
    QMutexLocker lock( &m_mutex );
    ui.motoEn->setChecked( m_en );
}

void CClientGui::slotMotoCb()
{
    QMutexLocker lock( &m_mutex );
    ui.dir1->setText( QString( "%1" ).arg( m_dir1 ) );
    ui.dir2->setText( QString( "%1" ).arg( m_dir2 ) );
}

void CClientGui::slotServoEnCb()
{
    QMutexLocker lock( &m_mutex );
    ui.servoEn->setChecked( m_en );
}

void CClientGui::slotServoCb()
{
    QMutexLocker lock( &m_mutex );
    ui.servo1->setText( QString( "%1" ).arg( m_servo1 ) );
    ui.servo2->setText( QString( "%1" ).arg( m_servo2 ) );
    ui.servoSl1->setValue( static_cast<int>( m_servo1 ) );
    ui.servoSl2->setValue( static_cast<int>( m_servo2 ) );
}

void CClientGui::slotAcceptImageCb()
{
    QMutexLocker lock( &m_mutex );
    m_imageBa.clear();
    m_imageBa.resize( m_imageData.size() );
    ::Ice::Byte * d = reinterpret_cast<::Ice::Byte *>( m_imageBa.data() );
    for ( unsigned i=0; i<m_imageData.size(); i++ )
        d[i] = m_imageData.at( i );
    QBuffer b( &m_imageBa );
    b.open( QIODevice::ReadOnly );
    m_image.load( &b, "PNG" );
    ui.image->setPixmap( QPixmap::fromImage( m_image ) );
}



void CClientGui::connect()
{
    setMotoSuperEnabled( false );
    setCamSuperEnabled( false );
    setChatEnabled( false );
    disconnect();

    m_client = new CClientIceThread( this, m_host.toStdString(), ui.userName->text().toStdString() );
    m_client->setAcceptMessageCb( boost::bind( &CClientGui::acceptMessageCb, this, _1 ) );
    m_client->setAcceptClientListCb( boost::bind( &CClientGui::acceptClientListCb, this, _1, _2 ) );
    m_client->setMotoEnCb( boost::bind( &CClientGui::motoEnCb,       this, _1 ) );
    m_client->setMotoCb( boost::bind( &CClientGui::motoCb,           this, _1, _2 ) );
    m_client->setServoEnCb( boost::bind( &CClientGui::servoEnCb,     this, _1 ) );
    m_client->setServoCb( boost::bind( &CClientGui::servoCb,         this, _1, _2 ) );
    m_client->setAcceptImageCb( boost::bind( &CClientGui::acceptImageCb, this, _1 ) );
    m_client->connect();
    if ( m_client->status() != "connected" )
    {
        disconnect();
        ui.connect->setChecked( false );
        ui.connect->setText( "Connect" );
    }
    else
    {
    	ui.connect->setText( "Disconnect" );
        bool res = m_client->queryView();
        setChatEnabled( res );
    }
}

void CClientGui::disconnect()
{
    saveSettings();
    if ( m_client )
        m_client->shutdown();
}

void CClientGui::loadSettings()
{
    QSettings set( g_iniFileName,  QSettings::IniFormat, this );
    m_host = set.value( "host", "tcp -p 26001 -h localhost" ).toString();
    ui.host->setText( m_host );
    QString login = set.value( "login", "Stupid one!" ).toString();
    ui.userName->setText( login );
}

void CClientGui::saveSettings()
{
    QSettings set( g_iniFileName,  QSettings::IniFormat, this );
    m_host = ui.host->text();
    set.setValue( "host",  m_host );
    set.setValue( "login", ui.userName->text() );
}

void CClientGui::setMotoCtrlEnabled( bool en )
{
    ui.fwd->setEnabled( en );
    ui.bwd->setEnabled( en );
    ui.left->setEnabled( en );
    ui.right->setEnabled( en );
    ui.servoSl1->setEnabled( en );
    ui.servoSl2->setEnabled( en );
}

void CClientGui::setMotoSuperEnabled( bool en )
{
    setMotoCtrlEnabled( en );
    ui.motoEn->setEnabled( en );
    ui.servoEn->setEnabled( en );
}

void CClientGui::setCamCtrlEnabled( bool en )
{

}

void CClientGui::setCamSuperEnabled( bool en )
{

}

void CClientGui::setChatEnabled( bool en )
{
	ui.clientList->setEnabled( en );
	ui.chat->setEnabled( en );
	ui.message->setEnabled( en );
	ui.userName->setEnabled( !en );
	ui.send->setEnabled( en );
}

void CClientGui::acceptMessageCb( const std::string & stri )
{
    QMutexLocker lock( &m_mutex );
    m_msg = stri;
    emit sigAcceptMessageCb();
}

void CClientGui::acceptClientListCb( const std::vector<std::string> & clients, const std::string & driverNickname )
{
    QMutexLocker lock( &m_mutex );
    m_clients = clients;
    m_driverNickname = driverNickname;
    emit sigAcceptClientListCb();
}

void CClientGui::motoEnCb( bool en )
{
    QMutexLocker lock( &m_mutex );
    m_en = en;
    emit sigMotoEnCb();
}

void CClientGui::motoCb( int dir1, int dir2 )
{
    QMutexLocker lock( &m_mutex );
    m_dir1 = dir1;
    m_dir2 = dir2;
    emit sigMotoCb();
}

void CClientGui::servoEnCb( bool en )
{
    QMutexLocker lock( &m_mutex );
    m_en = en;
    emit sigServoEnCb();
}

void CClientGui::servoCb( double servo1, double servo2 )
{
    QMutexLocker lock( &m_mutex );
    m_servo1 = servo1;
    m_servo2 = servo2;
    emit sigServoCb();
}

void CClientGui::acceptImageCb( const ::Types::TByteArray & data )
{
    QMutexLocker lock( &m_mutex );
    m_imageData = data;
    emit sigAcceptImageCb();
}






