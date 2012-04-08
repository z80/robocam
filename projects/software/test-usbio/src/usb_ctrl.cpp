
#include "usb_ctrl.h"
#include "motors_ctrl.h"

CUsbCtrl::CUsbCtrl( QWidget * parent )
{
    ui.setupUi( this );
    io = new CMotorsCtrl( this );

    ui.servo1->setEnabled( false );
    ui.servo2->setEnabled( false );

    connect( ui.open,    SIGNAL(clicked()),      this, SLOT(open()) );
    connect( ui.motoEn,  SIGNAL(clicked()),   this, SLOT(motoEnChanged()) );
    connect( ui.servoEn, SIGNAL(clicked()),      this, SLOT(servoEnChanged()) );
    connect( ui.dir1,    SIGNAL(valueChanged(int)), this, SLOT(motoChanged()) );
    connect( ui.dir2,    SIGNAL(valueChanged(int)), this, SLOT(motoChanged()) );
    connect( ui.servo1,  SIGNAL(valueChanged(int)), this, SLOT(servoChanged()) );
    connect( ui.servo2,  SIGNAL(valueChanged(int)), this, SLOT(servoChanged()) );
}

CUsbCtrl::~CUsbCtrl()
{
    if ( io )
        io->deleteLater();
}

void CUsbCtrl::open()
{
    if ( io->isOpened() )
        io->close();
    if ( ui.open->isChecked() )
        io->open();
    ui.open->setChecked( io->isOpened() );
    log( QString( "%1 = isOpened()" ).arg( (io->isOpened()) ? "true" : "false" ) );
}

void CUsbCtrl::motoEnChanged()
{
    io->setMotoEn( ui.motoEn->isChecked() );
    log( QString( "setMotoEn( %1 )" ).arg( ui.motoEn->isChecked() ? "true" : "false" ) );
}

void CUsbCtrl::servoEnChanged()
{
    if ( !ui.servoEn->isChecked() )
        io->setServo( 0, 0 );
    ui.servo1->setEnabled( ui.servoEn->isChecked() );
    ui.servo2->setEnabled( ui.servoEn->isChecked() );
    io->setServoEn( ui.servoEn->isChecked() );
    log( QString( "setServoEn( %1 )" ).arg( ui.servoEn->isChecked() ? "true" : "false" ) );
}

void CUsbCtrl::motoChanged()
{
    io->setMoto( ui.dir1->value(), ui.dir2->value() );
    log( QString( "setMoto( %1, %2 )" ).arg( ui.dir1->value() ).arg( ui.dir2->value() ) );
}

void CUsbCtrl::servoChanged()
{
    io->setServo( ui.servo1->value(), ui.servo2->value() );
    log( QString( "setServo( %1, %2 )" ).arg( ui.servo1->value() ).arg( ui.servo2->value() ) );
}

void CUsbCtrl::log( const QString & stri )
{
    ui.log->append( stri );
    out();
}

void CUsbCtrl::out()
{
    ui.output->append( io->lastCmd() );
}
