#!/usr/bin/python
# -*- coding:utf-8 -*-
#test while

"""
import time

n1 = True
while n1:
	print("1")
	time.sleep(1)
	n1 = False
	
print("done")
"""

index = 1
flag = True

while flag:
	print(index)
	if index == 10:
		flag = False
	index = index + 1

print("done")