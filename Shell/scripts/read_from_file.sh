#!/bin/bash

#read from file

function while_read_LINE1()
{
	while read LINE
	do
		echo $LINE | cut -d ":" -f 1
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

while_read_LINE1 $1
