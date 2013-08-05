
#include "pipe_setup.h"

PipeSetup::PipeSetup( QWidget * p )
    : QDialog( p )
{
    ui.setupUi( this );
}

PipeSetup::~PipeSetup()
{
}

void PipeSetup::setPipe( int localPort, int remotePort, const QString & remoteHost )
{
    ui.localPort->setValue( localPort );
    ui.remotePort->setValue( remotePort );
    ui.remoteHost->setText( remoteHost );
}

void PipeSetup::pipe( int & localPort, int & remotePort, QString & remoteHost ) const
{
    localPort  = ui.localPort->value();
    remotePort = ui.remotePort->value();
    remoteHost = ui.remoteHost->text();
}




