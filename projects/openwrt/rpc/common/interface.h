// **********************************************************************
//
// Copyright (c) 2003-2007 ZeroC, Inc. All rights reserved.
//
// This copy of Ice-E is licensed to you under the terms described in the
// ICEE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice-E version 1.3.0
// Generated from file `interface.ice'

#ifndef __interface_h__
#define __interface_h__

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

namespace Demo
{

class Hello;

class Camera;

}

}

namespace Demo
{

class Hello;
bool operator==(const Hello&, const Hello&);
bool operator<(const Hello&, const Hello&);

class Camera;
bool operator==(const Camera&, const Camera&);
bool operator<(const Camera&, const Camera&);

}

namespace IceInternal
{

::Ice::Object* upCast(::Demo::Hello*);
::IceProxy::Ice::Object* upCast(::IceProxy::Demo::Hello*);

::Ice::Object* upCast(::Demo::Camera*);
::IceProxy::Ice::Object* upCast(::IceProxy::Demo::Camera*);

}

namespace Demo
{

typedef ::IceInternal::Handle< ::Demo::Hello> HelloPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::Demo::Hello> HelloPrx;

void __read(::IceInternal::BasicStream*, HelloPrx&);
void __patch__HelloPtr(void*, ::Ice::ObjectPtr&);

typedef ::IceInternal::Handle< ::Demo::Camera> CameraPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::Demo::Camera> CameraPrx;

void __read(::IceInternal::BasicStream*, CameraPrx&);
void __patch__CameraPtr(void*, ::Ice::ObjectPtr&);

}

namespace Demo
{

typedef ::std::vector< ::std::string> TStringList;

typedef ::std::vector< ::Ice::Int> TIntList;

typedef ::std::vector< ::Ice::Byte> TByteList;

}

namespace Demo
{

class Hello : virtual public ::Ice::Object
{
public:

