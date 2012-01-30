#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include "stove.h"

void menu()
{
	char *str=new char[100];
	CharToOem("b - ������ ������ ��� ������������� ���",str);
	printf("\n%s\n",str);
	CharToOem("d - �������/������� �����",str);
	printf("%s\n",str);
	CharToOem("ESC - �����",str);
	printf("%s\n\n",str);
}
stove::stove()
{	curr_lamp=off;
	curr_door=close;
	curr_power=no;
	time=-1;
}
char *stove::take_door(void)
{
	char *str = new char[100];
	if (curr_door==open)
	{	curr_door=close;
		curr_lamp=off;
		CharToOem("����� �������",str);
	}
	else
	{	curr_door=open;
		curr_lamp=on;
		time=-1;
		CharToOem("����� �������",str);
		if (curr_power==yes)
		{
			char *str1=new char[30];
			CharToOem(". ������� �������",str1);
			strcat(str,str1);
			curr_power=no;
		}
	}
	return str;
}
char* stove::push_button(void)
{	
	char *str = new char[100];
	if (curr_door==open)
		CharToOem("�������� �����!",str);
	else
	{	if (curr_power==yes)
		{	time+=60;
			CharToOem("��� ��������� ������",str);
		}
		else
		{	curr_power=yes;
			curr_lamp=on;
			time=60;
			CharToOem("������ ������������� ���",str);
		}
	}
	return str; 
}
char* stove::ready(void)
{	
	char *str=new char[100];
	curr_power=no;
	curr_lamp=off;
	time=-1;
	CharToOem("\a��� ������",str);
	return str;
}
void stove::Run(void)
{
	int i,flag=0;
	char *str=new char[100];
	char *str1=new char[100];
	while (flag!=1)
	{
		while (!kbhit() && time>0)
		{
			time--;
			Sleep(100);
			sprintf(str1,"�������� %d ������",time);
			CharToOem(str1,str);
			printf("%s\n",str);
		}
		if (time==0)
		{
			strcpy(str,ready());
			printf("%s\n",str);
		}
		if (time==-1)
			menu();
		i=getch();
		switch (i)
		{	case 'b': strcpy(str,push_button()); break;
			case 'd': strcpy(str,take_door()); break;
			case 27: flag=1; break;
		}
		fflush(stdin);
		if (i=='b' || i=='d')
			printf("%s\n",str);
	}
	return;
}
