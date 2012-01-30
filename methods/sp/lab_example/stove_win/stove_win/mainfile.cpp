#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "stove.h"

#define IDC_BUTPUSHBUTTON 4001
#define IDC_BUTTONTAKEDOOR 4002


LONG MyWinP(HWND, UINT,WPARAM,LPARAM); //�������� ������� �������


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{ 
	char ProgName[]="My Window";
	char Title[]="��������� ����";
	HWND hWnd;	MSG msg; 
	WNDCLASS w; 
	w.lpszClassName=ProgName;
	w.hInstance=hInstance; 
	w.lpfnWndProc=(WNDPROC)MyWinP;
	w.hCursor=LoadCursor(NULL, IDC_ARROW); 
	w.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	w.lpszMenuName=NULL;
	w.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
	w.style=CS_HREDRAW | CS_VREDRAW;
	w.cbClsExtra=0;
	w.cbWndExtra=0; 
	if(!RegisterClass(&w)) return false;
	hWnd=CreateWindow(ProgName,Title, WS_SYSMENU,0,0,420, 215, NULL, NULL, hInstance, NULL);
	if (!hWnd) return false;
	ShowWindow(hWnd, nCmdShow);
	while(GetMessage(&msg, NULL, 0, 0)) 
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}


LONG  MyWinP(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
static HWND stat[4], ed[3], but[2];
	static stove st;
	int n;
	char s[300];
	switch (msg)
	{
	case WM_TIMER:
		if (st.GetTime()>0)
		{
			st.SubTime();
			sprintf_s(s,sizeof(s),"�������� �������: %d", st.GetTime());
			SetWindowText(ed[2],s);
		}
		else
		{
			st.ready();
			if (st.GetLamp()==on)
				SetWindowText(ed[0],"�����"); 
			else
				SetWindowText(ed[0],"�� �����");
			if (st.GetDoor()==close)
				SetWindowText(ed[1],"�������"); 
			else
				SetWindowText(ed[1],"�������");
			SetWindowText(ed[2],"��� �� ���������");
			KillTimer(hWnd,1);
		}
		break;
	case WM_CREATE:
		stat[0]=CreateWindow("static","�����:", WS_CHILD|WS_VISIBLE, 10,10,50,20,hWnd,NULL,NULL,NULL);
		if (st.GetLamp()==on)
			strcpy_s(s,sizeof(s),"�����"); 
		else
			strcpy_s(s,sizeof(s),"�� �����");
		ed[0]=CreateWindow("edit",s,WS_DISABLED|WS_CHILD|WS_VISIBLE|WS_BORDER|WS_TABSTOP|ES_AUTOHSCROLL, 70,10,330,20,hWnd,NULL,NULL,NULL);
		stat[1]=CreateWindow("static","�����:", WS_CHILD|WS_VISIBLE, 10,40,50,20,hWnd,NULL,NULL,NULL);
		but[0]=CreateWindow("button","������� �����", WS_CHILD|WS_VISIBLE|WS_TABSTOP,10,100,390,30,hWnd,(HMENU)IDC_BUTTONTAKEDOOR,NULL,NULL);
		but[1]=CreateWindow("button","��������", WS_CHILD|WS_VISIBLE|WS_TABSTOP, 10,140,390,30,hWnd,(HMENU)IDC_BUTPUSHBUTTON,NULL,NULL);
		if (st.GetDoor()==close)
		{
			strcpy_s(s,sizeof(s),"�������"); 
			SetWindowText(but[0],"������� �����");
		}
		else
		{
			strcpy_s(s,sizeof(s),"�������");
			EnableWindow(but[1],FALSE);
		}
		ed[1]=CreateWindow("edit",s,WS_DISABLED|WS_CHILD|WS_VISIBLE|WS_BORDER|WS_TABSTOP|ES_AUTOHSCROLL, 70,40,330,20,hWnd,NULL,NULL,NULL);
		stat[2]=CreateWindow("static","�������� ������� �� ���������:", WS_CHILD|WS_VISIBLE, 10,70,220,20,hWnd,NULL,NULL,NULL);
		ed[2]=CreateWindow("edit","��� �� ���������",WS_CHILD|WS_VISIBLE|WS_BORDER|WS_DISABLED|ES_MULTILINE, 240,70,160,20,hWnd,NULL,NULL,NULL);
		break;
	case WM_COMMAND:
		if (LOWORD(wParam)==IDC_BUTTONTAKEDOOR)
		{
			n=st.take_door();
			if (st.GetDoor()==close)
			{
				SetWindowText(ed[1],"�������"); 
				SetWindowText(but[0],"������� �����");
				EnableWindow(but[1],TRUE);
				if (st.GetLamp()==on)
					SetWindowText(ed[0],"�����"); 
				else
					SetWindowText(ed[0],"�� �����");
			}
			else
			{
				SetWindowText(ed[1],"�������");
				SetWindowText(but[0],"������� �����");
				if (st.GetLamp()==on)
					SetWindowText(ed[0],"�����"); 
				else
					SetWindowText(ed[0],"�� �����");
				EnableWindow(but[1],FALSE);
				if (n==2)
				{
					SetWindowText(ed[2],"��� �� ���������");
					KillTimer(hWnd,1);
					MessageBox(NULL,"������� ������������ ��� �������!","",MB_OK);
				}

			}
		}
		if (LOWORD(wParam)==IDC_BUTPUSHBUTTON)
		{
			n=st.push_button();
			if (n==1)
			{
				SetTimer(hWnd,1,100,NULL);
				sprintf_s(s,sizeof(s),"�������� �������: %d", st.GetTime());
				SetWindowText(ed[2],s);
				if (st.GetLamp()==on)
					SetWindowText(ed[0],"�����"); 
				else
					SetWindowText(ed[0],"�� �����");
			}
			if (n==0)
				MessageBox(NULL,"�������� �����!!!",NULL,MB_OK);
		}
		break;
	case WM_DESTROY: //��������� �� ����������� ����
		PostQuitMessage(0);
		break;
	default: 
		return LONG(DefWindowProc(hWnd, msg, wParam, lParam));
	}
return 0;
}


