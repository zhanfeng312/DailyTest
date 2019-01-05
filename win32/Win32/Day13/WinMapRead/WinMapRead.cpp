// WinMapRead.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"
#include "stdio.h"

int main(int argc, char* argv[])
{
	//打开内存映射文件
	HANDLE hMap = OpenFileMapping(FILE_MAP_ALL_ACCESS,
		TRUE, "FZF");
	char *pszText = (char*)MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 
		0, 64*1024, 0);
	printf("%s\n", pszText);
	UnmapViewOfFile(pszText);
	CloseHandle(hMap);

	return 0;
}
