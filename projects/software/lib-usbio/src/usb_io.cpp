

#include "usb_io.h"
extern "C"
{
    #ifdef WIN32
        #include <lusb0_usb.h>
    #else
        #include <usb.h>
    #endif
    #include "opendevice.h"
}

const int CUsbIo::VENDOR_ID  = 0x16C0;
const int CUsbIo::PRODUCT_ID = 0x05DC;
const int CUsbIo::TIMEOUT    = 1000;

class CUsbIo::PD
{
public:
    PD() {}
    ~PD() {}
    usb_dev_handle  * handle;
    std::string err;
    std::string res;
    std::string output;
};

CUsbIo::CUsbIo()
{
    pd = new PD();
    pd->handle = 0;
    usb_init();
    pd->res.resize( 8 );
}

CUsbIo::~CUsbIo()
{
    delete pd;
}

bool CUsbIo::open()
{
    int res = usbOpenDevice( &(pd->handle),
                             VENDOR_ID, NULL,
                             PRODUCT_ID, NULL,
                             NULL, NULL, NULL );
    return (res == 0);
}

void CUsbIo::close()
{
    if ( isOpen() )
    {
        usb_close( pd->handle );
        pd->handle = 0;
    }
}

bool CUsbIo::isOpen() const
{
    return (pd->handle != 0);
}

int CUsbIo::io( const std::string & send, std::string & receive )
{
    if ( isOpen() )
    {
        int totalCnt = 0;
        pd->output.clear();
        receive.clear();
        receive.reserve( send.size() );
        std::string s = send;
        s.push_back( '\0' );
        for ( unsigned i=0; i<s.size(); i++ )
        {
            int cnt = usb_control_msg( pd->handle,
                                       USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_IN,
                                       s[i], 
                                       0, 0, 
                                       const_cast<char *>( pd->res.data() ), pd->res.size(),
                                       TIMEOUT );
            if ( cnt < 0 )
            {
                pd->err = usb_strerror();
                close();
                open();
                return -1;
            }
            else
            {
                for ( int j=0; j<cnt; j++ )
                {
                    receive.push_back( pd->res[j] );
                    pd->output.push_back( pd->res[j] );
                }
                totalCnt += cnt;
            }
        }
        return totalCnt;
    }
    else
        return -1;
}

std::string CUsbIo::lastCmd()
{
    std::string res = pd->output;
    pd->output.clear();
    return res;
}


