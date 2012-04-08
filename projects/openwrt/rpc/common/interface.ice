// **********************************************************************
//
// Copyright (c) 2003-2008 ZeroC, Inc. All rights reserved.
//
// This copy of Ice-E is licensed to you under the terms described in the
// ICEE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef HELLO_ICE
#define HELLO_ICE

module Demo
{

interface Hello
{
    idempotent void sayHello(int delay);
    void shutdown();
};

sequence<string> TStringList;
sequence<int>    TIntList;
sequence<byte>   TByteList;

interface Camera
{
    void setDeviceName( string devName );
    bool open();
    void close();
    bool isOpened();
    TStringList formats();
    TIntList    resolutions();
    bool initDevice( string format, int width, int height );
    void imageSize( out int width, out int height, out int bufferSz );
    bool startCapture();
    void stopCapture();
    bool started();
    bool acquire();
    void data( int from, int sz, out TByteList res );
    string lastError();
};

};

#endif




