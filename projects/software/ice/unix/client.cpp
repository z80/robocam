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

#include <client.h>
#include <IceE/LocalException.h>
#include <IceE/ObjectFactory.h>
#include <IceE/BasicStream.h>
#include <IceE/Iterator.h>

#ifndef ICEE_IGNORE_VERSION
#   if ICEE_INT_VERSION / 100 != 103
#       error IceE version mismatch!
#   endif
#   if ICEE_INT_VERSION % 100 < 0
#       error IceE patch level mismatch!
#   endif
#endif

static const ::std::string __Client__CChat__acceptMessage_name = "acceptMessage";

static const ::std::string __Client__CChat__acceptClientList_name = "acceptClientList";

static const ::std::string __Client__CMoto__acceptMotoEn_name = "acceptMotoEn";

static const ::std::string __Client__CMoto__acceptMoto_name = "acceptMoto";

static const ::std::string __Client__CMoto__acceptServoEn_name = "acceptServoEn";

static const ::std::string __Client__CMoto__acceptServo_name = "acceptServo";

static const ::std::string __Client__CCam__acceptImage_name = "acceptImage";

static const ::std::string __Client__CCam__acceptResolution_name = "acceptResolution";

static const ::std::string __Client__CCam__acceptPeriod_name = "acceptPeriod";

static const ::std::string __Client__CClient__chat_name = "chat";

static const ::std::string __Client__CClient__moto_name = "moto";

static const ::std::string __Client__CClient__cam_name = "cam";

::Ice::Object* IceInternal::upCast(::Client::CChat* p) { return p; }
::IceProxy::Ice::Object* IceInternal::upCast(::IceProxy::Client::CChat* p) { return p; }

::Ice::Object* IceInternal::upCast(::Client::CMoto* p) { return p; }
::IceProxy::Ice::Object* IceInternal::upCast(::IceProxy::Client::CMoto* p) { return p; }

::Ice::Object* IceInternal::upCast(::Client::CCam* p) { return p; }
::IceProxy::Ice::Object* IceInternal::upCast(::IceProxy::Client::CCam* p) { return p; }

::Ice::Object* IceInternal::upCast(::Client::CClient* p) { return p; }
::IceProxy::Ice::Object* IceInternal::upCast(::IceProxy::Client::CClient* p) { return p; }

void
Client::__read(::IceInternal::BasicStream* __is, ::Client::CChatPrx& v)
{
    ::Ice::ObjectPrx proxy;
    __is->read(proxy);
    if(!proxy)
    {
        v = 0;
    }
    else
    {
        v = new ::IceProxy::Client::CChat;
        v->__copyFrom(proxy);
    }
}

void
Client::__read(::IceInternal::BasicStream* __is, ::Client::CMotoPrx& v)
{
    ::Ice::ObjectPrx proxy;
    __is->read(proxy);
    if(!proxy)
    {
        v = 0;
    }
    else
    {
        v = new ::IceProxy::Client::CMoto;
        v->__copyFrom(proxy);
    }
}

void
Client::__read(::IceInternal::BasicStream* __is, ::Client::CCamPrx& v)
{
    ::Ice::ObjectPrx proxy;
    __is->read(proxy);
    if(!proxy)
    {
        v = 0;
    }
    else
    {
        v = new ::IceProxy::Client::CCam;
        v->__copyFrom(proxy);
    }
}

void
Client::__read(::IceInternal::BasicStream* __is, ::Client::CClientPrx& v)
{
    ::Ice::ObjectPrx proxy;
    __is->read(proxy);
    if(!proxy)
    {
        v = 0;
    }
    else
    {
        v = new ::IceProxy::Client::CClient;
        v->__copyFrom(proxy);
    }
}

static const ::std::string __Client__CChat_ids[2] =
{
    "::Client::CChat",
    "::Ice::Object"
};

bool
Client::CChat::ice_isA(const ::std::string& _s, const ::Ice::Current&) const
{
    return ::std::binary_search(__Client__CChat_ids, __Client__CChat_ids + 2, _s);
}

