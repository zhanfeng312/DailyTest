// WinCreate.cpp : Defines the entry point for the application.
//
#include "stdafx.h"
#include "stdio.h"
HMENU hFile = 0;
HINSTANCE g_hInstance=0; //���ܵ�ǰ����ʵ�����
HANDLE g_hOutput = 0;
void OnCreate(HWND hWnd)
{
	HMENU hMain = CreateMenu();  //����һ����˶���˵�
	hFile = CreatePopupMenu();
	AppendMenu(hFile, MF_STRING | MF_CHECKED, 1003, "�½�");
	AppendMenu(hFile, MF_SEPARATOR, 0, "");
	AppendMenu(hFile, MF_STRING | MF_ENABLED, 1004, "�˳�");

	HMENU hHelp = CreatePopupMenu(); //����һ����˵���ʽ�˵�
	AppendMenu(hHelp, MF_STRING | MF_GRAYED, 1005, "����");

	AppendMenu(hMain, MF_POPUP, (UINT)hFile, "�ļ�");
	AppendMenu(hMain, MF_POPUP, (UINT)hHelp, "����");
	SetMenu(hWnd, hMain);
}
BOOL g_state = 0;  //��ʶ��
BOOL g_state1 = 0;
void OnCommand(HWND hWnd, WPARAM wParam)
{
	switch(LOWORD(wParam))
	{
	case 1003:
		{
			if(g_state == 0)
			{
				CheckMenuItem(hFile, 1003,  MF_BYCOMMAND | MF_UNCHECKED);
			}
			else{
				CheckMenuItem(hFile, 0, MF_BYPOSITION | MF_CHECKED);
			}
		}
		g_state = !g_state;  //ÿ��һ��,��ʶ��ȡ��
		break;
	case 1004:
		MessageBox(hWnd, "�˳������", "Infor", MB_OK);
		break;
	case 1005:
		MessageBox(NULL, "���ڱ����", "Infor", MB_OK);
		break;
	}
}
void OnInitMenuPopup(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	char szText[256] = {0};
	sprintf(szText,
		"������ʾ�˵�=%08X, ���������˵���λ��=%d,�Ƿ�Ϊ���ڲ˵�=%d\n", 
		wParam, LOWORD(lParam), HIWORD(lParam));
	WriteConsole(g_hOutput, szText, strlen(szText),
		NULL, NULL);
}
//���ڴ�����
LRESULT CALLBACK WndProc(HWND hWnd,UINT nMsg,WPARAM wParam,LPARAM lParam)
{
	switch(nMsg)
	{
	case WM_INITMENUPOPUP: //�ڲ˵�������,����û��ʾʱ,���ڻᷢ�������Ϣ
		OnInitMenuPopup(hWnd, wParam, lParam);
		break;
	case WM_COMMAND:
		OnCommand(hWnd, wParam);
		break;
	case WM_CREATE: //��Ȼ���ڻ�û��ʾ,��Ҫ�Ѳ˵���ʾ����,û������������ʾ,Ȼ������ʾ�˵�
		OnCreate(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd,nMsg,wParam,lParam);
}
//ע�ᴰ����
BOOL Register(LPSTR lpClassName,WNDPROC wndproc)
{
	WNDCLASSEX wce={0};
	wce.cbSize=sizeof(wce);
	wce.cbClsExtra=0;
	wce.cbWndExtra=0;
	wce.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
	wce.hCursor=NULL;
	wce.hIcon=NULL;
	wce.hIconSm=NULL;
	wce.hInstance=g_hInstance;
	wce.lpfnWndProc=wndproc;
	wce.lpszClassName=lpClassName;
	wce.lpszMenuName=NULL;
	wce.style=CS_HREDRAW | CS_VREDRAW;
	ATOM nAtom=RegisterClassEx(&wce);
	if(nAtom==0)
		return FALSE;
	return TRUE;
}
//����������
HWND CreateMain(LPSTR lpClassName,LPSTR lpWndName)
{
	HWND hWnd=CreateWindowEx(0,lpClassName,lpWndName,WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,g_hInstance,NULL);
	return hWnd;
}
//��ʾ����
void Display(HWND hWnd)
{
	ShowWindow(hWnd,SW_SHOW);
	UpdateWindow(hWnd);
}
//��Ϣѭ��
void Message()
{
	MSG nMsg={0};
	while(GetMessage(&nMsg,NULL,0,0))
	{
		TranslateMessage(&nMsg);
		DispatchMessage(&nMsg);
	}
}
//������
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	AllocConsole();
	g_hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	g_hInstance=hInstance;
	if(!Register("Main",WndProc))
	{
		MessageBox(NULL,"ע��ʧ��","Error",MB_OK);
		return 0;
	}
	HWND hWnd=CreateMain("Main","window");
	Display(hWnd);
	Message();
	return 0;
}



