#include <stdio.h>
#include <string.h>


int main(int argc, char *argv[])
{
	char buf[] = "1;http://acs.totaltv.com.tw";
	char* pURL = NULL;
	char* pStatus = NULL;
	char* pSting = NULL;

	//×Ö·û´®·Ö¸î
	pStatus = strtok_r(buf, ";", &pSting);
	pURL = strtok_r(NULL, ";", &pSting);

	printf("%s:%s\n", pURL, pSting);

    return 0;
}