::std::vector< ::std::string>
Client::CChat::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&__Client__CChat_ids[0], &__Client__CChat_ids[2]);
}

const ::std::string&
Client::CChat::ice_id(const ::Ice::Current&) const
{
    return __Client__CChat_ids[0];
}

const ::std::string&
Client::CChat::ice_staticId()
{
    return __Client__CChat_ids[0];
}

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Client::CChat::___acceptMessage(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::std::string stri;
    __is->read(stri);
    acceptMessage(stri, __current);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Client::CChat::___acceptClientList(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::Types::TStringArray list;
    ::std::string driverNickname;
    __is->read(list);
    __is->read(driverNickname);
    acceptClientList(list, driverNickname, __current);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
static ::std::string __Client__CChat_all[] =
{
    "acceptClientList",
    "acceptMessage",
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping"
};

::Ice::DispatchStatus
Client::CChat::__dispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair< ::std::string*, ::std::string*> r = ::std::equal_range(__Client__CChat_all, __Client__CChat_all + 6, current.operation);
    if(r.first == r.second)
    {
        throw Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
    }

    switch(r.first - __Client__CChat_all)
    {
        case 0:
        {
            return ___acceptClientList(in, current);
        }
        case 1:
        {
            return ___acceptMessage(in, current);
        }
        case 2:
        {
            return ___ice_id(in, current);
        }
        case 3:
        {
            return ___ice_ids(in, current);
        }
        case 4:
        {
            return ___ice_isA(in, current);
        }
        case 5:
        {
            return ___ice_ping(in, current);
        }
    }

    assert(false);
    throw Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
}
#endif // ICEE_PURE_CLIENT

void
Client::CChat::__write(::IceInternal::BasicStream* __os) const
{
    __os->writeTypeId(ice_staticId());
    __os->startWriteSlice();
    __os->endWriteSlice();
    ::Ice::Object::__write(__os);
}

void
Client::CChat::__read(::IceInternal::BasicStream* __is, bool __rid)
{
    if(__rid)
    {
        ::std::string myId;
        __is->readTypeId(myId);
    }
    __is->startReadSlice();
    __is->endReadSlice();
    ::Ice::Object::__read(__is, true);
}


bool
Client::operator==(const ::Client::CChat& l, const ::Client::CChat& r)
{
    return static_cast<const ::Ice::Object&>(l) == static_cast<const ::Ice::Object&>(r);
}

bool
Client::operator<(const ::Client::CChat& l, const ::Client::CChat& r)
{
    return static_cast<const ::Ice::Object&>(l) < static_cast<const ::Ice::Object&>(r);
}

void 
Client::__patch__CChatPtr(void* __addr, ::Ice::ObjectPtr& v)
{
    ::Client::CChatPtr* p = static_cast< ::Client::CChatPtr*>(__addr);
    assert(p);
    *p = ::Client::CChatPtr::dynamicCast(v);
    if(v && !*p)
    {
        IceInternal::Ex::throwUOE(::Client::CChat::ice_staticId(), v->ice_id());
    }
}

static const ::std::string __Client__CMoto_ids[2] =
{
    "::Client::CMoto",
    "::Ice::Object"
};

bool
Client::CMoto::ice_isA(const ::std::string& _s, const ::Ice::Current&) const
{
    return ::std::binary_search(__Client__CMoto_ids, __Client__CMoto_ids + 2, _s);
}

::std::vector< ::std::string>
Client::CMoto::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&__Client__CMoto_ids[0], &__Client__CMoto_ids[2]);
}

const ::std::string&
Client::CMoto::ice_id(const ::Ice::Current&) const
{
    return __Client__CMoto_ids[0];
}

