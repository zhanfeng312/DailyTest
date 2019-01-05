// WinCreate.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
HINSTANCE g_hInstance=0;//���ܵ�ǰ����ʵ�����
void OnCreate(HWND hWnd)
{
	CreateWindowEx(0, "STATIC", "hello static",   //���־�̬��
		WS_CHILD | WS_VISIBLE | SS_NOTIFY,
		100, 100, 200, 50, hWnd, (HMENU)1001,
		g_hInstance, NULL);
	CreateWindowEx(0, "STATIC", "#101", WS_CHILD | WS_VISIBLE | SS_ICON | SS_NOTIFY,  //ͼ�꾲̬�� 
		400, 100, 0, 0, hWnd, (HMENU)1002,
		g_hInstance, NULL);
}
void OnCommand(HWND hWnd, WPARAM wParam)
{
	switch ( LOWORD(wParam))
	{
	case 1001: //�ĸ��ؼ�
		{
			if (HIWORD (wParam) == STN_CLICKED) //������ʲô��
			{
				MessageBox(NULL, "����ʲô", "Infor",
					MB_OK);
			}
		}
		break;
	case ID_BLACK:
		{
		HICON hBlack = LoadIcon(g_hInstance,
			MAKEINTRESOURCE(IDI_ICON1));
		HWND hStatic = GetDlgItem(hWnd, 1002); //�õ��ؼ����
		SendMessage(hStatic, STM_SETICON,
				(WPARAM)hBlack, 0);
		}
		break;
	case ID_BLUE:
		HICON hBlue = LoadIcon (g_hInstance, 
			MAKEINTRESOURCE(IDI_ICON2));
		HWND hStatic = GetDlgItem(hWnd, 1002);
		SendMessage(hStatic, STM_SETICON,
				(WPARAM)hBlue, 0);
		break;
	}
}
//���ڴ�����
LRESULT CALLBACK WndProc(HWND hWnd,UINT nMsg,WPARAM wParam,LPARAM lParam)
{
	switch(nMsg)
	{
	case WM_COMMAND:
		OnCommand(hWnd, wParam);
		break;
	case WM_CREATE:
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
	wce.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
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



