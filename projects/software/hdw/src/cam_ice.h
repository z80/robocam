
#ifndef __CAM_ICE_H_
#define __CAM_ICE_H_

#include "hdw.h"
#include <queue>
#include <vector>

class CCamCtrl;

class CCamIce: public Hdw::CCam
{
public:
    CCamIce( CCamCtrl * camCtrl );
    ~CCamIce();
    void setDeviceName(const ::std::string&, const ::Ice::Current& = ::Ice::Current());
    bool open(const ::Ice::Current& = ::Ice::Current());
    bool isOpen(const ::Ice::Current& = ::Ice::Current());
    void close(const ::Ice::Current& = ::Ice::Current());
    bool capabilities( ::Types::TStringArray & cap, 
                       ::Types::TBoolArray & en, 
                       ::Types::TStringArray & info, 
                       const ::Ice::Current& = ::Ice::Current() );
    bool formats( ::Types::TStringArray & fmt, ::Types::TLongArray & fourcc, const ::Ice::Current& = ::Ice::Current());
    ::Types::TIntArray resolutions(const ::Ice::Current& = ::Ice::Current());
    bool initDevice( bool streaming, 
                     ::Ice::Long fourcc, 
                     ::Ice::Int w, ::Ice::Int h, 
                     ::Ice::Int fps, 
                     const ::Ice::Current& = ::Ice::Current());
    void imageSize(::Ice::Int&, ::Ice::Int&, ::Ice::Int&, const ::Ice::Current& = ::Ice::Current());
    bool startCapture(const ::Ice::Current& = ::Ice::Current());
    void stopCapture(const ::Ice::Current& = ::Ice::Current());
    bool started(const ::Ice::Current& = ::Ice::Current());
    bool acquire(const ::Ice::Current& = ::Ice::Current());
    bool release(const ::Ice::Current& = ::Ice::Current());
    void data(::Ice::Int, ::Ice::Int, ::Types::TByteArray&, const ::Ice::Current& = ::Ice::Current());
    ::std::string lastError(const ::Ice::Current& = ::Ice::Current());
private:
    CCamCtrl * m_camCtrl;
};


#endif


