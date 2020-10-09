#wildcard: 该函数是通配符函数，通过它可以得到当前工作目录中满足_pattern模式的文件或目录名列表
#用法: $(wildcard _pattern)
SRCS = $(wildcard *.c) $(wildcard sub/*.c)

#patsubst: 该函数用于将名字列表_text中符合_pattern模式的名字替换为_replacement，并将替换后的名字列表返回
#用法：$(patsubst _pattern, _replacement, _text)
mixed = foo.c bar.c main.o
objects = $(patsubst %.c, %.o, $(mixed))

#strip: 用于清除名字列表中的多余空格
#用法：$(strip _string)
original =      foo.c           bar.c 
stripped := $(strip $(original))

#addprefix: 加前缀
#用法：$(addprefix _prefix, _names)
without_dir = main.c bar.c foo.c
with_dir := $(addprefix src/, $(without_dir))

#addsuffix: 加后缀
#用法：$(addsuffix _suffix, _names)
without_suffix = main foo bar
with_suffix := $(addsuffix .c, $(without_suffix))

#filter: 该函数用于从一个名字列表_text中根据模式_pattern得到满足需要的名字列表返回
#用法：$(filter _pattern, _text)
sources = foo.c bar.c bar.s ugh.h
sources := $(filter %.c %.s, $(sources))

#filter-out: 该函数用于从名字列表_text中根据模式_pattern滤除一部分名字，并将滤除后的列表返回
#用法：$(filter-out _pattern, _text)
#objects = main1.o foo.o main2.o bar.o
result = $(filter-out main%.o, $(objects))

#notdir: 该函数用于从路径_names中抽取文件名，并将文件名返回
#用法：$(notdir _names)
file_name := $(notdir code/foo/src/foo.c code/bar/src/bar.c)

#eval: eval函数的存在使得Makefile具有动态语言的特征。eval函数使得make将再一次解析_text语句
#用法：$(eval _text)

#用法：$(abspath _names)
#该函数主要用于将_names中的各路径转换成绝对路径，并将转换后的结果返回
#ROOT := $(abspath /usr/../lib)

#用法：$(realpath _names)
#用于获取_names所对应的真实路径
#ROOT := $(realpath ./..)

all:
	@echo $(SRCS)
	@echo $(objects)
	@echo $(stripped)
	@echo $(with_dir)
	@echo $(with_suffix)
	@echo $(sources)
	@echo $(result)
	@echo $(file_name)
	@echo $(ROOT)
