#make -n调试模式

#常用的自动变量:
#$@--目标文件
#$^--所有的依赖文件
#$<--第一个依赖文件

#wildcard
#patsubst

C_SRC = $(wildcard *.c)
CPP_SRC = $(wildcard *.cpp)

C_OBJ = $(patsubst %.c, %.o, $(C_SRC))
CPP_OBJ = $(patsubst %.cpp, %.o, $(CPP_SRC))

target = test

%.o: %.c
	gcc -c $<

%.o: %.cpp
	g++ -c $<

$(target): $(C_OBJ) $(CPP_OBJ)
	g++ $^ -o $@

run:
	@./test

clean:
	rm -rf $(C_OBJ) $(CPP_OBJ) $(target) run

#伪目标
.PHONY: clean $(target) run