
require( "luactrlboard" )

local POWER_ON_FIRST   = 60 * 60 * 3
local POWER_ON_REGULAR = 60 * 60 * 3 
local POWER_OFF        = 20

function main()
    local client = nil
    local timeoutToConnect = 20
    local timeToGetClient  = 180
    local triesLeft = 3
    local connected
    initMcu()
    -- Connection to XMPP servers
    for ttt = 1, triesLeft do
        local t0 = os.time()
        local t1 = t0
        while ( t1 - t0 < timeoutToConnect ) do
            t1 = os.time()
            sleep( 1000 )
            connected = isConnected()
            if ( connected ) then
                break
            end
            print( 'waiting for connection.' )
        end
        if ( connected ) then
            break
        end
    end
    -- Connection with server established.
    if ( connected ) then
        local stri = string.format( "Online! %s", mcu:isOpen() and "Mcu initialized" or "ERROR: Failed to open Mcu!" )
        print( stri )
        stri = string.format( "print( \'%s\' )", stri )
        --send( "print( \'Here!\' )" )
        send( stri )
        --send( "print( \'And here!\' )" )
        t0 = os.time()
        t1 = t0
        --send( "print( \'And damn here!\' )" )
        --stri = string.format( "print( \'%s, %s, %s\' )", type(t0), type(t1), type(timeToGetClient) )
        --send( stri )
        while ( t1 - t0 < timeToGetClient ) do
            --send( "print( \'Awesome!\' )" )
            t1 = os.time()
            sleep( 1000 )
            -- If there was timer reset by client
            -- the "client" variable is set.
            -- Then reset timeout to shutdown.
            if ( client ) then
                t0 = t1
                client = nil
            end
            --print( 'waiting for client command' )
        end
        send( "print( \'Going to shutdown\' )" )
    end
    print( "Leave!" )
    --[[
    ps = luaprocess.create()
    ps:start( "sudo", "halt", "-p" )
    ps:waitForFinished()
    ]]
end

function sleep( msec )
    msec = ( msec < 10000 ) and msec or 10000
    for i=1, msec, 50 do
        msleep( 50 )
    end
end

function initMcu()
    mcu = luactrlboard.create()
    local res = mcu:open()
    return res
end

function motoSet( moto1, moto2, moto3, moto4, t )
    print( "moto" )
    client = true
    if ( mcu:isOpen() ) then
        mcu:motoSet( moto1, moto2, moto3, moto4 )
    end
    t = t or 0
    if ( t > 0 ) then
        sleep( t or 1000 )
        if ( mcu:isOpen() ) then    
            mcu:motoSet( false, false, false, false )
        end
    end
    print( "moto left" )
end

function motoConfig( en, t )
    print( "moto config" )
    client = true
    if ( mcu:isOpen() ) then
        mcu:motoConfig( en, t or 3 )
    end
    print( "motoConfig left" )
end

function led( en )
    print( "led" )
    client = true
    if ( mcu:isOpen() ) then
        mcu:led( en )
    end
    print( "led left" )
end

function image( w, h )
    print( "image entered" )
    client = true
    if ( not imgProc ) then
        imgProc = luafsw.create()
        imgProc:setPeer( peer() )
    end
    if ( imgProc:isRunning() ) then
        send( "print( \"Pending image is in procress. Another image capture is possible only after finishing current one.\" )" )
    else
        imgProc:start()
    end
    print( "image left" )
end

function volts()
    print( "volts" )
    client = true
    if ( mcu ) and ( mcu:isOpen() ) then
        local res, solar, battery = mcu:adc()
        if ( res ) then
            local stri = string.format( "setVolts( %i, %i )", solar or -1, battery or -1 )
            send( stri )
        end
    end
    --send( "setVolts( 123, 456 )" )
    print( "volts left" )
end

function powerEn( en )
    if ( mcu ) and ( mcu:isOpen() ) then
        mcu:powerEn( en )
    end
    print( "volts left" )
end

print( "host.lua loaded!!!" )
main()








