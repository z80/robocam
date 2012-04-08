
#include "moto.h"
#include "main_wnd.h"

CMoto::CMoto( CMainWnd * mainWnd )
: QWidget( mainWnd ), 
  m_mainWnd( mainWnd )
{
    ui.setupUi( this );
    ui.servo->setBackgroundColor1( QColor( qRgb( 0xff, 0xcc, 0x19 ) ) );
    ui.servo->setBackgroundColor2( QColor( qRgb( 0xac, 0x86, 0x00 ) ) );
    ui.servo->setEffectColor( QColor( qRgb( 0x39, 0xba, 0x00 ) ) );
    QObject::connect( ui.left,     SIGNAL(pressed()),            this, SLOT(slotMoto()) );
    QObject::connect( ui.left,     SIGNAL(released()),           this, SLOT(slotMoto()) );
    QObject::connect( ui.right,    SIGNAL(pressed()),            this, SLOT(slotMoto()) );
    QObject::connect( ui.right,    SIGNAL(released()),           this, SLOT(slotMoto()) );
    QObject::connect( ui.fwd,      SIGNAL(pressed()),            this, SLOT(slotMoto()) );
    QObject::connect( ui.fwd,      SIGNAL(released()),           this, SLOT(slotMoto()) );
    QObject::connect( ui.bwd,      SIGNAL(pressed()),            this, SLOT(slotMoto()) );
    QObject::connect( ui.bwd,      SIGNAL(released()),           this, SLOT(slotMoto()) );
    QObject::connect( ui.servo,    SIGNAL(valueChanged(QPointF, bool)), 
                      this,        SLOT(slotServoChanged(QPointF, bool)) );
    QObject::connect( ui.open,     SIGNAL(clicked()),            this, SLOT(slotOpen()) );
    QObject::connect( ui.motoEn,   SIGNAL(clicked()),            this, SLOT(slotMotoEn()) );
    QObject::connect( ui.servoEn,  SIGNAL(clicked()),            this, SLOT(slotServoEn()) );
}

CMoto::~CMoto()
{
}

void CMoto::setCtrlEnabled( bool en )
{
    ui.left->setEnabled( en );
    ui.right->setEnabled( en );
    ui.fwd->setEnabled( en );
    ui.bwd->setEnabled( en );
    ui.servo->setEnabled( en );
}

void CMoto::setSuperEnabled( bool en )
{
    setCtrlEnabled( en );
    ui.open->setEnabled( en );
    ui.motoEn->setEnabled( en );
    ui.servoEn->setEnabled( en );
}

void CMoto::keyPressEvent( QKeyEvent * e )
{
    switch( e->key() )
    {
    case Qt::Key_Up:
    case Qt::Key_W:
        ui.fwd->setDown( true );
        slotMoto();
        break;
    case Qt::Key_Down:
    case Qt::Key_S:
        ui.bwd->setDown( true );
        slotMoto();
        break;
    case Qt::Key_Left:
    case Qt::Key_A:
        ui.left->setDown( true );
        slotMoto();
        break;
    case Qt::Key_Right:
    case Qt::Key_D:
        ui.right->setDown( true );
        slotMoto();
        break;
    }
}

void CMoto::keyReleaseEvent( QKeyEvent * e )
{
    switch( e->key() )
    {
    case Qt::Key_Up:
    case Qt::Key_W:
        ui.fwd->setDown( false );
        slotMoto();
        break;
    case Qt::Key_Down:
    case Qt::Key_S:
        ui.bwd->setDown( false );
        slotMoto();
        break;
    case Qt::Key_Left:
    case Qt::Key_A:
        ui.left->setDown( false );
        slotMoto();
        break;
    case Qt::Key_Right:
    case Qt::Key_D:
        ui.right->setDown( false );
        slotMoto();
        break;
    }
}

void CMoto::slotMoto()
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
        dir1 = 1;
        dir2 = -1;
    }
    else if ( ui.right->isDown() )
    {
        dir1 = -1;
        dir2 = 1;
    }
    else
    {
        dir1 = dir2 = 0;
    }

    m_mainWnd->client()->moto()->setMoto( dir1, dir2, 30.0 );
    qDebug( "moto( %i, %i )", dir1, dir2 );
}

void CMoto::slotServoChanged( QPointF newValue, bool mouseDown )
{
    double servo1 = static_cast<double>( newValue.x() ) * 45.0 * 2.0;
    double servo2 = static_cast<double>( newValue.y() ) * 45.0 * 2.0;
    m_mainWnd->client()->moto()->setServo( servo1, servo2 );
    qDebug( "moto( %2.1f, %2.1f )", servo1, servo2 );
}

void CMoto::slotOpen()
{
    m_mainWnd->client()->moto()->close();
    if ( ui.open->isChecked() )
    {
        bool res = m_mainWnd->client()->moto()->open();
        if ( !res )
        {
            ui.open->setChecked( false );
            qDebug( "open() res is false" );
        }
    }
    qDebug( "open() res is %s", m_mainWnd->client()->moto()->isOpen() ? "true" : "false" );
}

void CMoto::slotMotoEn()
{
    bool en = ui.motoEn->isChecked();
    m_mainWnd->client()->moto()->setMotoEn( en );
    qDebug( "setMotoEn( %s )", en ? "true" : "false" );
}

void CMoto::slotServoEn()
{
    bool en = ui.servoEn->isChecked();
    m_mainWnd->client()->moto()->setServoEn( en );
    qDebug( "setServoEn( %s )", en ? "true" : "false" );
}




