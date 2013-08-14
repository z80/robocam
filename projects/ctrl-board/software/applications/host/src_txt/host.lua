
require( "luactrlboard" )

local I2C_ADDR         = 1
local status_table     = {}
local TRIES_CNT        = 5
local TRY_DELAY        = 100

local CMD_SET_POWER_TIMES = 1
local CMD_POWER_RESET     = 2
local CMD_SHUTDOWN_RESET  = 3
local CMD_SET_SECONDS_PER_DAY = 4
local CMD_SET_CURRENT_TIME    = 5
local CMD_CURRENT_TIME        = 6
local CMD_SET_WAKEUPS_CNT     = 7
local CMD_SET_WAKEUP          = 8
local CMD_TEMP            = 9
local CMD_CURR            = 10
local CMD_SET_SOLAR_VOLT  = 11
local CMD_SET_CHARGE_VOLT = 12
local CMD_SET_MOTO_EN     = 13
local CMD_SET_MOTO        = 14
local CMD_SET_LIGHT       = 15
local CMD_SET_LED         = 16
local CMD_BUCK_FB         = 17
local CMD_BOOST_FB        = 18
local CMD_SOLAR_FB        = 19
local CMD_SETUP_OSC       = 20 -- 2 bytes period in seconds, 1 byte what to measure: current, temperature.
local CMD_OSC_STATUS      = 21 -- 2 bytes number of measures in memory and 1 byte signals measured.
local CMD_OSC             = 22 -- Get value/values by index. 0 - most recent, 1 - previous, 2 - prev-previous.


function sendStatus()
    status(  )
    local stri = "<h3><b>Status:</b></h3><br>"
    for k, v in pairs( status_table ) do
        stri = string.format( "%s\n<b>%s</b> = <b>%s</b><br>", stri, tostring(k), tostring(v) )
    end
    status( stri )
end

function main()
    dontSleep = true
    local timeToConnect = 180
    local timeToGetClient  = 180
    local connected
    initMcu()
    -- Connection to XMPP servers
    local t0 = os.time()
    local t1 = t0
    while ( timeToConnect > 0 ) do
        sleep( 1000 )
        connected = isConnected()
        timeoutReset()
        if ( connected ) then
            break
        end
	timeToConnect = timeToConnect - 1
    end
    -- Connection with server established.
    if ( connected ) then
        local stri = "Host is online"
        print( stri )
        t = timeToGetClient
        while ( t > 0 ) do
            sleep( 1000 )
            -- Here should be no timeoutReset().
            -- It should be called remotely.
	        -- timeoutReset()
            if ( dontSleep ) then
                t = timeToGetClient
                dontSleep = nil
            end
        end
    else
        print( "Failed to get connected" )
    end
    print( "Terminating host" )
    process( "sudo halt -p" )
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
        t[2] = en and 1 or 0
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

function timeoutReset()
    dontSleep = true
    enterCritical()
    local res = mcu:open()
    if ( res ) then
        local t = {}
        t[1] = CMD_SHUTDOWN_RESET
        t[2] = 0 
        t[3] = 0
        res = mcu:write( I2C_ADDR, t )
        if ( not res ) then
	    mcu:close()
	    leaveCritical()
            return false
        end
        mcu:close()
	leaveCritical()
        return true
    end
    leaveCritical()
    return false
end

function setPowerTimeout( onTime )
    local res = mcu:open()
    if ( res ) then
        local t = {}
        t[1] = CMD_SET_POWER_TIMEOUT
        t[2] = bit.band( onTime, 255 )
        t[3] = bit.rshift( onTime, 8 )
        res = mcu:write( I2C_ADDR, t )
        if ( not res ) then
            return false
        end
        status_table.onTime  = onTime
        mcu:close()
        return true
    end
    return false
end

function setSecondsPerDay( cnt )
    local res = mcu:open()
    if ( res ) then
        local t = {}
        t[1] = CMD_SET_SECONDS_PER_DAY
        t[2] = bit.band( onTime, 255 )
        t[3] = bit.band( bit.rshift( cnt, 8 ), 255 )
	t[4] = bit.band( bit.rshift( cnt, 16 ), 255 )
	t[5] = bit.band( bit.rshift( cnt, 24 ), 255 )
        res = mcu:write( I2C_ADDR, t )
        if ( not res ) then
            return false
        end
        status_table.onTime  = onTime
        mcu:close()
        return true
    end
    return false
end

