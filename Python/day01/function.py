#!/usr/bin/python
#filename function.py

def printMax(a, b):
	if a > b:
		print ("maximum is", a)
	else:
		print ("maximum is", b)
		
x = int(input("input first number: "))
y = int(input("input second number: "))

printMax(x, y)
