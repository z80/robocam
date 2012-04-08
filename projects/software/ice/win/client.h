// **********************************************************************
//
// Copyright (c) 2003-2007 ZeroC, Inc. All rights reserved.
//
// This copy of Ice-E is licensed to you under the terms described in the
// ICEE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice-E version 1.3.0
// Generated from file `client.ice'

#ifndef __client_h__
#define __client_h__

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
#include <C:/projects/avr/chassis/projects/software/ice/win/types.h>
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

namespace Client
{

class CChat;

class CMoto;

class CCam;

class CClient;

}

}

namespace Client
{

class CChat;
bool operator==(const CChat&, const CChat&);
bool operator<(const CChat&, const CChat&);

class CMoto;
bool operator==(const CMoto&, const CMoto&);
bool operator<(const CMoto&, const CMoto&);

class CCam;
bool operator==(const CCam&, const CCam&);
bool operator<(const CCam&, const CCam&);

class CClient;
bool operator==(const CClient&, const CClient&);
bool operator<(const CClient&, const CClient&);

}

namespace IceInternal
{

::Ice::Object* upCast(::Client::CChat*);
::IceProxy::Ice::Object* upCast(::IceProxy::Client::CChat*);

::Ice::Object* upCast(::Client::CMoto*);
::IceProxy::Ice::Object* upCast(::IceProxy::Client::CMoto*);

::Ice::Object* upCast(::Client::CCam*);
::IceProxy::Ice::Object* upCast(::IceProxy::Client::CCam*);

::Ice::Object* upCast(::Client::CClient*);
::IceProxy::Ice::Object* upCast(::IceProxy::Client::CClient*);

}

namespace Client
{

typedef ::IceInternal::Handle< ::Client::CChat> CChatPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::Client::CChat> CChatPrx;

void __read(::IceInternal::BasicStream*, CChatPrx&);
void __patch__CChatPtr(void*, ::Ice::ObjectPtr&);

typedef ::IceInternal::Handle< ::Client::CMoto> CMotoPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::Client::CMoto> CMotoPrx;

void __read(::IceInternal::BasicStream*, CMotoPrx&);
void __patch__CMotoPtr(void*, ::Ice::ObjectPtr&);

typedef ::IceInternal::Handle< ::Client::CCam> CCamPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::Client::CCam> CCamPrx;

void __read(::IceInternal::BasicStream*, CCamPrx&);
void __patch__CCamPtr(void*, ::Ice::ObjectPtr&);

typedef ::IceInternal::Handle< ::Client::CClient> CClientPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::Client::CClient> CClientPrx;

void __read(::IceInternal::BasicStream*, CClientPrx&);
void __patch__CClientPtr(void*, ::Ice::ObjectPtr&);

}

namespace Client
{

}

namespace Client
{

class CChat : virtual public ::Ice::Object
{
public:

    typedef CChatPrx ProxyType;
    typedef CChatPtr PointerType;
    
