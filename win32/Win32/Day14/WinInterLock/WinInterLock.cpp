

#include "stdafx.h"
#include "windows.h"
#include "stdio.h"
long g_nValue = 0;   //ȫ�ֱ���

DWORD CALLBACK TestProc1 (LPVOID pParam)
{
	for (int i = 0; i < 100000; i++)
	{
	//	g_nValue++;
		InterlockedIncrement(&g_nValue);  //�Ȱѱ������ڴ���ס, ������
	}
	return 0;
}
DWORD CALLBACK TestProc2 (LPVOID pParam)
{
	for (int i = 0; i < 100000; i++)
	{
	//  g_nValue++;
		InterlockedIncrement(&g_nValue);  //����������   ����,CPUʱ��Ƭ���˷�
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
