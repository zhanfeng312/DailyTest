// WinCreate.cpp : Defines the entry point for the application.
#include "stdafx.h"

HINSTANCE g_hInstance = 0;//���ܵ�ǰ����ʵ�����
void OnCreate(HWND hWnd)
{
	HMENU hSys = GetSystemMenu(hWnd, FALSE);  //���ϵͳ�˵����
	for(int i = 0; i < 6; i++)
	{
		DeleteMenu(hSys, 0, MF_BYPOSITION);  //ɾ���˵���
	}
	AppendMenu(hSys, MF_SEPARATOR, 0, "");   //���Ӳ˵���
	AppendMenu(hSys, MF_STRING, 1001, "�ҵĲ˵���");
}
void OnSysCommand(HWND hWnd, WPARAM wParam)
{
	switch(LOWORD(wParam))
	{
	case 1001:
		MessageBox(NULL, "�ҵĲ˵�����", "Infor", 
			MB_ABORTRETRYIGNORE);
		break;
	}
}
void OnRButtonUp(HWND hWnd, LPARAM lParam)
{
	HMENU hPopup = CreatePopupMenu();           //������嵯��ʽ�˵�
	AppendMenu(hPopup, MF_STRING, 1002, "�½�");//���Ӳ˵���
	AppendMenu(hPopup, MF_SEPARATOR, 0, "");
	AppendMenu(hPopup, MF_STRING, 1003, "�˳�");
	POINT pt = {0};
	pt.x = LOWORD(lParam);  //ת��һ��
	pt.y = HIWORD(lParam);
	ClientToScreen(hWnd, &pt); //���õ��ǿͻ����µ�����

	int nRet = TrackPopupMenu(hPopup, 
		TPM_CENTERALIGN | TPM_VCENTERALIGN | TPM_RETURNCMD,   //����TPM_RETURNCMD���
		pt.x, pt.y, 0, hWnd, NULL); //�������������ص��ǵ���Ĳ˵����ID
	switch(nRet)
	{
	case 1002:
		MessageBox(NULL, "û������Ϣ,�½������",
			"Infor", MB_OK);
		break;
	case 1003:
		MessageBox(NULL, "û������Ϣ,�˳������",
			"Infor", MB_OK);
		break;
	}
}
void OnCommand(HWND hWnd, WPARAM wParam)
{
	switch(LOWORD(wParam))
	{
	case 1002:
		MessageBox(NULL, "�½������", "Infor", MB_OK);
		break;
	case 1003:
		MessageBox(NULL, "�˳������", "Infor", MB_OK);
		break;
	}
}
void OnContextmenu(HWND hWnd, LPARAM lParam)
{
	HMENU hPopup = CreatePopupMenu();           //������嵯��ʽ�˵�
	AppendMenu(hPopup, MF_STRING, 1002, "�½�");//���Ӳ˵���
	AppendMenu(hPopup, MF_SEPARATOR, 0, "");
	AppendMenu(hPopup, MF_STRING, 1003, "�˳�");
	POINT pt = {0};
	pt.x = LOWORD(lParam);  //ת��һ��
	pt.y = HIWORD(lParam);
	//ClientToScreen(hWnd, &pt); //����Ҫת��(רҵ��ʿ)

	int nRet = TrackPopupMenu(hPopup, 
		TPM_CENTERALIGN | TPM_VCENTERALIGN | TPM_RETURNCMD,   //����TPM_RETURNCMD���
		pt.x, pt.y, 0, hWnd, NULL); //�������������ص��ǵ���Ĳ˵����ID
	switch(nRet)
	{
	case 1002:
		MessageBox(NULL, "û������Ϣ,�½������",
			"Infor", MB_OK);
		break;
	case 1003:
		MessageBox(NULL, "û������Ϣ,�˳������",
			"Infor", MB_OK);
		break;
	}
}
//���ڴ�����
LRESULT CALLBACK WndProc(HWND hWnd,UINT nMsg,WPARAM wParam,LPARAM lParam)
{
	switch(nMsg)
	{
	case WM_CONTEXTMENU:  //�����Ϣ�����Ҽ���������
		OnContextmenu(hWnd, lParam);
		break;
	case WM_COMMAND:
		OnCommand(hWnd, wParam);
		break;
	case WM_RBUTTONUP:
		//OnRButtonUp(hWnd, lParam); //���ڿͻ�����������λ��
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
	wce.lpszMenuName=NULL;
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



