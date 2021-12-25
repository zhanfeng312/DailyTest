#!/bin/bash

echo $0
echo $1
echo $2
echo $3

foo()
{
    echo $0 #不管放在哪,当前的进程名
    echo $1
    echo $2
    echo $3

    echo $#
    echo $@
}

echo "----start---"
foo 11 22 33 44
echo "-----end----"
