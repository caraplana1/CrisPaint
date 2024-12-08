#pragma once
#include "CShape.h"

class CRectangle : CShape
{
public:
	CRectangle();
	CRectangle(int x0, int y0, int x1, int y1);
	~CRectangle();
	void setEndPoint(int x, int y);
	void render(CDC* pDC);
	void read(CArchive& ar);
	void write(CArchive& ar);

private:
	int x0, x1, y0, y1;
};

