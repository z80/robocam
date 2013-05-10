
#include "ctrlboard.h"

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

class CtrlBoard::PD
{
public:
    PD() {}
    ~PD() {}

    int fd;
};

CtrlBoard::CtrlBoard()
{
    pd = new PD();
    pd->fd = -1;
}

CtrlBoard::~CtrlBoard()
{
    if ( isOpen() )
        close();
    delete pd;
}

bool CtrlBoard::open()
{
    const char fileName[] = "/dev/i2c-0";   // Name of the port we will be using
    pd->fd = ::open(fileName, O_RDWR);
    return ( pd->fd >= 0 );
}

bool CtrlBoard::isOpen()
{
    return ( pd->fd >= 0 );
}

void CtrlBoard::close()
{
    ::close( pd->fd );
    pd->fd = -1;
}

bool CtrlBoard::write( unsigned char addr, const unsigned char * data, int cnt )
{
    if ( ioctl( pd->fd, I2C_SLAVE, addr ) < 0 )
        return false;
    int sz = ::write( pd->fd, data, cnt );
    return ( sz == cnt );
}

bool CtrlBoard::read( unsigned char addr, unsigned char * data, int cnt )
{
    if ( ioctl( pd->fd, I2C_SLAVE, addr ) < 0 )
        return false;
    int sz = ::read( pd->fd, data, cnt );
    return ( sz == cnt );
}






