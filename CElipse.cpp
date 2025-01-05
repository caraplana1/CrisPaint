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
	if (isFiled)
	{
		CBrush* oldBrush;
		CBrush newBrush;

		newBrush.CreateSolidBrush(currentColor.getColor());
		oldBrush = (CBrush*)pDC->SelectObject(&newBrush);

		pDC->MoveTo(0, 0);
		pDC->Ellipse(x0, y0, x1, y1);

		pDC->SelectObject(oldBrush);
	}
	else
	{
		CPen* oldPen;
		CPen newPen;

		newPen.CreatePen(PS_SOLID, 1, currentColor.getColor());
		oldPen = (CPen*)pDC->SelectObject(&newPen);

		pDC->Arc(x0, y0, x1, y1, x1, ((y1 -y0)/2) + y0, ((x1 - x0) / 2) + x0, y1);
		pDC->Arc(x0, y0, x1, y1, ((x1 - x0) / 2) + x0, y1, x1, ((y1 -y0)/2) + y0);

		pDC->SelectObject(oldPen);
	}
}

void CElipse::read(CArchive& ar)
{
}

void CElipse::write(CArchive& ar)
{
}

std::string CElipse::ToString()
{
	return std::string();
}

// Check if a point is inside a shape
bool CElipse::IsInside(int x, int y)
{
	int minX = x0 < x1 ? x0 : x1;
	int maxX = x0 > x1 ? x0 : x1;
	int minY = y0 < y1 ? y0 : y1;
	int maxY = y0 > y1 ? y0 : y1;

	return minX < x && x < maxX && minY < y && y < maxY;
}

void CElipse::paintShape(float r, float g, float b)
{
}
