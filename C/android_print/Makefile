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

RM=rm -rf

TARGET=android_print_test

CC=/opt/toolchains/arm-android-gcc/bin/arm-linux-androideabi-gcc

SRCS=$(wildcard *.c)

CFLAGS += -Wall -pie -fPIE

LDFLAGS += -llog -pie -fPIE

$(TARGET): $(SRCS)
	echo "building   $@"
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@

.PHONY : run clean

run: $(TARGET)
	./$(TARGET)

clean:
	$(RM) $(TARGET)


