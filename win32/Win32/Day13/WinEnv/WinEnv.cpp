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
		pszText = pszText + strlen(pszText) + 1;//�����Ϳ�������\0
	}
	//�ͷ�����ַ
	FreeEnvironmentStrings(pszEnv);
}
void Variable()
{
	SetEnvironmentVariable("FZF", "GOOD");
	char szValue[256] = {0};
	//����������ֵ
	GetEnvironmentVariable("FZF", szValue, 256);  //���Ķ������õ�
	printf("%s\n", szValue);
}
void ProcInfo()
{
	DWORD nID = GetCurrentProcessId();
	HANDLE hProc = GetCurrentProcess();
	printf("����ID=%d,���̾��=%d\n", nID, hProc);
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