const ::std::string&
Client::CMoto::ice_staticId()
{
    return __Client__CMoto_ids[0];
}

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Client::CMoto::___acceptMotoEn(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    bool en;
    __is->read(en);
    acceptMotoEn(en, __current);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Client::CMoto::___acceptMoto(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::Ice::Int dir1;
    ::Ice::Int dir2;
    __is->read(dir1);
    __is->read(dir2);
    acceptMoto(dir1, dir2, __current);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Client::CMoto::___acceptServoEn(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    bool en;
    __is->read(en);
    acceptServoEn(en, __current);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Client::CMoto::___acceptServo(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::Ice::Double servo1;
    ::Ice::Double servo2;
    __is->read(servo1);
    __is->read(servo2);
    acceptServo(servo1, servo2, __current);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
static ::std::string __Client__CMoto_all[] =
{
    "acceptMoto",
    "acceptMotoEn",
    "acceptServo",
    "acceptServoEn",
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping"
};

::Ice::DispatchStatus
Client::CMoto::__dispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair< ::std::string*, ::std::string*> r = ::std::equal_range(__Client__CMoto_all, __Client__CMoto_all + 8, current.operation);
    if(r.first == r.second)
    {
        throw Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
    }

    switch(r.first - __Client__CMoto_all)
    {
        case 0:
        {
            return ___acceptMoto(in, current);
        }
        case 1:
        {
            return ___acceptMotoEn(in, current);
        }
        case 2:
        {
            return ___acceptServo(in, current);
        }
        case 3:
        {
            return ___acceptServoEn(in, current);
        }
        case 4:
        {
            return ___ice_id(in, current);
        }
        case 5:
        {
            return ___ice_ids(in, current);
        }
        case 6:
        {
            return ___ice_isA(in, current);
        }
        case 7:
        {
            return ___ice_ping(in, current);
        }
    }

    assert(false);
    throw Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
}
#endif // ICEE_PURE_CLIENT

void
Client::CMoto::__write(::IceInternal::BasicStream* __os) const
{
    __os->writeTypeId(ice_staticId());
    __os->startWriteSlice();
    __os->endWriteSlice();
    ::Ice::Object::__write(__os);
}

void
Client::CMoto::__read(::IceInternal::BasicStream* __is, bool __rid)
{
    if(__rid)
    {
        ::std::string myId;
        __is->readTypeId(myId);
    }
    __is->startReadSlice();
    __is->endReadSlice();
    ::Ice::Object::__read(__is, true);
}


bool
Client::operator==(const ::Client::CMoto& l, const ::Client::CMoto& r)
{
    return static_cast<const ::Ice::Object&>(l) == static_cast<const ::Ice::Object&>(r);
}

bool
Client::operator<(const ::Client::CMoto& l, const ::Client::CMoto& r)
{
    return static_cast<const ::Ice::Object&>(l) < static_cast<const ::Ice::Object&>(r);
}

void 
Client::__patch__CMotoPtr(void* __addr, ::Ice::ObjectPtr& v)
{
    ::Client::CMotoPtr* p = static_cast< ::Client::CMotoPtr*>(__addr);
    assert(p);
    *p = ::Client::CMotoPtr::dynamicCast(v);
    if(v && !*p)
    {
        IceInternal::Ex::throwUOE(::Client::CMoto::ice_staticId(), v->ice_id());
    }
}

static const ::std::string __Client__CCam_ids[2] =
{
    "::Client::CCam",
    "::Ice::Object"
};

bool
Client::CCam::ice_isA(const ::std::string& _s, const ::Ice::Current&) const
{
    return ::std::binary_search(__Client__CCam_ids, __Client__CCam_ids + 2, _s);
}

::std::vector< ::std::string>
Client::CCam::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&__Client__CCam_ids[0], &__Client__CCam_ids[2]);
}

const ::std::string&
Client::CCam::ice_id(const ::Ice::Current&) const
{
    return __Client__CCam_ids[0];
}

const ::std::string&
Client::CCam::ice_staticId()
{
    return __Client__CCam_ids[0];
}

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Client::CCam::___acceptImage(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::Types::TByteArray image;
    ::std::pair<const ::Ice::Byte*, const ::Ice::Byte*> ___image;
    __is->read(___image);
    ::std::vector< ::Ice::Byte>(___image.first, ___image.second).swap(image);
    acceptImage(image, __current);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Client::CCam::___acceptResolution(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::Ice::Int width;
    ::Ice::Int height;
    __is->read(width);
    __is->read(height);
    acceptResolution(width, height, __current);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Client::CCam::___acceptPeriod(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::Ice::Double value;
    __is->read(value);
    acceptPeriod(value, __current);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
static ::std::string __Client__CCam_all[] =
{
    "acceptImage",
    "acceptPeriod",
    "acceptResolution",
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping"
};

::Ice::DispatchStatus
Client::CCam::__dispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair< ::std::string*, ::std::string*> r = ::std::equal_range(__Client__CCam_all, __Client__CCam_all + 7, current.operation);
    if(r.first == r.second)
    {
        throw Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
    }

    switch(r.first - __Client__CCam_all)
    {
        case 0:
        {
            return ___acceptImage(in, current);
        }
        case 1:
        {
            return ___acceptPeriod(in, current);
        }
        case 2:
        {
            return ___acceptResolution(in, current);
        }
        case 3:
        {
            return ___ice_id(in, current);
        }
        case 4:
        {
            return ___ice_ids(in, current);
        }
        case 5:
        {
            return ___ice_isA(in, current);
        }
        case 6:
        {
            return ___ice_ping(in, current);
        }
    }

    assert(false);
    throw Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
}
#endif // ICEE_PURE_CLIENT

void
Client::CCam::__write(::IceInternal::BasicStream* __os) const
{
    __os->writeTypeId(ice_staticId());
    __os->startWriteSlice();
    __os->endWriteSlice();
    ::Ice::Object::__write(__os);
}

void
Client::CCam::__read(::IceInternal::BasicStream* __is, bool __rid)
{
    if(__rid)
    {
        ::std::string myId;
        __is->readTypeId(myId);
    }
    __is->startReadSlice();
    __is->endReadSlice();
    ::Ice::Object::__read(__is, true);
}


bool
Client::operator==(const ::Client::CCam& l, const ::Client::CCam& r)
{
    return static_cast<const ::Ice::Object&>(l) == static_cast<const ::Ice::Object&>(r);
}

bool
Client::operator<(const ::Client::CCam& l, const ::Client::CCam& r)
{
    return static_cast<const ::Ice::Object&>(l) < static_cast<const ::Ice::Object&>(r);
}

void 
Client::__patch__CCamPtr(void* __addr, ::Ice::ObjectPtr& v)
{
    ::Client::CCamPtr* p = static_cast< ::Client::CCamPtr*>(__addr);
    assert(p);
    *p = ::Client::CCamPtr::dynamicCast(v);
    if(v && !*p)
    {
        IceInternal::Ex::throwUOE(::Client::CCam::ice_staticId(), v->ice_id());
    }
}

static const ::std::string __Client__CClient_ids[2] =
{
    "::Client::CClient",
    "::Ice::Object"
};

bool
Client::CClient::ice_isA(const ::std::string& _s, const ::Ice::Current&) const
{
    return ::std::binary_search(__Client__CClient_ids, __Client__CClient_ids + 2, _s);
}

::std::vector< ::std::string>
Client::CClient::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&__Client__CClient_ids[0], &__Client__CClient_ids[2]);
}

const ::std::string&
Client::CClient::ice_id(const ::Ice::Current&) const
{
    return __Client__CClient_ids[0];
}

const ::std::string&
Client::CClient::ice_staticId()
{
    return __Client__CClient_ids[0];
}

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Client::CClient::___chat(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    ::Client::CChatPrx __ret = chat(__current);
    __os->write(::Ice::ObjectPrx(::IceInternal::upCast(__ret.get())));
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Client::CClient::___moto(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    ::Client::CMotoPrx __ret = moto(__current);
    __os->write(::Ice::ObjectPrx(::IceInternal::upCast(__ret.get())));
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Client::CClient::___cam(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    ::Client::CCamPrx __ret = cam(__current);
    __os->write(::Ice::ObjectPrx(::IceInternal::upCast(__ret.get())));
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
static ::std::string __Client__CClient_all[] =
{
    "cam",
    "chat",
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping",
    "moto"
};

::Ice::DispatchStatus
Client::CClient::__dispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair< ::std::string*, ::std::string*> r = ::std::equal_range(__Client__CClient_all, __Client__CClient_all + 7, current.operation);
    if(r.first == r.second)
    {
        throw Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
    }

    switch(r.first - __Client__CClient_all)
    {
        case 0:
        {
            return ___cam(in, current);
        }
        case 1:
        {
            return ___chat(in, current);
        }
        case 2:
        {
            return ___ice_id(in, current);
        }
        case 3:
        {
            return ___ice_ids(in, current);
        }
        case 4:
        {
            return ___ice_isA(in, current);
        }
        case 5:
        {
            return ___ice_ping(in, current);
        }
        case 6:
        {
            return ___moto(in, current);
        }
    }

    assert(false);
    throw Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
}
#endif // ICEE_PURE_CLIENT

void
Client::CClient::__write(::IceInternal::BasicStream* __os) const
{
    __os->writeTypeId(ice_staticId());
    __os->startWriteSlice();
    __os->endWriteSlice();
    ::Ice::Object::__write(__os);
}

void
Client::CClient::__read(::IceInternal::BasicStream* __is, bool __rid)
{
    if(__rid)
    {
        ::std::string myId;
        __is->readTypeId(myId);
    }
    __is->startReadSlice();
    __is->endReadSlice();
    ::Ice::Object::__read(__is, true);
}


bool
Client::operator==(const ::Client::CClient& l, const ::Client::CClient& r)
{
    return static_cast<const ::Ice::Object&>(l) == static_cast<const ::Ice::Object&>(r);
}

bool
Client::operator<(const ::Client::CClient& l, const ::Client::CClient& r)
{
    return static_cast<const ::Ice::Object&>(l) < static_cast<const ::Ice::Object&>(r);
}

void 
Client::__patch__CClientPtr(void* __addr, ::Ice::ObjectPtr& v)
{
    ::Client::CClientPtr* p = static_cast< ::Client::CClientPtr*>(__addr);
    assert(p);
    *p = ::Client::CClientPtr::dynamicCast(v);
    if(v && !*p)
    {
        IceInternal::Ex::throwUOE(::Client::CClient::ice_staticId(), v->ice_id());
    }
}

void
IceProxy::Client::CChat::acceptMessage(const ::std::string& stri, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Client__CChat__acceptMessage_name, ::Ice::Normal, __ctx);
            try
            {
                ::IceInternal::BasicStream* __os = __outS.os();
                __os->write(stri);
            }
            catch(const ::Ice::LocalException& __ex)
            {
                __outS.abort(__ex);
            }
            bool __ok = __outS.invoke();
            try
            {
                if(!__ok)
                {
                    __outS.is()->throwUnknownUserException();
                }
            }
            catch(const ::Ice::LocalException& __ex)
            {
                throw ::IceInternal::LocalExceptionWrapper(__ex, false);
            }
#if defined(_MSC_VER) && defined(_M_ARM) // ARM bug.
            catch(...)
            {
                throw;
            }
#endif
            return;
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__handler, __ex);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__handler, __ex, __cnt);
        }
