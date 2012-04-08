#!/bin/bash
echo "=================================================================="
echo "This script will upload dd-wrt firmware (firmware.bin)"
echo "in the current directory to 192.168.1.1 "
echo "during the router's bootup. "
echo ""
echo "* Set your ethernet card's settings to: "
echo "     IP:      192.168.0.10 "
echo "     Mask:    255.255.255.0 "
echo "     Gateway: 192.168.0.1 "
echo "* Unplug the router's power cable. "
echo ""
echo "Press Ctrl+C to abort or any other key to continue... " 

read

echo ""
echo "* Re-plug the router's power cable. "
echo "" 
echo "=================================================================="
echo "Waiting for the router... Press Ctrl+C to abort. "
echo ""


try(){
ping -c 1 -w 1 192.168.0.1
}
try
while [ "$?" != "0" ] ;
do
try
done
echo "*** Start Flashing **** "
# atftp --no-source-port-checking -p -l ./firmware.bin 192.168.0.1
atftp --trace --option "timeout 1" --option "mode octet" --put --local-file firmware.bin 192.168.0.1
echo "Firmware successfully loaded!"

