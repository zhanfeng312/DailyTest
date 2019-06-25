#!/bin/sh

#my adb script

if [ $# -ne 1 ]; then
	echo "Usage: $0 ip:port"
	exit 1
fi

adb disconnect

adb kill-server
adb start-server

sleep 1

adb connect $1

sleep 1

adb remount