#if defined(_MSC_VER) && defined(_M_ARM) // ARM bug.
        catch(...)
        {
            throw;
        }
#endif
    }
}

void
IceProxy::Client::CChat::acceptClientList(const ::Types::TStringArray& list, const ::std::string& driverNickname, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Client__CChat__acceptClientList_name, ::Ice::Normal, __ctx);
            try
            {
                ::IceInternal::BasicStream* __os = __outS.os();
                if(list.size() == 0)
                {
                    __os->writeSize(0);
                }
                else
                {
                    __os->write(&list[0], &list[0] + list.size());
                }
                __os->write(driverNickname);
            }
            catch(const ::Ice::LocalException& __ex)
            {
                __outS.abort(__ex);
            }
            bool __ok = __outS.invoke();
            try
            {
                if(!__ok)
                {
                    __outS.is()->throwUnknownUserException();
                }
            }
            catch(const ::Ice::LocalException& __ex)
            {
                throw ::IceInternal::LocalExceptionWrapper(__ex, false);
            }
#if defined(_MSC_VER) && defined(_M_ARM) // ARM bug.
            catch(...)
            {
                throw;
            }
#endif
            return;
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__handler, __ex);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__handler, __ex, __cnt);
        }
#if defined(_MSC_VER) && defined(_M_ARM) // ARM bug.
        catch(...)
        {
            throw;
        }
