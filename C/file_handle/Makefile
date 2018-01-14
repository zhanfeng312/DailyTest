TARGET = test

PWD=$(shell pwd)
CFLAGS = -I $(PWD)/..

SRCS = $(wildcard *.c)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@
	
.PHONY: run clean
run:
	@$(PWD)/$(TARGET)
	
clean:
	rm -rf $(TARGET)
