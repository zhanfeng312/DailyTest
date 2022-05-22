#gcc hello.c -o hello

src = $(wildcard *.c) #hello.c
obj = $(patsubst %.c, %, $(src))

all:$(obj)

%:%.c #模式规则
	gcc $< -o $@

clean:
	rm -rf $(obj)

.PHONY: clean all