#endif
    }
}

const ::std::string&
IceProxy::Client::CChat::ice_staticId()
{
    return __Client__CChat_ids[0];
}

::IceProxy::Ice::Object*
IceProxy::Client::CChat::__newInstance() const
{
    return new CChat;
}

void
IceProxy::Client::CMoto::acceptMotoEn(bool en, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Client__CMoto__acceptMotoEn_name, ::Ice::Normal, __ctx);
            try
            {
                ::IceInternal::BasicStream* __os = __outS.os();
                __os->write(en);
            }
            catch(const ::Ice::LocalException& __ex)
            {
                __outS.abort(__ex);
            }
            bool __ok = __outS.invoke();
            try
            {
                if(!__ok)
                {
                    __outS.is()->throwUnknownUserException();
                }
            }
            catch(const ::Ice::LocalException& __ex)
            {
                throw ::IceInternal::LocalExceptionWrapper(__ex, false);
            }
#if defined(_MSC_VER) && defined(_M_ARM) // ARM bug.
            catch(...)
            {
                throw;
            }
#endif
            return;
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__handler, __ex);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__handler, __ex, __cnt);
        }
#if defined(_MSC_VER) && defined(_M_ARM) // ARM bug.
        catch(...)
        {
            throw;
        }
#endif
    }
}

