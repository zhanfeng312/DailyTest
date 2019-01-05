// WinVirtual.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "windows.h"
#include "stdio.h"

void status()
{
	MEMORYSTATUS ms = {0};
	ms.dwLength = sizeof (ms);
	GlobalMemoryStatus(&ms);   //�õ��ڴ�ʹ������ĺ���
	printf("Load:%d\n", ms.dwMemoryLoad);  //�����ڴ��ʹ����
	printf("TotalPhy:%u\n", ms.dwTotalPhys);
	printf("AvailPhy:%u\n", ms.dwAvailPhys);
	printf("TotalVir:%u\n", ms.dwTotalPageFile);
	printf("AvailVir:%u\n", ms.dwAvailPageFile);
	printf("TotalAddr:%u\n", ms.dwTotalVirtual);  //��ַ�ж���
	printf("AvailAddr:%u\n", ms.dwAvailVirtual);
	printf("***********************************\n");
}
void Virtual_Info()
{
	status();
	CHAR *pszText = (char*)VirtualAlloc(NULL, 1024*1024*1024, 
				MEM_COMMIT, PAGE_READWRITE);
	/*
	MEM_COMMIT - �� ��ַ �� �ڴ� һ������
	MEM_RESERVE - ֻ���� ��ַ ��Ҫ �ڴ�
    */
	status();
	VirtualFree(pszText, 0, MEM_RELEASE);
	/*
	MEM_DECOMMIT - ֻ�ͷ��ڴ� ���ͷ� ��ַ
	MEM_RELEASE  - �� ��ַ �� �ڴ� ���ͷ�
	*/
	status();
}
void Virtual_Commit()
{
	char *pszText = (char*)VirtualAlloc(NULL, 
		             4096, MEM_COMMIT, PAGE_READWRITE);
	strcpy(pszText, "hello commit");
	printf("%s\n", pszText);
	VirtualFree(pszText, 0, MEM_RELEASE);
}
void Virtual_Reserve()
{
	//������1��G�ĵ�ַ
	char *pszText = (char*)VirtualAlloc(NULL,
					1024*1024*1024, MEM_RESERVE, PAGE_READWRITE);
	//�ύ�ڴ�,�ύ��4K���ֽڵ��ڴ�
	char *pszText1 = (char*)VirtualAlloc(   
		pszText+4096, 1, MEM_COMMIT, PAGE_READWRITE );
	//���ڴ�д����
	strcpy(pszText1, "hello reserve");
	//��ȡ�ڴ��е�����
	printf("%s\n", pszText1);
	//�ڴ���ͷ�
	VirtualFree(pszText, 0, MEM_RELEASE);
}
int main(int argc, char* argv[])
{
	//Virtual_Info();
	//Virtual_Commit();
	Virtual_Reserve();
	return 0;
}
