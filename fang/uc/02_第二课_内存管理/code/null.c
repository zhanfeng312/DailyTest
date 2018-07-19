#include <stdio.h>
#include <string.h>

// 求字符串最大值
// 成功返回参数字符串中的最大值，失败返回NULL
const char* strmax (const char* a, const char* b) {
	return a && b ? (strcmp (a, b) > 0 ? a : b) : NULL;
}

int main (void) {
	const char* max = strmax ("hello", "world");
//	const char* max = strmax ("hello", NULL);
	if (! max) {
		printf ("求字符串最大值失败！\n");
		return -1;
	}

	printf ("字符串最大值：%s\n", max);

	return 0;
}
