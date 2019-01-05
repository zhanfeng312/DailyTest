// WinCreate.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "stdio.h"
#include "resource.h"   //要使用菜单,需要包含这个资源头文件
HINSTANCE g_hInstance=0;//接受当前程序实例句柄
void OnCreate(HWND hWnd)
{
	HWND hSimple = CreateWindowEx(0, "COMBOBOX", "simple",
		WS_CHILD | WS_VISIBLE | CBS_SIMPLE | WS_VSCROLL,
		50, 50, 200, 200, hWnd, (HMENU)1001,
		g_hInstance, NULL);
	HWND hDropDown = CreateWindowEx(0, "COMBOBOX", "DropDown",
		WS_CHILD | WS_VISIBLE | CBS_DROPDOWN |WS_VSCROLL,
		260, 50, 200, 200, hWnd, (HMENU)1002,
		g_hInstance, NULL);
	HWND hDropList = CreateWindowEx(0, "COMBOBOX", "DropDownList",
		WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST |WS_VSCROLL,
		470, 50, 200, 200, hWnd, (HMENU)1003,
		g_hInstance, NULL);
	HFONT hFont = CreateFont(30, 0, 0, 0, 900, 0, 0, 0,
		GB2312_CHARSET, 0, 0, 0, 0, "黑体");
	SendMessage(hSimple, WM_SETFONT, (WPARAM)hFont, 1);
	SendMessage(hDropDown, WM_SETFONT, (WPARAM)hFont, 1);
	SendMessage(hDropList, WM_SETFONT, (WPARAM)hFont, 1);
}
void OnAdd (HWND hWnd)
{
	HWND hSimple = GetDlgItem(hWnd, 1001);  //获得控件句柄函数,第一个参数为父窗口句柄,第二个为控件ID
	HWND hDropDown = GetDlgItem(hWnd, 1002);
	HWND hDropList = GetDlgItem(hWnd, 1003);
	for (int i = 0; i < 100; i++)
	{
		char szItem[256] = {0};
		sprintf(szItem, "Item%d", i);
		SendMessage(hSimple,
			CB_ADDSTRING, 0, (LPARAM)szItem);
		SendMessage(hDropDown,
			CB_ADDSTRING, 0, (LPARAM)szItem);
		SendMessage(hDropList,
			CB_ADDSTRING, 0, (LPARAM)szItem);
		char *pszText = "hello data";
		SendMessage(hSimple,
			CB_SETITEMDATA, i, (LPARAM)pszText);
	}
	SendMessage(hSimple, CB_SETCURSEL, 99, 0);
	SendMessage(hDropDown, CB_SETCURSEL, 99, 0);
	SendMessage(hDropList, CB_SETCURSEL, 99, 0);
}
void OnClean(HWND hWnd)
{
	HWND hSimple = GetDlgItem(hWnd, 1001);
   	HWND hDropDown = GetDlgItem(hWnd, 1002);
	HWND hDropList = GetDlgItem(hWnd, 1003);
	SendMessage(hSimple, CB_RESETCONTENT, 0, 0);
	SendMessage(hDropDown, CB_RESETCONTENT, 0, 0);
	SendMessage(hDropList, CB_RESETCONTENT, 0 , 0);
}
void OnDelete(HWND hWnd)
{
	HWND hSimple = GetDlgItem(hWnd, 1001);
	HWND hDropDown = GetDlgItem(hWnd, 1002);
	HWND hDropList = GetDlgItem(hWnd, 1003);
	LRESULT nSel = SendMessage(hSimple, CB_GETCURSEL, 0, 0);
	if (nSel != CB_ERR)
	{
		SendMessage(hSimple, CB_DELETESTRING, (WPARAM)nSel, 0);
	}
	nSel = SendMessage(hDropDown, CB_GETCURSEL, 0, 0);
	if (nSel != CB_ERR)
	{
		SendMessage(hDropDown, CB_DELETESTRING, nSel, 0);
	}
	nSel = SendMessage(hDropList, CB_GETCURSEL, 0, 0);
	if (nSel != CB_ERR)
	{
		SendMessage(hDropList, CB_DELETESTRING, nSel, 0);
	}
}
void OnFind(HWND hWnd)
{
	HWND hSimple = GetDlgItem(hWnd, 1001);
	char szText[] = "Item10"; //要匹配的字符串
	LRESULT nFind = SendMessage(hSimple, 
		CB_SELECTSTRING, -1, (LPARAM)szText);
	if (nFind != CB_ERR)
	{
		CHAR szText[256] = {0};
		sprintf(szText, "%d", nFind);
		MessageBox(NULL, szText, "Infor", MB_OK);
	}else{
		MessageBox(NULL, "匹配失败", "Infor", MB_OK);
	}
}
void OnText(HWND hWnd)
{
	HWND hSimple = GetDlgItem(hWnd, 1001);
	LRESULT index = SendMessage(hSimple, CB_GETCURSEL, 0, 0);
	if (index != CB_ERR)
	{
		char szText[256] = {0};
		SendMessage(hSimple, 
			CB_GETLBTEXT, index, (LPARAM)szText);
		MessageBox(NULL, szText, "Infor", MB_OK);
	}else{
		MessageBox(NULL, "无选择项", "Infor", MB_OK);
	}
	CHAR szText[256] = {0};
	SendMessage(hSimple, WM_GETTEXT, 256, (LPARAM)szText);  //拿到键盘输入的内容
	MessageBox(NULL, szText, "Infor", MB_OK);
}
void OnData(HWND hWnd)
{
	HWND hSimple = GetDlgItem(hWnd, 1001);
	LRESULT index = SendMessage(hSimple, CB_GETCURSEL, 0, 0);
	if(index != CB_ERR)
	{
		LRESULT nData = SendMessage(hSimple, CB_GETITEMDATA, index, 0);
		char szText[256] = {0};
		sprintf(szText, "附加数据=%s", (char*)nData);
		MessageBox(NULL, szText, "Infor", MB_OK);
	}
}
void OnCommand(HWND hWnd, WPARAM wParam)
{
	switch (LOWORD(wParam))
	{
	case 1001:  //简单组合框有事发生
		{
			if (HIWORD (wParam) == CBN_SELCHANGE) //简单选择项的菜单项发生变化
			{
				HWND hSimple = GetDlgItem(hWnd, 1001);
				HWND hDropDown = GetDlgItem(hWnd, 1002);
				HWND hDropList = GetDlgItem(hWnd, 1003);
				LRESULT index = SendMessage(hSimple,
					CB_GETCURSEL, 0, 0);
				SendMessage(hDropDown, CB_SETCURSEL, index, 0);
				SendMessage(hDropList, CB_SETCURSEL, index, 0);
			}
		}
		break;
	case ID_ADD:
		OnAdd(hWnd);  //添加选项
		break;
	case ID_CLEAN:
		OnClean(hWnd); //清空选项
		break;
	case ID_DELETE:
		OnDelete(hWnd); //删除选择项
		break;
	case ID_FIND:
		OnFind(hWnd);
		break;
	case ID_TEXT:
		OnText(hWnd);   //选择项文本
		break;
	case ID_DATA:
		OnData(hWnd);  //选择项附加数据
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
	wce.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);//IDR_MENU1是菜单资源ID
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



