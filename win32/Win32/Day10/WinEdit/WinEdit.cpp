// WinCreate.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include "resource.h"
HINSTANCE g_hInstance = 0;//接受当前程序实例句柄
void OnCreate(HWND hWnd)
{
	HWND hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", WS_CHILD | WS_VISIBLE |  //在扩展风格加WS_EX_CLIENTEDGE,陷进去
		WS_BORDER | ES_AUTOHSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | WS_HSCROLL |
		WS_VSCROLL,                                                       //加上一个黑边界
		0, 0, 200, 200, hWnd, (HMENU)1001, g_hInstance,
		NULL);
	/*
	  ES_PASSWORD - 只针对单行编辑框
	  ES_NUMBER   - 只能输入 数字键 ，不能输入 字符键
	*/
	HFONT hFont = CreateFont(30, 0, 0, 0, 900, 0, 0, 0,
		GB2312_CHARSET, 0, 0, 0, 0, "华文彩云");
	SendMessage(hEdit, WM_SETFONT		, (WPARAM)hFont, 1);
}
void OnSave(HWND hWnd)
{
	HWND hEdit = GetDlgItem(hWnd, 1001);
	LRESULT nLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
	CHAR *pszText = (CHAR*)malloc(nLen+1);
	memset(pszText, 0, nLen+1);  //好的编程习惯
	SendMessage(hEdit, WM_GETTEXT, nLen+1, (LPARAM)pszText);
	FILE *pFile = fopen("c:/my.txt", "w");
	fwrite(pszText, 1, nLen, pFile);
	fclose(pFile);
	free(pszText);
	SetWindowText(hWnd, "window");
}
void OnOpen(HWND hWnd)
{
	FILE *pFile = fopen("c:/my.txt", "r");
	fseek(pFile, 0, SEEK_END);
	long nLen = ftell(pFile);
	char *pszText = (char*)malloc(nLen+1);
	memset(pszText, 0, nLen+1);
	fseek(pFile, 0, SEEK_SET);
	fread(pszText, 1, nLen, pFile);
	fclose(pFile);
	HWND hEdit = GetDlgItem(hWnd, 1001);
	SendMessage(hEdit, WM_SETTEXT,0, (LPARAM)pszText);
	free(pszText);
}

void OnCommand(HWND hWnd, WPARAM wParam)
{
	switch (LOWORD (wParam))
	{
	case 1001:
		{
			if (HIWORD (wParam) == EN_CHANGE)  //wParam的高十六位保存通知码，依附WM_COMMAND消息发送出来
			{
				SetWindowText(hWnd, "window *");
			}
		}
		break;
	case ID_SAVE:
		OnSave(hWnd);
		break;
	case ID_OPEN:
		OnOpen(hWnd);
		break;
	case ID_FIND:
		OnFind(hWnd);  //匹配选项
		break;
	}
}
void OnSize(HWND hWnd, LPARAM lParam)
{
	int nWidth = LOWORD(lParam);
	int nHight = HIWORD(lParam); //变化后的高度和宽度
	HWND hEdit = GetDlgItem(hWnd, 1001); //得到控件的句柄
	MoveWindow(hEdit, 0, 0, nWidth, nHight, TRUE);
}
//窗口处理函数
LRESULT CALLBACK WndProc(HWND hWnd,UINT nMsg,WPARAM wParam,LPARAM lParam)
{
	switch(nMsg)
	{
	case WM_CTLCOLOREDIT:  //给父窗口发送
		{
			HDC hEditdc = (HDC)wParam;
			SetTextColor(hEditdc, RGB(0, 255, 0)); //改字体颜色
			SetBkColor(hEditdc, RGB(255, 0, 0) );
		    return (LRESULT)CreateSolidBrush( RGB(255, 0, 0));
		}
		break;
	case WM_SIZE:
		OnSize(hWnd, lParam);
		break;
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
	wce.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
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



