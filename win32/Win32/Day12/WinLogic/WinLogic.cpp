// WinLogic.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "windows.h"
#include "stdio.h"
#include "string.h"
void UseDir()
{
	//CreateDirectory("c:/123", NULL);
	//MoveFile("c:/hello", "c:/123/nohello");//移动目录
	RemoveDirectory("c:/123/nohello");  //只能删除空目录
}
void GetLogic()
{
	DWORD nLogic = GetLogicalDrives(); //得到盘符
	printf("%08x\n", nLogic);
}
void GetPath()
{
	char szText[256] = {0};
	UINT nS1 = GetSystemDirectory(szText, 256);
	printf("系统目录为:%s\n", szText);
	printf("---------------\n");

	memset(szText, 0, sizeof (szText));
	DWORD nS2 = GetCurrentDirectory(256, szText);
	printf("当前程序的工作目录为:%s\n", szText);
	printf("---------------\n");

	memset(szText, 0, sizeof (szText));
	SetCurrentDirectory("C:/123");
	DWORD nS3 = GetCurrentDirectory(256, szText);
	printf("当前程序的工作目录为:%s\n", szText);
	printf("---------------\n");

	memset(szText, 0, sizeof (szText));
	UINT nS4 = GetWindowsDirectory(szText, 256);
	printf("windows目录为:%s\n", szText);
}
void OnFile()
{
	HANDLE handle = CreateFile("C:/123/1.txt", GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ,
		NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	char szText[256] = "hello world!";
	unsigned long length;
	WriteFile(handle, szText, strlen(szText), &length, NULL);
	printf("%d\n", length);
}
void Find()
{
	char szPath[] = "c:/*.*";
	WIN32_FIND_DATA wfd = {0};
	HANDLE hFind = FindFirstFile(szPath, &wfd);
	BOOL goFind = TRUE;
	while (goFind)
	{
		if (wfd.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
		{
			printf("[%s]\n", wfd.cFileName);
		}
		else{
			printf("%s\n", wfd.cFileName);
		}
		goFind = FindNextFile(hFind, &wfd);
	}
	FindClose(hFind);
}
int main(int argc, char* argv[])
{
	//UseDir();
	//GetLogic();
	//GetPath();
	//OnFile(); //windows下的文件操作函数
	Find();
	return 0;
}
