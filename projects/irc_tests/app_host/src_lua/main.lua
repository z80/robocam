
require( "luamcuctrl" )

local POWER_ON_FIRST   = 60 * 60 * 3
local POWER_ON_REGULAR = 60 * 60 * 3 
local POWER_OFF        = 20

function main()
    local client = nil
    local timeoutToConnect = 20
    local timeToGetClient  = 300
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
        local stri = string.format( "Online! %s", mcu and "Mcu initialized" or "ERROR: Failed to open Mcu!" )
        print( stri )
        stri = string.format( "print( \'%s\' )", stri )
        send( stri )
        t0 = os.time()
        t1 = t0
        while ( t1 - t0 < timeToClient ) do
            t1 = os.time()
            sleep( 1000 )
            -- If there was timer reset by client
            -- the "client" variable is set.
            -- Then reset timeout to shutdown.
            if ( client ) then
                t0 = t1
                client = nil
            end
            print( 'waiting for client command' )
        end
    end
    print( "Leave!" )
    --[[
    ps = luaprocess.create()
    ps:start( "sudo", "halt", "-p" )
    ps:waitForFinished()
    ]]
end

function image( resX, resY, dev, file )
    resX, resY = resX or 640, resY or 480
    dev = dev or "/dev/video0"
    file = file or "/tmp/image.png"
    client = true
    local ps = luaprocess.create()
    ps:start( "fswebcam", "-q", "-d", dev, 
              "-r", string.format( "%ix%i", resX, resY ), 
              "-S", "5", "-F", "5", file )
    ps:waitForFinished()
    local stri = ps:readAll()
    --send( string.format( "print( '$s' )", stri ) )
    sendFile( file, file )
end

function sleep( msec )
    if ( mcu and mcu:isOpen() ) then
        mcu:powerReset()
    end
    msec = ( msec < 10000 ) and msec or 10000
    msleep( msec )
end

function initMcu()
    mcu = luamcuctrl.create()
    local res = mcu:open()
    if ( not res ) then
        mcu = nil
        return
    end
    mcu:powerConfig( POWER_ON_FIRST, POWER_ON_REGULAR, POWER_OFF )
end

main()







