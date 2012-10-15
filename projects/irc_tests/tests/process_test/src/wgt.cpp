
#include "wgt.h"

#include "lua.hpp"
#include <boost/bind.hpp>
#include <boost/bind/placeholders.hpp>

Wgt::Wgt( QWidget * parent )
: QWidget( parent )
{
    ui.setupUi( this );
    connect( ui.runBtn, SIGNAL(clicked()), this, SLOT(slotRun()) );

    ps = new QProcess( this );
    //ps = new FswProcess();
    //ps->setCommand( "fswebcam -d /dev/video0 -q --png 9 --no-banner image2.png" );
}

Wgt::~Wgt()
{
}

void Wgt::slotRun()
{
    ps->start( "fswebcam", QStringList() << "-d" << "/dev/video0" << "--no-banner" << "-q" << "--png" << "9" << "image.png" );
	//ps->start();
}




