

#include "../dllclass/dllclass.h"  //���Ŀ¼
#include "stdio.h"

#pragma comment(lib, "../lib/dllclass.lib") //�����ҵ�ַ

int main()
{
	CMath math;
	int sum =  math.Add(6, 5);
	int sub  = math.Add(6, 5);
	printf("sum = %d, sub = %d\n", sum, sub);
	return 0;
}