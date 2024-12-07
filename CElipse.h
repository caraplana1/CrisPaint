#pragma once
#include "CShape.h"

class CElipse : public CShape
{
public:
	CElipse();
	~CElipse();
	void render(CDC* pDC);
	void read(CArchive& ar);
	void write(CArchive& ar);

private:
	int x0, y0, x1, y1;
};

