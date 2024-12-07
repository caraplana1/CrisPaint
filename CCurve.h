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
private:
	int x0, x1, y0, y1;
};

