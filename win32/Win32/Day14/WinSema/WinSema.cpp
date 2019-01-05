

#include "stdafx.h"
#include "windows.h"
#include "stdio.h"

HANDLE g_hSema = 0; //���ڽ����ź������

DWORD CALLBACK TestProc (LPVOID pParam)
{
	while (1)
	{
		WaitForSingleObject(g_hSema, INFINITE); //ͨ������,WaitFor����������
		printf("***************\n");
	}
	return 0;
}
int main(int argc, char* argv[])
{
	g_hSema = CreateSemaphore(NULL, 3, 10, NULL);  //�����ź������
	DWORD nID = 0; //�����̺߳��������һ������
	HANDLE hThread = CreateThread(NULL, 0, 
						TestProc, NULL, 0, &nID);
	getchar();
	ReleaseSemaphore(g_hSema, 6, NULL);   //���¸��ź������ü���ֵ, С�ڵ���10
	WaitForSingleObject(hThread, INFINITE); //��ֹ���߳̽���
	CloseHandle(hThread );
	CloseHandle(g_hSema );
	return 0;
}
