
require( "luactrlboard" )

function display( ... )
    local t = { ... }
    for i=1, #t do
        local stri = string.format( "print( \'arg[%i] = %s\' )", i, tostring( t[i] ) )
        print( stri )
    end
end

local POWER_ON_FIRST   = 60 * 60 * 3
local POWER_ON_REGULAR = 60 * 60 * 3 
local POWER_OFF        = 20
local I2C_ADDR         = 1
local status_table     = {}
local TRIES_CNT        = 5
local TRY_DELAY        = 100

local CMD_SET_POWER_TIMES = 1
local CMD_POWER_RESET     = 2
local CMD_SHUTDOWN_RESET  = 3
local CMD_TEMP            = 4
local CMD_CURR            = 5
local CMD_SET_SOLAR_VOLT  = 6
local CMD_SET_CHARGE_VOLT = 7
local CMD_SET_MOTO_EN     = 8
local CMD_SET_MOTO        = 9
local CMD_SET_LIGHT       = 10
local CMD_SET_LED         = 11

function sendStatus()
    print( "<h3><b>Status:</b></h>" )
    local stri = ""
    for k, v in pairs( status_table ) do
        stri = string.format( "%s\n<b>%s</b> = <b>%s</b>", stri, tostring(k), tostring(v) )
    end
    status( stri )
end

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
            send( 'Awesome!' )
            t1 = os.time()
            sleep( 1000 )
            -- If there was timer reset by client
            -- the "client" variable is set.
            -- Then reset timeout to shutdown.
            -- if ( client ) then
                t0 = t1
                client = nil
            -- end
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
end

function setMotoEn( en )
    local res = mcu:open()
    if ( res ) then
        local t = {}
        t[1] = CMD_SET_MOTO_EN
        t[2] = 1
        t[3] = 0
        res = mcu:write( I2C_ADDR, t )
        if ( not res ) then
            return false
        end
        status_table.moto = en
        mcu:close()
        return true
    end
    return false
end

function setMoto( m1, m2, m3, m4 )
    local res = mcu:open()
    if ( res ) then
        local t = {}
        t[1] = CMD_SET_MOTO
        t[2] = (m1 and 1 or 0) + (m2 and 2 or 0) + (m3 and 4 or 0) + (m4 and 8 or 0)
        t[3] = 0
        res = mcu:write( I2C_ADDR, t )
        if ( not res ) then
            return false
        end
        status_table.moto1 = m1
        status_table.moto2 = m2
        status_table.moto3 = m3
        status_table.moto4 = m4
        mcu:close()
        return true
    end
    return false
end

function setLight( en )
    local res = mcu:open()
    if ( res ) then
        local t = {}
        t[1] = CMD_SET_LIGHT
        t[2] = (en and 1 or 0)
        t[3] = 0
        res = mcu:write( I2C_ADDR, t )
        if ( not res ) then
            return false
        end
        status_table.light = en
        mcu:close()
        return true
    end
    return false
end

function setLed( v )
    local res = mcu:open()
    if ( res ) then
        local t = {}
        t[1] = CMD_SET_LED
        t[2] = v
        t[3] = 0
        res = mcu:write( I2C_ADDR, t )
        if ( not res ) then
            return false
        end
        status_table.led = en
        mcu:close()
        return true
    end
    return false
end

function powerSetup( onTime, offTime )
    local res = mcu:open()
    if ( res ) then
        local t = {}
        t[1] = CMD_SET_POWER_TIMES
        t[2] = bit.rshift( onTime, 8 )
        t[3] = bit.band( onTime, 255 )
        t[4] = bit.rshift( offTime, 8 )
        t[5] = bit.band( offTime, 255 )
        res = mcu:write( I2C_ADDR, t )
        if ( not res ) then
            return false
        end
        status_table.led = en
        mcu:close()
        return true
    end
    return false
end

function temp()
    local res = mcu:open()
    if ( res ) then
        local t = {}
        t[1] = CMD_TEMP
        t[2] = 0
        t[3] = 0
        res = mcu:write( I2C_ADDR, t )
        if ( not res ) then
            return false
        end
        for i = 1, TRIES_CNT do
            res = mcu:read( I2C_ADDR, 5 )
            if ( res ) then
                break
            end
            sleep( TRY_DELAY )
        end
        if ( res ) then
            status_table.temp = res[2] * 256 + res[3]
        end
        mcu:close()
        return true
    end
    return false
end

function curr()
    local res = mcu:open()
    if ( res ) then
        local t = {}
        t[1] = CMD_CURR
        t[2] = 0
        t[3] = 0
        res = mcu:write( I2C_ADDR, t )
        if ( not res ) then
            return false
        end
        for i = 1, TRIES_CNT do
            res = mcu:read( I2C_ADDR, 5 )
            if ( res ) then
                break
            end
            sleep( TRY_DELAY )
        end
        if ( res ) then
            status_table.temp = res[2] * 256 + res[3]
        end
        mcu:close()
        return true
    end
    return false
end

function motoStop()
    setMoto( false, false, false, false )
end

print( "host.lua loaded!!!" )
main()








