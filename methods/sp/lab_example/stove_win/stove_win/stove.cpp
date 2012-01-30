#include <stdio.h>
#include <conio.h>
#include "stove.h"

stove::stove()
{	curr_lamp=off;
	curr_door=close;
	curr_power=no;
	time=-1;
}
int stove::take_door()
{
	int n;
	if (curr_door==open)
	{
		curr_door=close;
		curr_lamp=off;
		n=0;
	}
	else
	{	curr_door=open;
		curr_lamp=on;
		time=-1;
		if (curr_power==yes)
		{
			curr_power=no;
			n=2;
		}
		else
			n=1;
	}
	return n;
}
int stove::push_button()
{	
	int n;
	if (curr_door==close)
	{
		if (curr_power==yes)
		{
			time+=60;
			n=2;
		}
		else
		{	curr_power=yes;
			curr_lamp=on;
			time=60;
			n=1;
		}
	}
	else
		n=0;
	return n; 
}
void stove::ready()
{	
	curr_power=no;
	curr_lamp=off;
	time=-1;
	return;
}


int stove::GetTime()
{
	return time;
}

void stove::SubTime()
{
	time--;
}

lamp stove::GetLamp()
{
	return curr_lamp;
}

door stove::GetDoor()
{
	return curr_door;
}

power stove::GetPower()
{
	return curr_power;
}