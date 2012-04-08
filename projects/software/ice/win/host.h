// **********************************************************************
//
// Copyright (c) 2003-2007 ZeroC, Inc. All rights reserved.
//
// This copy of Ice-E is licensed to you under the terms described in the
// ICEE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice-E version 1.3.0
// Generated from file `host.ice'

#ifndef __host_h__
#define __host_h__

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
#ifdef ICEE_HAS_AMI
#   include <IceE/OutgoingAsync.h>
#endif
#include <IceE/Identity.h>
#include <C:/projects/avr/chassis/projects/software/ice/win/types.h>
#include <C:/projects/avr/chassis/projects/software/ice/win/client.h>
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

namespace Host
{

class CMoto;

class CCam;

class CHost;

}

}

namespace Host
{

class CMoto;
bool operator==(const CMoto&, const CMoto&);
bool operator<(const CMoto&, const CMoto&);

class CCam;
bool operator==(const CCam&, const CCam&);
bool operator<(const CCam&, const CCam&);

class CHost;
bool operator==(const CHost&, const CHost&);
bool operator<(const CHost&, const CHost&);

}

namespace IceInternal
{

::Ice::Object* upCast(::Host::CMoto*);
::IceProxy::Ice::Object* upCast(::IceProxy::Host::CMoto*);

::Ice::Object* upCast(::Host::CCam*);
::IceProxy::Ice::Object* upCast(::IceProxy::Host::CCam*);

::Ice::Object* upCast(::Host::CHost*);
::IceProxy::Ice::Object* upCast(::IceProxy::Host::CHost*);

}

namespace Host
{

typedef ::IceInternal::Handle< ::Host::CMoto> CMotoPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::Host::CMoto> CMotoPrx;

void __read(::IceInternal::BasicStream*, CMotoPrx&);
void __patch__CMotoPtr(void*, ::Ice::ObjectPtr&);

typedef ::IceInternal::Handle< ::Host::CCam> CCamPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::Host::CCam> CCamPrx;

void __read(::IceInternal::BasicStream*, CCamPrx&);
void __patch__CCamPtr(void*, ::Ice::ObjectPtr&);

typedef ::IceInternal::Handle< ::Host::CHost> CHostPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::Host::CHost> CHostPrx;

void __read(::IceInternal::BasicStream*, CHostPrx&);
void __patch__CHostPtr(void*, ::Ice::ObjectPtr&);

}

namespace Host
{

}

