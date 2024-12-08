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
private:
	int x0, x1, x2, y0, y1, y2;
};

