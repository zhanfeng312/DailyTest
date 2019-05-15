#!/usr/bin/python
# -*- coding:utf-8 -*-
#test if
"""
1、
if 条件:
	代码
else:
	代码
2、
if 条件1:
	xxx
elif 条件2:
	xxx
elif 条件3:
	xxx
else
	xxx
3、
True False
1 > 2 n1 > n2 n1 == n2
name == "alex" and pwd == "123"
name == "alex" or name == "fang"
name != "fang"
"""

if True:
    print("11111")
else:
    print("22222")

n1 = 1
n2 = 2
if n1 < n2:
    print("yes")
else:
    print("no")

inp = input("请输入数字:")
if inp == "1":
	print("1")
elif inp == "2":
	print("2")
elif inp == "3":
	print("3")
else:
	print("...")