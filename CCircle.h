#pragma once
#include "CShape.h"

class CCircle : public CShape
{
public: 
	CCircle();
	CCircle(int x0, int y0, int x1, int y1);
	~CCircle();
	void setPointZero(int x0, int y0);
	void setPointOne(int x1, int y1);
	void render(CDC* pDC);
	void read(CArchive& ar);
	void write(CArchive& ar);

private:
	int x0, y0, x1, y1, centerX, centerY, r;
};

