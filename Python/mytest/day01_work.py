#!/usr/bin/python
# -*- coding:utf-8 -*-

"""
1����1-100������
2����1-100ż����
3����1-2+3-4+...99��
"""

def get_first_sum():
	sum = 0
	index = 1
	while index < 101:
		if index % 2 == 1:
			sum += index
		index += 1
	print(sum)

def get_senond_sum():
	sum = 0
	index = 1
	while index < 101:
		if index % 2 == 0:
			sum += indexss
		index += 1
	print(sum)

def get_third_sum():
	sum = 0
	index = 1
	while index < 100:
		if index % 2 == 0:
			sum = sum - index
		else:
			sum = sum + index
		index += 1
	print(sum)

get_first_sum()
get_senond_sum()
get_third_sum()