void
IceProxy::Client::CMoto::acceptMoto(::Ice::Int dir1, ::Ice::Int dir2, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Client__CMoto__acceptMoto_name, ::Ice::Normal, __ctx);
            try
            {
                ::IceInternal::BasicStream* __os = __outS.os();
                __os->write(dir1);
                __os->write(dir2);
            }
            catch(const ::Ice::LocalException& __ex)
            {
                __outS.abort(__ex);
            }
            bool __ok = __outS.invoke();
            try
            {
                if(!__ok)
                {
                    __outS.is()->throwUnknownUserException();
                }
            }
            catch(const ::Ice::LocalException& __ex)
            {
                throw ::IceInternal::LocalExceptionWrapper(__ex, false);
            }
#if defined(_MSC_VER) && defined(_M_ARM) // ARM bug.
            catch(...)
            {
                throw;
            }
#endif
            return;
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__handler, __ex);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__handler, __ex, __cnt);
        }
#if defined(_MSC_VER) && defined(_M_ARM) // ARM bug.
        catch(...)
        {
            throw;
        }
#endif
    }
}

void
IceProxy::Client::CMoto::acceptServoEn(bool en, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Client__CMoto__acceptServoEn_name, ::Ice::Normal, __ctx);
            try
            {
                ::IceInternal::BasicStream* __os = __outS.os();
                __os->write(en);
            }
            catch(const ::Ice::LocalException& __ex)
            {
                __outS.abort(__ex);
            }
            bool __ok = __outS.invoke();
            try
            {
                if(!__ok)
                {
                    __outS.is()->throwUnknownUserException();
                }
            }
            catch(const ::Ice::LocalException& __ex)
            {
                throw ::IceInternal::LocalExceptionWrapper(__ex, false);
            }
#if defined(_MSC_VER) && defined(_M_ARM) // ARM bug.
            catch(...)
            {
                throw;
            }
#endif
            return;
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__handler, __ex);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__handler, __ex, __cnt);
        }
#if defined(_MSC_VER) && defined(_M_ARM) // ARM bug.
        catch(...)
        {
            throw;
        }
#endif
    }
}

