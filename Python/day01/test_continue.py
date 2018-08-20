#!/usr/bin/python
# -*- coding:utf-8 -*-
#退出本次循环

while True:
	s = raw_input("Enter a string : ")
	if s == "quit":
		break
	if len(s) < 3:
		continue
	
print ("done")