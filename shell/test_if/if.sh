#!/bin/bash

if [[ $USER == f* ]]; then
	echo "the user is ${USER}"
fi

case $USER in
	fzf)
		echo "the user is fzf"
		;;
	*)
		echo "other"
		;;
esac
