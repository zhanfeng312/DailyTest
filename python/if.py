#!/usr/bin/python
#filename if.py

number = 23
guess = int(raw_input('Enter an integer :'))

if guess == number:
	print '='
elif guess < number:
	print '<'
else:
	print '>'
	
print 'Done'