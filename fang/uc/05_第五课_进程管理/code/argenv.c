#include <stdio.h>

void printarg (int argc, char* argv[]) {
	printf ("---- 命令参数 ----\n");

	int i;
	for (i = 0; i < argc; i++)
		printf ("argv[%d] = %s\n", i, argv[i]);

	printf ("------------------\n");
}

void printenv (void) {
	printf ("---- 环境变量 ----\n");

	extern char** environ;
	char** env;
	for (env = environ; env && *env; env++)
		printf ("%s\n", *env);

	printf ("------------------\n");
}

int main (int argc, char* argv[]) {
	printarg (argc, argv);
	printenv ();

	return 0;
}