void
IceProxy::Client::CMoto::acceptServo(::Ice::Double servo1, ::Ice::Double servo2, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Client__CMoto__acceptServo_name, ::Ice::Normal, __ctx);
            try
            {
                ::IceInternal::BasicStream* __os = __outS.os();
                __os->write(servo1);
                __os->write(servo2);
            }
            catch(const ::Ice::LocalException& __ex)
            {
                __outS.abort(__ex);
            }
            bool __ok = __outS.invoke();
            try
            {
                if(!__ok)
                {
                    __outS.is()->throwUnknownUserException();
                }
            }
            catch(const ::Ice::LocalException& __ex)
            {
                throw ::IceInternal::LocalExceptionWrapper(__ex, false);
            }
#if defined(_MSC_VER) && defined(_M_ARM) // ARM bug.
            catch(...)
            {
                throw;
            }
#endif
            return;
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__handler, __ex);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__handler, __ex, __cnt);
        }
#if defined(_MSC_VER) && defined(_M_ARM) // ARM bug.
        catch(...)
        {
            throw;
        }
#endif
    }
}

const ::std::string&
IceProxy::Client::CMoto::ice_staticId()
{
    return __Client__CMoto_ids[0];
}

::IceProxy::Ice::Object*
IceProxy::Client::CMoto::__newInstance() const
{
    return new CMoto;
}

void
IceProxy::Client::CCam::acceptImage(const ::Types::TByteArray& image, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Client__CCam__acceptImage_name, ::Ice::Normal, __ctx);
            try
            {
                ::IceInternal::BasicStream* __os = __outS.os();
                if(image.size() == 0)
                {
                    __os->writeSize(0);
                }
                else
                {
                    __os->write(&image[0], &image[0] + image.size());
                }
            }
            catch(const ::Ice::LocalException& __ex)
            {
                __outS.abort(__ex);
            }
            bool __ok = __outS.invoke();
            try
            {
                if(!__ok)
                {
                    __outS.is()->throwUnknownUserException();
                }
            }
            catch(const ::Ice::LocalException& __ex)
            {
                throw ::IceInternal::LocalExceptionWrapper(__ex, false);
            }
#if defined(_MSC_VER) && defined(_M_ARM) // ARM bug.
            catch(...)
            {
                throw;
            }
#endif
            return;
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__handler, __ex);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__handler, __ex, __cnt);
        }
#if defined(_MSC_VER) && defined(_M_ARM) // ARM bug.
        catch(...)
        {
            throw;
        }
#endif
    }
}

void
IceProxy::Client::CCam::acceptResolution(::Ice::Int width, ::Ice::Int height, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Client__CCam__acceptResolution_name, ::Ice::Normal, __ctx);
            try
            {
                ::IceInternal::BasicStream* __os = __outS.os();
                __os->write(width);
                __os->write(height);
            }
            catch(const ::Ice::LocalException& __ex)
            {
                __outS.abort(__ex);
            }
            bool __ok = __outS.invoke();
            try
            {
                if(!__ok)
                {
                    __outS.is()->throwUnknownUserException();
                }
            }
            catch(const ::Ice::LocalException& __ex)
            {
                throw ::IceInternal::LocalExceptionWrapper(__ex, false);
            }
#if defined(_MSC_VER) && defined(_M_ARM) // ARM bug.
            catch(...)
            {
                throw;
            }
#endif
            return;
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__handler, __ex);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__handler, __ex, __cnt);
        }
#if defined(_MSC_VER) && defined(_M_ARM) // ARM bug.
        catch(...)
        {
            throw;
        }
#endif
    }
}

void
IceProxy::Client::CCam::acceptPeriod(::Ice::Double value, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Client__CCam__acceptPeriod_name, ::Ice::Normal, __ctx);
            try
            {
                ::IceInternal::BasicStream* __os = __outS.os();
                __os->write(value);
            }
            catch(const ::Ice::LocalException& __ex)
            {
                __outS.abort(__ex);
            }
            bool __ok = __outS.invoke();
            try
            {
                if(!__ok)
                {
                    __outS.is()->throwUnknownUserException();
                }
            }
            catch(const ::Ice::LocalException& __ex)
            {
                throw ::IceInternal::LocalExceptionWrapper(__ex, false);
            }
