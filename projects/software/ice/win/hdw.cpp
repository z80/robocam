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

#include <hdw.h>
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

static const ::std::string __Hdw__CMoto__open_name = "open";

static const ::std::string __Hdw__CMoto__isOpen_name = "isOpen";

static const ::std::string __Hdw__CMoto__close_name = "close";

static const ::std::string __Hdw__CMoto__setMotoEn_name = "setMotoEn";

static const ::std::string __Hdw__CMoto__motoEn_name = "motoEn";

static const ::std::string __Hdw__CMoto__setMoto_name = "setMoto";

static const ::std::string __Hdw__CMoto__moto_name = "moto";

static const ::std::string __Hdw__CMoto__setServoEn_name = "setServoEn";

static const ::std::string __Hdw__CMoto__servoEn_name = "servoEn";

static const ::std::string __Hdw__CMoto__setServo_name = "setServo";

static const ::std::string __Hdw__CMoto__servo_name = "servo";

static const ::std::string __Hdw__CMoto__setWatchdog_name = "setWatchdog";

static const ::std::string __Hdw__CMoto__resetWatchdog_name = "resetWatchdog";

static const ::std::string __Hdw__CCam__setDeviceName_name = "setDeviceName";

static const ::std::string __Hdw__CCam__open_name = "open";

static const ::std::string __Hdw__CCam__isOpen_name = "isOpen";

static const ::std::string __Hdw__CCam__close_name = "close";

static const ::std::string __Hdw__CCam__capabilities_name = "capabilities";

static const ::std::string __Hdw__CCam__formats_name = "formats";

static const ::std::string __Hdw__CCam__resolutions_name = "resolutions";

static const ::std::string __Hdw__CCam__initDevice_name = "initDevice";

static const ::std::string __Hdw__CCam__imageSize_name = "imageSize";

static const ::std::string __Hdw__CCam__startCapture_name = "startCapture";

static const ::std::string __Hdw__CCam__stopCapture_name = "stopCapture";

static const ::std::string __Hdw__CCam__started_name = "started";

static const ::std::string __Hdw__CCam__acquire_name = "acquire";

static const ::std::string __Hdw__CCam__release_name = "release";

static const ::std::string __Hdw__CCam__data_name = "data";

static const ::std::string __Hdw__CCam__lastError_name = "lastError";

static const ::std::string __Hdw__CLua__exec_name = "exec";

static const ::std::string __Hdw__CHdw__moto_name = "moto";

static const ::std::string __Hdw__CHdw__cam_name = "cam";

::Ice::Object* IceInternal::upCast(::Hdw::CMoto* p) { return p; }
::IceProxy::Ice::Object* IceInternal::upCast(::IceProxy::Hdw::CMoto* p) { return p; }

::Ice::Object* IceInternal::upCast(::Hdw::CCam* p) { return p; }
::IceProxy::Ice::Object* IceInternal::upCast(::IceProxy::Hdw::CCam* p) { return p; }

::Ice::Object* IceInternal::upCast(::Hdw::CLua* p) { return p; }
::IceProxy::Ice::Object* IceInternal::upCast(::IceProxy::Hdw::CLua* p) { return p; }

::Ice::Object* IceInternal::upCast(::Hdw::CHdw* p) { return p; }
::IceProxy::Ice::Object* IceInternal::upCast(::IceProxy::Hdw::CHdw* p) { return p; }

void
Hdw::__read(::IceInternal::BasicStream* __is, ::Hdw::CMotoPrx& v)
{
    ::Ice::ObjectPrx proxy;
    __is->read(proxy);
    if(!proxy)
    {
        v = 0;
    }
    else
    {
        v = new ::IceProxy::Hdw::CMoto;
        v->__copyFrom(proxy);
    }
}

void
Hdw::__read(::IceInternal::BasicStream* __is, ::Hdw::CCamPrx& v)
{
    ::Ice::ObjectPrx proxy;
    __is->read(proxy);
    if(!proxy)
    {
        v = 0;
    }
    else
    {
        v = new ::IceProxy::Hdw::CCam;
        v->__copyFrom(proxy);
    }
}

