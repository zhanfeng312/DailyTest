##############################################################################
#
# Copyright (c) Inspur Group Co., Ltd. Unpublished
#
# Inspur Group Co., Ltd.
# Proprietary & Confidential
#
# This source code and the algorithms implemented therein constitute
# confidential information and may comprise trade secrets of Inspur
# or its associates, and any use thereof is subject to the terms and
# conditions of the Non-Disclosure Agreement pursuant to which this
# source code was originally received.
#
##############################################################################

#	README	
#  	This is a Makefile for bbb.c
#
TARGET  = bbb-compile
OBJS    = src/bbb.o src/main.o src/dictionary.o src/iniparser.o

CC      = gcc
CFLAGS  = -Wall -Werror -I/usr/include/mysql
LFLAGS  = -L/usr/lib/mysql -lmysqlclient
RM      = rm -f

default:$(TARGET)

$(TARGET):$(OBJS)
	@(echo "compiling $@ ...")
	$(CC) -g -o $@ $(OBJS) $(LFLAGS)
	
clean:
	$(RM) $(TARGET) $(OBJS) *.o 

$(OBJS):%.o:%.c
	$(CC) -c -g $(CFLAGS) $(LFLAGS) $< -o $@		
    