#if defined(_MSC_VER) && defined(_M_ARM) // ARM bug.
            catch(...)
            {
                throw;
            }
#endif
            return;
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__handler, __ex);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__handler, __ex, __cnt);
        }
#if defined(_MSC_VER) && defined(_M_ARM) // ARM bug.
        catch(...)
        {
            throw;
        }
#endif
    }
}

const ::std::string&
IceProxy::Client::CCam::ice_staticId()
{
    return __Client__CCam_ids[0];
}

::IceProxy::Ice::Object*
IceProxy::Client::CCam::__newInstance() const
{
    return new CCam;
}

::Client::CChatPrx
IceProxy::Client::CClient::chat(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __checkTwowayOnly(__Client__CClient__chat_name);
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Client__CClient__chat_name, ::Ice::Normal, __ctx);
            bool __ok = __outS.invoke();
            try
            {
                if(!__ok)
                {
                    __outS.is()->throwUnknownUserException();
                }
                ::Client::CChatPrx __ret;
                ::IceInternal::BasicStream* __is = __outS.is();
                ::Client::__read(__is, __ret);
                return __ret;
            }
            catch(const ::Ice::LocalException& __ex)
            {
                throw ::IceInternal::LocalExceptionWrapper(__ex, false);
            }
#if defined(_MSC_VER) && defined(_M_ARM) // ARM bug.
            catch(...)
            {
                throw;
            }
#endif
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__handler, __ex);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__handler, __ex, __cnt);
        }
#if defined(_MSC_VER) && defined(_M_ARM) // ARM bug.
        catch(...)
        {
            throw;
        }
#endif
    }
}

::Client::CMotoPrx
IceProxy::Client::CClient::moto(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __checkTwowayOnly(__Client__CClient__moto_name);
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Client__CClient__moto_name, ::Ice::Normal, __ctx);
            bool __ok = __outS.invoke();
            try
            {
                if(!__ok)
                {
                    __outS.is()->throwUnknownUserException();
                }
                ::Client::CMotoPrx __ret;
                ::IceInternal::BasicStream* __is = __outS.is();
                ::Client::__read(__is, __ret);
                return __ret;
            }
            catch(const ::Ice::LocalException& __ex)
            {
                throw ::IceInternal::LocalExceptionWrapper(__ex, false);
            }
#if defined(_MSC_VER) && defined(_M_ARM) // ARM bug.
            catch(...)
            {
                throw;
            }
#endif
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__handler, __ex);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__handler, __ex, __cnt);
        }
#if defined(_MSC_VER) && defined(_M_ARM) // ARM bug.
        catch(...)
        {
            throw;
        }
#endif
    }
}

::Client::CCamPrx
IceProxy::Client::CClient::cam(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __checkTwowayOnly(__Client__CClient__cam_name);
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Client__CClient__cam_name, ::Ice::Normal, __ctx);
            bool __ok = __outS.invoke();
            try
            {
                if(!__ok)
                {
                    __outS.is()->throwUnknownUserException();
                }
                ::Client::CCamPrx __ret;
                ::IceInternal::BasicStream* __is = __outS.is();
                ::Client::__read(__is, __ret);
                return __ret;
            }
            catch(const ::Ice::LocalException& __ex)
            {
                throw ::IceInternal::LocalExceptionWrapper(__ex, false);
            }
#if defined(_MSC_VER) && defined(_M_ARM) // ARM bug.
            catch(...)
            {
                throw;
            }
#endif
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__handler, __ex);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__handler, __ex, __cnt);
        }
#if defined(_MSC_VER) && defined(_M_ARM) // ARM bug.
        catch(...)
        {
            throw;
        }
#endif
    }
}

const ::std::string&
IceProxy::Client::CClient::ice_staticId()
{
    return __Client__CClient_ids[0];
}

::IceProxy::Ice::Object*
IceProxy::Client::CClient::__newInstance() const
{
    return new CClient;
}
