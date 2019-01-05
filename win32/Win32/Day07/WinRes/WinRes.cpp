// WinCreate.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
HINSTANCE g_hInstance=0; //���ܵ�ǰ����ʵ�����
//���ڴ�����
void OnCommand(HWND hWnd, WPARAM wParam)
{
	switch(LOWORD(wParam) )
	{
	case ID_SET:
		MessageBox(NULL, "����CTRL+M", "Infor", MB_OK);
		break;
	case ID_NEW:
		{
			if (HIWORD(wParam) == 0)
				MessageBox(NULL, "�½������", "Infor", MB_OK);
			else
				MessageBox(NULL, "û���½�", "Infor", MB_OK);
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
	case WM_SETCURSOR:  //������ƶ�,�ͻ��������ϵز���
		{
		//  HCURSOR hBall = LoadCursor(g_hInstance,
		//	    MAKEINTRESOURCE(IDC_CURSOR2));
		//	HCURSOR hRect = LoadCursor(g_hInstance,
		//		MAKEINTRESOURCE(IDC_CURSOR1));
			HCURSOR hBall = LoadCursorFromFile(     //Ƶ�������ڴ�
				"c:/Windows/Cursors/aero_working_l.ani");
			HCURSOR hRect = LoadCursorFromFile(
				"c:/Windows/Cursors/aero_working.ani");
		
			if (LOWORD(lParam) == HTCLIENT) //��ǰ�����ڿͻ���
			{
				POINT pt = {0};
	            GetCursorPos(&pt);       //��Ļ����ϵ�µ�����
				RECT rc = {0};
			    GetClientRect(hWnd, &rc);//�ͻ�������ϵ�µ�����
				ScreenToClient(hWnd, &pt); //�����������
				if(pt.x <= rc.right/2)
				{
					SetCursor(hRect);
				}else{
					SetCursor(hBall);
				}
				return 0;
			}else{
				//ʲô����д
			}
		}
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
//������
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	g_hInstance=hInstance;
	if(!Register("Main",WndProc))
	{
		MessageBox(NULL,"ע��ʧ��","Error",MB_OK);
		return 0;
	}
	CHAR szTitle[256] = {0};
	LoadString(g_hInstance, IDS_WND, szTitle, 256); //��̬��ȡ�ַ�����Դ
	HWND hWnd=CreateMain("Main",szTitle);
	Display(hWnd);
	Message();
	return 0;
}



