
#include "stdio.h"
int CPPlib_add(int add1, int add2);
int CPPlib_sub(int sub1, int sub2);
//以上三句代码 给 C++编译器 看的

#pragma comment (lib, "../lib/CPPClib.lib")
//通知链接器 到哪 拷贝源代码

#pragma comment(lib, "../lib/Clib.lib")
extern "C" int Clib_add(int add1, int add2);  //后面这个函数不能按照c++方式编译
extern "C" int Clib_sub(int sub1, int sub2);

int main()
{
	int sum = CPPlib_add(5, 4);
	int sub = CPPlib_sub(5, 4);
	printf("sum = %d, sub = %d\n", sum, sub);
	sum = Clib_add(5, 6);
	sub = Clib_sub(5, 6);
	printf("sum = %d, sub = %d\n", sum, sub);
	return 0;
}