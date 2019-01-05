// WinCreate.cpp : Defines the entry point for the application.

#include "stdafx.h"
#include "resource.h"
HINSTANCE g_hInstance = 0;//接受当前程序实例句柄
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
	case ID_BMP:
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
	MoveToEx(hdc, 100, 100, NULL);  //设置窗口当前点为100, 100
	LineTo(hdc, 300, 300);   //直线画完后,把当前点
	LineTo(hdc, 0, 300);
	LineTo(hdc, 100, 100);
}
void DrawRec(HDC hdc)
{
	Rectangle(hdc, 100, -100, 300, -300);
	RoundRect(hdc, 300, 100, 500, 300, 1000, 1000); //对参数进行了判断
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
void DrawBmp(HDC hdc)
{
	HBITMAP hBmp = LoadBitmap(g_hInstance,
		MAKEINTRESOURCE(IDB_BITMAP2));
	BITMAP bmpInfo = {0};
	GetObject(hBmp, sizeof(bmpInfo), &bmpInfo); 
	//获得位图的宽和高

	HDC hMemdc = CreateCompatibleDC(hdc);
	//创建了一个内存DC,同时还构建了一个虚拟区域

	HGDIOBJ nOldBmp = SelectObject(hMemdc, hBmp);
	//内存将送入的图片 绘制在 虚拟区域中 (0,0)

//	BitBlt(hdc, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, 
	//	hMemdc, 0, 0, SRCCOPY); 
	//一比一成像

	StretchBlt(hdc, 150, 100, 96, 96,
		hMemdc, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, NOTSRCCOPY);
	//缩放成像

	SelectObject(hMemdc, nOldBmp);
	DeleteObject(hBmp);
	DeleteDC(hMemdc);
}
void OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps = {0};
	HDC hdc = BeginPaint(hWnd, &ps); //从OS中抓出来，在咱们这个窗口中画
	HPEN hPen = CreatePen(PS_DASH, 1, RGB(255, 0, 0)); //创建一个画笔 如果不是PS_SOLID,第二个参数还写的不是1,那画笔就失效了
	HGDIOBJ nOldPen = SelectObject(hdc, hPen);  //送给它
//	HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 0)); //把原来的白色画刷交出来
//	HBRUSH hBrush = CreateHatchBrush(
		//HS_CROSS, RGB(0, 255, 0));
//	HGDIOBJ hBrush = GetStockObject(NULL_BRUSH);
	HBITMAP hBmp = LoadBitmap(g_hInstance,
		MAKEINTRESOURCE(IDB_BITMAP1));
	HBRUSH hBrush = CreatePatternBrush(hBmp);
	HGDIOBJ nOldBrush = SelectObject(hdc, hBrush);

	int nOldMode = SetMapMode(hdc, MM_ANISOTROPIC);
	SetWindowExtEx(hdc, 1, 1, NULL);
	SetViewportExtEx(hdc, 2, -2, NULL);

	switch (g_kind)
	{
	case ID_BMP:
		DrawBmp(hdc); //绘制位图
		break;
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
	SetMapMode(hdc, nOldMode);

	SelectObject(hdc, nOldBrush);
	DeleteObject(hBrush);
	SelectObject(hdc, nOldPen); //还给它 不需要接受
	DeleteObject(hPen);  //把笔销毁掉
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
	wce.hbrBackground = CreateSolidBrush(RGB(0, 255, 0)); //窗口的背景色
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



