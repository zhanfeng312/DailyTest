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

void test()
{
    int aOperID[8];
    char aOperator[] = "2;5311,;10,;";
    char *pToken = strtok(aOperator, ";");
    int i = 0;
    pToken = strtok(NULL, ";");

    while (pToken)
    {
        printf("%s\n", pToken);
        aOperID[i] = atoi(pToken);
        printf("%d\n", aOperID[i]);
        pToken = strtok(NULL, ";");
        i++;
    }

    printf("i = %d\n", i);
}

int main(int argc, char *argv[])
{

    test();

    /*test_strdup();

    test_strtok_r();*/

    return 0;
}