function setCurrentTime( cnt )
    local res = mcu:open()
    if ( res ) then
        local t = {}
        t[1] = CMD_SET_CURRENT_TIME
        t[2] = bit.band( cnt, 255 )
        t[3] = bit.band( bit.rshift( cnt, 8 ), 255 )
	t[4] = bit.band( bit.rshift( cnt, 16 ), 255 )
	t[5] = bit.band( bit.rshift( cnt, 24 ), 255 )
        res = mcu:write( I2C_ADDR, t )
        if ( not res ) then
            return false
        end
        status_table.curTime  = onTime
        mcu:close()
        return true
    end
    return false
end

function currentTime()
    local res = mcu:open()
    if ( res ) then
        local t = {}
        t[1] = CMD_CURRENT_TIME
        t[2] = 0
        t[3] = 0
        res = mcu:write( I2C_ADDR, t )
        if ( not res ) then
            return false
        end
        sleep( TRY_DELAY )
        res = mcu:read( I2C_ADDR, 5 )
        if ( not res ) then
            return false
        end
	if ( res[1] ~= CMD_CURRENT_TIME ) then
            status_table.time = "not ready"
	else
            local v = res[2] + res[3] * 256 + res[4] * 256 * 256 + res[5] * 256 * 256 * 256
            status_table.time = v
	end
        mcu:close()
        return true
    end
    return false
end



function setWakeupsCnt( cnt )
    local res = mcu:open()
    if ( res ) then
        local t = {}
        t[1] = CMD_SET_WAKEUPS_CNT
	t[2] = bit.band( cnt, 255 )
        t[3] = 0
	t[4] = 0
        res = mcu:write( I2C_ADDR, t )
        if ( not res ) then
            return false
        end
        mcu:close()
        return true
    end
    return false
end

function setWakeup( ind, t )
    local res = mcu:open()
    if ( res ) then
        local t = {}
        t[1] = CMD_SET_CURRENT_TIME
	t[2] = ind
        t[3] = bit.band( t, 255 )
        t[4] = bit.band( bit.rshift( t, 8 ), 255 )
	t[5] = bit.band( bit.rshift( t, 16 ), 255 )
	t[6] = bit.band( bit.rshift( t, 24 ), 255 )
        res = mcu:write( I2C_ADDR, t )
        if ( not res ) then
            return false
        end
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
	if ( res[1] ~= CMD_TEMP ) then
            status_table.temp = "not ready"
	else
            local v = res[2] + res[3] * 256
            local t = ( v * (3300 / 4095) - 500 ) / 10
            status_table.temp = t
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
        sleep( TRY_DELAY )
        res = mcu:read( I2C_ADDR, 3 )
        if ( not res ) then
            return false
        end
	if ( res[1] ~= CMD_CURR ) then
            status_table.curr = "not ready"
	else
            local i = res[2] + res[3] * 256 
            -- V = I(A) * 0.3(Ohm) * 11(gain)
            -- A(adc) = 4095 / 3.3 * I + 2047(shift to range center with another OpAmp)
            i = 0.2442 * (i - 2047) -- mA
            status_table.curr = i
	end
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
    setMoto( true, false, false, false )
end

function motoRight()
    setMoto( false, false, true, false )
end

--local CMD_SETUP_OSC       = 15 -- 2 bytes period in seconds, 1 byte what to measure: current, temperature.
--local CMD_OSC_STATUS      = 16 -- 2 bytes number of measures in memory and 1 byte signals measured.
--local CMD_OSC             = 17 -- Get value/values by index. 0 - most recent, 1 - previous, 2 - prev-previous.

function oscStatus()
    local res = mcu:open()
    if ( res ) then
        local t = {}
        t[1] = CMD_OSC_STATUS
        t[2] = 0
        t[3] = 0
        res = mcu:write( I2C_ADDR, t )
        if ( not res ) then
            return false
        end
        sleep( TRY_DELAY )
        res = mcu:read( I2C_ADDR, 4 )
        if ( not res ) then
            return false
        end
	local cnt = res[2] + res[3] * 256 
        status_table.oscCnt = cnt
        mcu:close()
        return cnt
    end
    return false
end

function oscValue( index )
    local res = mcu:open()
    if ( res ) then
        local t = {}
        t[1] = CMD_OSC
        t[2] = bit.band( index, 255 )
        t[3] = bit.rshift( index, 8 )
        res = mcu:write( I2C_ADDR, t )
        if ( not res ) then
            return false
        end
        sleep( TRY_DELAY )
        res = mcu:read( I2C_ADDR, 4 )
        if ( not res ) then
            return false
        end
	local val = res[2] + res[3] * 256 
        mcu:close()
        return val
    end
    return false
end

function sendOsc()
    status( "Now it\'s empty..." )
end




print( "host.lua loaded!!!" )
main()








