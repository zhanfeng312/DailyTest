#!/bin/bash

echo "get system type and test"
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
echo -e "\ntest bool type"
USE_PRODUCT_KIND_FLAG=false

if $USE_PRODUCT_KIND_FLAG; then
    echo "USE_PRODUCT_KIND_FLAG is true"
else
    echo "USE_PRODUCT_KIND_FLAG is false"
fi

#-------------------------------------------------------
echo -e "\ntest math cal"
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

echo -e "\ntest str compare"
if [ "fang" \< "gong" ]; then
	echo "fang < gong"
fi
