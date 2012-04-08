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

#include <host.h>
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

static const ::std::string __Host__CMoto__isOpen_name = "isOpen";

static const ::std::string __Host__CMoto__motoEn_name = "motoEn";

static const ::std::string __Host__CMoto__moto_name = "moto";

static const ::std::string __Host__CMoto__servoEn_name = "servoEn";

static const ::std::string __Host__CMoto__servo_name = "servo";

static const ::std::string __Host__CMoto__setMoto_name = "setMoto";

static const ::std::string __Host__CMoto__setServo_name = "setServo";

static const ::std::string __Host__CMoto__open_name = "open";

static const ::std::string __Host__CMoto__close_name = "close";

static const ::std::string __Host__CMoto__setMotoEn_name = "setMotoEn";

static const ::std::string __Host__CMoto__setServoEn_name = "setServoEn";

static const ::std::string __Host__CCam__isOpen_name = "isOpen";

static const ::std::string __Host__CCam__setResolution_name = "setResolution";

static const ::std::string __Host__CCam__resolution_name = "resolution";

static const ::std::string __Host__CCam__period_name = "period";

static const ::std::string __Host__CCam__image_name = "image";

static const ::std::string __Host__CCam__setReceiveImages_name = "setReceiveImages";

static const ::std::string __Host__CCam__receiveImages_name = "receiveImages";

static const ::std::string __Host__CCam__deviceName_name = "deviceName";

static const ::std::string __Host__CCam__setPeriod_name = "setPeriod";

static const ::std::string __Host__CCam__setDeviceName_name = "setDeviceName";

static const ::std::string __Host__CCam__open_name = "open";

static const ::std::string __Host__CCam__close_name = "close";

static const ::std::string __Host__CHost__registerClient_name = "registerClient";

static const ::std::string __Host__CHost__removeClient_name = "removeClient";

static const ::std::string __Host__CHost__postMessage_name = "postMessage";

static const ::std::string __Host__CHost__queryCtrl_name = "queryCtrl";

static const ::std::string __Host__CHost__querySuper_name = "querySuper";

static const ::std::string __Host__CHost__releaseCtrl_name = "releaseCtrl";

static const ::std::string __Host__CHost__cam_name = "cam";

static const ::std::string __Host__CHost__moto_name = "moto";

::Ice::Object* IceInternal::upCast(::Host::CMoto* p) { return p; }
::IceProxy::Ice::Object* IceInternal::upCast(::IceProxy::Host::CMoto* p) { return p; }

::Ice::Object* IceInternal::upCast(::Host::CCam* p) { return p; }
::IceProxy::Ice::Object* IceInternal::upCast(::IceProxy::Host::CCam* p) { return p; }

::Ice::Object* IceInternal::upCast(::Host::CHost* p) { return p; }
::IceProxy::Ice::Object* IceInternal::upCast(::IceProxy::Host::CHost* p) { return p; }

void
Host::__read(::IceInternal::BasicStream* __is, ::Host::CMotoPrx& v)
{
    ::Ice::ObjectPrx proxy;
    __is->read(proxy);
    if(!proxy)
    {
        v = 0;
    }
    else
    {
        v = new ::IceProxy::Host::CMoto;
        v->__copyFrom(proxy);
    }
}

void
Host::__read(::IceInternal::BasicStream* __is, ::Host::CCamPrx& v)
{
    ::Ice::ObjectPrx proxy;
    __is->read(proxy);
    if(!proxy)
    {
        v = 0;
    }
    else
    {
        v = new ::IceProxy::Host::CCam;
        v->__copyFrom(proxy);
    }
}

void
Host::__read(::IceInternal::BasicStream* __is, ::Host::CHostPrx& v)
{
    ::Ice::ObjectPrx proxy;
    __is->read(proxy);
    if(!proxy)
    {
        v = 0;
    }
    else
    {
        v = new ::IceProxy::Host::CHost;
        v->__copyFrom(proxy);
    }
}

static const ::std::string __Host__CMoto_ids[2] =
{
    "::Host::CMoto",
    "::Ice::Object"
};

bool
Host::CMoto::ice_isA(const ::std::string& _s, const ::Ice::Current&) const
{
    return ::std::binary_search(__Host__CMoto_ids, __Host__CMoto_ids + 2, _s);
}

::std::vector< ::std::string>
Host::CMoto::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&__Host__CMoto_ids[0], &__Host__CMoto_ids[2]);
}

const ::std::string&
Host::CMoto::ice_id(const ::Ice::Current&) const
{
    return __Host__CMoto_ids[0];
}

