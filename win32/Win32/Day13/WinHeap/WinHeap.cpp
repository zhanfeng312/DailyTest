// WinHeap.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"
#include "stdio.h"

void HeapInfo()
{
	HANDLE hHeap = GetProcessHeap(); //本进程第一个堆的句柄
	printf("第一个堆:%d\n", hHeap);
	HANDLE hHeaps[256] = {0};
	DWORD nCount = GetProcessHeaps(256, hHeaps);
	for (int i = 0; i < nCount; i++)
	{
		printf("%d-%d\n", i, hHeaps[i]);
	}
}
void Heap()
{
	HANDLE hHeap = HeapCreate(HEAP_NO_SERIALIZE,
						1024*1024, 0); //不封顶
	CHAR *pszText = (CHAR*)HeapAlloc(hHeap, 
						HEAP_ZERO_MEMORY, 2*1024*1024);
	strcpy(pszText, "hello heap");
	printf("%s\n", pszText);
	HeapFree(hHeap, HEAP_NO_SERIALIZE, pszText);
	HeapDestroy(hHeap);
}
int main(int argc, char* argv[])
{
	//HeapInfo();
	Heap();
	return 0;
}
