#include <stdio.h>

int main (void) {
	int data;
	fscanf (stdin, "%d", &data);
	fprintf (stdout, "标准输出：%d\n", data);
	fprintf (stderr, "标准错误：%d\n", data);
	return 0;
}
