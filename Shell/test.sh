#!/bin/sh

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
