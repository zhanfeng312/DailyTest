

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
	printf("���̾��=%d,����ID=%d\n",
		pi.hProcess, pi.dwProcessId);
	WaitForSingleObject(pi.hProcess, INFINITE); // ��������, �ǳ���Ҫ, �Ⱥ�ɵȺ�Ľ������ź�
	printf("wait over!\n");
}
void Kill()
{
	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, 15136); //��ȡ���̾��
	TerminateProcess(hProc, 12345);
}
int main(int argc, char* argv[]) //�������Ĳ���
{
	Proc();
	//Kill();
	return 0;
}