const ::std::string&
Host::CMoto::ice_staticId()
{
    return __Host__CMoto_ids[0];
}

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Host::CMoto::___isOpen(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Idempotent, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    bool __ret = isOpen(__current);
    __os->write(__ret);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Host::CMoto::___motoEn(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Idempotent, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    bool __ret = motoEn(__current);
    __os->write(__ret);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Host::CMoto::___moto(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Idempotent, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    ::Ice::Int dir1;
    ::Ice::Int dir2;
    moto(dir1, dir2, __current);
    __os->write(dir1);
    __os->write(dir2);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Host::CMoto::___servoEn(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Idempotent, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    bool __ret = servoEn(__current);
    __os->write(__ret);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Host::CMoto::___servo(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Idempotent, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    ::Ice::Double servo1;
    ::Ice::Double servo2;
    servo(servo1, servo2, __current);
    __os->write(servo1);
    __os->write(servo2);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Host::CMoto::___setMoto(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::Ice::Int dir1;
    ::Ice::Int dir2;
    ::Ice::Double period;
    __is->read(dir1);
    __is->read(dir2);
    __is->read(period);
    setMoto(dir1, dir2, period, __current);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Host::CMoto::___setServo(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::Ice::Double servo1;
    ::Ice::Double servo2;
    __is->read(servo1);
    __is->read(servo2);
    setServo(servo1, servo2, __current);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Host::CMoto::___open(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    bool __ret = open(__current);
    __os->write(__ret);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Host::CMoto::___close(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    close(__current);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Host::CMoto::___setMotoEn(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    bool en;
    __is->read(en);
    setMotoEn(en, __current);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Host::CMoto::___setServoEn(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    bool en;
    __is->read(en);
    setServoEn(en, __current);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
static ::std::string __Host__CMoto_all[] =
{
    "close",
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping",
    "isOpen",
    "moto",
    "motoEn",
    "open",
    "servo",
    "servoEn",
    "setMoto",
    "setMotoEn",
    "setServo",
    "setServoEn"
};

::Ice::DispatchStatus
Host::CMoto::__dispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair< ::std::string*, ::std::string*> r = ::std::equal_range(__Host__CMoto_all, __Host__CMoto_all + 15, current.operation);
    if(r.first == r.second)
    {
        throw Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
    }

    switch(r.first - __Host__CMoto_all)
    {
        case 0:
        {
            return ___close(in, current);
        }
        case 1:
        {
            return ___ice_id(in, current);
        }
        case 2:
        {
            return ___ice_ids(in, current);
        }
        case 3:
        {
            return ___ice_isA(in, current);
        }
        case 4:
        {
            return ___ice_ping(in, current);
        }
        case 5:
        {
            return ___isOpen(in, current);
        }
        case 6:
        {
            return ___moto(in, current);
        }
        case 7:
        {
            return ___motoEn(in, current);
        }
        case 8:
        {
            return ___open(in, current);
        }
        case 9:
        {
            return ___servo(in, current);
        }
        case 10:
        {
            return ___servoEn(in, current);
        }
        case 11:
        {
            return ___setMoto(in, current);
        }
        case 12:
        {
            return ___setMotoEn(in, current);
        }
        case 13:
        {
            return ___setServo(in, current);
        }
        case 14:
        {
            return ___setServoEn(in, current);
        }
    }

    assert(false);
    throw Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
}
#endif // ICEE_PURE_CLIENT

void
Host::CMoto::__write(::IceInternal::BasicStream* __os) const
{
    __os->writeTypeId(ice_staticId());
    __os->startWriteSlice();
    __os->endWriteSlice();
    ::Ice::Object::__write(__os);
}

void
Host::CMoto::__read(::IceInternal::BasicStream* __is, bool __rid)
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
Host::operator==(const ::Host::CMoto& l, const ::Host::CMoto& r)
{
    return static_cast<const ::Ice::Object&>(l) == static_cast<const ::Ice::Object&>(r);
}

bool
Host::operator<(const ::Host::CMoto& l, const ::Host::CMoto& r)
{
    return static_cast<const ::Ice::Object&>(l) < static_cast<const ::Ice::Object&>(r);
}

void 
Host::__patch__CMotoPtr(void* __addr, ::Ice::ObjectPtr& v)
{
    ::Host::CMotoPtr* p = static_cast< ::Host::CMotoPtr*>(__addr);
    assert(p);
    *p = ::Host::CMotoPtr::dynamicCast(v);
    if(v && !*p)
    {
        IceInternal::Ex::throwUOE(::Host::CMoto::ice_staticId(), v->ice_id());
    }
}

static const ::std::string __Host__CCam_ids[2] =
{
    "::Host::CCam",
    "::Ice::Object"
};

bool
Host::CCam::ice_isA(const ::std::string& _s, const ::Ice::Current&) const
{
    return ::std::binary_search(__Host__CCam_ids, __Host__CCam_ids + 2, _s);
}

::std::vector< ::std::string>
Host::CCam::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&__Host__CCam_ids[0], &__Host__CCam_ids[2]);
}

const ::std::string&
Host::CCam::ice_id(const ::Ice::Current&) const
{
    return __Host__CCam_ids[0];
}

const ::std::string&
Host::CCam::ice_staticId()
{
    return __Host__CCam_ids[0];
}

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Host::CCam::___isOpen(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Idempotent, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    bool __ret = isOpen(__current);
    __os->write(__ret);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Host::CCam::___setResolution(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::Ice::Int width;
    ::Ice::Int height;
    __is->read(width);
    __is->read(height);
    setResolution(width, height, __current);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Host::CCam::___resolution(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Idempotent, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    ::Ice::Int width;
    ::Ice::Int height;
    resolution(width, height, __current);
    __os->write(width);
    __os->write(height);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Host::CCam::___period(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Idempotent, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    ::Ice::Double __ret = period(__current);
    __os->write(__ret);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Host::CCam::___image(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Idempotent, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    ::Types::TByteArray data;
    bool __ret = image(data, __current);
    if(data.size() == 0)
    {
        __os->writeSize(0);
    }
    else
    {
        __os->write(&data[0], &data[0] + data.size());
    }
    __os->write(__ret);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Host::CCam::___setReceiveImages(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    bool en;
    __is->read(en);
    setReceiveImages(en, __current);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Host::CCam::___receiveImages(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Idempotent, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    bool __ret = receiveImages(__current);
    __os->write(__ret);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Host::CCam::___deviceName(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Idempotent, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    ::std::string __ret = deviceName(__current);
    __os->write(__ret);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Host::CCam::___setPeriod(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::Ice::Double period;
    __is->read(period);
    setPeriod(period, __current);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Host::CCam::___setDeviceName(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::std::string devName;
    __is->read(devName);
    setDeviceName(devName, __current);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Host::CCam::___open(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    bool __ret = open(__current);
    __os->write(__ret);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Host::CCam::___close(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    close(__current);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
static ::std::string __Host__CCam_all[] =
{
    "close",
    "deviceName",
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping",
    "image",
    "isOpen",
    "open",
    "period",
    "receiveImages",
    "resolution",
    "setDeviceName",
    "setPeriod",
    "setReceiveImages",
    "setResolution"
};

::Ice::DispatchStatus
Host::CCam::__dispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair< ::std::string*, ::std::string*> r = ::std::equal_range(__Host__CCam_all, __Host__CCam_all + 16, current.operation);
    if(r.first == r.second)
    {
        throw Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
    }

    switch(r.first - __Host__CCam_all)
    {
        case 0:
        {
            return ___close(in, current);
        }
        case 1:
        {
            return ___deviceName(in, current);
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
            return ___image(in, current);
        }
        case 7:
        {
            return ___isOpen(in, current);
        }
        case 8:
        {
            return ___open(in, current);
        }
        case 9:
        {
            return ___period(in, current);
        }
        case 10:
        {
            return ___receiveImages(in, current);
        }
        case 11:
        {
            return ___resolution(in, current);
        }
        case 12:
        {
            return ___setDeviceName(in, current);
        }
        case 13:
        {
            return ___setPeriod(in, current);
        }
        case 14:
        {
            return ___setReceiveImages(in, current);
        }
        case 15:
        {
            return ___setResolution(in, current);
        }
    }

    assert(false);
    throw Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
}
#endif // ICEE_PURE_CLIENT

void
Host::CCam::__write(::IceInternal::BasicStream* __os) const
{
    __os->writeTypeId(ice_staticId());
    __os->startWriteSlice();
    __os->endWriteSlice();
    ::Ice::Object::__write(__os);
}

void
Host::CCam::__read(::IceInternal::BasicStream* __is, bool __rid)
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
Host::operator==(const ::Host::CCam& l, const ::Host::CCam& r)
{
    return static_cast<const ::Ice::Object&>(l) == static_cast<const ::Ice::Object&>(r);
}

bool
Host::operator<(const ::Host::CCam& l, const ::Host::CCam& r)
{
    return static_cast<const ::Ice::Object&>(l) < static_cast<const ::Ice::Object&>(r);
}

void 
Host::__patch__CCamPtr(void* __addr, ::Ice::ObjectPtr& v)
{
    ::Host::CCamPtr* p = static_cast< ::Host::CCamPtr*>(__addr);
    assert(p);
    *p = ::Host::CCamPtr::dynamicCast(v);
    if(v && !*p)
    {
        IceInternal::Ex::throwUOE(::Host::CCam::ice_staticId(), v->ice_id());
    }
}

static const ::std::string __Host__CHost_ids[2] =
{
    "::Host::CHost",
    "::Ice::Object"
};

bool
Host::CHost::ice_isA(const ::std::string& _s, const ::Ice::Current&) const
{
    return ::std::binary_search(__Host__CHost_ids, __Host__CHost_ids + 2, _s);
}

::std::vector< ::std::string>
Host::CHost::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&__Host__CHost_ids[0], &__Host__CHost_ids[2]);
}

const ::std::string&
Host::CHost::ice_id(const ::Ice::Current&) const
{
    return __Host__CHost_ids[0];
}

const ::std::string&
Host::CHost::ice_staticId()
{
    return __Host__CHost_ids[0];
}

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Host::CHost::___registerClient(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::Client::CClientPrx client;
    ::std::string nickname;
    ::Client::__read(__is, client);
    __is->read(nickname);
    ::IceInternal::BasicStream* __os = __inS.os();
    ::std::string idOrErrMsg;
    bool __ret = registerClient(client, nickname, idOrErrMsg, __current);
    __os->write(idOrErrMsg);
    __os->write(__ret);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Host::CHost::___removeClient(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::std::string id;
    __is->read(id);
    removeClient(id, __current);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Host::CHost::___postMessage(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::std::string id;
    ::std::string stri;
    __is->read(id);
    __is->read(stri);
    postMessage(id, stri, __current);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Host::CHost::___queryCtrl(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::std::string id;
    __is->read(id);
    ::IceInternal::BasicStream* __os = __inS.os();
    bool __ret = queryCtrl(id, __current);
    __os->write(__ret);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Host::CHost::___querySuper(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::std::string id;
    ::std::string password;
    __is->read(id);
    __is->read(password);
    ::IceInternal::BasicStream* __os = __inS.os();
    bool __ret = querySuper(id, password, __current);
    __os->write(__ret);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Host::CHost::___releaseCtrl(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::std::string id;
    __is->read(id);
    releaseCtrl(id, __current);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Host::CHost::___cam(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::std::string id;
    __is->read(id);
    ::IceInternal::BasicStream* __os = __inS.os();
    ::Host::CCamPrx __ret = cam(id, __current);
    __os->write(::Ice::ObjectPrx(::IceInternal::upCast(__ret.get())));
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Host::CHost::___moto(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::std::string id;
    __is->read(id);
    ::IceInternal::BasicStream* __os = __inS.os();
    ::Host::CMotoPrx __ret = moto(id, __current);
    __os->write(::Ice::ObjectPrx(::IceInternal::upCast(__ret.get())));
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
static ::std::string __Host__CHost_all[] =
{
    "cam",
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping",
    "moto",
    "postMessage",
    "queryCtrl",
    "querySuper",
    "registerClient",
    "releaseCtrl",
    "removeClient"
};

::Ice::DispatchStatus
Host::CHost::__dispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair< ::std::string*, ::std::string*> r = ::std::equal_range(__Host__CHost_all, __Host__CHost_all + 12, current.operation);
    if(r.first == r.second)
    {
        throw Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
    }

    switch(r.first - __Host__CHost_all)
    {
        case 0:
        {
            return ___cam(in, current);
        }
        case 1:
        {
            return ___ice_id(in, current);
        }
        case 2:
        {
            return ___ice_ids(in, current);
        }
        case 3:
        {
            return ___ice_isA(in, current);
        }
        case 4:
        {
            return ___ice_ping(in, current);
        }
        case 5:
        {
            return ___moto(in, current);
        }
        case 6:
        {
            return ___postMessage(in, current);
        }
        case 7:
        {
            return ___queryCtrl(in, current);
        }
        case 8:
        {
            return ___querySuper(in, current);
        }
        case 9:
        {
            return ___registerClient(in, current);
        }
        case 10:
        {
            return ___releaseCtrl(in, current);
        }
        case 11:
        {
            return ___removeClient(in, current);
        }
    }

    assert(false);
    throw Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
}
#endif // ICEE_PURE_CLIENT

void
Host::CHost::__write(::IceInternal::BasicStream* __os) const
{
    __os->writeTypeId(ice_staticId());
    __os->startWriteSlice();
    __os->endWriteSlice();
    ::Ice::Object::__write(__os);
}

void
Host::CHost::__read(::IceInternal::BasicStream* __is, bool __rid)
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
Host::operator==(const ::Host::CHost& l, const ::Host::CHost& r)
{
    return static_cast<const ::Ice::Object&>(l) == static_cast<const ::Ice::Object&>(r);
}

bool
Host::operator<(const ::Host::CHost& l, const ::Host::CHost& r)
{
    return static_cast<const ::Ice::Object&>(l) < static_cast<const ::Ice::Object&>(r);
}

void 
Host::__patch__CHostPtr(void* __addr, ::Ice::ObjectPtr& v)
{
    ::Host::CHostPtr* p = static_cast< ::Host::CHostPtr*>(__addr);
    assert(p);
    *p = ::Host::CHostPtr::dynamicCast(v);
    if(v && !*p)
    {
        IceInternal::Ex::throwUOE(::Host::CHost::ice_staticId(), v->ice_id());
    }
}
#ifdef ICEE_HAS_AMI

bool
Host::AMI_CMoto_setMoto::__invoke(const ::Host::CMotoPrx& __prx, ::Ice::Int dir1, ::Ice::Int dir2, ::Ice::Double period, const ::Ice::Context* __ctx)
{
    __acquireCallback(__prx);
    try
    {
        __prepare(__prx, __Host__CMoto__setMoto_name, ::Ice::Normal, __ctx);
        __os->write(dir1);
        __os->write(dir2);
        __os->write(period);
        __os->endWriteEncaps();
        return __send();
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __releaseCallback(__ex);
        return false;
    }
#if defined(_MSC_VER) && defined(_M_ARM) // ARM bug.
    catch(...)
    {
        throw;
    }
#endif
}

void
Host::AMI_CMoto_setMoto::__response(bool __ok)
{
    try
    {
        if(!__ok)
        {
            __is->throwUnknownUserException();
        }
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __finished(__ex);
        return;
    }
#if defined(_MSC_VER) && defined(_M_ARM) // ARM bug.
    catch(...)
    {
        throw;
    }
#endif
    ice_response();
    __releaseCallback();
}
#endif
#ifdef ICEE_HAS_AMI

bool
Host::AMI_CMoto_setServo::__invoke(const ::Host::CMotoPrx& __prx, ::Ice::Double servo1, ::Ice::Double servo2, const ::Ice::Context* __ctx)
{
    __acquireCallback(__prx);
    try
    {
        __prepare(__prx, __Host__CMoto__setServo_name, ::Ice::Normal, __ctx);
        __os->write(servo1);
        __os->write(servo2);
        __os->endWriteEncaps();
        return __send();
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __releaseCallback(__ex);
        return false;
    }
#if defined(_MSC_VER) && defined(_M_ARM) // ARM bug.
    catch(...)
    {
        throw;
    }
#endif
}

void
Host::AMI_CMoto_setServo::__response(bool __ok)
{
    try
    {
        if(!__ok)
        {
            __is->throwUnknownUserException();
        }
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __finished(__ex);
        return;
    }
#if defined(_MSC_VER) && defined(_M_ARM) // ARM bug.
    catch(...)
    {
        throw;
    }
#endif
    ice_response();
    __releaseCallback();
}
#endif
#ifdef ICEE_HAS_AMI

bool
Host::AMI_CHost_postMessage::__invoke(const ::Host::CHostPrx& __prx, const ::std::string& id, const ::std::string& stri, const ::Ice::Context* __ctx)
{
    __acquireCallback(__prx);
    try
    {
        __prepare(__prx, __Host__CHost__postMessage_name, ::Ice::Normal, __ctx);
        __os->write(id);
        __os->write(stri);
        __os->endWriteEncaps();
        return __send();
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __releaseCallback(__ex);
        return false;
    }
#if defined(_MSC_VER) && defined(_M_ARM) // ARM bug.
    catch(...)
    {
        throw;
    }
#endif
}

void
Host::AMI_CHost_postMessage::__response(bool __ok)
{
    try
    {
        if(!__ok)
        {
            __is->throwUnknownUserException();
        }
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __finished(__ex);
        return;
    }
#if defined(_MSC_VER) && defined(_M_ARM) // ARM bug.
    catch(...)
    {
        throw;
    }
#endif
    ice_response();
    __releaseCallback();
}
#endif

bool
IceProxy::Host::CMoto::isOpen(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __checkTwowayOnly(__Host__CMoto__isOpen_name);
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Host__CMoto__isOpen_name, ::Ice::Idempotent, __ctx);
            bool __ok = __outS.invoke();
            try
            {
                if(!__ok)
                {
                    __outS.is()->throwUnknownUserException();
                }
                bool __ret;
                ::IceInternal::BasicStream* __is = __outS.is();
                __is->read(__ret);
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
            __handleExceptionWrapperRelaxed(__handler, __ex, __cnt);
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

bool
IceProxy::Host::CMoto::motoEn(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __checkTwowayOnly(__Host__CMoto__motoEn_name);
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Host__CMoto__motoEn_name, ::Ice::Idempotent, __ctx);
            bool __ok = __outS.invoke();
            try
            {
                if(!__ok)
                {
                    __outS.is()->throwUnknownUserException();
                }
                bool __ret;
                ::IceInternal::BasicStream* __is = __outS.is();
                __is->read(__ret);
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
            __handleExceptionWrapperRelaxed(__handler, __ex, __cnt);
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
IceProxy::Host::CMoto::moto(::Ice::Int& dir1, ::Ice::Int& dir2, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __checkTwowayOnly(__Host__CMoto__moto_name);
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Host__CMoto__moto_name, ::Ice::Idempotent, __ctx);
            bool __ok = __outS.invoke();
            try
            {
                if(!__ok)
                {
                    __outS.is()->throwUnknownUserException();
                }
                ::IceInternal::BasicStream* __is = __outS.is();
                __is->read(dir1);
                __is->read(dir2);
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
            __handleExceptionWrapperRelaxed(__handler, __ex, __cnt);
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

bool
IceProxy::Host::CMoto::servoEn(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __checkTwowayOnly(__Host__CMoto__servoEn_name);
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Host__CMoto__servoEn_name, ::Ice::Idempotent, __ctx);
            bool __ok = __outS.invoke();
            try
            {
                if(!__ok)
                {
                    __outS.is()->throwUnknownUserException();
                }
                bool __ret;
                ::IceInternal::BasicStream* __is = __outS.is();
                __is->read(__ret);
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
            __handleExceptionWrapperRelaxed(__handler, __ex, __cnt);
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
IceProxy::Host::CMoto::servo(::Ice::Double& servo1, ::Ice::Double& servo2, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __checkTwowayOnly(__Host__CMoto__servo_name);
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Host__CMoto__servo_name, ::Ice::Idempotent, __ctx);
            bool __ok = __outS.invoke();
            try
            {
                if(!__ok)
                {
                    __outS.is()->throwUnknownUserException();
                }
                ::IceInternal::BasicStream* __is = __outS.is();
                __is->read(servo1);
                __is->read(servo2);
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
            __handleExceptionWrapperRelaxed(__handler, __ex, __cnt);
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
IceProxy::Host::CMoto::setMoto(::Ice::Int dir1, ::Ice::Int dir2, ::Ice::Double period, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Host__CMoto__setMoto_name, ::Ice::Normal, __ctx);
            try
            {
                ::IceInternal::BasicStream* __os = __outS.os();
                __os->write(dir1);
                __os->write(dir2);
                __os->write(period);
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
#ifdef ICEE_HAS_AMI

bool
IceProxy::Host::CMoto::setMoto_async(const ::Host::AMI_CMoto_setMotoPtr& __cb, ::Ice::Int dir1, ::Ice::Int dir2, ::Ice::Double period)
{
    return __cb->__invoke(this, dir1, dir2, period, 0);
}

bool
IceProxy::Host::CMoto::setMoto_async(const ::Host::AMI_CMoto_setMotoPtr& __cb, ::Ice::Int dir1, ::Ice::Int dir2, ::Ice::Double period, const ::Ice::Context& __ctx)
{
    return __cb->__invoke(this, dir1, dir2, period, &__ctx);
}
#endif

void
IceProxy::Host::CMoto::setServo(::Ice::Double servo1, ::Ice::Double servo2, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Host__CMoto__setServo_name, ::Ice::Normal, __ctx);
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
#ifdef ICEE_HAS_AMI

bool
IceProxy::Host::CMoto::setServo_async(const ::Host::AMI_CMoto_setServoPtr& __cb, ::Ice::Double servo1, ::Ice::Double servo2)
{
    return __cb->__invoke(this, servo1, servo2, 0);
}

bool
IceProxy::Host::CMoto::setServo_async(const ::Host::AMI_CMoto_setServoPtr& __cb, ::Ice::Double servo1, ::Ice::Double servo2, const ::Ice::Context& __ctx)
{
    return __cb->__invoke(this, servo1, servo2, &__ctx);
}
#endif

bool
IceProxy::Host::CMoto::open(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __checkTwowayOnly(__Host__CMoto__open_name);
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Host__CMoto__open_name, ::Ice::Normal, __ctx);
            bool __ok = __outS.invoke();
            try
            {
                if(!__ok)
                {
                    __outS.is()->throwUnknownUserException();
                }
                bool __ret;
                ::IceInternal::BasicStream* __is = __outS.is();
                __is->read(__ret);
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

void
IceProxy::Host::CMoto::close(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Host__CMoto__close_name, ::Ice::Normal, __ctx);
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
IceProxy::Host::CMoto::setMotoEn(bool en, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Host__CMoto__setMotoEn_name, ::Ice::Normal, __ctx);
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
IceProxy::Host::CMoto::setServoEn(bool en, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Host__CMoto__setServoEn_name, ::Ice::Normal, __ctx);
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

const ::std::string&
IceProxy::Host::CMoto::ice_staticId()
{
    return __Host__CMoto_ids[0];
}

::IceProxy::Ice::Object*
IceProxy::Host::CMoto::__newInstance() const
{
    return new CMoto;
}

bool
IceProxy::Host::CCam::isOpen(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __checkTwowayOnly(__Host__CCam__isOpen_name);
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Host__CCam__isOpen_name, ::Ice::Idempotent, __ctx);
            bool __ok = __outS.invoke();
            try
            {
                if(!__ok)
                {
                    __outS.is()->throwUnknownUserException();
                }
                bool __ret;
                ::IceInternal::BasicStream* __is = __outS.is();
                __is->read(__ret);
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
            __handleExceptionWrapperRelaxed(__handler, __ex, __cnt);
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
IceProxy::Host::CCam::setResolution(::Ice::Int width, ::Ice::Int height, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Host__CCam__setResolution_name, ::Ice::Normal, __ctx);
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
IceProxy::Host::CCam::resolution(::Ice::Int& width, ::Ice::Int& height, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __checkTwowayOnly(__Host__CCam__resolution_name);
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Host__CCam__resolution_name, ::Ice::Idempotent, __ctx);
            bool __ok = __outS.invoke();
            try
            {
                if(!__ok)
                {
                    __outS.is()->throwUnknownUserException();
                }
                ::IceInternal::BasicStream* __is = __outS.is();
                __is->read(width);
                __is->read(height);
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
            __handleExceptionWrapperRelaxed(__handler, __ex, __cnt);
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

::Ice::Double
IceProxy::Host::CCam::period(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __checkTwowayOnly(__Host__CCam__period_name);
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Host__CCam__period_name, ::Ice::Idempotent, __ctx);
            bool __ok = __outS.invoke();
            try
            {
                if(!__ok)
                {
                    __outS.is()->throwUnknownUserException();
                }
                ::Ice::Double __ret;
                ::IceInternal::BasicStream* __is = __outS.is();
                __is->read(__ret);
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
            __handleExceptionWrapperRelaxed(__handler, __ex, __cnt);
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

bool
IceProxy::Host::CCam::image(::Types::TByteArray& data, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __checkTwowayOnly(__Host__CCam__image_name);
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Host__CCam__image_name, ::Ice::Idempotent, __ctx);
            bool __ok = __outS.invoke();
            try
            {
                if(!__ok)
                {
                    __outS.is()->throwUnknownUserException();
                }
                bool __ret;
                ::IceInternal::BasicStream* __is = __outS.is();
                ::std::pair<const ::Ice::Byte*, const ::Ice::Byte*> ___data;
                __is->read(___data);
                ::std::vector< ::Ice::Byte>(___data.first, ___data.second).swap(data);
                __is->read(__ret);
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
            __handleExceptionWrapperRelaxed(__handler, __ex, __cnt);
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
IceProxy::Host::CCam::setReceiveImages(bool en, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Host__CCam__setReceiveImages_name, ::Ice::Normal, __ctx);
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

bool
IceProxy::Host::CCam::receiveImages(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __checkTwowayOnly(__Host__CCam__receiveImages_name);
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Host__CCam__receiveImages_name, ::Ice::Idempotent, __ctx);
            bool __ok = __outS.invoke();
            try
            {
                if(!__ok)
                {
                    __outS.is()->throwUnknownUserException();
                }
                bool __ret;
                ::IceInternal::BasicStream* __is = __outS.is();
                __is->read(__ret);
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
            __handleExceptionWrapperRelaxed(__handler, __ex, __cnt);
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

::std::string
IceProxy::Host::CCam::deviceName(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __checkTwowayOnly(__Host__CCam__deviceName_name);
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Host__CCam__deviceName_name, ::Ice::Idempotent, __ctx);
            bool __ok = __outS.invoke();
            try
            {
                if(!__ok)
                {
                    __outS.is()->throwUnknownUserException();
                }
                ::std::string __ret;
                ::IceInternal::BasicStream* __is = __outS.is();
                __is->read(__ret);
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
            __handleExceptionWrapperRelaxed(__handler, __ex, __cnt);
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
IceProxy::Host::CCam::setPeriod(::Ice::Double period, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Host__CCam__setPeriod_name, ::Ice::Normal, __ctx);
            try
            {
                ::IceInternal::BasicStream* __os = __outS.os();
                __os->write(period);
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
IceProxy::Host::CCam::setDeviceName(const ::std::string& devName, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Host__CCam__setDeviceName_name, ::Ice::Normal, __ctx);
            try
            {
                ::IceInternal::BasicStream* __os = __outS.os();
                __os->write(devName);
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

bool
IceProxy::Host::CCam::open(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __checkTwowayOnly(__Host__CCam__open_name);
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Host__CCam__open_name, ::Ice::Normal, __ctx);
            bool __ok = __outS.invoke();
            try
            {
                if(!__ok)
                {
                    __outS.is()->throwUnknownUserException();
                }
                bool __ret;
                ::IceInternal::BasicStream* __is = __outS.is();
                __is->read(__ret);
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

void
IceProxy::Host::CCam::close(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Host__CCam__close_name, ::Ice::Normal, __ctx);
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
IceProxy::Host::CCam::ice_staticId()
{
    return __Host__CCam_ids[0];
}

::IceProxy::Ice::Object*
IceProxy::Host::CCam::__newInstance() const
{
    return new CCam;
}

bool
IceProxy::Host::CHost::registerClient(const ::Client::CClientPrx& client, const ::std::string& nickname, ::std::string& idOrErrMsg, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __checkTwowayOnly(__Host__CHost__registerClient_name);
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Host__CHost__registerClient_name, ::Ice::Normal, __ctx);
            try
            {
                ::IceInternal::BasicStream* __os = __outS.os();
                __os->write(::Ice::ObjectPrx(::IceInternal::upCast(client.get())));
                __os->write(nickname);
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
                bool __ret;
                ::IceInternal::BasicStream* __is = __outS.is();
                __is->read(idOrErrMsg);
                __is->read(__ret);
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

void
IceProxy::Host::CHost::removeClient(const ::std::string& id, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Host__CHost__removeClient_name, ::Ice::Normal, __ctx);
            try
            {
                ::IceInternal::BasicStream* __os = __outS.os();
                __os->write(id);
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
IceProxy::Host::CHost::postMessage(const ::std::string& id, const ::std::string& stri, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Host__CHost__postMessage_name, ::Ice::Normal, __ctx);
            try
            {
                ::IceInternal::BasicStream* __os = __outS.os();
                __os->write(id);
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
#ifdef ICEE_HAS_AMI

bool
IceProxy::Host::CHost::postMessage_async(const ::Host::AMI_CHost_postMessagePtr& __cb, const ::std::string& id, const ::std::string& stri)
{
    return __cb->__invoke(this, id, stri, 0);
}

bool
IceProxy::Host::CHost::postMessage_async(const ::Host::AMI_CHost_postMessagePtr& __cb, const ::std::string& id, const ::std::string& stri, const ::Ice::Context& __ctx)
{
    return __cb->__invoke(this, id, stri, &__ctx);
}
#endif

bool
IceProxy::Host::CHost::queryCtrl(const ::std::string& id, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __checkTwowayOnly(__Host__CHost__queryCtrl_name);
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Host__CHost__queryCtrl_name, ::Ice::Normal, __ctx);
            try
            {
                ::IceInternal::BasicStream* __os = __outS.os();
                __os->write(id);
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
                bool __ret;
                ::IceInternal::BasicStream* __is = __outS.is();
                __is->read(__ret);
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

bool
IceProxy::Host::CHost::querySuper(const ::std::string& id, const ::std::string& password, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __checkTwowayOnly(__Host__CHost__querySuper_name);
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Host__CHost__querySuper_name, ::Ice::Normal, __ctx);
            try
            {
                ::IceInternal::BasicStream* __os = __outS.os();
                __os->write(id);
                __os->write(password);
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
                bool __ret;
                ::IceInternal::BasicStream* __is = __outS.is();
                __is->read(__ret);
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

void
IceProxy::Host::CHost::releaseCtrl(const ::std::string& id, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Host__CHost__releaseCtrl_name, ::Ice::Normal, __ctx);
            try
            {
                ::IceInternal::BasicStream* __os = __outS.os();
                __os->write(id);
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

::Host::CCamPrx
IceProxy::Host::CHost::cam(const ::std::string& id, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __checkTwowayOnly(__Host__CHost__cam_name);
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Host__CHost__cam_name, ::Ice::Normal, __ctx);
            try
            {
                ::IceInternal::BasicStream* __os = __outS.os();
                __os->write(id);
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
                ::Host::CCamPrx __ret;
                ::IceInternal::BasicStream* __is = __outS.is();
                ::Host::__read(__is, __ret);
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

::Host::CMotoPrx
IceProxy::Host::CHost::moto(const ::std::string& id, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __checkTwowayOnly(__Host__CHost__moto_name);
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Host__CHost__moto_name, ::Ice::Normal, __ctx);
            try
            {
                ::IceInternal::BasicStream* __os = __outS.os();
                __os->write(id);
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
                ::Host::CMotoPrx __ret;
                ::IceInternal::BasicStream* __is = __outS.is();
                ::Host::__read(__is, __ret);
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
IceProxy::Host::CHost::ice_staticId()
{
    return __Host__CHost_ids[0];
}

::IceProxy::Ice::Object*
IceProxy::Host::CHost::__newInstance() const
{
    return new CHost;
}
