
#include "stdio.h"
int CPPlib_add(int add1, int add2);
int CPPlib_sub(int sub1, int sub2);
//����������� �� C++������ ����

#pragma comment (lib, "../lib/CPPClib.lib")
//֪ͨ������ ���� ����Դ����

#pragma comment(lib, "../lib/Clib.lib")
extern "C" int Clib_add(int add1, int add2);  //��������������ܰ���c++��ʽ����
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