
#include "stdafx.h"
#include "windows.h"
#include "stdio.h"
HANDLE g_hEvent = 0;  //用于接收事件句柄

DWORD CALLBACK PrintProc (LPVOID pParam)
{
	while (1)
	{
		WaitForSingleObject(g_hEvent, INFINITE);
		//ResetEvent(g_hEvent);  //变成无信号
		printf("***********************************\n");
	}
	return 0;
}
DWORD CALLBACK CtrlProc (LPVOID pParam)
{
	while (1)
	{
		Sleep(1000);   //使程序睡上1秒
		SetEvent(g_hEvent); //设置为有信号状态
	}
	return 0;
}
int main(int argc, char* argv[])
{
	g_hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	DWORD nID = 0;
	HANDLE hThread[2] = {0};
	hThread[0] = CreateThread(NULL, 0, PrintProc, NULL, 
					0, &nID);
	hThread[1] = CreateThread(NULL, 0, CtrlProc, NULL, 
					0, &nID);
	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);
	CloseHandle(hThread[0] );
	CloseHandle(hThread[1] );
	CloseHandle(g_hEvent );
	return 0;
}
