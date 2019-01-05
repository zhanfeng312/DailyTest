// WinCreate.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
HINSTANCE g_hInstance=0; //接受当前程序实例句柄
//窗口处理函数
void OnCommand(HWND hWnd, WPARAM wParam)
{
	switch(LOWORD(wParam) )
	{
	case ID_SET:
		MessageBox(NULL, "点了CTRL+M", "Infor", MB_OK);
		break;
	case ID_NEW:
		{
			if (HIWORD(wParam) == 0)
				MessageBox(NULL, "新建被点击", "Infor", MB_OK);
			else
				MessageBox(NULL, "没点新建", "Infor", MB_OK);
		}
		break;
	}
}BYTE
LRESULT CALLBACK WndProc(HWND hWnd,UINT nMsg,WPARAM wParam,LPARAM lParam)
{
	switch(nMsg)
	{
	case WM_COMMAND:
		OnCommand(hWnd, wParam);
		break;
	case WM_SETCURSOR:  //鼠标有移动,就会连续不断地产生
		{
		//  HCURSOR hBall = LoadCursor(g_hInstance,
		//	    MAKEINTRESOURCE(IDC_CURSOR2));
		//	HCURSOR hRect = LoadCursor(g_hInstance,
		//		MAKEINTRESOURCE(IDC_CURSOR1));
			HCURSOR hBall = LoadCursorFromFile(     //频繁加载内存
				"c:/Windows/Cursors/aero_working_l.ani");
			HCURSOR hRect = LoadCursorFromFile(
				"c:/Windows/Cursors/aero_working.ani");
		
			if (LOWORD(lParam) == HTCLIENT) //当前区域在客户区
			{
				POINT pt = {0};
	            GetCursorPos(&pt);       //屏幕坐标系下的坐标
				RECT rc = {0};
			    GetClientRect(hWnd, &rc);//客户区坐标系下的坐标
				ScreenToClient(hWnd, &pt); //输入输出参数
				if(pt.x <= rc.right/2)
				{
					SetCursor(hRect);
				}else{
					SetCursor(hBall);
				}
				return 0;
			}else{
				//什么都不写
			}
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
	wce.hCursor = LoadCursor(g_hInstance,
		MAKEINTRESOURCE(IDC_CURSOR1));
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
	HACCEL hAccel = LoadAccelerators(g_hInstance,
		MAKEINTRESOURCE(IDR_ACCELERATOR1));
	MSG nMsg={0};
	while(GetMessage(&nMsg,NULL,0,0))
	{
		if (! TranslateAccelerator(nMsg.hwnd,
			                     hAccel, &nMsg))
		{
			TranslateMessage(&nMsg);
			DispatchMessage(&nMsg);
		}
	}
}
//主函数
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	g_hInstance=hInstance;
	if(!Register("Main",WndProc))
	{
		MessageBox(NULL,"注册失败","Error",MB_OK);
		return 0;
	}
	CHAR szTitle[256] = {0};
	LoadString(g_hInstance, IDS_WND, szTitle, 256); //动态获取字符串资源
	HWND hWnd=CreateMain("Main",szTitle);
	Display(hWnd);
	Message();
	return 0;
}