namespace Host
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

    virtual bool isOpen(const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___isOpen(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual bool motoEn(const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___motoEn(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual void moto(::Ice::Int&, ::Ice::Int&, const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___moto(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual bool servoEn(const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___servoEn(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual void servo(::Ice::Double&, ::Ice::Double&, const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___servo(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual void setMoto(::Ice::Int, ::Ice::Int, ::Ice::Double, const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___setMoto(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual void setServo(::Ice::Double, ::Ice::Double, const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___setServo(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual bool open(const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___open(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual void close(const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___close(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual void setMotoEn(bool, const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___setMotoEn(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual void setServoEn(bool, const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___setServoEn(::IceInternal::Incoming&, const ::Ice::Current&);
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

    virtual bool isOpen(const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___isOpen(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual void setResolution(::Ice::Int, ::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___setResolution(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual void resolution(::Ice::Int&, ::Ice::Int&, const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___resolution(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual ::Ice::Double period(const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___period(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual bool image(::Types::TByteArray&, const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___image(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual void setReceiveImages(bool, const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___setReceiveImages(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual bool receiveImages(const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___receiveImages(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual ::std::string deviceName(const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___deviceName(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual void setPeriod(::Ice::Double, const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___setPeriod(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual void setDeviceName(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___setDeviceName(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual bool open(const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___open(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual void close(const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___close(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
};

class CHost : virtual public ::Ice::Object
{
public:

    typedef CHostPrx ProxyType;
    typedef CHostPtr PointerType;
    
    CHost() {}

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual bool registerClient(const ::Client::CClientPrx&, const ::std::string&, ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___registerClient(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual void removeClient(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___removeClient(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual void postMessage(const ::std::string&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___postMessage(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual bool queryCtrl(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___queryCtrl(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual bool querySuper(const ::std::string&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___querySuper(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual void releaseCtrl(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___releaseCtrl(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual ::Host::CCamPrx cam(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___cam(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual ::Host::CMotoPrx moto(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___moto(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
};

}

namespace Host
{
#ifdef ICEE_HAS_AMI

class AMI_CMoto_setMoto : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response() = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::Host::CMotoPrx&, ::Ice::Int, ::Ice::Int, ::Ice::Double, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::Host::AMI_CMoto_setMoto> AMI_CMoto_setMotoPtr;
#endif
#ifdef ICEE_HAS_AMI

class AMI_CMoto_setServo : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response() = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::Host::CMotoPrx&, ::Ice::Double, ::Ice::Double, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::Host::AMI_CMoto_setServo> AMI_CMoto_setServoPtr;
#endif
#ifdef ICEE_HAS_AMI

class AMI_CHost_postMessage : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response() = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::Host::CHostPrx&, const ::std::string&, const ::std::string&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::Host::AMI_CHost_postMessage> AMI_CHost_postMessagePtr;
#endif

}

namespace IceProxy
{

namespace Host
{

class CMoto : virtual public ::IceProxy::Ice::Object
{
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

    void servo(::Ice::Double& servo1, ::Ice::Double& servo2)
    {
        servo(servo1, servo2, 0);
    }
    void servo(::Ice::Double& servo1, ::Ice::Double& servo2, const ::Ice::Context& __ctx)
    {
        servo(servo1, servo2, &__ctx);
    }
    
private:

    void servo(::Ice::Double&, ::Ice::Double&, const ::Ice::Context*);
    
public:

    void setMoto(::Ice::Int dir1, ::Ice::Int dir2, ::Ice::Double period)
    {
        setMoto(dir1, dir2, period, 0);
    }
    void setMoto(::Ice::Int dir1, ::Ice::Int dir2, ::Ice::Double period, const ::Ice::Context& __ctx)
    {
        setMoto(dir1, dir2, period, &__ctx);
    }
    
private:

    void setMoto(::Ice::Int, ::Ice::Int, ::Ice::Double, const ::Ice::Context*);
    
public:
    #ifdef ICEE_HAS_AMI
    bool setMoto_async(const ::Host::AMI_CMoto_setMotoPtr&, ::Ice::Int, ::Ice::Int, ::Ice::Double);
    bool setMoto_async(const ::Host::AMI_CMoto_setMotoPtr&, ::Ice::Int, ::Ice::Int, ::Ice::Double, const ::Ice::Context&);
    #endif

    void setServo(::Ice::Double servo1, ::Ice::Double servo2)
    {
        setServo(servo1, servo2, 0);
    }
    void setServo(::Ice::Double servo1, ::Ice::Double servo2, const ::Ice::Context& __ctx)
    {
        setServo(servo1, servo2, &__ctx);
    }
    
private:

    void setServo(::Ice::Double, ::Ice::Double, const ::Ice::Context*);
    
public:
    #ifdef ICEE_HAS_AMI
    bool setServo_async(const ::Host::AMI_CMoto_setServoPtr&, ::Ice::Double, ::Ice::Double);
    bool setServo_async(const ::Host::AMI_CMoto_setServoPtr&, ::Ice::Double, ::Ice::Double, const ::Ice::Context&);
    #endif

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

    void setResolution(::Ice::Int width, ::Ice::Int height)
    {
        setResolution(width, height, 0);
    }
    void setResolution(::Ice::Int width, ::Ice::Int height, const ::Ice::Context& __ctx)
    {
        setResolution(width, height, &__ctx);
    }
    
private:

    void setResolution(::Ice::Int, ::Ice::Int, const ::Ice::Context*);
    
public:

    void resolution(::Ice::Int& width, ::Ice::Int& height)
    {
        resolution(width, height, 0);
    }
    void resolution(::Ice::Int& width, ::Ice::Int& height, const ::Ice::Context& __ctx)
    {
        resolution(width, height, &__ctx);
    }
    
private:

    void resolution(::Ice::Int&, ::Ice::Int&, const ::Ice::Context*);
    
public:

    ::Ice::Double period()
    {
        return period(0);
    }
    ::Ice::Double period(const ::Ice::Context& __ctx)
    {
        return period(&__ctx);
    }
    
private:

    ::Ice::Double period(const ::Ice::Context*);
    
public:

    bool image(::Types::TByteArray& data)
    {
        return image(data, 0);
    }
    bool image(::Types::TByteArray& data, const ::Ice::Context& __ctx)
    {
        return image(data, &__ctx);
    }
    
private:

    bool image(::Types::TByteArray&, const ::Ice::Context*);
    
public:

    void setReceiveImages(bool en)
    {
        setReceiveImages(en, 0);
    }
    void setReceiveImages(bool en, const ::Ice::Context& __ctx)
    {
        setReceiveImages(en, &__ctx);
    }
    
private:

    void setReceiveImages(bool, const ::Ice::Context*);
    
public:

    bool receiveImages()
    {
        return receiveImages(0);
    }
    bool receiveImages(const ::Ice::Context& __ctx)
    {
        return receiveImages(&__ctx);
    }
    
private:

    bool receiveImages(const ::Ice::Context*);
    
public:

    ::std::string deviceName()
    {
        return deviceName(0);
    }
    ::std::string deviceName(const ::Ice::Context& __ctx)
    {
        return deviceName(&__ctx);
    }
    
private:

    ::std::string deviceName(const ::Ice::Context*);
    
public:

    void setPeriod(::Ice::Double period)
    {
        setPeriod(period, 0);
    }
    void setPeriod(::Ice::Double period, const ::Ice::Context& __ctx)
    {
        setPeriod(period, &__ctx);
    }
    
private:

    void setPeriod(::Ice::Double, const ::Ice::Context*);
    
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

class CHost : virtual public ::IceProxy::Ice::Object
{
public:

    bool registerClient(const ::Client::CClientPrx& client, const ::std::string& nickname, ::std::string& idOrErrMsg)
    {
        return registerClient(client, nickname, idOrErrMsg, 0);
    }
    bool registerClient(const ::Client::CClientPrx& client, const ::std::string& nickname, ::std::string& idOrErrMsg, const ::Ice::Context& __ctx)
    {
        return registerClient(client, nickname, idOrErrMsg, &__ctx);
    }
    
private:

    bool registerClient(const ::Client::CClientPrx&, const ::std::string&, ::std::string&, const ::Ice::Context*);
    
public:

    void removeClient(const ::std::string& id)
    {
        removeClient(id, 0);
    }
    void removeClient(const ::std::string& id, const ::Ice::Context& __ctx)
    {
        removeClient(id, &__ctx);
    }
    
private:

    void removeClient(const ::std::string&, const ::Ice::Context*);
    
public:

    void postMessage(const ::std::string& id, const ::std::string& stri)
    {
        postMessage(id, stri, 0);
    }
    void postMessage(const ::std::string& id, const ::std::string& stri, const ::Ice::Context& __ctx)
    {
        postMessage(id, stri, &__ctx);
    }
    
private:

    void postMessage(const ::std::string&, const ::std::string&, const ::Ice::Context*);
    
public:
    #ifdef ICEE_HAS_AMI
    bool postMessage_async(const ::Host::AMI_CHost_postMessagePtr&, const ::std::string&, const ::std::string&);
    bool postMessage_async(const ::Host::AMI_CHost_postMessagePtr&, const ::std::string&, const ::std::string&, const ::Ice::Context&);
    #endif

    bool queryCtrl(const ::std::string& id)
    {
        return queryCtrl(id, 0);
    }
    bool queryCtrl(const ::std::string& id, const ::Ice::Context& __ctx)
    {
        return queryCtrl(id, &__ctx);
    }
    
private:

    bool queryCtrl(const ::std::string&, const ::Ice::Context*);
    
public:

    bool querySuper(const ::std::string& id, const ::std::string& password)
    {
        return querySuper(id, password, 0);
    }
    bool querySuper(const ::std::string& id, const ::std::string& password, const ::Ice::Context& __ctx)
    {
        return querySuper(id, password, &__ctx);
    }
    
private:

    bool querySuper(const ::std::string&, const ::std::string&, const ::Ice::Context*);
    
public:

    void releaseCtrl(const ::std::string& id)
    {
        releaseCtrl(id, 0);
    }
    void releaseCtrl(const ::std::string& id, const ::Ice::Context& __ctx)
    {
        releaseCtrl(id, &__ctx);
    }
    
private:

    void releaseCtrl(const ::std::string&, const ::Ice::Context*);
    
public:

    ::Host::CCamPrx cam(const ::std::string& id)
    {
        return cam(id, 0);
    }
    ::Host::CCamPrx cam(const ::std::string& id, const ::Ice::Context& __ctx)
    {
        return cam(id, &__ctx);
    }
    
private:

    ::Host::CCamPrx cam(const ::std::string&, const ::Ice::Context*);
    
public:

    ::Host::CMotoPrx moto(const ::std::string& id)
    {
        return moto(id, 0);
    }
    ::Host::CMotoPrx moto(const ::std::string& id, const ::Ice::Context& __ctx)
    {
        return moto(id, &__ctx);
    }
    
private:

    ::Host::CMotoPrx moto(const ::std::string&, const ::Ice::Context*);
    
public:
    
    ::IceInternal::ProxyHandle<CHost> ice_context(const ::Ice::Context& __context) const
    {
        return dynamic_cast<CHost*>(::IceProxy::Ice::Object::ice_context(__context).get());
    }
    
    ::IceInternal::ProxyHandle<CHost> ice_secure(bool __secure) const
    {
        return dynamic_cast<CHost*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    }
    
#ifdef ICEE_HAS_ROUTER
    ::IceInternal::ProxyHandle<CHost> ice_router(const ::Ice::RouterPrx& __router) const
    {
        return dynamic_cast<CHost*>(::IceProxy::Ice::Object::ice_router(__router).get());
    }
#endif // ICEE_HAS_ROUTER
    
#ifdef ICEE_HAS_LOCATOR
    ::IceInternal::ProxyHandle<CHost> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
        return dynamic_cast<CHost*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    }
    
    ::IceInternal::ProxyHandle<CHost> ice_adapterId(const std::string& __id) const
    {
        return dynamic_cast<CHost*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    }
#endif // ICEE_HAS_LOCATOR
    
    ::IceInternal::ProxyHandle<CHost> ice_twoway() const
    {
        return dynamic_cast<CHost*>(::IceProxy::Ice::Object::ice_twoway().get());
    }
    
    ::IceInternal::ProxyHandle<CHost> ice_oneway() const
    {
        return dynamic_cast<CHost*>(::IceProxy::Ice::Object::ice_oneway().get());
    }
    
    ::IceInternal::ProxyHandle<CHost> ice_batchOneway() const
    {
        return dynamic_cast<CHost*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    }
    
    ::IceInternal::ProxyHandle<CHost> ice_datagram() const
    {
        return dynamic_cast<CHost*>(::IceProxy::Ice::Object::ice_datagram().get());
    }
    
    ::IceInternal::ProxyHandle<CHost> ice_batchDatagram() const
    {
        return dynamic_cast<CHost*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    }
    
    ::IceInternal::ProxyHandle<CHost> ice_timeout(int __timeout) const
    {
        return dynamic_cast<CHost*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    }
    
    static const ::std::string& ice_staticId();
    
private:
    
    virtual ::IceProxy::Ice::Object* __newInstance() const;
};

}

}

#endif
