

#include "stdafx.h"
#include "windows.h"
#include "stdio.h"

HANDLE g_hSema = 0; //用于接收信号量句柄

DWORD CALLBACK TestProc (LPVOID pParam)
{
	while (1)
	{
		WaitForSingleObject(g_hSema, INFINITE); //通过三次,WaitFor函数会阻塞
		printf("***************\n");
	}
	return 0;
}
int main(int argc, char* argv[])
{
	g_hSema = CreateSemaphore(NULL, 3, 10, NULL);  //返回信号量句柄
	DWORD nID = 0; //创建线程函数的最后一个参数
	HANDLE hThread = CreateThread(NULL, 0, 
						TestProc, NULL, 0, &nID);
	getchar();
	ReleaseSemaphore(g_hSema, 6, NULL);   //重新给信号量设置计数值, 小于等于10
	WaitForSingleObject(hThread, INFINITE); //防止主线程结束
	CloseHandle(hThread );
	CloseHandle(g_hSema );
	return 0;
}
