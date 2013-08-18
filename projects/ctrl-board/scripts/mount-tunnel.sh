#!/bin/sh
MOUNTPOINT=~/projects/_pi
mkdir -p $MOUNTPOINT
sshfs -p 1234 pi@localhost:/home/pi $MOUNTPOINT

