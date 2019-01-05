// WinEnv.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"
#include "stdio.h"

void Env()
{
	char *pszEnv = (char*)GetEnvironmentStrings( );
	char *pszText = pszEnv;
	while (pszText[0])
	{
		printf("%s\n", pszText);
		pszText = pszText + strlen(pszText) + 1;//这样就可以跳过\0
	}
	//释放这块地址
	FreeEnvironmentStrings(pszEnv);
}
void Variable()
{
	SetEnvironmentVariable("FZF", "GOOD");
	char szValue[256] = {0};
	//环境变量的值
	GetEnvironmentVariable("FZF", szValue, 256);  //在哪都可以拿到
	printf("%s\n", szValue);
}
void ProcInfo()
{
	DWORD nID = GetCurrentProcessId();
	HANDLE hProc = GetCurrentProcess();
	printf("进程ID=%d,进程句柄=%d\n", nID, hProc);
	getchar();
}
int main(int argc, char* argv[])
{
	//Env();
	//Variable();
	ProcInfo();
	//system("pause");
	return 0;
}
