#!/bin/sh
MOUNTPOINT=~/projects/_pi
mkdir -p $MOUNTPOINT
sshfs pi@192.168.1.125:/home/pi $MOUNTPOINT

