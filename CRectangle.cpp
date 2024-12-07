#include "pch.h"
#include "CRectangle.h"

CRectangle::CRectangle()
{
	this->x0 = 0;
	this->x1 = 0;
	this->y0 = 0;
	this->y1 = 0;

	this->type = SQUARE;
}

CRectangle::CRectangle(int x0, int x1, int y0, int y1)
{
	this->x0 = x0;
	this->x1 = x1;
	this->y0 = y0;
	this->y1 = y1;

	this->type = SQUARE;
}

void CRectangle::render(CDC* pDC)
{
	pDC->MoveTo(x0, y0);
	pDC->Rectangle(x0, y0, x1, y1);
}

void CRectangle::read(CArchive& ar)
{
}

void CRectangle::write(CArchive& ar)
{
}
