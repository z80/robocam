// **********************************************************************
//
// Copyright (c) 2003-2007 ZeroC, Inc. All rights reserved.
//
// This copy of Ice-E is licensed to you under the terms described in the
// ICEE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice-E version 1.3.0
// Generated from file `hdw.ice'

#ifndef __hdw_h__
#define __hdw_h__

#include <IceE/ProxyF.h>
#include <IceE/ObjectF.h>
#include <IceE/Exception.h>
#include <IceE/ScopedArray.h>
#include <IceE/Proxy.h>
#include <IceE/Object.h>
#ifndef ICEE_PURE_CLIENT
#  include <IceE/Incoming.h>
#endif
#include <IceE/Outgoing.h>
#include </home/z80/projects/pcb/chassis/projects/software/ice/unix/types.h>
#include <IceE/UndefSysMacros.h>

#ifndef ICEE_IGNORE_VERSION
#   if ICEE_INT_VERSION / 100 != 103
#       error IceE version mismatch!
#   endif
#   if ICEE_INT_VERSION % 100 < 0
#       error IceE patch level mismatch!
#   endif
#endif

namespace IceProxy
{

namespace Hdw
{

class CMoto;

class CCam;

class CLua;

class CHdw;

}

}

namespace Hdw
{

class CMoto;
bool operator==(const CMoto&, const CMoto&);
bool operator<(const CMoto&, const CMoto&);

class CCam;
bool operator==(const CCam&, const CCam&);
bool operator<(const CCam&, const CCam&);

class CLua;
bool operator==(const CLua&, const CLua&);
bool operator<(const CLua&, const CLua&);

class CHdw;
bool operator==(const CHdw&, const CHdw&);
bool operator<(const CHdw&, const CHdw&);

}

namespace IceInternal
{

::Ice::Object* upCast(::Hdw::CMoto*);
::IceProxy::Ice::Object* upCast(::IceProxy::Hdw::CMoto*);

::Ice::Object* upCast(::Hdw::CCam*);
::IceProxy::Ice::Object* upCast(::IceProxy::Hdw::CCam*);

::Ice::Object* upCast(::Hdw::CLua*);
::IceProxy::Ice::Object* upCast(::IceProxy::Hdw::CLua*);

::Ice::Object* upCast(::Hdw::CHdw*);
::IceProxy::Ice::Object* upCast(::IceProxy::Hdw::CHdw*);

}

namespace Hdw
{

typedef ::IceInternal::Handle< ::Hdw::CMoto> CMotoPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::Hdw::CMoto> CMotoPrx;

void __read(::IceInternal::BasicStream*, CMotoPrx&);
void __patch__CMotoPtr(void*, ::Ice::ObjectPtr&);

typedef ::IceInternal::Handle< ::Hdw::CCam> CCamPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::Hdw::CCam> CCamPrx;

void __read(::IceInternal::BasicStream*, CCamPrx&);
void __patch__CCamPtr(void*, ::Ice::ObjectPtr&);

typedef ::IceInternal::Handle< ::Hdw::CLua> CLuaPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::Hdw::CLua> CLuaPrx;

void __read(::IceInternal::BasicStream*, CLuaPrx&);
void __patch__CLuaPtr(void*, ::Ice::ObjectPtr&);

typedef ::IceInternal::Handle< ::Hdw::CHdw> CHdwPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::Hdw::CHdw> CHdwPrx;

void __read(::IceInternal::BasicStream*, CHdwPrx&);
void __patch__CHdwPtr(void*, ::Ice::ObjectPtr&);

}

namespace Hdw
{

}

namespace Hdw
{

class CMoto : virtual public ::Ice::Object
{
public:

    typedef CMotoPrx ProxyType;
    typedef CMotoPtr PointerType;
    
