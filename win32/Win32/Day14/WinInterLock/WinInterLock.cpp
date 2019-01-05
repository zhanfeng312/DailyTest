

#include "stdafx.h"
#include "windows.h"
#include "stdio.h"
long g_nValue = 0;   //全局变量

DWORD CALLBACK TestProc1 (LPVOID pParam)
{
	for (int i = 0; i < 100000; i++)
	{
	//	g_nValue++;
		InterlockedIncrement(&g_nValue);  //先把变量的内存锁住, 最后解锁
	}
	return 0;
}
DWORD CALLBACK TestProc2 (LPVOID pParam)
{
	for (int i = 0; i < 100000; i++)
	{
	//  g_nValue++;
		InterlockedIncrement(&g_nValue);  //阻塞在这里   阻塞,CPU时间片被浪费
	}
	return 0;
}
int main(int argc, char* argv[])
{
	DWORD nID = 0;
	HANDLE hThread[2] = { 0 };
	hThread[0] = CreateThread(NULL, 0, TestProc1, NULL, 
		0, &nID);
	hThread[1] = CreateThread(NULL, 0, TestProc2, NULL,
		0, &nID);
	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);
	printf("%d\n", g_nValue);
	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);
	return 0;
}
