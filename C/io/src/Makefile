#gcc hello.c -o hello

src = $(wildcard *.c) #hello.c
obj = $(patsubst %.c, %, $(src))

ALL:$(obj)

%:%.c #模式规则 与 静态模式规则
	gcc $< -o $@

clean:
	rm -rf $(obj)

.PHONY:clean
