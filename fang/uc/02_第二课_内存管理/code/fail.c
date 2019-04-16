#include <stdio.h>

// 整数取模
// 成功返回0，失败返回-1
int intmod (int a, int b, int* mod) {
	if (b == 0)
		return -1;

	*mod = a % b;

	return 0;
}

int main (void) {
	printf ("两个整数：");
	int a, b;
	scanf ("%d%d", &a, &b);

	int mod;
	if (intmod (a, b, &mod) == -1) {
		printf ("整数取模失败！\n");
		return -1;
	}

	printf ("整数取模：%d\n", mod);

	return 0;
}
