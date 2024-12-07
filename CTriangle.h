#pragma once
#include "CShape.h"

class CTriangle : public CShape
{
public:
	CTriangle();
	~CTriangle();
	void render(CDC* pDC);
	void read(CArchive& ar);
	void write(CArchive& ar);
private:
	int x0, x1, x2, y0, y1, y2;
};

