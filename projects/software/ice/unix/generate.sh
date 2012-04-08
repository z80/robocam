#/bin/sh
PTH=../../3dparty/IceE-1.3.0/slice
SLICE=../../build/icee/cpp/bin/slice2cppe
$SLICE -I$PTH ../types.ice
$SLICE -I$PTH ../hdw.ice
$SLICE -I$PTH ../host.ice
$SLICE -I$PTH ../client.ice
echo DONE!!!