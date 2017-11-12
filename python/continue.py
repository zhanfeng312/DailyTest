#!/usr/bin/python
#filename continue.py

while True:
	s = input("Enter a string : ")
	if s == "quit":
		break
	if len(s) < 3:
		continue
	print ("Input is of sufficient length")
	
print ("Done")
