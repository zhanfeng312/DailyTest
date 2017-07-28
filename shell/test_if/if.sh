#!/bin/bash

# 可以采用正则表达式
# if 用来全词匹配 
if [[ $USER == f* ]]; then
	echo "the user is f..."
fi

# case 的用法
case $USER in
	fzf)
		echo "user is fzf"
		;;
	*)
		echo "other"
		;;
esac
