#pragma once
#include "CShape.h"

class CCurve : public CShape
{
public:
	CCurve();
	~CCurve();
	void render(CDC* pDC);
	void read(CArchive& ar);
	void write(CArchive& ar);

	std::string ToString();
	// Check if a point is inside a shape
	bool IsInside(int x, int y);
	void paintShape(float r, float g, float b);
private:
	int x0, x1, y0, y1;
};

