#include <stdio.h>

void printenv (void) {
	printf ("---- 环境变量 ----\n");

	extern char** environ;
	char** env;
	for (env = environ; env && *env; ++env)
		printf ("%s\n", *env);

	printf ("------------------\n");
}

int main (void) {
	char env[256];
	const char* name = "MYNAME";
	// 添加环境变量
	sprintf (env, "%s=minwei", name);
	putenv (env);
	printf ("%s=%s\n", name, getenv (name));
	// 修改环境变量
	sprintf (env, "%s=bjarne", name);
	putenv (env);
	printf ("%s=%s\n", name, getenv (name));
	// 不存在就添加，存在不覆盖
	setenv (name, "minwei", 0);
	printf ("%s=%s\n", name, getenv (name));
	// 不存在就添加，存在就覆盖
	setenv (name, "minwei", 1);
	printf ("%s=%s\n", name, getenv (name));

	printenv ();
	// 删除环境变量
	unsetenv (name);
	printenv ();
	// 清空环境变量
	clearenv ();
	printenv ();

	return 0;
}
