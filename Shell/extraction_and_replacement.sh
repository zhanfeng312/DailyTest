#!/bin/bash

var=/home/centos
echo $var
# /home/centos

# 字符串提取
echo ${var:5}
# /centos

echo ${var: -6}
# centos

echo ${var:(-6)}
# centos

echo ${var:1:4}
# home

# 字符串替换
echo ${var/o/h}
# /hhme/centos

echo ${var//o/h}
# /hhme/cenths