
#include "camera_ctrl.h"
#include "client_ice.h"

class CCameraCtrl::PD
{
public:
    PD() {}
    ~PD() {}

    IceUtil::Handle<CClientIce> rpc;
    // Параметры соединения.
    std::string serverInfo;
};


CCameraCtrl::CCameraCtrl( QObject * parent )
: QObject( parent )
{
    pd = new PD();
}

CCameraCtrl::~CCameraCtrl()
{
    if ( pd->rpc )
    {
        bool started = pd->rpc->isAlive();
        if ( started )
        {
            pd->rpc->m_semaphore.lock();
            pd->rpc->shutdown();
            pd->rpc->m_semaphore.wait();
            pd->rpc->m_semaphore.unlock();
        }
    }
    delete pd;
}

bool CCameraCtrl::connect( const std::string & host )
{
    pd->rpc = new CClientIce( this );
    pd->rpc->m_server = host;
    pd->rpc->m_semaphore.lock();
    pd->rpc->start();
    pd->rpc->m_semaphore.wait();
    pd->rpc->m_semaphore.unlock();
    if ( pd->rpc->status() == "connected" )
        return true;
    return false;
}

void CCameraCtrl::shutdown()
{
    if ( pd->rpc )
    {
        pd->rpc->m_semaphore.lock();
        pd->rpc->shutdown();
        pd->rpc->m_semaphore.wait();
        pd->rpc->m_semaphore.unlock();
    }
}

std::string CCameraCtrl::status()
{
    if ( ( pd->rpc ) )
        return pd->rpc->status();
    return std::string();
}

void CCameraCtrl::setDeviceName( const std::string & stri )
{
    if ( ( pd->rpc ) && ( pd->rpc->m_camera ) )
        pd->rpc->m_camera->setDeviceName( stri );
}

bool CCameraCtrl::open()
{
    if ( ( pd->rpc ) && ( pd->rpc->m_camera ) )
        return pd->rpc->m_camera->open();
    return false;
}

void CCameraCtrl::close()
{
    if ( ( pd->rpc ) && ( pd->rpc->m_camera ) )
        pd->rpc->m_camera->close();
}

bool CCameraCtrl::isOpened()
{
    if ( ( pd->rpc ) && ( pd->rpc->m_camera ) )
        return pd->rpc->m_camera->isOpened();
    return false;
}

bool CCameraCtrl::initDevice( const std::string & format, int width, int height )
{
    if ( ( pd->rpc ) && ( pd->rpc->m_camera ) )
        return pd->rpc->m_camera->initDevice( format, width, height );
    return false;
}

void CCameraCtrl::imageSize( int & width, int & height, int & sz )
{
    if ( ( pd->rpc ) && ( pd->rpc->m_camera ) )
        pd->rpc->m_camera->imageSize( width, height, sz );
    else
    {
        width  = -1;
        height = -1;
        sz     = -1;
    }
}

bool CCameraCtrl::startCapture()
{
    if ( ( pd->rpc ) && ( pd->rpc->m_camera ) )
        return pd->rpc->m_camera->startCapture();
    return false;
 }

void CCameraCtrl::stopCapture()
{
    if ( ( pd->rpc ) && ( pd->rpc->m_camera ) )
        pd->rpc->m_camera->stopCapture();
}

bool CCameraCtrl::started()
{
    if ( ( pd->rpc ) && ( pd->rpc->m_camera ) )
        return pd->rpc->m_camera->started();
    return false;
}

bool CCameraCtrl::acquire()
{
    if ( ( pd->rpc ) && ( pd->rpc->m_camera ) )
        return pd->rpc->m_camera->acquire();
    return false;
}

void CCameraCtrl::data( int from, int sz, std::vector<unsigned char> & res )
{
    if ( ( pd->rpc ) && ( pd->rpc->m_camera ) )
        pd->rpc->m_camera->data( from, sz, res );
}

std::string CCameraCtrl::lastError()
{
    if ( ( pd->rpc ) && ( pd->rpc->m_camera ) )
        return pd->rpc->m_camera->lastError();
    return std::string();
}

void CCameraCtrl::decodeYuyv( int w, int h, const std::vector<unsigned char> & yuyv, std::vector<unsigned char> & data )
{
    data.resize( w * h * 3 );
    int z = 0;
    int ind = 0;
    int indOut = 0;
    for ( int y=0; y<h; y++ )
    {
        for ( int x=0; x<w; x++ )
        {
            int y = ( z==0 ) ? (static_cast<int>(yuyv[ind]) << 8) :
                               (static_cast<int>(yuyv[ind+2]) << 8);
            int u = static_cast<int>(yuyv[ind+1]) - 128;
            int v = static_cast<int>(yuyv[ind+3]) - 128;
            int r = (y + (359 * v)) >> 8;
            int g = (y - (88  * u) - (183 * v)) >> 8;
            int b = (y + (454 * u)) >> 8;
            data[ indOut++ ] = static_cast<unsigned char>( r );
            data[ indOut++ ] = static_cast<unsigned char>( g );
            data[ indOut++ ] = static_cast<unsigned char>( b );
            if (z++)
            {
                z = 0;
                ind += 4;
            }
        }
    }


/*	ptr = (uint8_t *) src->img;
	z = 0;

	for(y = 0; y < src->height; y++)
	{
		for(x = 0; x < src->width; x++)
		{
			int r, g, b;
			int y, u, v;

			if(src->palette == SRC_PAL_UYVY)
			{
				if(!z) y = ptr[1] << 8;
				else   y = ptr[3] << 8;

				u = ptr[0] - 128;
				v = ptr[2] - 128;
			}
			else // SRC_PAL_YUYV
			{
				if(!z) y = ptr[0] << 8;
				else   y = ptr[2] << 8;

				u = ptr[1] - 128;
				v = ptr[3] - 128;
			}

			r = (y + (359 * v)) >> 8;
			g = (y - (88 * u) - (183 * v)) >> 8;
			b = (y + (454 * u)) >> 8;

			*(abitmap++) += CLIP(r, 0x00, 0xFF);
			*(abitmap++) += CLIP(g, 0x00, 0xFF);
			*(abitmap++) += CLIP(b, 0x00, 0xFF);

			if(z++)
			{
				z = 0;
				ptr += 4;
			}
		}
	}
*/
}







