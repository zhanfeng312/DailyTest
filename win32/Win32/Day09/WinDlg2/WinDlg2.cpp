// WinCreate.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
HINSTANCE g_hInstance=0;//接受当前程序实例句柄
/*
INT CALLBACK DialogProc(
	HWND hwndDlg,  //窗口句柄
	UINT uMsg,     //消息ID
	WPARAM wParam, //消息参数
	LPARAM lParam  //消息参数
);
*/
INT CALLBACK DlgProc(HWND hwndDlg, UINT uMsg,
					 WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		MessageBox(NULL, "WM_INITDIALOG", "Infor", MB_OK);
		break;
	case WM_CREATE:
		MessageBox(NULL, "WM_CREATE", "Infor", MB_OK);
		break;
	case WM_DESTROY:
		MessageBox(NULL, "对话框被销毁了", "Infor", MB_OK);
		break;
	case WM_SYSCOMMAND:
		if (wParam == SC_CLOSE)
		{
			DestroyWindow(hwndDlg);
			//EndDialog(hwndDlg, 1231);
			//只能隐藏 无模式对话框，不能销毁
			return true;
		}
		break;
	}
	return FALSE;
}
void OnDlg(HWND hWnd)
{
	HWND hDlg = CreateDialog(g_hInstance, MAKEINTRESOURCE(IDD_DIALOG1),
		hWnd, DlgProc);
	ShowWindow(hDlg, SW_SHOW); //原样显示
}
void OnCommand(HWND hWnd, WPARAM wParam)
{
	switch (LOWORD (wParam))
	{
	case ID_DLG:
		OnDlg(hWnd);  //创建无模式对话框
		break;
	}
}
//窗口处理函数
LRESULT CALLBACK WndProc(HWND hWnd,UINT nMsg,WPARAM wParam,LPARAM lParam)
{
	switch(nMsg)
	{
	case WM_COMMAND:
		OnCommand(hWnd, wParam);
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
	wce.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1); //把菜单挂在窗口上
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



