#!/bin/bash

function show_warning()
{
	echo -e "\033[32m $1 \033[0m"
}

function show_error()
{
	echo -e "\033[33m $1 \033[0m"
}

if [ $# -lt 2 ]; then
	show_error "parameters must >=2"
	exit 1
fi

# deal with
