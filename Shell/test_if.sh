#!/bin/bash

#get system type and test

SYSTEM=`uname -s`

if [ "x${SYSTEM}" = "xLinux" ]; then
	echo "Linux"
elif [ "x${SYSTEM}"  = "xFreeBSD" ]; then
	echo "FreeBSD"
elif [ "x${SYSTEM}" =  "Solaris" ]; then
	echo "Solaris"
else
	echo "unknown"
fi

#-------------------------------------------------------

var1=1
var2=2
var3=3

if [ "$var1" -eq 1 -a "$var2" -eq 2 ]; then
    echo "equal"
fi

if [ "$var1" -eq 1 ] && [ "$var2" -eq 2 ]; then
    echo "equal"
fi

if [[ "$var1" -eq 1 && "$var2" -eq 2 ]]; then
    echo "equal"
fi

if [[ "$var1" == 1 && "$var2" == 2 ]]; then
    echo "equal"
fi

if [[ "$var1" == 1 && "$var3" != 2 ]]; then
    echo "not equal"
fi

if [ "fang" \< "gong" ]; then
	echo "fang < gong"
fi
