
#wildcard: �ú�����ͨ���������ͨ�������Եõ���ǰ����Ŀ¼������_patternģʽ���ļ���Ŀ¼���б�
#�÷���$(wildcard _pattern)
SRCS = $(wildcard *.c)

#patsubst: �ú������ڽ������б�_text�з���_patternģʽ�������滻Ϊ_replacement�������滻��������б�����
#�÷���$(patsubst _pattern, _replacement, _text)
mixed = foo.c bar.c main.o
objects = $(patsubst %.c, %.o, $(mixed))

#strip: ������������б��еĶ���ո�
#�÷���$(strip _string)
original = foo.c           bar.c
stripped := $(strip $(original))

#addprefix: ��ǰ׺
#�÷���$(addprefix _prefix, _names)
without_dir = main.c bar.c foo.c
with_dir := $(addprefix src/, $(without_dir))

#addsuffix: �Ӻ�׺
#�÷���$(addsuffix _suffix, _names)
without_suffix = main foo bar
with_suffix := $(addsuffix .c, $(without_suffix))

#filter: �ú������ڴ�һ�������б�_text�и���ģʽ_pattern�õ�������Ҫ�������б�����
#�÷���$(filter _pattern, _text)
sources = foo.c bar.c bar.s ugh.h
sources := $(filter %.c %.s, $(sources))

#filter-out: �ú������ڴ������б�_text�и���ģʽ_pattern�˳�һ�������֣������˳�����б�����
#�÷���$(filter-out _pattern, _text)
objects = main1.o foo.o main2.o bar.o
result = $(filter-out main%.o, $(objects))

#notdir: �ú������ڴ�·��_names�г�ȡ�ļ����������ļ�������
#�÷���$(notdir _names)
file_name := $(notdir code/foo/src/foo.c code/bar/src/bar.c)

#eval: eval�����Ĵ���ʹ��Makefile���ж�̬���Ե�������eval����ʹ��make����һ�ν���_text���
#�÷���$(eval _text)

#�÷���$(abspath _names)
#�ú�����Ҫ���ڽ�_names�еĸ�·��ת���ɾ���·��������ת����Ľ������
#ROOT := $(abspath /usr/../lib)

#�÷���$(realpath _names)
#���ڻ�ȡ_names����Ӧ����ʵ·��
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