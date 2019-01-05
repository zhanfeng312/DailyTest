

#include "../dllclass/dllclass.h"  //相对目录
#include "stdio.h"

#pragma comment(lib, "../lib/dllclass.lib") //到这找地址

int main()
{
	CMath math;
	int sum =  math.Add(6, 5);
	int sub  = math.Add(6, 5);
	printf("sum = %d, sub = %d\n", sum, sub);
	return 0;
}