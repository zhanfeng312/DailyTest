

#include "stdafx.h"
#include "windows.h"
#include "stdio.h"

DWORD CALLBACK TestProc1(LPVOID pParam)
{
	CHAR *pszText = (CHAR*)pParam;
	while (1)
	{
		printf("%s\n", pszText);
		Sleep(1000);
	}
	return 0;
}
DWORD CALLBACK TestProc2(LPVOID pParam)
{
	CHAR *pszText = (CHAR*)pParam;
	while (1)
	{
		printf("%s\n", pszText);
		Sleep(1000);
	}
}
void Thread()
{
	DWORD nID = 0;
	char *szText1 = "***************************";  //它是字面值常量,存放在代码区
	HANDLE hThread1 = CreateThread(NULL, 0, 
		TestProc1, szText1,  0, &nID);

	//WaitForSingleObject(hThread1, INFINITE); //可等候句柄 加个等候
	
	char *szText2 = "---------------------------";
	HANDLE hThread2 = CreateThread(NULL, 0, 
		TestProc2, szText2, 0, &nID);  //挂起状态

	//getchar();
	//SuspendThread(hThread1);
	//ResumeThread(hThread2);
}
int main(int argc, char* argv[])
{
	Thread();
	getchar();
	return 0;
}
