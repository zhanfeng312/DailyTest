#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_strdup()
{
	const char *s = "Hello, I am Justin Fang";

	char *d = strdup(s);//内部调用了malloc
	if (d != NULL) {
		printf("%s\n", d);
		free(d);//一定要free
		d = NULL;
	}
}

void test_strtok_r()
{
	char buf[] = "1;http://acs.totaltv.com.tw";
	char* pURL = NULL;
	char* pStatus = NULL;
	char* pSting = NULL;

	//字符串分割
	pStatus = strtok_r(buf, ";", &pSting);
	pURL = strtok_r(NULL, ";", &pSting);

	printf("%s:%s\n", pURL, pSting);
}

int main(int argc, char *argv[])
{
	test_strdup();

	test_strtok_r();

	getchar();

    return 0;
}