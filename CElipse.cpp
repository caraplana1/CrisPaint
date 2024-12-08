#include "pch.h"
#include "CElipse.h"

CElipse::CElipse()
{
	x0 = 0;
	y0 = 0;
	x1 = 0;
	y1 = 0;

	isReady = false;
	type = ELIPSE;
}

CElipse::CElipse(int x0, int y0, int x1, int y1)
{
	this->x0 = x0;
	this->y0 = y0;
	this->x1 = x1;
	this->y1 = y1;

	isReady = x0 != x1 || y0 != y1;
	type = ELIPSE;
}

void CElipse::setFirst(int x0, int y0)
{
	this->x0 = x0;
	this->y0 = y0;

	isReady = x0 != x1 || y0 != y1;
}

void CElipse::setSecond(int x1, int y1)
{
	this->x1 = x1;
	this->y1 = y1;

	isReady = x0 != x1 || y0 != y1;
}

void CElipse::render(CDC* pDC)
{
	pDC->MoveTo(0, 0);
	pDC->Ellipse(x0, y0, x1, y1);
}

void CElipse::read(CArchive& ar)
{
}

void CElipse::write(CArchive& ar)
{
}
