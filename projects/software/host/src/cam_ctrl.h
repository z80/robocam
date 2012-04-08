
#ifndef __CAM_CTRL_H_
#define __CAM_CTRL_H_

#include "host.h"
class CHostIceThread;

class CCamCtrl
{
public:
    CCamCtrl( CHostIceThread * owner );
	virtual ~CCamCtrl();

    virtual bool isOpen() = 0;
    virtual void setResolution( ::Ice::Int & width, ::Ice::Int & height ) = 0;
	virtual void resolution( ::Ice::Int & width, ::Ice::Int & height ) = 0;
    virtual ::Ice::Double period() = 0;
    virtual bool image( ::Types::TByteArray & data ) = 0;
    virtual void setReceiveImages(bool en) = 0;
    virtual bool receiveImages() = 0;
    virtual ::std::string deviceName() = 0;
    virtual void setPeriod(::Ice::Double value) = 0;
    virtual void setDeviceName(const ::std::string& stri) = 0;
    virtual bool open() = 0;
    virtual void close() = 0;
protected:
    CHostIceThread * m_owner;
    friend class CCamCtrlHdw;
    friend class CCamCtrlEml;
};

#endif

