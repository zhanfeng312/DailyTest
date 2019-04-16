#include <stdio.h>

int g_vm = 0;

int main (void) {
	printf ("&g_vm = %p\n", &g_vm);

	printf ("整数：");
	scanf ("%d%*c", &g_vm);

	printf ("启动另一进程，输入不同数据，按<回车>继续...");
	getchar ();
	printf ("g_vm = %d\n", g_vm);

	return 0;
}
