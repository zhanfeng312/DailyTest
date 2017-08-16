target = file.elf

PWD=$(shell pwd)
CFLAGS = -I $(PWD)/../log_module

$(target): file_handle.c
	gcc $(CFLAGS) $^ -o $@

clean:
	rm $(target)