    typedef HelloPrx ProxyType;
    typedef HelloPtr PointerType;
    

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual void sayHello(::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___sayHello(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual void shutdown(const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___shutdown(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
};

class Camera : virtual public ::Ice::Object
{
public:

    typedef CameraPrx ProxyType;
    typedef CameraPtr PointerType;
    

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

    virtual void close(const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___close(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual bool isOpened(const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___isOpened(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual ::Demo::TStringList formats(const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___formats(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual ::Demo::TIntList resolutions(const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___resolutions(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual bool initDevice(const ::std::string&, ::Ice::Int, ::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
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

    virtual void data(::Ice::Int, ::Ice::Int, ::Demo::TByteList&, const ::Ice::Current& = ::Ice::Current()) = 0;
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

}

namespace IceProxy
{

namespace Demo
{

class Hello : virtual public ::IceProxy::Ice::Object
{
public:

    void sayHello(::Ice::Int delay)
    {
        sayHello(delay, 0);
    }
    void sayHello(::Ice::Int delay, const ::Ice::Context& __ctx)
    {
        sayHello(delay, &__ctx);
    }
    
private:

    void sayHello(::Ice::Int, const ::Ice::Context*);
    
public:

    void shutdown()
    {
        shutdown(0);
    }
    void shutdown(const ::Ice::Context& __ctx)
    {
        shutdown(&__ctx);
    }
    
private:

    void shutdown(const ::Ice::Context*);
    
public:
    
    ::IceInternal::ProxyHandle<Hello> ice_context(const ::Ice::Context& __context) const
    {
        return dynamic_cast<Hello*>(::IceProxy::Ice::Object::ice_context(__context).get());
    }
    
    ::IceInternal::ProxyHandle<Hello> ice_secure(bool __secure) const
    {
        return dynamic_cast<Hello*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    }
    
#ifdef ICEE_HAS_ROUTER
    ::IceInternal::ProxyHandle<Hello> ice_router(const ::Ice::RouterPrx& __router) const
    {
        return dynamic_cast<Hello*>(::IceProxy::Ice::Object::ice_router(__router).get());
    }
#endif // ICEE_HAS_ROUTER
    
#ifdef ICEE_HAS_LOCATOR
    ::IceInternal::ProxyHandle<Hello> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
        return dynamic_cast<Hello*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    }
    
    ::IceInternal::ProxyHandle<Hello> ice_adapterId(const std::string& __id) const
    {
        return dynamic_cast<Hello*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    }
#endif // ICEE_HAS_LOCATOR
    
    ::IceInternal::ProxyHandle<Hello> ice_twoway() const
    {
        return dynamic_cast<Hello*>(::IceProxy::Ice::Object::ice_twoway().get());
    }
    
    ::IceInternal::ProxyHandle<Hello> ice_oneway() const
    {
        return dynamic_cast<Hello*>(::IceProxy::Ice::Object::ice_oneway().get());
    }
    
    ::IceInternal::ProxyHandle<Hello> ice_batchOneway() const
    {
        return dynamic_cast<Hello*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    }
    
    ::IceInternal::ProxyHandle<Hello> ice_datagram() const
    {
        return dynamic_cast<Hello*>(::IceProxy::Ice::Object::ice_datagram().get());
    }
    
    ::IceInternal::ProxyHandle<Hello> ice_batchDatagram() const
    {
        return dynamic_cast<Hello*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    }
    
    ::IceInternal::ProxyHandle<Hello> ice_timeout(int __timeout) const
    {
        return dynamic_cast<Hello*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    }
    
    static const ::std::string& ice_staticId();
    
private:
    
    virtual ::IceProxy::Ice::Object* __newInstance() const;
};

class Camera : virtual public ::IceProxy::Ice::Object
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

    bool isOpened()
    {
        return isOpened(0);
    }
    bool isOpened(const ::Ice::Context& __ctx)
    {
        return isOpened(&__ctx);
    }
    
private:

    bool isOpened(const ::Ice::Context*);
    
public:

    ::Demo::TStringList formats()
    {
        return formats(0);
    }
    ::Demo::TStringList formats(const ::Ice::Context& __ctx)
    {
        return formats(&__ctx);
    }
    
private:

    ::Demo::TStringList formats(const ::Ice::Context*);
    
public:

    ::Demo::TIntList resolutions()
    {
        return resolutions(0);
    }
    ::Demo::TIntList resolutions(const ::Ice::Context& __ctx)
    {
        return resolutions(&__ctx);
    }
    
private:

    ::Demo::TIntList resolutions(const ::Ice::Context*);
    
public:

    bool initDevice(const ::std::string& format, ::Ice::Int width, ::Ice::Int height)
    {
        return initDevice(format, width, height, 0);
    }
    bool initDevice(const ::std::string& format, ::Ice::Int width, ::Ice::Int height, const ::Ice::Context& __ctx)
    {
        return initDevice(format, width, height, &__ctx);
    }
    
private:

    bool initDevice(const ::std::string&, ::Ice::Int, ::Ice::Int, const ::Ice::Context*);
    
public:

    void imageSize(::Ice::Int& width, ::Ice::Int& height, ::Ice::Int& bufferSz)
    {
        imageSize(width, height, bufferSz, 0);
    }
    void imageSize(::Ice::Int& width, ::Ice::Int& height, ::Ice::Int& bufferSz, const ::Ice::Context& __ctx)
    {
        imageSize(width, height, bufferSz, &__ctx);
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

    void data(::Ice::Int from, ::Ice::Int sz, ::Demo::TByteList& res)
    {
        data(from, sz, res, 0);
    }
    void data(::Ice::Int from, ::Ice::Int sz, ::Demo::TByteList& res, const ::Ice::Context& __ctx)
    {
        data(from, sz, res, &__ctx);
    }
    
private:

    void data(::Ice::Int, ::Ice::Int, ::Demo::TByteList&, const ::Ice::Context*);
    
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
    
    ::IceInternal::ProxyHandle<Camera> ice_context(const ::Ice::Context& __context) const
    {
        return dynamic_cast<Camera*>(::IceProxy::Ice::Object::ice_context(__context).get());
    }
    
    ::IceInternal::ProxyHandle<Camera> ice_secure(bool __secure) const
    {
        return dynamic_cast<Camera*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    }
    
#ifdef ICEE_HAS_ROUTER
    ::IceInternal::ProxyHandle<Camera> ice_router(const ::Ice::RouterPrx& __router) const
    {
        return dynamic_cast<Camera*>(::IceProxy::Ice::Object::ice_router(__router).get());
    }
#endif // ICEE_HAS_ROUTER
    
#ifdef ICEE_HAS_LOCATOR
    ::IceInternal::ProxyHandle<Camera> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
        return dynamic_cast<Camera*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    }
    
    ::IceInternal::ProxyHandle<Camera> ice_adapterId(const std::string& __id) const
    {
        return dynamic_cast<Camera*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    }
#endif // ICEE_HAS_LOCATOR
    
    ::IceInternal::ProxyHandle<Camera> ice_twoway() const
    {
        return dynamic_cast<Camera*>(::IceProxy::Ice::Object::ice_twoway().get());
    }
    
    ::IceInternal::ProxyHandle<Camera> ice_oneway() const
    {
        return dynamic_cast<Camera*>(::IceProxy::Ice::Object::ice_oneway().get());
    }
    
    ::IceInternal::ProxyHandle<Camera> ice_batchOneway() const
    {
        return dynamic_cast<Camera*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    }
    
    ::IceInternal::ProxyHandle<Camera> ice_datagram() const
    {
        return dynamic_cast<Camera*>(::IceProxy::Ice::Object::ice_datagram().get());
    }
    
    ::IceInternal::ProxyHandle<Camera> ice_batchDatagram() const
    {
        return dynamic_cast<Camera*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    }
    
    ::IceInternal::ProxyHandle<Camera> ice_timeout(int __timeout) const
    {
        return dynamic_cast<Camera*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    }
    
    static const ::std::string& ice_staticId();
    
private:
    
    virtual ::IceProxy::Ice::Object* __newInstance() const;
};

}

}

#endif
