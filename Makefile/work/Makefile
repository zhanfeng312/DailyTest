src = $(wildcard src/*.c) #./src/cal.c
obj = $(patsubst src/%.c, obj/%.o, $(src))

INC_PATH = inc
ALL:a.out

$(obj):obj/%.o:src/%.c #模式规则 与 静态模式规则
	gcc -c $< -o $@ -I$(INC_PATH)

a.out:$(obj)
	gcc $^ -o $@

clean:
	rm -rf a.out $(obj)

.PHONY:clean
