#include <windows.h>
#include <stdio.h>
#include "rects.h"

#define IDC_SETPARAMETERS 4001
#define IDC_RECT 4002
#define IDC_COLORRECT 4003


LRESULT MyWinP(HWND, UINT,WPARAM,LPARAM); 


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{ 
	char ProgName[]="My Window";
	char Title[]="Прямоугольники";
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
	hWnd=CreateWindow(ProgName,Title, WS_SYSMENU,100,100,350, 210, NULL, NULL, hInstance, NULL);
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
static HWND stat[4], ed[4], but[3];
	int a,b,pr;
	char s[20],s1[30];
	static CRectangle *p;
	static CRectangle r;
	static CColorRectangle cr;
	switch (msg)
	{
	
	case WM_CREATE:
		p=&r;
		strcpy(s,p->GetParameters(&a,&b));
		stat[0]=CreateWindow("static","Ширина:", WS_CHILD|WS_VISIBLE, 10,10,80,20,hWnd,NULL,NULL,NULL);
		sprintf_s(s1,"%d",a);
		ed[0]=CreateWindow("edit",s1,WS_CHILD|WS_VISIBLE|WS_BORDER|WS_TABSTOP|ES_AUTOHSCROLL, 10,40,80,20,hWnd,NULL,NULL,NULL);
		stat[1]=CreateWindow("static","Высота:", WS_CHILD|WS_VISIBLE, 100,10,80,20,hWnd,NULL,NULL,NULL);
		sprintf_s(s1,"%d",b);
		ed[1]=CreateWindow("edit",s1,WS_CHILD|WS_VISIBLE|WS_BORDER|WS_TABSTOP|ES_AUTOHSCROLL, 100,40,80,20,hWnd,NULL,NULL,NULL);
		stat[2]=CreateWindow("static","Площадь:", WS_CHILD|WS_VISIBLE, 10,70,80,20,hWnd,NULL,NULL,NULL);
		sprintf_s(s1,"%d",p->GetArea());
		ed[2]=CreateWindow("edit",s1,WS_DISABLED|WS_CHILD|WS_VISIBLE|WS_BORDER|WS_TABSTOP|ES_AUTOHSCROLL, 10,100,80,20,hWnd,NULL,NULL,NULL);
		stat[3]=CreateWindow("static","Цвет:", WS_CHILD|WS_VISIBLE, 100,70,80,20,hWnd,NULL,NULL,NULL);
		ed[3]=CreateWindow("edit",s,WS_DISABLED|WS_CHILD|WS_VISIBLE|WS_BORDER|WS_TABSTOP|ES_AUTOHSCROLL, 100,100,80,20,hWnd,NULL,NULL,NULL);
		but[0]=CreateWindow("button","Установить параметры", WS_CHILD|WS_VISIBLE|WS_TABSTOP,10,130,170,30,hWnd,(HMENU)IDC_SETPARAMETERS,NULL,NULL);
		but[1]=CreateWindow("button","Прямоугольник",WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_GROUP|BS_AUTORADIOBUTTON|BS_FLAT|BS_PUSHLIKE, 190,10,140,70, hWnd, (HMENU)IDC_RECT,NULL,NULL);
		but[2]=CreateWindow("button","Цветной прямоугольник",WS_CHILD|WS_VISIBLE|WS_TABSTOP|BS_AUTORADIOBUTTON|BS_FLAT|BS_PUSHLIKE|BS_MULTILINE, 190,90,140,70, hWnd, (HMENU)IDC_COLORRECT,NULL,NULL);		
		SendMessage(but[1],BM_SETCHECK,1,0);

		break;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDC_SETPARAMETERS:
			GetWindowText(ed[0],s1,sizeof(s));
			a=atoi(s1);
			GetWindowText(ed[1],s1,sizeof(s));
			b=atoi(s1);
			GetWindowText(ed[3],s,sizeof(s));
			pr=p->SetParameters(a,b,s);
			if (pr==0)
			{
				sprintf(s1,"%d",p->GetArea());
				SetWindowText(ed[2],s1);
			}
			else
				MessageBox(NULL,"Неверно заданы стороны прямоугольника",NULL,MB_OK);

			break;
		case IDC_RECT:
			p=&r;
			strcpy(s,p->GetParameters(&a,&b));
			sprintf_s(s1,"%d",a);
			SetWindowText(ed[0],s1);
			sprintf_s(s1,"%d",b);
			SetWindowText(ed[1],s1);
			sprintf_s(s1,"%d",p->GetArea());
			SetWindowText(ed[2],s1);
			EnableWindow(ed[3],FALSE);
			SetWindowText(ed[3],s);
			break;
		case IDC_COLORRECT:
			p=&cr;
			strcpy(s,p->GetParameters(&a,&b));
			sprintf_s(s1,"%d",a);
			SetWindowText(ed[0],s1);
			sprintf_s(s1,"%d",b);
			SetWindowText(ed[1],s1);
			sprintf_s(s1,"%d",p->GetArea());
			SetWindowText(ed[2],s1);
			EnableWindow(ed[3],TRUE);
			SetWindowText(ed[3],s);
			break;
		}
		break;
	case WM_DESTROY: //сообщение на уничтожение окна
		PostQuitMessage(0);
		break;
	default: 
		return LONG(DefWindowProc(hWnd, msg, wParam, lParam));
	}
return 0;
}

