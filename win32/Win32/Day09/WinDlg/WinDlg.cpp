// WinCreate.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
HINSTANCE g_hInstance=0;//���ܵ�ǰ����ʵ�����
int CALLBACK DlgProc (HWND hwndDlg, UINT uMsg,
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
	case WM_SYSCOMMAND:
		if (wParam == SC_CLOSE)
		{
			EndDialog(hwndDlg, 1001);//����ģʽ�Ի���
		//	DestroyWindow(hwndDlg);
		}
		return TRUE;
		break;
	}
	return FALSE;  
	//����Ϣ����ȱʡ (ָ��Ի�����������������Ĭ�ϴ���)
}
void OnModel(HWND hWnd)
{
	int nRet = DialogBox(g_hInstance,
		MAKEINTRESOURCE(IDD_DIALOG1), hWnd, DlgProc);
	if (nRet == 1001)
	{
		MessageBox(NULL, "Successful", "Infor", MB_OK);
	}
}
void OnCommand(HWND hWnd, WPARAM wParam)
{
	switch ( LOWORD(wParam))
	{
	case ID_MODEL:
		OnModel(hWnd);   //����ģʽ�Ի���
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