void
Hdw::__read(::IceInternal::BasicStream* __is, ::Hdw::CLuaPrx& v)
{
    ::Ice::ObjectPrx proxy;
    __is->read(proxy);
    if(!proxy)
    {
        v = 0;
    }
    else
    {
        v = new ::IceProxy::Hdw::CLua;
        v->__copyFrom(proxy);
    }
}

void
Hdw::__read(::IceInternal::BasicStream* __is, ::Hdw::CHdwPrx& v)
{
    ::Ice::ObjectPrx proxy;
    __is->read(proxy);
    if(!proxy)
    {
        v = 0;
    }
    else
    {
        v = new ::IceProxy::Hdw::CHdw;
        v->__copyFrom(proxy);
    }
}

static const ::std::string __Hdw__CMoto_ids[2] =
{
    "::Hdw::CMoto",
    "::Ice::Object"
};

bool
Hdw::CMoto::ice_isA(const ::std::string& _s, const ::Ice::Current&) const
{
    return ::std::binary_search(__Hdw__CMoto_ids, __Hdw__CMoto_ids + 2, _s);
}

::std::vector< ::std::string>
Hdw::CMoto::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&__Hdw__CMoto_ids[0], &__Hdw__CMoto_ids[2]);
}

const ::std::string&
Hdw::CMoto::ice_id(const ::Ice::Current&) const
{
    return __Hdw__CMoto_ids[0];
}

