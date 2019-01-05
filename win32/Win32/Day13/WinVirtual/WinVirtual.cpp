// WinVirtual.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "windows.h"
#include "stdio.h"

void status()
{
	MEMORYSTATUS ms = {0};
	ms.dwLength = sizeof (ms);
	GlobalMemoryStatus(&ms);   //得到内存使用情况的函数
	printf("Load:%d\n", ms.dwMemoryLoad);  //物理内存的使用率
	printf("TotalPhy:%u\n", ms.dwTotalPhys);
	printf("AvailPhy:%u\n", ms.dwAvailPhys);
	printf("TotalVir:%u\n", ms.dwTotalPageFile);
	printf("AvailVir:%u\n", ms.dwAvailPageFile);
	printf("TotalAddr:%u\n", ms.dwTotalVirtual);  //地址有多少
	printf("AvailAddr:%u\n", ms.dwAvailVirtual);
	printf("***********************************\n");
}
void Virtual_Info()
{
	status();
	CHAR *pszText = (char*)VirtualAlloc(NULL, 1024*1024*1024, 
				MEM_COMMIT, PAGE_READWRITE);
	/*
	MEM_COMMIT - 连 地址 带 内存 一起申请
	MEM_RESERVE - 只申请 地址 不要 内存
    */
	status();
	VirtualFree(pszText, 0, MEM_RELEASE);
	/*
	MEM_DECOMMIT - 只释放内存 不释放 地址
	MEM_RELEASE  - 连 地址 带 内存 都释放
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
	//申请了1个G的地址
	char *pszText = (char*)VirtualAlloc(NULL,
					1024*1024*1024, MEM_RESERVE, PAGE_READWRITE);
	//提交内存,提交了4K个字节的内存
	char *pszText1 = (char*)VirtualAlloc(   
		pszText+4096, 1, MEM_COMMIT, PAGE_READWRITE );
	//给内存写数据
	strcpy(pszText1, "hello reserve");
	//读取内存中的数据
	printf("%s\n", pszText1);
	//内存的释放
	VirtualFree(pszText, 0, MEM_RELEASE);
}
int main(int argc, char* argv[])
{
	//Virtual_Info();
	//Virtual_Commit();
	Virtual_Reserve();
	return 0;
}
