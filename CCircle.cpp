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
	CPen *old, white;
	CBrush *oldBrush, bWhite;

	white.CreatePen(PS_SOLID | PS_COSMETIC, 1, RGB(255, 255, 255));
	bWhite.CreateSolidBrush(RGB(255, 255, 255));

	pDC->MoveTo(0, 0);
	pDC->Chord(centerX - r, centerY - r, centerX + r, centerY + r, centerX + r, centerY, centerX - r, centerY);
	pDC->Chord(centerX - r, centerY - r, centerX + r, centerY + r, centerX - r, centerY, centerX + r, centerY);

	old = pDC->SelectObject(&white);
	oldBrush = pDC->SelectObject(&bWhite);

	pDC->MoveTo(centerX - r + 1, centerY);
	pDC->LineTo(centerX + r - 1, centerY);
	pDC->MoveTo(centerX - r + 1, centerY-1);
	pDC->LineTo(centerX + r - 1, centerY-1);

	pDC->SelectObject(old);
	pDC->SelectObject(oldBrush);
}

void CCircle::read(CArchive& ar)
{
}

void CCircle::write(CArchive& ar)
{
}

std::string CCircle::ToString()
{
	return std::string();
}

bool CCircle::IsInside(int x, int y)
{
	return false;
}

void CCircle::paintShape(float r, float g, float b)
{
}
