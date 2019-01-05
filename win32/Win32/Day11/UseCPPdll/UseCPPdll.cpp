
#include "stdio.h"
//声明导出
_declspec(dllimport)int CPPdll_add(int add1, int add2);
_declspec(dllimport)int CPPdll_sub(int sub1, int sub2);
_declspec(dllimport)int CPPdll_mul(int mul1, int mul2);

#pragma comment(lib, "../lib/CPPdll.lib")  //和某一个lib文件配套的dll文件

extern "C" _declspec(dllimport)int Cdll_add(int add1, int add2);
extern "C" _declspec(dllimport)int Cdll_sub(int sub1, int sub2);

//在这个目录下找函数的偏移地址
#pragma comment(lib, "../lib/Cdll.lib") 

int main ()
{
	int sum = CPPdll_add(3, 4);
	int sub = CPPdll_sub(3, 4);
	int mul = CPPdll_mul(3, 4);
	printf("sum = %d, sub = %d, mul = %d\n", sum, sub, mul);
	sum = Cdll_add(5, 8);
	sub = Cdll_sub(5, 8);
	printf("sum = %d, sub = %d\n", sum, sub);
	return 0;
}