#!/bin/bash

var=testcase
echo $var

echo ${var%s*e} # testca 是否以给定的pattern结尾, 如果是，把var的内容去掉右边最短的匹配模式

echo ${var%%s*e} # te

echo ${var#?e} # stcase

echo ${var##?e} # stcase

echo ${var##*e} # 空

echo ${var##*s} # e

echo ${var##test} # case