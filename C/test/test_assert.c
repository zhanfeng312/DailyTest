#include <stdio.h>
#define NDEBUG
#include <assert.h>

void swap(int *a, int *b)
{
	assert(a != NULL);//������
	assert(b != NULL);

	int tmp_value = *a;
	*a = *b;
	*b = tmp_value;
}

int main(int argc, char *argv[])
{
	int a = 3, b = 4;

	assert(a != 3);//����������ش�������ֹ����ִ�У�����stderr��ӡһ��������Ϣ��Ȼ��ͨ������ abort ����ֹ��������

	printf("before swap: a = %d, b = %d\n", a, b);

	swap(&a, &b);

	printf("after  swap: a = %d, b = %d\n", a, b);

	return 0;
}