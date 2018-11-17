#!/bin/bash

#read from file

function show_warning()
{
	echo -e "\033[32m $1 \033[0m"
}

function show_error()
{
	echo -e "\033[33m $1 \033[0m"
}

function while_read_LINE1()
{
	while read LINE
	do
		echo $LINE
	done < $1
}

function while_read_LINE2()
{
	cat $1 | while read LINE
	do
		echo $LINE
	done
}

function for_in_file()
{
	for i in `cat $1`
	do
		echo $i
	done
}

if [ $# -ne 1 ]; then
	show_error "usage $0 file"
	exit 1
fi

while_read_LINE1 $1
