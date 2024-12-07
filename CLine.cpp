#include "pch.h"
#include "CLine.h"

CLine::CLine(int x0, int y0, int x1, int y1)
{
	this->x0 = x0;
	this->x1 = x1;
	this->y0 = y0;
	this->y1 = y1;

	this->type = LINE;
}

void CLine::setEnd(int x1, int y1)
{
	this->x1 = x1;
	this->y1 = y1;
}

void CLine::render(CDC* pDC)
{
	pDC->MoveTo(x0, y0);
	pDC->LineTo(x1, y1);
}
