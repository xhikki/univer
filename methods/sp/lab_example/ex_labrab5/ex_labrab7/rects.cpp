#include "rects.h"

CRectangle::CRectangle()
{
	a=10;
	b=20;
}

int CRectangle::SetParameters(int w, int h, char[])
{
	int pr=0;
	if (w<=0 || h<=0)
		pr=1;
	else
	{
		a=h;
		b=w;
	}
	return pr;
}

char *CRectangle::GetParameters(int *w, int *h)
{
	char *s=new char [100];
	strcpy(s,"");
	*w=a;
	*h=b;
	return s;
}

int CRectangle::GetArea()
{
	return a*b;
}

int CRectangle::IsKind()
{
	return 1;
}

CColorRectangle::CColorRectangle()
{
	color=new char[20];
	strcpy(color,"Black");
}

int CColorRectangle::SetParameters(int w,int h, char c[])
{
	int pr=CRectangle::SetParameters(w,h);
	strcpy(color,c);
	return pr;
}

char *CColorRectangle::GetParameters(int *w, int *h)
{
	char *s=new char[100];
	*w=a;
	*h=b;
	strcpy(s,color);
	return s;
}

CColorRectangle::~CColorRectangle()
{
	delete [] color;
}

int CColorRectangle::IsKind()
{
	return 2;
}
