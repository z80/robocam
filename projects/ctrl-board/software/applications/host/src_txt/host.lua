
require( "luactrlboard" )

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
    status(  )
    local stri = "<h3><b>Status:</b></h3><br>"
    for k, v in pairs( status_table ) do
        stri = string.format( "%s\n<b>%s</b> = <b>%s</b><br>", stri, tostring(k), tostring(v) )
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
        local stri = "Online"
        print( stri )
        t0 = os.time()
        t1 = t0
        --send( "print( \'And damn here!\' )" )
        --stri = string.format( "print( \'%s, %s, %s\' )", type(t0), type(t1), type(timeToGetClient) )
        --send( stri )
        while ( t1 - t0 < timeToGetClient ) do
            --send( 'Awesome!' )
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
    print( "Terminating" )
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
        t[2] = bit.band( onTime, 255 )
        t[3] = bit.rshift( onTime, 8 )
        t[4] = bit.band( offTime, 255 )
        t[5] = bit.rshift( offTime, 8 )
        res = mcu:write( I2C_ADDR, t )
        if ( not res ) then
            return false
        end
        status_table.onTime  = onTime
	status_table.offTime = offTime
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
        sleep( TRY_DELAY )
        res = mcu:read( I2C_ADDR, 3 )
        if ( not res ) then
            return false
        end
        local v = res[2] + res[3] * 256
	local t = ( v * (3300 / 4095) - 500 ) / 10
        status_table.temp = t
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
        sleep( TRY_DELAY )
        res = mcu:read( I2C_ADDR, 3 )
        if ( not res ) then
            return false
        end
	local i = res[2] + res[3] * 256 
	-- V = I(A) * 0.3(Ohm) * 11(gain)
	-- A(adc) = 4095 / 3.3 * I + 2047(shift to range center with another OpAmp)
	i = 0.2442 * (i - 2047) -- mA
        status_table.curr = i
        mcu:close()
        return true
    end
    return false
end

function motoStop()
    setMoto( false, false, false, false )
end

function motoForward()
    setMoto( true, false, true, false )
end

function motoBackward()
    setMoto( false, true, false, true )
end

function motoLeft()
    setMoto( false, false, true, false )
end

function motoRight()
    setMoto( true, false, false, false )
end




print( "host.lua loaded!!!" )
main()








