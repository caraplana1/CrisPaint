#pragma once
#include "CShape.h"

class CCircle : public CShape
{
public: 
	CCircle();
	~CCircle();
	void render(CDC* pDC);
	void read(CArchive& ar);
	void write(CArchive& ar);

private:
	int x0, y1, r;
};

