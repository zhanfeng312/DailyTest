// WinCreate.cpp : Defines the entry point for the application.
#include "stdafx.h"

HINSTANCE g_hInstance = 0;//接受当前程序实例句柄
void OnCreate(HWND hWnd)
{
	HMENU hSys = GetSystemMenu(hWnd, FALSE);  //获得系统菜单句柄
	for(int i = 0; i < 6; i++)
	{
		DeleteMenu(hSys, 0, MF_BYPOSITION);  //删除菜单项
	}
	AppendMenu(hSys, MF_SEPARATOR, 0, "");   //增加菜单项
	AppendMenu(hSys, MF_STRING, 1001, "我的菜单项");
}
void OnSysCommand(HWND hWnd, WPARAM wParam)
{
	switch(LOWORD(wParam))
	{
	case 1001:
		MessageBox(NULL, "我的菜单项被点击", "Infor", 
			MB_ABORTRETRYIGNORE);
		break;
	}
}
void OnRButtonUp(HWND hWnd, LPARAM lParam)
{
	HMENU hPopup = CreatePopupMenu();           //建立光板弹出式菜单
	AppendMenu(hPopup, MF_STRING, 1002, "新建");//增加菜单项
	AppendMenu(hPopup, MF_SEPARATOR, 0, "");
	AppendMenu(hPopup, MF_STRING, 1003, "退出");
	POINT pt = {0};
	pt.x = LOWORD(lParam);  //转换一下
	pt.y = HIWORD(lParam);
	ClientToScreen(hWnd, &pt); //设置的是客户区下的坐标

	int nRet = TrackPopupMenu(hPopup, 
		TPM_CENTERALIGN | TPM_VCENTERALIGN | TPM_RETURNCMD,   //加了TPM_RETURNCMD风格
		pt.x, pt.y, 0, hWnd, NULL); //阻塞函数，返回的是点击的菜单项的ID
	switch(nRet)
	{
	case 1002:
		MessageBox(NULL, "没发出消息,新建被点击",
			"Infor", MB_OK);
		break;
	case 1003:
		MessageBox(NULL, "没发出消息,退出被点击",
			"Infor", MB_OK);
		break;
	}
}
void OnCommand(HWND hWnd, WPARAM wParam)
{
	switch(LOWORD(wParam))
	{
	case 1002:
		MessageBox(NULL, "新建被点击", "Infor", MB_OK);
		break;
	case 1003:
		MessageBox(NULL, "退出被点击", "Infor", MB_OK);
		break;
	}
}
void OnContextmenu(HWND hWnd, LPARAM lParam)
{
	HMENU hPopup = CreatePopupMenu();           //建立光板弹出式菜单
	AppendMenu(hPopup, MF_STRING, 1002, "新建");//增加菜单项
	AppendMenu(hPopup, MF_SEPARATOR, 0, "");
	AppendMenu(hPopup, MF_STRING, 1003, "退出");
	POINT pt = {0};
	pt.x = LOWORD(lParam);  //转换一下
	pt.y = HIWORD(lParam);
	//ClientToScreen(hWnd, &pt); //不需要转换(专业人士)

	int nRet = TrackPopupMenu(hPopup, 
		TPM_CENTERALIGN | TPM_VCENTERALIGN | TPM_RETURNCMD,   //加了TPM_RETURNCMD风格
		pt.x, pt.y, 0, hWnd, NULL); //阻塞函数，返回的是点击的菜单项的ID
	switch(nRet)
	{
	case 1002:
		MessageBox(NULL, "没发出消息,新建被点击",
			"Infor", MB_OK);
		break;
	case 1003:
		MessageBox(NULL, "没发出消息,退出被点击",
			"Infor", MB_OK);
		break;
	}
}
//窗口处理函数
LRESULT CALLBACK WndProc(HWND hWnd,UINT nMsg,WPARAM wParam,LPARAM lParam)
{
	switch(nMsg)
	{
	case WM_CONTEXTMENU:  //这个消息是在右键弹起后产生
		OnContextmenu(hWnd, lParam);
		break;
	case WM_COMMAND:
		OnCommand(hWnd, wParam);
		break;
	case WM_RBUTTONUP:
		//OnRButtonUp(hWnd, lParam); //窗口客户区坐标区的位置
		break;
	case WM_SYSCOMMAND:
		OnSysCommand(hWnd, wParam);
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