    CChat() {}

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual void acceptMessage(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___acceptMessage(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual void acceptClientList(const ::Types::TStringArray&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___acceptClientList(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
};

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

    virtual void acceptMotoEn(bool, const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___acceptMotoEn(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual void acceptMoto(::Ice::Int, ::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___acceptMoto(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual void acceptServoEn(bool, const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___acceptServoEn(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual void acceptServo(::Ice::Double, ::Ice::Double, const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___acceptServo(::IceInternal::Incoming&, const ::Ice::Current&);
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

    virtual void acceptImage(const ::Types::TByteArray&, const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___acceptImage(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual void acceptResolution(::Ice::Int, ::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___acceptResolution(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual void acceptPeriod(::Ice::Double, const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___acceptPeriod(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
};

class CClient : virtual public ::Ice::Object
{
public:

    typedef CClientPrx ProxyType;
    typedef CClientPtr PointerType;
    
    CClient() {}

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual ::Client::CChatPrx chat(const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___chat(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual ::Client::CMotoPrx moto(const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___moto(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual ::Client::CCamPrx cam(const ::Ice::Current& = ::Ice::Current()) = 0;
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

namespace Client
{

class CChat : virtual public ::IceProxy::Ice::Object
{
public:

    void acceptMessage(const ::std::string& stri)
    {
        acceptMessage(stri, 0);
    }
    void acceptMessage(const ::std::string& stri, const ::Ice::Context& __ctx)
    {
        acceptMessage(stri, &__ctx);
    }
    
private:

    void acceptMessage(const ::std::string&, const ::Ice::Context*);
    
public:

    void acceptClientList(const ::Types::TStringArray& list, const ::std::string& driverNickname)
    {
        acceptClientList(list, driverNickname, 0);
    }
    void acceptClientList(const ::Types::TStringArray& list, const ::std::string& driverNickname, const ::Ice::Context& __ctx)
    {
        acceptClientList(list, driverNickname, &__ctx);
    }
    
private:

    void acceptClientList(const ::Types::TStringArray&, const ::std::string&, const ::Ice::Context*);
    
public:
    
    ::IceInternal::ProxyHandle<CChat> ice_context(const ::Ice::Context& __context) const
    {
        return dynamic_cast<CChat*>(::IceProxy::Ice::Object::ice_context(__context).get());
    }
    
    ::IceInternal::ProxyHandle<CChat> ice_secure(bool __secure) const
    {
        return dynamic_cast<CChat*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    }
    
#ifdef ICEE_HAS_ROUTER
    ::IceInternal::ProxyHandle<CChat> ice_router(const ::Ice::RouterPrx& __router) const
    {
        return dynamic_cast<CChat*>(::IceProxy::Ice::Object::ice_router(__router).get());
    }
#endif // ICEE_HAS_ROUTER
    
#ifdef ICEE_HAS_LOCATOR
    ::IceInternal::ProxyHandle<CChat> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
        return dynamic_cast<CChat*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    }
    
    ::IceInternal::ProxyHandle<CChat> ice_adapterId(const std::string& __id) const
    {
        return dynamic_cast<CChat*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    }
#endif // ICEE_HAS_LOCATOR
    
    ::IceInternal::ProxyHandle<CChat> ice_twoway() const
    {
        return dynamic_cast<CChat*>(::IceProxy::Ice::Object::ice_twoway().get());
    }
    
    ::IceInternal::ProxyHandle<CChat> ice_oneway() const
    {
        return dynamic_cast<CChat*>(::IceProxy::Ice::Object::ice_oneway().get());
    }
    
    ::IceInternal::ProxyHandle<CChat> ice_batchOneway() const
    {
        return dynamic_cast<CChat*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    }
    
    ::IceInternal::ProxyHandle<CChat> ice_datagram() const
    {
        return dynamic_cast<CChat*>(::IceProxy::Ice::Object::ice_datagram().get());
    }
    
    ::IceInternal::ProxyHandle<CChat> ice_batchDatagram() const
    {
        return dynamic_cast<CChat*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    }
    
    ::IceInternal::ProxyHandle<CChat> ice_timeout(int __timeout) const
    {
        return dynamic_cast<CChat*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    }
    
    static const ::std::string& ice_staticId();
    
private:
    
    virtual ::IceProxy::Ice::Object* __newInstance() const;
};

class CMoto : virtual public ::IceProxy::Ice::Object
{
public:

    void acceptMotoEn(bool en)
    {
        acceptMotoEn(en, 0);
    }
    void acceptMotoEn(bool en, const ::Ice::Context& __ctx)
    {
        acceptMotoEn(en, &__ctx);
    }
    
private:

    void acceptMotoEn(bool, const ::Ice::Context*);
    
public:

    void acceptMoto(::Ice::Int dir1, ::Ice::Int dir2)
    {
        acceptMoto(dir1, dir2, 0);
    }
    void acceptMoto(::Ice::Int dir1, ::Ice::Int dir2, const ::Ice::Context& __ctx)
    {
        acceptMoto(dir1, dir2, &__ctx);
    }
    
private:

    void acceptMoto(::Ice::Int, ::Ice::Int, const ::Ice::Context*);
    
public:

    void acceptServoEn(bool en)
    {
        acceptServoEn(en, 0);
    }
    void acceptServoEn(bool en, const ::Ice::Context& __ctx)
    {
        acceptServoEn(en, &__ctx);
    }
    
private:

    void acceptServoEn(bool, const ::Ice::Context*);
    
public:

    void acceptServo(::Ice::Double servo1, ::Ice::Double servo2)
    {
        acceptServo(servo1, servo2, 0);
    }
    void acceptServo(::Ice::Double servo1, ::Ice::Double servo2, const ::Ice::Context& __ctx)
    {
        acceptServo(servo1, servo2, &__ctx);
    }
    
private:

    void acceptServo(::Ice::Double, ::Ice::Double, const ::Ice::Context*);
    
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

    void acceptImage(const ::Types::TByteArray& image)
    {
        acceptImage(image, 0);
    }
    void acceptImage(const ::Types::TByteArray& image, const ::Ice::Context& __ctx)
    {
        acceptImage(image, &__ctx);
    }
    
private:

    void acceptImage(const ::Types::TByteArray&, const ::Ice::Context*);
    
public:

    void acceptResolution(::Ice::Int width, ::Ice::Int height)
    {
        acceptResolution(width, height, 0);
    }
    void acceptResolution(::Ice::Int width, ::Ice::Int height, const ::Ice::Context& __ctx)
    {
        acceptResolution(width, height, &__ctx);
    }
    
private:

    void acceptResolution(::Ice::Int, ::Ice::Int, const ::Ice::Context*);
    
public:

    void acceptPeriod(::Ice::Double value)
    {
        acceptPeriod(value, 0);
    }
    void acceptPeriod(::Ice::Double value, const ::Ice::Context& __ctx)
    {
        acceptPeriod(value, &__ctx);
    }
    
private:

    void acceptPeriod(::Ice::Double, const ::Ice::Context*);
    
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

class CClient : virtual public ::IceProxy::Ice::Object
{
public:

    ::Client::CChatPrx chat()
    {
        return chat(0);
    }
    ::Client::CChatPrx chat(const ::Ice::Context& __ctx)
    {
        return chat(&__ctx);
    }
    
private:

    ::Client::CChatPrx chat(const ::Ice::Context*);
    
public:

    ::Client::CMotoPrx moto()
    {
        return moto(0);
    }
    ::Client::CMotoPrx moto(const ::Ice::Context& __ctx)
    {
        return moto(&__ctx);
    }
    
private:

    ::Client::CMotoPrx moto(const ::Ice::Context*);
    
public:

    ::Client::CCamPrx cam()
    {
        return cam(0);
    }
    ::Client::CCamPrx cam(const ::Ice::Context& __ctx)
    {
        return cam(&__ctx);
    }
    
private:

    ::Client::CCamPrx cam(const ::Ice::Context*);
    
public:
    
    ::IceInternal::ProxyHandle<CClient> ice_context(const ::Ice::Context& __context) const
    {
        return dynamic_cast<CClient*>(::IceProxy::Ice::Object::ice_context(__context).get());
    }
    
    ::IceInternal::ProxyHandle<CClient> ice_secure(bool __secure) const
    {
        return dynamic_cast<CClient*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    }
    
#ifdef ICEE_HAS_ROUTER
    ::IceInternal::ProxyHandle<CClient> ice_router(const ::Ice::RouterPrx& __router) const
    {
        return dynamic_cast<CClient*>(::IceProxy::Ice::Object::ice_router(__router).get());
    }
#endif // ICEE_HAS_ROUTER
    
#ifdef ICEE_HAS_LOCATOR
    ::IceInternal::ProxyHandle<CClient> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
        return dynamic_cast<CClient*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    }
    
    ::IceInternal::ProxyHandle<CClient> ice_adapterId(const std::string& __id) const
    {
        return dynamic_cast<CClient*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    }
#endif // ICEE_HAS_LOCATOR
    
    ::IceInternal::ProxyHandle<CClient> ice_twoway() const
    {
        return dynamic_cast<CClient*>(::IceProxy::Ice::Object::ice_twoway().get());
    }
    
    ::IceInternal::ProxyHandle<CClient> ice_oneway() const
    {
        return dynamic_cast<CClient*>(::IceProxy::Ice::Object::ice_oneway().get());
    }
    
    ::IceInternal::ProxyHandle<CClient> ice_batchOneway() const
    {
        return dynamic_cast<CClient*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    }
    
    ::IceInternal::ProxyHandle<CClient> ice_datagram() const
    {
        return dynamic_cast<CClient*>(::IceProxy::Ice::Object::ice_datagram().get());
    }
    
    ::IceInternal::ProxyHandle<CClient> ice_batchDatagram() const
    {
        return dynamic_cast<CClient*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    }
    
    ::IceInternal::ProxyHandle<CClient> ice_timeout(int __timeout) const
    {
        return dynamic_cast<CClient*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    }
    
    static const ::std::string& ice_staticId();
    
private:
    
    virtual ::IceProxy::Ice::Object* __newInstance() const;
};

}

}

#endif
