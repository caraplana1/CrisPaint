#include "pch.h"
#include "CLine.h"

CRGB* WHITE;

CLine::CLine(int x0, int y0, int x1, int y1)
{
	this->x0 = x0;
	this->x1 = x1;
	this->y0 = y0;
	this->y1 = y1;

	this->type = LINE;
	isReady = x0 != x1 || y0 != y1;
	WHITE = new CRGB(255, 255, 255);
}

void CLine::setEnd(int x1, int y1)
{
	this->x1 = x1;
	this->y1 = y1;

	isReady = x0 != x1 || y0 != y1;
}

void CLine::render(CDC* pDC)
{
	// If the line is white draw it black
	if (currentColor == WHITE)
	{
		pDC->MoveTo(x0, y0);
		pDC->LineTo(x1, y1);
		return;
	}

	CPen* oldPen;
	CPen newPen;

	newPen.CreatePen(PS_SOLID, 1, currentColor.getColor());

	oldPen = (CPen*)pDC->SelectObject(&newPen);

	pDC->SelectObject(oldPen);
}

void CLine::read(CArchive& ar)
{
}

void CLine::write(CArchive& ar)
{
}

std::string CLine::ToString()
{
	return std::string();
}

// Check if a point is inside a shape
bool CLine::IsInside(int x, int y)
{
	int minX = x0 < x1 ? x0 : x1;
	int maxX = x0 > x1 ? x0 : x1;
	int minY = y0 < y1 ? y0 : y1;
	int maxY = y0 > y1 ? y0 : y1;

	return minX < x && x < maxX && minY < y && y < maxY;
}

void CLine::paintShape(float r, float g, float b)
{
}
