// **********************************************************************
//
// Copyright (c) 2003-2008 ZeroC, Inc. All rights reserved.
//
// This copy of Ice-E is licensed to you under the terms described in the
// ICEE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <IceE/TraceLevels.h>
#include <IceE/Properties.h>

using namespace std;
using namespace Ice;
using namespace IceInternal;

IceUtil::Shared* IceInternal::upCast(TraceLevels* p) { return p; }

IceInternal::TraceLevels::TraceLevels(const PropertiesPtr& properties) :
    network(0),
    networkCat("Network"),
    protocol(0),
    protocolCat("Protocol"),
    retry(0),
    retryCat("Retry"),
    location(0),
    locationCat("Locator")
{
    const string keyBase = "Ice.Trace.";
    const_cast<int&>(network) = properties->getPropertyAsInt(keyBase + networkCat);
    const_cast<int&>(protocol) = properties->getPropertyAsInt(keyBase + protocolCat);
    const_cast<int&>(retry) = properties->getPropertyAsInt(keyBase + retryCat);
    const_cast<int&>(location) = properties->getPropertyAsInt(keyBase + locationCat);
}
