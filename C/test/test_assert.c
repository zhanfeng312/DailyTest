#include <stdio.h>
#define NDEBUG
#include <assert.h>

void swap(int *a, int *b)
{
	assert(a != NULL);//函数宏
	assert(b != NULL);

	int tmp_value = *a;
	*a = *b;
	*b = tmp_value;
}

int main(int argc, char *argv[])
{
	int a = 3, b = 4;

	assert(a != 3);//如果条件返回错误，则终止程序执行，先向stderr打印一条出错信息，然后通过调用 abort 来终止程序运行

	printf("before swap: a = %d, b = %d\n", a, b);

	swap(&a, &b);

	printf("after  swap: a = %d, b = %d\n", a, b);

	return 0;
}