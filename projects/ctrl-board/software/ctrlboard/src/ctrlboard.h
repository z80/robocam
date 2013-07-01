
#ifndef __CTRLBOARD_H_
#define __CTRLBOARD_H_

class CtrlBoard
{
public:
    CtrlBoard();
    virtual ~CtrlBoard();

    bool open();
    bool isOpen();
    void close();
    bool write( unsigned char addr, const unsigned char * data, int cnt );
    bool read( unsigned char addr, unsigned char * data, int cnt );

private:
    class PD;
    PD * pd;
};


#endif




