#include <string.h>
#include <stdio.h>

class CRectangle
{
protected:
	int a,b;
public:
	CRectangle();
	virtual int SetParameters(int,int,char[]=0);
	virtual char* GetParameters(int *, int *);
	int GetArea();
	virtual int IsKind();
};

class CColorRectangle:public CRectangle
{
	char *color;
public:
	CColorRectangle();
	int SetParameters(int,int,char[]);
	char* GetParameters(int *, int *);
	~CColorRectangle();
	int IsKind();
};