


function setVolts( sol, batt )
    sol = ( sol / 4095 ) * 3.28 * 3
    batt = ( batt / 4095 ) * 3.28 * 3
    print( string.format( "sol: %3.2fV, batt: %3.2fV", sol, batt ) )
end

print( "client.lua loaded!!!" )



