#pragma once
#include "CShape.h"

class CTriangle : public CShape
{
public:
	CTriangle();
	CTriangle(int x0, int y0, int x1, int y1, int x2, int y2);
	~CTriangle();
	void setFirst(int x0, int y0);
	void setSecond(int x0, int y0);
	void setThird(int x0, int y0);
	void render(CDC* pDC);
	void read(CArchive& ar);
	void write(CArchive& ar);

	std::string ToString();
	// Check if a point is inside a shape
	bool IsInside(int x, int y);
	void paintShape(float r, float g, float b);
private:
	int x0, x1, x2, y0, y1, y2;
	// Return the min value in three. Use for a same axis of a set of points
	int minThreeCoord(int p0, int p1, int p2);
	// Return the max value in three. Use for a same axis of a set of points
	int maxThreeCoord(int p0, int p1, int p2);
};

