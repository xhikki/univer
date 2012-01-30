#include "stove.h"
#include <conio.h>

int main()
{	
	int key=getch();
	putch(key);
	stove MyStove;
	MyStove.Run();
	return 0;
}
