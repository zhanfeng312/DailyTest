// WinCreate.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "stdio.h"
HINSTANCE g_hInstance=0;//接受当前程序实例句柄
HANDLE g_hOutput = 0;
int g_xPos = 100; //两个全局变量
int g_yPos = 100;
BOOL Left_Right = 1;
BOOL Right_Left = 0;
BOOL Up_Down = 1;
BOOL Down_Up = 0;
void OnTimer(HWND hWnd, WPARAM wParam)
{
	char szText[256] = {0};
	sprintf(szText, "定时器:%d\n", wParam);
	WriteConsole(g_hOutput, szText, strlen(szText),
		NULL, NULL);
	RECT rc = {0};
	GetClientRect(hWnd, &rc); //获取窗口的边界信息
	if(g_xPos <= rc.left)
	{
		Left_Right = 1;
		Right_Left = 0;
	}
	else if(g_xPos >= rc.right-50)
	{
		Right_Left = 1;
		Left_Right = 0;
	}
	if (Left_Right == 1)
		g_xPos++;
	else if(Right_Left == 1)
		g_xPos--;
	if(g_yPos <= rc.top)
	{
		Up_Down = 1;
		Down_Up = 0;
	}
	else if(g_yPos >= rc.bottom-50)
	{
		Down_Up = 1;
		Up_Down = 0;
	}
	if(Up_Down == 1)
		g_yPos++;
	else if(Down_Up ==1)
		g_yPos--;
	InvalidateRect(hWnd, NULL, TRUE);
}
void OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps = { 0 };
	HDC hdc = BeginPaint(hWnd, &ps);
	Ellipse(hdc, g_xPos, g_yPos, g_xPos+50, g_yPos+50); //画圆
	EndPaint(hWnd, &ps);
}
/*VOID CALLBACK TimerProc(HWND hWnd, UINT nMsg,
						UINT idEvent, DWORD dwCurrent) //第二个参数消息ID, 第三个参数定时器ID
{
	char szText[256] = {0};
	sprintf(szText, "定时器处理函数处理:%d\n", idEvent);
	WriteConsole(g_hOutput, szText, strlen(szText),
		NULL, NULL);
}*/
//窗口处理函数
LRESULT CALLBACK WndProc(HWND hWnd,UINT nMsg,WPARAM wParam,LPARAM lParam)
{
	switch(nMsg)
	{
	case WM_LBUTTONDOWN:
		KillTimer(hWnd, 1);
		break;
	case WM_PAINT:
		OnPaint(hWnd);
		break;
	case WM_TIMER:
		OnTimer(hWnd, wParam);
		break;
	case WM_CREATE:
		{
			SetTimer(hWnd, 1, 10, NULL);
			//SetTimer(hWnd, 2, 2000, TimerProc);
		}
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
	HWND hWnd=CreateWindowEx(0,lpClassName,lpWndName,
		WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,
		CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,g_hInstance,
		NULL);
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



