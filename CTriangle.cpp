#include "pch.h"
#include "CTriangle.h"

CTriangle::CTriangle()
{
	this->x0 = 0;
	this->y0 = 0;
	this->x1 = 0;
	this->y1 = 0;
	this->x2 = 0;
	this->y2 = 0;

	isReady = false;
	type = TRIANGLE;
}

CTriangle::CTriangle(int x0, int y0, int x1, int y1, int x2, int y2)
{
	this->x0 = x0;
	this->y0 = y0;

	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;

	isReady = (x0 != x1 || y0 != y1) && (x0 != x2 || y0 != y2) && (x1 != x2 || y1 != y2);
	type = TRIANGLE;
}

void CTriangle::setFirst(int x0, int y0)
{
	this->x0 = x0;
	this->y0 = y0;
	isReady = (x0 != x1 || y0 != y1) && (x0 != x2 || y0 != y2) && (x1 != x2 || y1 != y2);
}

void CTriangle::setSecond(int x1, int y1)
{
	this->x1 = x1;
	this->y1 = y1;
	isReady = (x0 != x1 || y0 != y1) && (x0 != x2 || y0 != y2) && (x1 != x2 || y1 != y2);
}

void CTriangle::setThird(int x2, int y2)
{
	this->x2 = x2;
	this->y2 = y2;
	isReady = (x0 != x1 || y0 != y1) && (x0 != x2 || y0 != y2) && (x1 != x2 || y1 != y2);
}

void CTriangle::render(CDC* pDC)
{
	CPoint pts[3];
	pts[0].x = x0;
	pts[0].y = y0;

	pts[1].x = x1;
	pts[1].y = y1;

	pts[2].x = x2;
	pts[2].y = y2;

	pDC->Polygon(pts, 3);
}

void CTriangle::read(CArchive& ar)
{
}

void CTriangle::write(CArchive& ar)
{
}

std::string CTriangle::ToString()
{
	return std::string();
}

bool CTriangle::IsInside(int x, int y)
{
	return false;
}

void CTriangle::paintShape(float r, float g, float b)
{
}
