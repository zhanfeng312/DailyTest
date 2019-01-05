

#include "stdafx.h"
#include "windows.h"
#include "stdio.h"
void Proc()
{
	STARTUPINFO si = {0};
	PROCESS_INFORMATION pi = {0};
	
	CreateProcess("C:/Windows/system32/calc.exe", NULL,
		NULL, NULL, FALSE, 0, NULL, NULL, &si,
		&pi);
	printf("进程句柄=%d,进程ID=%d\n",
		pi.hProcess, pi.dwProcessId);
	WaitForSingleObject(pi.hProcess, INFINITE); // 阻塞函数, 非常重要, 等候可等候的进程有信号
	printf("wait over!\n");
}
void Kill()
{
	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, 15136); //获取进程句柄
	TerminateProcess(hProc, 12345);
}
int main(int argc, char* argv[]) //主函数的参数
{
	Proc();
	//Kill();
	return 0;
}
