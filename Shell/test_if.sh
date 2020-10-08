#!/bin/bash

#-------------------------------------------------------
echo -e "test bool type\n"
flag=false

if $flag; then
    echo "flag is true"
else
    echo "flag is false"
fi

#-------------------------------------------------------
var1=1
var2=2
if [ ${var1} -eq 1 -a ${var2} -eq 2 ]; then
    echo "var1 = 1 and var2 = 2"
fi

if [[ ${var1} -eq 1 ]] && [[ ${var2} -eq 2 ]]; then
    echo "var1 = 1 and var2 = 2"
fi