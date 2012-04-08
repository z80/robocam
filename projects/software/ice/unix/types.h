// **********************************************************************
//
// Copyright (c) 2003-2007 ZeroC, Inc. All rights reserved.
//
// This copy of Ice-E is licensed to you under the terms described in the
// ICEE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice-E version 1.3.0
// Generated from file `types.ice'

#ifndef __types_h__
#define __types_h__

#include <IceE/ProxyF.h>
#include <IceE/ObjectF.h>
#include <IceE/Exception.h>
#include <IceE/ScopedArray.h>
#include <IceE/UndefSysMacros.h>

#ifndef ICEE_IGNORE_VERSION
#   if ICEE_INT_VERSION / 100 != 103
#       error IceE version mismatch!
#   endif
#   if ICEE_INT_VERSION % 100 < 0
#       error IceE patch level mismatch!
#   endif
#endif

namespace Types
{

typedef ::std::vector<bool> TBoolArray;

typedef ::std::vector< ::Ice::Byte> TByteArray;

typedef ::std::vector< ::std::string> TStringArray;

typedef ::std::vector< ::Ice::Int> TIntArray;

typedef ::std::vector< ::Ice::Long> TLongArray;

}

#endif
