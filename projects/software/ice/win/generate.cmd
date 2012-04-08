set PATH=%PATH%;C:\projects\avr\chassis\projects\openwrt\build\icee\cpp\bin;C:\projects\avr\chassis\projects\openwrt\build\icee\slice

echo %PATH%

set SLICE=C:\projects\avr\chassis\projects\openwrt\build\icee\slice
slice2cppe -I%SLICE% ../types.ice
slice2cppe -I%SLICE% ../hdw.ice
slice2cppe -I%SLICE% ../host.ice
slice2cppe -I%SLICE% ../client.ice
