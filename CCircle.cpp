#include "pch.h"
#include "CCircle.h"

CCircle::CCircle()
{
	x0 = 0;
	y0 = 0;
	x1 = 0;
	y1 = 0;
	centerX = 0;
	centerY = 0;
	r = 0;
	isReady = false;
	type = CIRCLE;
}

CCircle::CCircle(int x0, int y0, int x1, int y1)
{
	this->x0 = x0;
	this->y0 = y0;
	this->x1 = x1;
	this->y1 = y1;

	centerX = x1 > x0 ? x0 + ((x1 - x0) / 2) : x1 + ((x0 - x1) / 2);
	centerY = y1 > y0 ? y0 + ((y1 - y0) / 2) : y1 + ((y0 - y1) / 2);
	int distanceX = abs(x0 - centerX);
	int distanceY = abs(y0 - centerY);
	r = distanceX > distanceY ? distanceY : distanceX;
	isReady = x0 != x1 || y0 != y1;
	type = CIRCLE;
}

void CCircle::setPointZero(int x0, int y0)
{
	this->x0 = x0;
	this->y0 = y0;
	centerX = x1 > x0 ? x0 + ((x1 - x0) / 2) : x1 + ((x0 - x1) / 2);
	centerY = y1 > y0 ? y0 + ((y1 - y0) / 2) : y1 + ((y0 - y1) / 2);
	int distanceX = abs(x0 - centerX);
	int distanceY = abs(y0 - centerY);
	r = distanceX > distanceY ? distanceY : distanceX;
	r = distanceX > distanceY ? distanceY : distanceX;
	isReady = x0 != x1 || y0 != y1;
}

void CCircle::setPointOne(int x1, int y1)
{
	this->x1 = x1;
	this->y1 = y1;
	centerX = x1 > x0 ? x0 + ((x1 - x0) / 2) : x1 + ((x0 - x1) / 2);
	centerY = y1 > y0 ? y0 + ((y1 - y0) / 2) : y1 + ((y0 - y1) / 2);
	int distanceX = abs(x0 - centerX);
	int distanceY = abs(y0 - centerY);
	r = distanceX > distanceY ? distanceY : distanceX;

	isReady = x0 != x1 || y0 != y1;
}

void CCircle::render(CDC* pDC)
{
	if (isFiled)
	{
		CBrush* oldBrush;
		CBrush newBrush;
		
		newBrush.CreateSolidBrush(currentColor.getColor());
		oldBrush = (CBrush*)pDC->SelectObject(&newBrush);

		pDC->MoveTo(0, 0);
		pDC->Ellipse(centerX - r, centerY - r, centerX + r, centerY + r);

		pDC->SelectObject(oldBrush);
	}
	else
	{
		CPen* oldPen;
		CPen newPen;

		newPen.CreatePen(PS_SOLID, 1, currentColor.getColor());
		oldPen = (CPen*)pDC->SelectObject(&newPen);

		pDC->Arc(centerX - r, centerY - r, centerX + r, centerY + r, centerX + r, centerY, centerX, centerY + r);
		pDC->Arc(centerX - r, centerY - r, centerX + r, centerY + r, centerX, centerY + r, centerX + r, centerY);

		pDC->SelectObject(oldPen);
	}
}

void CCircle::read(CArchive& ar)
{
}

void CCircle::write(CArchive& ar)
{
}

std::string CCircle::ToString()
{
	if (isFiled)
		return std::format("FILLED_CIRCLE {} {} {} {} {} {} {} {} {} {}", 
			x0, y0, x1, y1, 
			0, 0, 0, 
			(float)currentColor.getRed()/255, (float)currentColor.getGreen()/255, (float)currentColor.getBlue()/255);
	else
		return std::format("CIRCLE {} {} {} {} {} {} {}", 
			x0, y0, x1, y1, 
			(float)currentColor.getRed()/255, (float)currentColor.getGreen()/255, (float)currentColor.getBlue()/255);
}

// Check if a point is inside a shape
bool CCircle::IsInside(int x, int y)
{
	return centerX - r < x && x < centerX + r && centerY - r < y && y < centerY + y;
}

void CCircle::paintShape(float r, float g, float b)
{
}
