#!/bin/sh
#sleep 30
touch /home/pi/projects/aaa.aaa
echo "Trying to connect"
#sudo /home/pi/projects/sakis3gz start APN="internet.mts.ru" OTHER="USBMODEM" USBINTERFACE="0" USBMODEM="12d1:155b"
#sudo /home/pi/projects/sakis3gz start APN="internet.mts.ru" USBMODEM="12d1:155b"
sudo ./sakis3gz connect OTHER="USBMODEM" USBMODEM="12d1:1446" USBINTERFACE="0" APN="internet.mts.ru"
echo "Running regular software after connection"
echo "Done"

