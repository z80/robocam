
#ifndef __USB_IO_H_
#define __USB_IO_H_

#include <string>

class CUsbIo
{
public:
    CUsbIo();
    virtual ~CUsbIo();
    bool open();
    void close();
    bool isOpen() const;

    std::string lastCmd();
protected:
    static const int VENDOR_ID;
    static const int PRODUCT_ID;
    static const int TIMEOUT;
    class PD;
    PD * pd;
    int io( const std::string & send, std::string & receive );
};

#endif



