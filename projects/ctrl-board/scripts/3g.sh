#!/bin/sh

echo "Trying to connect"
HOME=/home/pi/projects/software/build.app
cd $HOME
sudo ./sakis3gz connect OTHER="USBMODEM" USBMODEM="12d1:1506" USBINTERFACE="0" APN="internet.mts.ru"
echo "Running regular software after connection"
./host

