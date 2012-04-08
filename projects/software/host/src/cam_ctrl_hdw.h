
#ifndef __CAM_CTRL_HDW_H_
#define __CAM_CTRL_HDW_H_

#include "cam_ctrl.h"
#include "hdw.h"
#include "dec.h"
#include <QtGui>
class CCamThreadHdw;

class CCamCtrlHdw: public CCamCtrl
{
public:
    CCamCtrlHdw( CHostIceThread * owner, Hdw::CHdwPrx hdwPrx );
	~CCamCtrlHdw();

    bool isOpen();
    void setResolution( ::Ice::Int & width, ::Ice::Int & height );
	void resolution( ::Ice::Int & width, ::Ice::Int & height );
    ::Ice::Double period();
    bool image( ::Types::TByteArray & data );
    void setReceiveImages(bool en);
    bool receiveImages();
    ::std::string deviceName();
    void setPeriod(::Ice::Double value);
    void setDeviceName(const ::std::string& stri);
    bool open();
    void close();
protected:
    bool acquireImage();
    void postImage();
    void caps();
    void debug();

    unsigned long       m_fourcc;
    ::Ice::Int          m_width, 
                        m_height, 
                        m_rawSz;
    ::Types::TByteArray m_raw;
    QImage              m_img;
    ::Types::TByteArray m_sendArray;
    CDec m_dec;
    QMutex m_mut;

    Hdw::CCamPrx    m_camPrx;
    std::string     m_deviceName;

	CCamThreadHdw * m_camThread;
    friend class CCamThreadHdw;

    bool m_inProgress;
};

#endif

