
#define DLLCLASS_EXPORTS
#include "dllclass.h"
#include "windows.h"
#include "stdio.h"
BOOL CALLBACK DllMain (HINSTANCE hDll, DWORD fdwReason,
					   LPVOID lpvReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		//��ʼ������ 
		printf("Loading... ...\n");
		break;
	case DLL_PROCESS_DETACH:
		//�ƺ���
		printf("UnLoading... ...\n");
		break;
	}
	return TRUE;
}
int CMath::Add(int add1, int add2)
{
	return add1 + add2;
}
int CMath::Sub(int sub1, int sub2)
{
	return sub1 - sub2;
}