

#include "stdafx.h"
#include "windows.h"
#include "stdio.h"

HANDLE g_hEvent = 0; //接收事件句柄
HANDLE g_hSeg = 0;   //接收信号量句柄
char c = 0;
//打印线程
DWORD CALLBACK PrintProc (LPVOID pParam)
{
	WaitForSingleObject(g_hEvent, INFINITE);
	while (1){
		WaitForSingleObject(g_hSeg, INFINITE);
		printf("************\n");
	}
		return 0;
}
//控制线程
DWORD CALLBACK CtrlProc (LPVOID pParam)
{
	SetEvent(g_hEvent);
	while (1)
	{
	    scanf("%c", &c);
		if (c >= '1' && c <= '9'){
		  ReleaseSemaphore(g_hSeg, c - '0', NULL);
		}
		else if (c == 'e' || c == 'E'){
			break;
		}
		else
			continue;
	}
	return 0;
}
int main(int argc, char* argv[])
{
	g_hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	g_hSeg = CreateSemaphore(NULL, 0, 10, NULL);

	DWORD nID = 0;
	HANDLE hThread[2] = {0};
	//创建两个线程
	hThread[0] = CreateThread(NULL, 0, 
					PrintProc, NULL, 0, &nID);
	hThread[1] = CreateThread(NULL, 0,
					CtrlProc, NULL, 0, &nID);
	WaitForMultipleObjects(2, hThread, FALSE, INFINITE);
	printf("wait over! \n");
	CloseHandle (hThread[0]);
	CloseHandle (hThread[1]);
	CloseHandle (g_hEvent);
	CloseHandle (g_hSeg);

	return 0;
}
