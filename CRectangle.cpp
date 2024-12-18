#include "pch.h"
#include "CRectangle.h"

CRectangle::CRectangle()
{
	this->x0 = 0;
	this->x1 = 0;
	this->y0 = 0;
	this->y1 = 0;

	this->type = SQUARE;
	isReady = x0 != x1 || y0 != y1;
}

CRectangle::CRectangle(int x0, int y0, int x1, int y1)
{
	this->x0 = x0;
	this->x1 = x1;
	this->y0 = y0;
	this->y1 = y1;

	this->type = SQUARE;
	isReady = x0 != x1 || y0 != y1;
}

void CRectangle::setEndPoint(int x, int y)
{
	this->x1 = x;
	this->y1 = y;
	isReady = x0 != x1 || y0 != y1;
}

void CRectangle::render(CDC* pDC)
{
	CBrush* oldBrush;
	CBrush newBrush;

	newBrush.CreateSolidBrush(currentColor.getColor());
	oldBrush = (CBrush*)pDC->SelectObject(&newBrush);

	pDC->MoveTo(0, 0);
	pDC->Rectangle(x0, y0, x1, y1);

	pDC->SelectObject(oldBrush);
}

void CRectangle::read(CArchive& ar)
{
}

void CRectangle::write(CArchive& ar)
{
}

std::string CRectangle::ToString()
{
	return std::string();
}

// Check if a point is inside a shape
bool CRectangle::IsInside(int x, int y)
{
	int minX = x0 < x1 ? x0 : x1;
	int maxX = x0 > x1 ? x0 : x1;
	int minY = y0 < y1 ? y0 : y1;
	int maxY = y0 > y1 ? y0 : y1;

	return minX < x && x < maxX && minY < y && y < maxY;
}

void CRectangle::paintShape(float r, float g, float b)
{
}
