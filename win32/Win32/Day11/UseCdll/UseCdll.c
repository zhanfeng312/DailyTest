
#pragma comment(lib, "../lib/Cdll.lib")
//֪ͨ������ ���� ���� �����ĵ�ַ

int main()  //һ����main������,��lib�ļ� ���� ��dll�ļ�
{
	int sum, sub;
	sum = Cdll_add(8, 5);
	sub = Cdll_sub(8, 5);
	printf("sum = %d, sub = %d\n", sum, sub);
	return 0;
}