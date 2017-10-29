#!/bin/bash

#get system type and test

SYSTEM=`uname -s`

if [ ${SYSTEM} = "Linux" ]; then
	echo "Linux"
elif [ ${SYSTEM}  = "FreeBSD" ]; then
	echo "FreeBSD"
elif [ ${SYSTEM} =  "Solaris" ]; then
	echo "Solaris"
else
	echo "unknown"
fi

if [ "fang" \< "gong" ]; then
	echo "fang < gong"
fi
