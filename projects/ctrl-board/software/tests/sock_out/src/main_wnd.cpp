
#include "main_wnd.h"

MainWnd::MainWnd( QWidget * parent )
: QWidget( parent )
{
    ui.setupUi( this );

    peer = new QXmppPeer( this );
    peer->connect( "out@xmpp", "12345", "localhost" );

    video = new QXmppVideo( peer );
    video->setTarget( "in@xmpp" );

    connect( ui.callBtn, SIGNAL(clicked()), this, SLOT(slotCall()) );
    connect( ui.endCallBtn, SIGNAL(clicked()), this, SLOT(slotEndCall()) );
    connect( video, SIGNAL(frameReady()), this, SLOT(slotFrameReady()) );
}

MainWnd::~MainWnd()
{
}

void MainWnd::slotCall()
{
    video->invokeCall();
}

void MainWnd::slotEndCall()
{
    video->invokeEndCall();
}

void MainWnd::slotFrameReady()
{
    QImage img;
    video->frame( img );

    ui.image->setPixmap( QPixmap::fromImage( img ) );
}