const ::std::string&
Hdw::CMoto::ice_staticId()
{
    return __Hdw__CMoto_ids[0];
}

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Hdw::CMoto::___open(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
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
Hdw::CMoto::___isOpen(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    bool __ret = isOpen(__current);
    __os->write(__ret);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Hdw::CMoto::___close(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    close(__current);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Hdw::CMoto::___setMotoEn(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
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
Hdw::CMoto::___motoEn(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    bool __ret = motoEn(__current);
    __os->write(__ret);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Hdw::CMoto::___setMoto(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::Ice::Int dir1;
    ::Ice::Int dir2;
    ::Ice::Int period;
    __is->read(dir1);
    __is->read(dir2);
    __is->read(period);
    setMoto(dir1, dir2, period, __current);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Hdw::CMoto::___moto(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
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
Hdw::CMoto::___setServoEn(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
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
::Ice::DispatchStatus
Hdw::CMoto::___servoEn(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    bool __ret = servoEn(__current);
    __os->write(__ret);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Hdw::CMoto::___setServo(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::Ice::Int servo1;
    ::Ice::Int servo2;
    __is->read(servo1);
    __is->read(servo2);
    setServo(servo1, servo2, __current);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Hdw::CMoto::___servo(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    ::Ice::Int servo1;
    ::Ice::Int servo2;
    servo(servo1, servo2, __current);
    __os->write(servo1);
    __os->write(servo2);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Hdw::CMoto::___setWatchdog(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::Ice::Int period;
    __is->read(period);
    setWatchdog(period, __current);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Hdw::CMoto::___resetWatchdog(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    resetWatchdog(__current);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
static ::std::string __Hdw__CMoto_all[] =
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
    "resetWatchdog",
    "servo",
    "servoEn",
    "setMoto",
    "setMotoEn",
    "setServo",
    "setServoEn",
    "setWatchdog"
};

::Ice::DispatchStatus
Hdw::CMoto::__dispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair< ::std::string*, ::std::string*> r = ::std::equal_range(__Hdw__CMoto_all, __Hdw__CMoto_all + 17, current.operation);
    if(r.first == r.second)
    {
        throw Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
    }

    switch(r.first - __Hdw__CMoto_all)
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
            return ___resetWatchdog(in, current);
        }
        case 10:
        {
            return ___servo(in, current);
        }
        case 11:
        {
            return ___servoEn(in, current);
        }
        case 12:
        {
            return ___setMoto(in, current);
        }
        case 13:
        {
            return ___setMotoEn(in, current);
        }
        case 14:
        {
            return ___setServo(in, current);
        }
        case 15:
        {
            return ___setServoEn(in, current);
        }
        case 16:
        {
            return ___setWatchdog(in, current);
        }
    }

    assert(false);
    throw Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
}
#endif // ICEE_PURE_CLIENT

void
Hdw::CMoto::__write(::IceInternal::BasicStream* __os) const
{
    __os->writeTypeId(ice_staticId());
    __os->startWriteSlice();
    __os->endWriteSlice();
    ::Ice::Object::__write(__os);
}

void
Hdw::CMoto::__read(::IceInternal::BasicStream* __is, bool __rid)
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
Hdw::operator==(const ::Hdw::CMoto& l, const ::Hdw::CMoto& r)
{
    return static_cast<const ::Ice::Object&>(l) == static_cast<const ::Ice::Object&>(r);
}

bool
Hdw::operator<(const ::Hdw::CMoto& l, const ::Hdw::CMoto& r)
{
    return static_cast<const ::Ice::Object&>(l) < static_cast<const ::Ice::Object&>(r);
}

void 
Hdw::__patch__CMotoPtr(void* __addr, ::Ice::ObjectPtr& v)
{
    ::Hdw::CMotoPtr* p = static_cast< ::Hdw::CMotoPtr*>(__addr);
    assert(p);
    *p = ::Hdw::CMotoPtr::dynamicCast(v);
    if(v && !*p)
    {
        IceInternal::Ex::throwUOE(::Hdw::CMoto::ice_staticId(), v->ice_id());
    }
}

static const ::std::string __Hdw__CCam_ids[2] =
{
    "::Hdw::CCam",
    "::Ice::Object"
};

bool
Hdw::CCam::ice_isA(const ::std::string& _s, const ::Ice::Current&) const
{
    return ::std::binary_search(__Hdw__CCam_ids, __Hdw__CCam_ids + 2, _s);
}

::std::vector< ::std::string>
Hdw::CCam::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&__Hdw__CCam_ids[0], &__Hdw__CCam_ids[2]);
}

const ::std::string&
Hdw::CCam::ice_id(const ::Ice::Current&) const
{
    return __Hdw__CCam_ids[0];
}

const ::std::string&
Hdw::CCam::ice_staticId()
{
    return __Hdw__CCam_ids[0];
}

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Hdw::CCam::___setDeviceName(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
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
Hdw::CCam::___open(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
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
Hdw::CCam::___isOpen(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    bool __ret = isOpen(__current);
    __os->write(__ret);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Hdw::CCam::___close(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    close(__current);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Hdw::CCam::___capabilities(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    ::Types::TStringArray cap;
    ::Types::TBoolArray en;
    ::Types::TStringArray info;
    bool __ret = capabilities(cap, en, info, __current);
    if(cap.size() == 0)
    {
        __os->writeSize(0);
    }
    else
    {
        __os->write(&cap[0], &cap[0] + cap.size());
    }
    __os->write(en);
    if(info.size() == 0)
    {
        __os->writeSize(0);
    }
    else
    {
        __os->write(&info[0], &info[0] + info.size());
    }
    __os->write(__ret);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Hdw::CCam::___formats(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    ::Types::TStringArray fmt;
    ::Types::TLongArray fourcc;
    bool __ret = formats(fmt, fourcc, __current);
    if(fmt.size() == 0)
    {
        __os->writeSize(0);
    }
    else
    {
        __os->write(&fmt[0], &fmt[0] + fmt.size());
    }
    if(fourcc.size() == 0)
    {
        __os->writeSize(0);
    }
    else
    {
        __os->write(&fourcc[0], &fourcc[0] + fourcc.size());
    }
    __os->write(__ret);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Hdw::CCam::___resolutions(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    ::Types::TIntArray __ret = resolutions(__current);
    if(__ret.size() == 0)
    {
        __os->writeSize(0);
    }
    else
    {
        __os->write(&__ret[0], &__ret[0] + __ret.size());
    }
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Hdw::CCam::___initDevice(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    bool streaming;
    ::Ice::Long fourcc;
    ::Ice::Int width;
    ::Ice::Int height;
    ::Ice::Int fps;
    __is->read(streaming);
    __is->read(fourcc);
    __is->read(width);
    __is->read(height);
    __is->read(fps);
    ::IceInternal::BasicStream* __os = __inS.os();
    bool __ret = initDevice(streaming, fourcc, width, height, fps, __current);
    __os->write(__ret);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Hdw::CCam::___imageSize(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    ::Ice::Int width;
    ::Ice::Int height;
    ::Ice::Int bufferSize;
    imageSize(width, height, bufferSize, __current);
    __os->write(width);
    __os->write(height);
    __os->write(bufferSize);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Hdw::CCam::___startCapture(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    bool __ret = startCapture(__current);
    __os->write(__ret);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Hdw::CCam::___stopCapture(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    stopCapture(__current);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Hdw::CCam::___started(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    bool __ret = started(__current);
    __os->write(__ret);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Hdw::CCam::___acquire(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    bool __ret = acquire(__current);
    __os->write(__ret);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Hdw::CCam::___release(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    bool __ret = release(__current);
    __os->write(__ret);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Hdw::CCam::___data(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::Ice::Int from;
    ::Ice::Int sz;
    __is->read(from);
    __is->read(sz);
    ::IceInternal::BasicStream* __os = __inS.os();
    ::Types::TByteArray res;
    data(from, sz, res, __current);
    if(res.size() == 0)
    {
        __os->writeSize(0);
    }
    else
    {
        __os->write(&res[0], &res[0] + res.size());
    }
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Hdw::CCam::___lastError(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    ::std::string __ret = lastError(__current);
    __os->write(__ret);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
static ::std::string __Hdw__CCam_all[] =
{
    "acquire",
    "capabilities",
    "close",
    "data",
    "formats",
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping",
    "imageSize",
    "initDevice",
    "isOpen",
    "lastError",
    "open",
    "release",
    "resolutions",
    "setDeviceName",
    "startCapture",
    "started",
    "stopCapture"
};

::Ice::DispatchStatus
Hdw::CCam::__dispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair< ::std::string*, ::std::string*> r = ::std::equal_range(__Hdw__CCam_all, __Hdw__CCam_all + 20, current.operation);
    if(r.first == r.second)
    {
        throw Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
    }

    switch(r.first - __Hdw__CCam_all)
    {
        case 0:
        {
            return ___acquire(in, current);
        }
        case 1:
        {
            return ___capabilities(in, current);
        }
        case 2:
        {
            return ___close(in, current);
        }
        case 3:
        {
            return ___data(in, current);
        }
        case 4:
        {
            return ___formats(in, current);
        }
        case 5:
        {
            return ___ice_id(in, current);
        }
        case 6:
        {
            return ___ice_ids(in, current);
        }
        case 7:
        {
            return ___ice_isA(in, current);
        }
        case 8:
        {
            return ___ice_ping(in, current);
        }
        case 9:
        {
            return ___imageSize(in, current);
        }
        case 10:
        {
            return ___initDevice(in, current);
        }
        case 11:
        {
            return ___isOpen(in, current);
        }
        case 12:
        {
            return ___lastError(in, current);
        }
        case 13:
        {
            return ___open(in, current);
        }
        case 14:
        {
            return ___release(in, current);
        }
        case 15:
        {
            return ___resolutions(in, current);
        }
        case 16:
        {
            return ___setDeviceName(in, current);
        }
        case 17:
        {
            return ___startCapture(in, current);
        }
        case 18:
        {
            return ___started(in, current);
        }
        case 19:
        {
            return ___stopCapture(in, current);
        }
    }

    assert(false);
    throw Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
}
#endif // ICEE_PURE_CLIENT

void
Hdw::CCam::__write(::IceInternal::BasicStream* __os) const
{
    __os->writeTypeId(ice_staticId());
    __os->startWriteSlice();
    __os->endWriteSlice();
    ::Ice::Object::__write(__os);
}

void
Hdw::CCam::__read(::IceInternal::BasicStream* __is, bool __rid)
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
Hdw::operator==(const ::Hdw::CCam& l, const ::Hdw::CCam& r)
{
    return static_cast<const ::Ice::Object&>(l) == static_cast<const ::Ice::Object&>(r);
}

bool
Hdw::operator<(const ::Hdw::CCam& l, const ::Hdw::CCam& r)
{
    return static_cast<const ::Ice::Object&>(l) < static_cast<const ::Ice::Object&>(r);
}

void 
Hdw::__patch__CCamPtr(void* __addr, ::Ice::ObjectPtr& v)
{
    ::Hdw::CCamPtr* p = static_cast< ::Hdw::CCamPtr*>(__addr);
    assert(p);
    *p = ::Hdw::CCamPtr::dynamicCast(v);
    if(v && !*p)
    {
        IceInternal::Ex::throwUOE(::Hdw::CCam::ice_staticId(), v->ice_id());
    }
}

static const ::std::string __Hdw__CLua_ids[2] =
{
    "::Hdw::CLua",
    "::Ice::Object"
};

bool
Hdw::CLua::ice_isA(const ::std::string& _s, const ::Ice::Current&) const
{
    return ::std::binary_search(__Hdw__CLua_ids, __Hdw__CLua_ids + 2, _s);
}

::std::vector< ::std::string>
Hdw::CLua::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&__Hdw__CLua_ids[0], &__Hdw__CLua_ids[2]);
}

const ::std::string&
Hdw::CLua::ice_id(const ::Ice::Current&) const
{
    return __Hdw__CLua_ids[0];
}

const ::std::string&
Hdw::CLua::ice_staticId()
{
    return __Hdw__CLua_ids[0];
}

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Hdw::CLua::___exec(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::std::string stri;
    __is->read(stri);
    ::IceInternal::BasicStream* __os = __inS.os();
    bool __ret = exec(stri, __current);
    __os->write(__ret);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
static ::std::string __Hdw__CLua_all[] =
{
    "exec",
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping"
};

::Ice::DispatchStatus
Hdw::CLua::__dispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair< ::std::string*, ::std::string*> r = ::std::equal_range(__Hdw__CLua_all, __Hdw__CLua_all + 5, current.operation);
    if(r.first == r.second)
    {
        throw Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
    }

    switch(r.first - __Hdw__CLua_all)
    {
        case 0:
        {
            return ___exec(in, current);
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
    }

    assert(false);
    throw Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
}
#endif // ICEE_PURE_CLIENT

void
Hdw::CLua::__write(::IceInternal::BasicStream* __os) const
{
    __os->writeTypeId(ice_staticId());
    __os->startWriteSlice();
    __os->endWriteSlice();
    ::Ice::Object::__write(__os);
}

void
Hdw::CLua::__read(::IceInternal::BasicStream* __is, bool __rid)
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
Hdw::operator==(const ::Hdw::CLua& l, const ::Hdw::CLua& r)
{
    return static_cast<const ::Ice::Object&>(l) == static_cast<const ::Ice::Object&>(r);
}

bool
Hdw::operator<(const ::Hdw::CLua& l, const ::Hdw::CLua& r)
{
    return static_cast<const ::Ice::Object&>(l) < static_cast<const ::Ice::Object&>(r);
}

void 
Hdw::__patch__CLuaPtr(void* __addr, ::Ice::ObjectPtr& v)
{
    ::Hdw::CLuaPtr* p = static_cast< ::Hdw::CLuaPtr*>(__addr);
    assert(p);
    *p = ::Hdw::CLuaPtr::dynamicCast(v);
    if(v && !*p)
    {
        IceInternal::Ex::throwUOE(::Hdw::CLua::ice_staticId(), v->ice_id());
    }
}

static const ::std::string __Hdw__CHdw_ids[2] =
{
    "::Hdw::CHdw",
    "::Ice::Object"
};

bool
Hdw::CHdw::ice_isA(const ::std::string& _s, const ::Ice::Current&) const
{
    return ::std::binary_search(__Hdw__CHdw_ids, __Hdw__CHdw_ids + 2, _s);
}

::std::vector< ::std::string>
Hdw::CHdw::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&__Hdw__CHdw_ids[0], &__Hdw__CHdw_ids[2]);
}

const ::std::string&
Hdw::CHdw::ice_id(const ::Ice::Current&) const
{
    return __Hdw__CHdw_ids[0];
}

const ::std::string&
Hdw::CHdw::ice_staticId()
{
    return __Hdw__CHdw_ids[0];
}

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Hdw::CHdw::___moto(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    ::Hdw::CMotoPrx __ret = moto(__current);
    __os->write(::Ice::ObjectPrx(::IceInternal::upCast(__ret.get())));
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Hdw::CHdw::___cam(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    ::Hdw::CCamPrx __ret = cam(__current);
    __os->write(::Ice::ObjectPrx(::IceInternal::upCast(__ret.get())));
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
static ::std::string __Hdw__CHdw_all[] =
{
    "cam",
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping",
    "moto"
};

::Ice::DispatchStatus
Hdw::CHdw::__dispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair< ::std::string*, ::std::string*> r = ::std::equal_range(__Hdw__CHdw_all, __Hdw__CHdw_all + 6, current.operation);
    if(r.first == r.second)
    {
        throw Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
    }

    switch(r.first - __Hdw__CHdw_all)
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
    }

    assert(false);
    throw Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
}
#endif // ICEE_PURE_CLIENT

void
Hdw::CHdw::__write(::IceInternal::BasicStream* __os) const
{
    __os->writeTypeId(ice_staticId());
    __os->startWriteSlice();
    __os->endWriteSlice();
    ::Ice::Object::__write(__os);
}

void
Hdw::CHdw::__read(::IceInternal::BasicStream* __is, bool __rid)
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
Hdw::operator==(const ::Hdw::CHdw& l, const ::Hdw::CHdw& r)
{
    return static_cast<const ::Ice::Object&>(l) == static_cast<const ::Ice::Object&>(r);
}

bool
Hdw::operator<(const ::Hdw::CHdw& l, const ::Hdw::CHdw& r)
{
    return static_cast<const ::Ice::Object&>(l) < static_cast<const ::Ice::Object&>(r);
}

void 
Hdw::__patch__CHdwPtr(void* __addr, ::Ice::ObjectPtr& v)
{
    ::Hdw::CHdwPtr* p = static_cast< ::Hdw::CHdwPtr*>(__addr);
    assert(p);
    *p = ::Hdw::CHdwPtr::dynamicCast(v);
    if(v && !*p)
    {
        IceInternal::Ex::throwUOE(::Hdw::CHdw::ice_staticId(), v->ice_id());
    }
}

bool
IceProxy::Hdw::CMoto::open(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __checkTwowayOnly(__Hdw__CMoto__open_name);
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Hdw__CMoto__open_name, ::Ice::Normal, __ctx);
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
IceProxy::Hdw::CMoto::isOpen(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __checkTwowayOnly(__Hdw__CMoto__isOpen_name);
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Hdw__CMoto__isOpen_name, ::Ice::Normal, __ctx);
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
IceProxy::Hdw::CMoto::close(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Hdw__CMoto__close_name, ::Ice::Normal, __ctx);
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
IceProxy::Hdw::CMoto::setMotoEn(bool en, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Hdw__CMoto__setMotoEn_name, ::Ice::Normal, __ctx);
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
IceProxy::Hdw::CMoto::motoEn(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __checkTwowayOnly(__Hdw__CMoto__motoEn_name);
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Hdw__CMoto__motoEn_name, ::Ice::Normal, __ctx);
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
IceProxy::Hdw::CMoto::setMoto(::Ice::Int dir1, ::Ice::Int dir2, ::Ice::Int period, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Hdw__CMoto__setMoto_name, ::Ice::Normal, __ctx);
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

void
IceProxy::Hdw::CMoto::moto(::Ice::Int& dir1, ::Ice::Int& dir2, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __checkTwowayOnly(__Hdw__CMoto__moto_name);
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Hdw__CMoto__moto_name, ::Ice::Normal, __ctx);
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
IceProxy::Hdw::CMoto::setServoEn(bool en, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Hdw__CMoto__setServoEn_name, ::Ice::Normal, __ctx);
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
IceProxy::Hdw::CMoto::servoEn(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __checkTwowayOnly(__Hdw__CMoto__servoEn_name);
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Hdw__CMoto__servoEn_name, ::Ice::Normal, __ctx);
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
IceProxy::Hdw::CMoto::setServo(::Ice::Int servo1, ::Ice::Int servo2, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Hdw__CMoto__setServo_name, ::Ice::Normal, __ctx);
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

void
IceProxy::Hdw::CMoto::servo(::Ice::Int& servo1, ::Ice::Int& servo2, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __checkTwowayOnly(__Hdw__CMoto__servo_name);
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Hdw__CMoto__servo_name, ::Ice::Normal, __ctx);
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
IceProxy::Hdw::CMoto::setWatchdog(::Ice::Int period, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Hdw__CMoto__setWatchdog_name, ::Ice::Normal, __ctx);
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
IceProxy::Hdw::CMoto::resetWatchdog(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Hdw__CMoto__resetWatchdog_name, ::Ice::Normal, __ctx);
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
IceProxy::Hdw::CMoto::ice_staticId()
{
    return __Hdw__CMoto_ids[0];
}

::IceProxy::Ice::Object*
IceProxy::Hdw::CMoto::__newInstance() const
{
    return new CMoto;
}

void
IceProxy::Hdw::CCam::setDeviceName(const ::std::string& devName, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Hdw__CCam__setDeviceName_name, ::Ice::Normal, __ctx);
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
IceProxy::Hdw::CCam::open(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __checkTwowayOnly(__Hdw__CCam__open_name);
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Hdw__CCam__open_name, ::Ice::Normal, __ctx);
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
IceProxy::Hdw::CCam::isOpen(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __checkTwowayOnly(__Hdw__CCam__isOpen_name);
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Hdw__CCam__isOpen_name, ::Ice::Normal, __ctx);
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
IceProxy::Hdw::CCam::close(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Hdw__CCam__close_name, ::Ice::Normal, __ctx);
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
IceProxy::Hdw::CCam::capabilities(::Types::TStringArray& cap, ::Types::TBoolArray& en, ::Types::TStringArray& info, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __checkTwowayOnly(__Hdw__CCam__capabilities_name);
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Hdw__CCam__capabilities_name, ::Ice::Normal, __ctx);
            bool __ok = __outS.invoke();
            try
            {
                if(!__ok)
                {
                    __outS.is()->throwUnknownUserException();
                }
                bool __ret;
                ::IceInternal::BasicStream* __is = __outS.is();
                __is->read(cap);
                __is->read(en);
                __is->read(info);
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
IceProxy::Hdw::CCam::formats(::Types::TStringArray& fmt, ::Types::TLongArray& fourcc, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __checkTwowayOnly(__Hdw__CCam__formats_name);
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Hdw__CCam__formats_name, ::Ice::Normal, __ctx);
            bool __ok = __outS.invoke();
            try
            {
                if(!__ok)
                {
                    __outS.is()->throwUnknownUserException();
                }
                bool __ret;
                ::IceInternal::BasicStream* __is = __outS.is();
                __is->read(fmt);
                __is->read(fourcc);
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

::Types::TIntArray
IceProxy::Hdw::CCam::resolutions(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __checkTwowayOnly(__Hdw__CCam__resolutions_name);
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Hdw__CCam__resolutions_name, ::Ice::Normal, __ctx);
            bool __ok = __outS.invoke();
            try
            {
                if(!__ok)
                {
                    __outS.is()->throwUnknownUserException();
                }
                ::Types::TIntArray __ret;
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
IceProxy::Hdw::CCam::initDevice(bool streaming, ::Ice::Long fourcc, ::Ice::Int width, ::Ice::Int height, ::Ice::Int fps, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __checkTwowayOnly(__Hdw__CCam__initDevice_name);
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Hdw__CCam__initDevice_name, ::Ice::Normal, __ctx);
            try
            {
                ::IceInternal::BasicStream* __os = __outS.os();
                __os->write(streaming);
                __os->write(fourcc);
                __os->write(width);
                __os->write(height);
                __os->write(fps);
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
IceProxy::Hdw::CCam::imageSize(::Ice::Int& width, ::Ice::Int& height, ::Ice::Int& bufferSize, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __checkTwowayOnly(__Hdw__CCam__imageSize_name);
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Hdw__CCam__imageSize_name, ::Ice::Normal, __ctx);
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
                __is->read(bufferSize);
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
IceProxy::Hdw::CCam::startCapture(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __checkTwowayOnly(__Hdw__CCam__startCapture_name);
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Hdw__CCam__startCapture_name, ::Ice::Normal, __ctx);
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
IceProxy::Hdw::CCam::stopCapture(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Hdw__CCam__stopCapture_name, ::Ice::Normal, __ctx);
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
IceProxy::Hdw::CCam::started(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __checkTwowayOnly(__Hdw__CCam__started_name);
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Hdw__CCam__started_name, ::Ice::Normal, __ctx);
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
IceProxy::Hdw::CCam::acquire(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __checkTwowayOnly(__Hdw__CCam__acquire_name);
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Hdw__CCam__acquire_name, ::Ice::Normal, __ctx);
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
IceProxy::Hdw::CCam::release(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __checkTwowayOnly(__Hdw__CCam__release_name);
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Hdw__CCam__release_name, ::Ice::Normal, __ctx);
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
IceProxy::Hdw::CCam::data(::Ice::Int from, ::Ice::Int sz, ::Types::TByteArray& res, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __checkTwowayOnly(__Hdw__CCam__data_name);
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Hdw__CCam__data_name, ::Ice::Normal, __ctx);
            try
            {
                ::IceInternal::BasicStream* __os = __outS.os();
                __os->write(from);
                __os->write(sz);
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
                ::IceInternal::BasicStream* __is = __outS.is();
                ::std::pair<const ::Ice::Byte*, const ::Ice::Byte*> ___res;
                __is->read(___res);
                ::std::vector< ::Ice::Byte>(___res.first, ___res.second).swap(res);
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

::std::string
IceProxy::Hdw::CCam::lastError(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __checkTwowayOnly(__Hdw__CCam__lastError_name);
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Hdw__CCam__lastError_name, ::Ice::Normal, __ctx);
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
IceProxy::Hdw::CCam::ice_staticId()
{
    return __Hdw__CCam_ids[0];
}

::IceProxy::Ice::Object*
IceProxy::Hdw::CCam::__newInstance() const
{
    return new CCam;
}

bool
IceProxy::Hdw::CLua::exec(const ::std::string& stri, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __checkTwowayOnly(__Hdw__CLua__exec_name);
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Hdw__CLua__exec_name, ::Ice::Normal, __ctx);
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

const ::std::string&
IceProxy::Hdw::CLua::ice_staticId()
{
    return __Hdw__CLua_ids[0];
}

::IceProxy::Ice::Object*
IceProxy::Hdw::CLua::__newInstance() const
{
    return new CLua;
}

::Hdw::CMotoPrx
IceProxy::Hdw::CHdw::moto(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __checkTwowayOnly(__Hdw__CHdw__moto_name);
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Hdw__CHdw__moto_name, ::Ice::Normal, __ctx);
            bool __ok = __outS.invoke();
            try
            {
                if(!__ok)
                {
                    __outS.is()->throwUnknownUserException();
                }
                ::Hdw::CMotoPrx __ret;
                ::IceInternal::BasicStream* __is = __outS.is();
                ::Hdw::__read(__is, __ret);
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

::Hdw::CCamPrx
IceProxy::Hdw::CHdw::cam(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __checkTwowayOnly(__Hdw__CHdw__cam_name);
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Hdw__CHdw__cam_name, ::Ice::Normal, __ctx);
            bool __ok = __outS.invoke();
            try
            {
                if(!__ok)
                {
                    __outS.is()->throwUnknownUserException();
                }
                ::Hdw::CCamPrx __ret;
                ::IceInternal::BasicStream* __is = __outS.is();
                ::Hdw::__read(__is, __ret);
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
IceProxy::Hdw::CHdw::ice_staticId()
{
    return __Hdw__CHdw_ids[0];
}

::IceProxy::Ice::Object*
IceProxy::Hdw::CHdw::__newInstance() const
{
    return new CHdw;
}
