// WinCreate.cpp : Defines the entry point for the application.
//
#include "stdafx.h"
#include "stdio.h"
HMENU hFile = 0;
HINSTANCE g_hInstance=0; //接受当前程序实例句柄
HANDLE g_hOutput = 0;
void OnCreate(HWND hWnd)
{
	HMENU hMain = CreateMenu();  //构造一个光杆顶层菜单
	hFile = CreatePopupMenu();
	AppendMenu(hFile, MF_STRING | MF_CHECKED, 1003, "新建");
	AppendMenu(hFile, MF_SEPARATOR, 0, "");
	AppendMenu(hFile, MF_STRING | MF_ENABLED, 1004, "退出");

	HMENU hHelp = CreatePopupMenu(); //构造一个光杆弹出式菜单
	AppendMenu(hHelp, MF_STRING | MF_GRAYED, 1005, "关于");

	AppendMenu(hMain, MF_POPUP, (UINT)hFile, "文件");
	AppendMenu(hMain, MF_POPUP, (UINT)hHelp, "帮助");
	SetMenu(hWnd, hMain);
}
BOOL g_state = 0;  //标识量
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
		g_state = !g_state;  //每点一次,标识量取反
		break;
	case 1004:
		MessageBox(hWnd, "退出被点击", "Infor", MB_OK);
		break;
	case 1005:
		MessageBox(NULL, "关于被点击", "Infor", MB_OK);
		break;
	}
}
void OnInitMenuPopup(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	char szText[256] = {0};
	sprintf(szText,
		"即将显示菜单=%08X, 被点击顶层菜单项位置=%d,是否为窗口菜单=%d\n", 
		wParam, LOWORD(lParam), HIWORD(lParam));
	WriteConsole(g_hOutput, szText, strlen(szText),
		NULL, NULL);
}
//窗口处理函数
LRESULT CALLBACK WndProc(HWND hWnd,UINT nMsg,WPARAM wParam,LPARAM lParam)
{
	switch(nMsg)
	{
	case WM_INITMENUPOPUP: //在菜单被激活,但还没显示时,窗口会发出这个消息
		OnInitMenuPopup(hWnd, wParam, lParam);
		break;
	case WM_COMMAND:
		OnCommand(hWnd, wParam);
		break;
	case WM_CREATE: //当然窗口还没显示,就要把菜单显示出来,没见过窗口先显示,然后再显示菜单
		OnCreate(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd,nMsg,wParam,lParam);
}
//注册窗口类
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
//创建主窗口
HWND CreateMain(LPSTR lpClassName,LPSTR lpWndName)
{
	HWND hWnd=CreateWindowEx(0,lpClassName,lpWndName,WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,g_hInstance,NULL);
	return hWnd;
}
//显示窗口
void Display(HWND hWnd)
{
	ShowWindow(hWnd,SW_SHOW);
	UpdateWindow(hWnd);
}
//消息循环
void Message()
{
	MSG nMsg={0};
	while(GetMessage(&nMsg,NULL,0,0))
	{
		TranslateMessage(&nMsg);
		DispatchMessage(&nMsg);
	}
}
//主函数
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
		MessageBox(NULL,"注册失败","Error",MB_OK);
		return 0;
	}
	HWND hWnd=CreateMain("Main","window");
	Display(hWnd);
	Message();
	return 0;
}



