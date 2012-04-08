// **********************************************************************
//
// Copyright (c) 2003-2008 ZeroC, Inc. All rights reserved.
//
// This copy of Ice-E is licensed to you under the terms described in the
// ICEE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <IceE/IceE.h>
#include "server_i.h"
#include "camera_i.h"

using namespace std;

int
run(int argc, char* argv[], const Ice::CommunicatorPtr& communicator)
{
    if(argc > 1)
    {
        fprintf(stderr, "%s: too many arguments\n", argv[0]);
        return EXIT_FAILURE;
    }

    Ice::ObjectAdapterPtr adapter = communicator->createObjectAdapterWithEndpoints( "Hi", "tcp -p 26011 -h 192.168.1.1" );
    Demo::HelloPtr object = new HelloI;
    adapter->add(object, communicator->stringToIdentity("hello"));
    Demo::CameraPtr camera = new CameraI;
    adapter->add(camera, communicator->stringToIdentity("camera"));
    adapter->activate();
    communicator->waitForShutdown();
    return EXIT_SUCCESS;
}

int
main(int argc, char* argv[])
{
    int status;
    Ice::CommunicatorPtr communicator;

    try
    {
        Ice::InitializationData initData;
        initData.properties = Ice::createProperties();
        //initData.properties->load("config");
        communicator = Ice::initialize(argc, argv, initData);
        status = run(argc, argv, communicator);
    }
    catch(const Ice::Exception& ex)
    {
        fprintf(stderr, "%s\n", ex.toString().c_str());
        status = EXIT_FAILURE;
    }

    if(communicator)
    {
        try
        {
            communicator->destroy();
        }
        catch(const Ice::Exception& ex)
        {
            fprintf(stderr, "%s\n", ex.toString().c_str());
            status = EXIT_FAILURE;
        }
    }

    return status;
}
