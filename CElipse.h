#pragma once
#include "CShape.h"

class CElipse : public CShape
{
public:
	CElipse();
	CElipse(int x0, int y0, int x1, int y1);
	~CElipse();
	void setFirst(int x0, int y0);
	void setSecond(int x1, int y1);
	void render(CDC* pDC);
	void read(CArchive& ar);
	void write(CArchive& ar);

private:
	int x0, y0, x1, y1;
};

