// WinCreate.cpp : Defines the entry point for the application.

#include "stdafx.h"
#include "resource.h"
HINSTANCE g_hInstance=0;//接受当前程序实例句柄
int g_kind = 0;  //标志量 (绘制哪种图形)  保证唯一就行
void OnCommand(HWND hWnd, WPARAM wParam)
{
	g_kind = LOWORD(wParam); //给标志量赋了个值

	switch (g_kind)
	{
	case ID_PIT:
	case ID_LINE:  //点击这几个都执行下面这段代码
	case ID_REC:
	case ID_ELL:
	case ID_ARC:
	case ID_PIE:
		InvalidateRect(hWnd, NULL, TRUE); //设置为无效区域
		break;
	}
}
void DrawPit(HDC hdc)
{
	//SetPixel(hdc, 100, 100, RGB(255, 0, 0)); //画点
	for(int i = 0; i < 256; i++)
	{
		for(int j = 0; j < 256; j++)
		{
			SetPixel(hdc, i, j, RGB(i, j, 0));
		}
	}
}
void DrawLine(HDC hdc)
{
	MoveToEx(hdc, 100, 100, NULL); // 设置窗口当前点为100, 100
	LineTo(hdc, 300, 300); //直线画完后,把当前点
	LineTo(hdc, 0, 300);
}
void DrawRec(HDC hdc)
{
	Rectangle(hdc, 100, 100, 300, 300);
	RoundRect(hdc, 300, 100, 500, 300, 1000, 1000);//对参数进行了判断
}
void DrawEll(HDC hdc)
{
	Ellipse(hdc, 100, 100, 300, 300); //正圆
	Ellipse(hdc, 300, 100, 600, 300); //椭圆
}
void DrawArc(HDC hdc)
{
	Arc(hdc, 100, 100, 300, 300 ,100, 100, 300, 300);
}
void DrawPie(HDC hdc)
{
	Pie(hdc, 100, 100, 300, 300, 300, 100, 100, 100);
}
void OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps = {0};
	HDC hdc = BeginPaint(hWnd, &ps); //从OS中抓出来，在咱们这个窗口中画
	switch (g_kind)
	{
	case ID_PIE:
		DrawPie(hdc);   //绘制扇形
		break;  
	case ID_ARC:
		DrawArc(hdc) ; //绘制弧线
		break;
	case ID_ELL:
		DrawEll(hdc) ;  //绘制圆形
		break;
	case ID_REC:
		DrawRec(hdc); //绘制矩形
		break;
	case ID_PIT:
		DrawPit(hdc); //绘制点
		break;
	case ID_LINE:
		DrawLine(hdc); //绘制直线
		break;
	}
	EndPaint(hWnd, &ps);
}
//窗口处理函数
LRESULT CALLBACK WndProc(HWND hWnd,UINT nMsg,WPARAM wParam,LPARAM lParam)
{
	switch(nMsg)
	{
	case WM_PAINT:
		OnPaint(hWnd);
		break;
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
	wce.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1); //挂载菜单
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



