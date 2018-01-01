#!/usr/bin/python
#filename while.py

number = 23
running = True

while running:
	guess = int(input('Enter an integer :'))
	
	if guess == number:
		print("Congratulations")
		running = False
	elif guess < number:
		print("No, it is a little lower than that")
	else:
		print("No, it is a little higher than that")

print("The while loop is over.")

print("Done")