    CMoto() {}

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual bool open(const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___open(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual bool isOpen(const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___isOpen(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual void close(const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___close(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual void setMotoEn(bool, const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___setMotoEn(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual bool motoEn(const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___motoEn(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual void setMoto(::Ice::Int, ::Ice::Int, ::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___setMoto(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual void moto(::Ice::Int&, ::Ice::Int&, const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___moto(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual void setServoEn(bool, const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___setServoEn(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual bool servoEn(const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___servoEn(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual void setServo(::Ice::Int, ::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___setServo(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual void servo(::Ice::Int&, ::Ice::Int&, const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___servo(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual void setWatchdog(::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___setWatchdog(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual void resetWatchdog(const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___resetWatchdog(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
};

class CCam : virtual public ::Ice::Object
{
public:

    typedef CCamPrx ProxyType;
    typedef CCamPtr PointerType;
    
    CCam() {}

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual void setDeviceName(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___setDeviceName(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual bool open(const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___open(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual bool isOpen(const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___isOpen(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual void close(const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___close(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual bool capabilities(::Types::TStringArray&, ::Types::TBoolArray&, ::Types::TStringArray&, const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___capabilities(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual bool formats(::Types::TStringArray&, ::Types::TLongArray&, const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___formats(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual ::Types::TIntArray resolutions(const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___resolutions(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual bool initDevice(bool, ::Ice::Long, ::Ice::Int, ::Ice::Int, ::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___initDevice(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual void imageSize(::Ice::Int&, ::Ice::Int&, ::Ice::Int&, const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___imageSize(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual bool startCapture(const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___startCapture(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual void stopCapture(const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___stopCapture(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual bool started(const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___started(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual bool acquire(const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___acquire(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual bool release(const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___release(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual void data(::Ice::Int, ::Ice::Int, ::Types::TByteArray&, const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___data(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual ::std::string lastError(const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___lastError(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
};

class CLua : virtual public ::Ice::Object
{
public:

    typedef CLuaPrx ProxyType;
    typedef CLuaPtr PointerType;
    
    CLua() {}

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual bool exec(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___exec(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
};

class CHdw : virtual public ::Ice::Object
{
public:

    typedef CHdwPrx ProxyType;
    typedef CHdwPtr PointerType;
    
    CHdw() {}

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual ::Hdw::CMotoPrx moto(const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___moto(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual ::Hdw::CCamPrx cam(const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___cam(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
};

}

namespace IceProxy
{

namespace Hdw
{

class CMoto : virtual public ::IceProxy::Ice::Object
{
public:

    bool open()
    {
        return open(0);
    }
    bool open(const ::Ice::Context& __ctx)
    {
        return open(&__ctx);
    }
    
private:

    bool open(const ::Ice::Context*);
    
public:

    bool isOpen()
    {
        return isOpen(0);
    }
    bool isOpen(const ::Ice::Context& __ctx)
    {
        return isOpen(&__ctx);
    }
    
private:

    bool isOpen(const ::Ice::Context*);
    
public:

    void close()
    {
        close(0);
    }
    void close(const ::Ice::Context& __ctx)
    {
        close(&__ctx);
    }
    
private:

    void close(const ::Ice::Context*);
    
public:

    void setMotoEn(bool en)
    {
        setMotoEn(en, 0);
    }
    void setMotoEn(bool en, const ::Ice::Context& __ctx)
    {
        setMotoEn(en, &__ctx);
    }
    
private:

    void setMotoEn(bool, const ::Ice::Context*);
    
public:

    bool motoEn()
    {
        return motoEn(0);
    }
    bool motoEn(const ::Ice::Context& __ctx)
    {
        return motoEn(&__ctx);
    }
    
private:

    bool motoEn(const ::Ice::Context*);
    
public:

    void setMoto(::Ice::Int dir1, ::Ice::Int dir2, ::Ice::Int period)
    {
        setMoto(dir1, dir2, period, 0);
    }
    void setMoto(::Ice::Int dir1, ::Ice::Int dir2, ::Ice::Int period, const ::Ice::Context& __ctx)
    {
        setMoto(dir1, dir2, period, &__ctx);
    }
    
private:

    void setMoto(::Ice::Int, ::Ice::Int, ::Ice::Int, const ::Ice::Context*);
    
public:

    void moto(::Ice::Int& dir1, ::Ice::Int& dir2)
    {
        moto(dir1, dir2, 0);
    }
    void moto(::Ice::Int& dir1, ::Ice::Int& dir2, const ::Ice::Context& __ctx)
    {
        moto(dir1, dir2, &__ctx);
    }
    
private:

    void moto(::Ice::Int&, ::Ice::Int&, const ::Ice::Context*);
    
public:

    void setServoEn(bool en)
    {
        setServoEn(en, 0);
    }
    void setServoEn(bool en, const ::Ice::Context& __ctx)
    {
        setServoEn(en, &__ctx);
    }
    
private:

    void setServoEn(bool, const ::Ice::Context*);
    
public:

    bool servoEn()
    {
        return servoEn(0);
    }
    bool servoEn(const ::Ice::Context& __ctx)
    {
        return servoEn(&__ctx);
    }
    
private:

    bool servoEn(const ::Ice::Context*);
    
public:

    void setServo(::Ice::Int servo1, ::Ice::Int servo2)
    {
        setServo(servo1, servo2, 0);
    }
    void setServo(::Ice::Int servo1, ::Ice::Int servo2, const ::Ice::Context& __ctx)
    {
        setServo(servo1, servo2, &__ctx);
    }
    
private:

    void setServo(::Ice::Int, ::Ice::Int, const ::Ice::Context*);
    
public:

    void servo(::Ice::Int& servo1, ::Ice::Int& servo2)
    {
        servo(servo1, servo2, 0);
    }
    void servo(::Ice::Int& servo1, ::Ice::Int& servo2, const ::Ice::Context& __ctx)
    {
        servo(servo1, servo2, &__ctx);
    }
    
private:

    void servo(::Ice::Int&, ::Ice::Int&, const ::Ice::Context*);
    
public:

    void setWatchdog(::Ice::Int period)
    {
        setWatchdog(period, 0);
    }
    void setWatchdog(::Ice::Int period, const ::Ice::Context& __ctx)
    {
        setWatchdog(period, &__ctx);
    }
    
private:

    void setWatchdog(::Ice::Int, const ::Ice::Context*);
    
public:

    void resetWatchdog()
    {
        resetWatchdog(0);
    }
    void resetWatchdog(const ::Ice::Context& __ctx)
    {
        resetWatchdog(&__ctx);
    }
    
private:

    void resetWatchdog(const ::Ice::Context*);
    
public:
    
    ::IceInternal::ProxyHandle<CMoto> ice_context(const ::Ice::Context& __context) const
    {
        return dynamic_cast<CMoto*>(::IceProxy::Ice::Object::ice_context(__context).get());
    }
    
    ::IceInternal::ProxyHandle<CMoto> ice_secure(bool __secure) const
    {
        return dynamic_cast<CMoto*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    }
    
#ifdef ICEE_HAS_ROUTER
    ::IceInternal::ProxyHandle<CMoto> ice_router(const ::Ice::RouterPrx& __router) const
    {
        return dynamic_cast<CMoto*>(::IceProxy::Ice::Object::ice_router(__router).get());
    }
#endif // ICEE_HAS_ROUTER
    
#ifdef ICEE_HAS_LOCATOR
    ::IceInternal::ProxyHandle<CMoto> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
        return dynamic_cast<CMoto*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    }
    
    ::IceInternal::ProxyHandle<CMoto> ice_adapterId(const std::string& __id) const
    {
        return dynamic_cast<CMoto*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    }
#endif // ICEE_HAS_LOCATOR
    
    ::IceInternal::ProxyHandle<CMoto> ice_twoway() const
    {
        return dynamic_cast<CMoto*>(::IceProxy::Ice::Object::ice_twoway().get());
    }
    
    ::IceInternal::ProxyHandle<CMoto> ice_oneway() const
    {
        return dynamic_cast<CMoto*>(::IceProxy::Ice::Object::ice_oneway().get());
    }
    
    ::IceInternal::ProxyHandle<CMoto> ice_batchOneway() const
    {
        return dynamic_cast<CMoto*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    }
    
    ::IceInternal::ProxyHandle<CMoto> ice_datagram() const
    {
        return dynamic_cast<CMoto*>(::IceProxy::Ice::Object::ice_datagram().get());
    }
    
    ::IceInternal::ProxyHandle<CMoto> ice_batchDatagram() const
    {
        return dynamic_cast<CMoto*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    }
    
    ::IceInternal::ProxyHandle<CMoto> ice_timeout(int __timeout) const
    {
        return dynamic_cast<CMoto*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    }
    
    static const ::std::string& ice_staticId();
    
private:
    
    virtual ::IceProxy::Ice::Object* __newInstance() const;
};

class CCam : virtual public ::IceProxy::Ice::Object
{
public:

    void setDeviceName(const ::std::string& devName)
    {
        setDeviceName(devName, 0);
    }
    void setDeviceName(const ::std::string& devName, const ::Ice::Context& __ctx)
    {
        setDeviceName(devName, &__ctx);
    }
    
private:

    void setDeviceName(const ::std::string&, const ::Ice::Context*);
    
public:

    bool open()
    {
        return open(0);
    }
    bool open(const ::Ice::Context& __ctx)
    {
        return open(&__ctx);
    }
    
private:

    bool open(const ::Ice::Context*);
    
public:

    bool isOpen()
    {
        return isOpen(0);
    }
    bool isOpen(const ::Ice::Context& __ctx)
    {
        return isOpen(&__ctx);
    }
    
private:

    bool isOpen(const ::Ice::Context*);
    
public:

    void close()
    {
        close(0);
    }
    void close(const ::Ice::Context& __ctx)
    {
        close(&__ctx);
    }
    
private:

    void close(const ::Ice::Context*);
    
public:

    bool capabilities(::Types::TStringArray& cap, ::Types::TBoolArray& en, ::Types::TStringArray& info)
    {
        return capabilities(cap, en, info, 0);
    }
    bool capabilities(::Types::TStringArray& cap, ::Types::TBoolArray& en, ::Types::TStringArray& info, const ::Ice::Context& __ctx)
    {
        return capabilities(cap, en, info, &__ctx);
    }
    
private:

    bool capabilities(::Types::TStringArray&, ::Types::TBoolArray&, ::Types::TStringArray&, const ::Ice::Context*);
    
public:

    bool formats(::Types::TStringArray& fmt, ::Types::TLongArray& fourcc)
    {
        return formats(fmt, fourcc, 0);
    }
    bool formats(::Types::TStringArray& fmt, ::Types::TLongArray& fourcc, const ::Ice::Context& __ctx)
    {
        return formats(fmt, fourcc, &__ctx);
    }
    
private:

    bool formats(::Types::TStringArray&, ::Types::TLongArray&, const ::Ice::Context*);
    
public:

    ::Types::TIntArray resolutions()
    {
        return resolutions(0);
    }
    ::Types::TIntArray resolutions(const ::Ice::Context& __ctx)
    {
        return resolutions(&__ctx);
    }
    
private:

    ::Types::TIntArray resolutions(const ::Ice::Context*);
    
public:

    bool initDevice(bool streaming, ::Ice::Long fourcc, ::Ice::Int width, ::Ice::Int height, ::Ice::Int fps)
    {
        return initDevice(streaming, fourcc, width, height, fps, 0);
    }
    bool initDevice(bool streaming, ::Ice::Long fourcc, ::Ice::Int width, ::Ice::Int height, ::Ice::Int fps, const ::Ice::Context& __ctx)
    {
        return initDevice(streaming, fourcc, width, height, fps, &__ctx);
    }
    
private:

    bool initDevice(bool, ::Ice::Long, ::Ice::Int, ::Ice::Int, ::Ice::Int, const ::Ice::Context*);
    
public:

    void imageSize(::Ice::Int& width, ::Ice::Int& height, ::Ice::Int& bufferSize)
    {
        imageSize(width, height, bufferSize, 0);
    }
    void imageSize(::Ice::Int& width, ::Ice::Int& height, ::Ice::Int& bufferSize, const ::Ice::Context& __ctx)
    {
        imageSize(width, height, bufferSize, &__ctx);
    }
    
private:

    void imageSize(::Ice::Int&, ::Ice::Int&, ::Ice::Int&, const ::Ice::Context*);
    
public:

    bool startCapture()
    {
        return startCapture(0);
    }
    bool startCapture(const ::Ice::Context& __ctx)
    {
        return startCapture(&__ctx);
    }
    
private:

    bool startCapture(const ::Ice::Context*);
    
public:

    void stopCapture()
    {
        stopCapture(0);
    }
    void stopCapture(const ::Ice::Context& __ctx)
    {
        stopCapture(&__ctx);
    }
    
private:

    void stopCapture(const ::Ice::Context*);
    
public:

    bool started()
    {
        return started(0);
    }
    bool started(const ::Ice::Context& __ctx)
    {
        return started(&__ctx);
    }
    
private:

    bool started(const ::Ice::Context*);
    
public:

    bool acquire()
    {
        return acquire(0);
    }
    bool acquire(const ::Ice::Context& __ctx)
    {
        return acquire(&__ctx);
    }
    
private:

    bool acquire(const ::Ice::Context*);
    
public:

    bool release()
    {
        return release(0);
    }
    bool release(const ::Ice::Context& __ctx)
    {
        return release(&__ctx);
    }
    
private:

    bool release(const ::Ice::Context*);
    
public:

    void data(::Ice::Int from, ::Ice::Int sz, ::Types::TByteArray& res)
    {
        data(from, sz, res, 0);
    }
    void data(::Ice::Int from, ::Ice::Int sz, ::Types::TByteArray& res, const ::Ice::Context& __ctx)
    {
        data(from, sz, res, &__ctx);
    }
    
private:

    void data(::Ice::Int, ::Ice::Int, ::Types::TByteArray&, const ::Ice::Context*);
    
public:

    ::std::string lastError()
    {
        return lastError(0);
    }
    ::std::string lastError(const ::Ice::Context& __ctx)
    {
        return lastError(&__ctx);
    }
    
private:

    ::std::string lastError(const ::Ice::Context*);
    
public:
    
    ::IceInternal::ProxyHandle<CCam> ice_context(const ::Ice::Context& __context) const
    {
        return dynamic_cast<CCam*>(::IceProxy::Ice::Object::ice_context(__context).get());
    }
    
    ::IceInternal::ProxyHandle<CCam> ice_secure(bool __secure) const
    {
        return dynamic_cast<CCam*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    }
    
#ifdef ICEE_HAS_ROUTER
    ::IceInternal::ProxyHandle<CCam> ice_router(const ::Ice::RouterPrx& __router) const
    {
        return dynamic_cast<CCam*>(::IceProxy::Ice::Object::ice_router(__router).get());
    }
#endif // ICEE_HAS_ROUTER
    
#ifdef ICEE_HAS_LOCATOR
    ::IceInternal::ProxyHandle<CCam> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
        return dynamic_cast<CCam*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    }
    
    ::IceInternal::ProxyHandle<CCam> ice_adapterId(const std::string& __id) const
    {
        return dynamic_cast<CCam*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    }
#endif // ICEE_HAS_LOCATOR
    
    ::IceInternal::ProxyHandle<CCam> ice_twoway() const
    {
        return dynamic_cast<CCam*>(::IceProxy::Ice::Object::ice_twoway().get());
    }
    
    ::IceInternal::ProxyHandle<CCam> ice_oneway() const
    {
        return dynamic_cast<CCam*>(::IceProxy::Ice::Object::ice_oneway().get());
    }
    
    ::IceInternal::ProxyHandle<CCam> ice_batchOneway() const
    {
        return dynamic_cast<CCam*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    }
    
    ::IceInternal::ProxyHandle<CCam> ice_datagram() const
    {
        return dynamic_cast<CCam*>(::IceProxy::Ice::Object::ice_datagram().get());
    }
    
    ::IceInternal::ProxyHandle<CCam> ice_batchDatagram() const
    {
        return dynamic_cast<CCam*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    }
    
    ::IceInternal::ProxyHandle<CCam> ice_timeout(int __timeout) const
    {
        return dynamic_cast<CCam*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    }
    
    static const ::std::string& ice_staticId();
    
private:
    
    virtual ::IceProxy::Ice::Object* __newInstance() const;
};

class CLua : virtual public ::IceProxy::Ice::Object
{
public:

    bool exec(const ::std::string& stri)
    {
        return exec(stri, 0);
    }
    bool exec(const ::std::string& stri, const ::Ice::Context& __ctx)
    {
        return exec(stri, &__ctx);
    }
    
private:

    bool exec(const ::std::string&, const ::Ice::Context*);
    
public:
    
    ::IceInternal::ProxyHandle<CLua> ice_context(const ::Ice::Context& __context) const
    {
        return dynamic_cast<CLua*>(::IceProxy::Ice::Object::ice_context(__context).get());
    }
    
    ::IceInternal::ProxyHandle<CLua> ice_secure(bool __secure) const
    {
        return dynamic_cast<CLua*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    }
    
#ifdef ICEE_HAS_ROUTER
    ::IceInternal::ProxyHandle<CLua> ice_router(const ::Ice::RouterPrx& __router) const
    {
        return dynamic_cast<CLua*>(::IceProxy::Ice::Object::ice_router(__router).get());
    }
#endif // ICEE_HAS_ROUTER
    
#ifdef ICEE_HAS_LOCATOR
    ::IceInternal::ProxyHandle<CLua> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
        return dynamic_cast<CLua*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    }
    
    ::IceInternal::ProxyHandle<CLua> ice_adapterId(const std::string& __id) const
    {
        return dynamic_cast<CLua*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    }
#endif // ICEE_HAS_LOCATOR
    
    ::IceInternal::ProxyHandle<CLua> ice_twoway() const
    {
        return dynamic_cast<CLua*>(::IceProxy::Ice::Object::ice_twoway().get());
    }
    
    ::IceInternal::ProxyHandle<CLua> ice_oneway() const
    {
        return dynamic_cast<CLua*>(::IceProxy::Ice::Object::ice_oneway().get());
    }
    
    ::IceInternal::ProxyHandle<CLua> ice_batchOneway() const
    {
        return dynamic_cast<CLua*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    }
    
    ::IceInternal::ProxyHandle<CLua> ice_datagram() const
    {
        return dynamic_cast<CLua*>(::IceProxy::Ice::Object::ice_datagram().get());
    }
    
    ::IceInternal::ProxyHandle<CLua> ice_batchDatagram() const
    {
        return dynamic_cast<CLua*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    }
    
    ::IceInternal::ProxyHandle<CLua> ice_timeout(int __timeout) const
    {
        return dynamic_cast<CLua*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    }
    
    static const ::std::string& ice_staticId();
    
private:
    
    virtual ::IceProxy::Ice::Object* __newInstance() const;
};

class CHdw : virtual public ::IceProxy::Ice::Object
{
public:

    ::Hdw::CMotoPrx moto()
    {
        return moto(0);
    }
    ::Hdw::CMotoPrx moto(const ::Ice::Context& __ctx)
    {
        return moto(&__ctx);
    }
    
private:

    ::Hdw::CMotoPrx moto(const ::Ice::Context*);
    
public:

    ::Hdw::CCamPrx cam()
    {
        return cam(0);
    }
    ::Hdw::CCamPrx cam(const ::Ice::Context& __ctx)
    {
        return cam(&__ctx);
    }
    
private:

    ::Hdw::CCamPrx cam(const ::Ice::Context*);
    
public:
    
    ::IceInternal::ProxyHandle<CHdw> ice_context(const ::Ice::Context& __context) const
    {
        return dynamic_cast<CHdw*>(::IceProxy::Ice::Object::ice_context(__context).get());
    }
    
    ::IceInternal::ProxyHandle<CHdw> ice_secure(bool __secure) const
    {
        return dynamic_cast<CHdw*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    }
    
#ifdef ICEE_HAS_ROUTER
    ::IceInternal::ProxyHandle<CHdw> ice_router(const ::Ice::RouterPrx& __router) const
    {
        return dynamic_cast<CHdw*>(::IceProxy::Ice::Object::ice_router(__router).get());
    }
#endif // ICEE_HAS_ROUTER
    
#ifdef ICEE_HAS_LOCATOR
    ::IceInternal::ProxyHandle<CHdw> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
        return dynamic_cast<CHdw*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    }
    
    ::IceInternal::ProxyHandle<CHdw> ice_adapterId(const std::string& __id) const
    {
        return dynamic_cast<CHdw*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    }
#endif // ICEE_HAS_LOCATOR
    
    ::IceInternal::ProxyHandle<CHdw> ice_twoway() const
    {
        return dynamic_cast<CHdw*>(::IceProxy::Ice::Object::ice_twoway().get());
    }
    
    ::IceInternal::ProxyHandle<CHdw> ice_oneway() const
    {
        return dynamic_cast<CHdw*>(::IceProxy::Ice::Object::ice_oneway().get());
    }
    
    ::IceInternal::ProxyHandle<CHdw> ice_batchOneway() const
    {
        return dynamic_cast<CHdw*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    }
    
    ::IceInternal::ProxyHandle<CHdw> ice_datagram() const
    {
        return dynamic_cast<CHdw*>(::IceProxy::Ice::Object::ice_datagram().get());
    }
    
    ::IceInternal::ProxyHandle<CHdw> ice_batchDatagram() const
    {
        return dynamic_cast<CHdw*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    }
    
    ::IceInternal::ProxyHandle<CHdw> ice_timeout(int __timeout) const
    {
        return dynamic_cast<CHdw*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    }
    
    static const ::std::string& ice_staticId();
    
private:
    
    virtual ::IceProxy::Ice::Object* __newInstance() const;
};

}

}

#endif
