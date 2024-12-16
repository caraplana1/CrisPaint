#pragma once
#include "CShape.h"

class CLine : public CShape
{
public:
	CLine();
	CLine(int x0, int y0, int x1, int y1);
	~CLine();
	void setEnd(int x1, int y1);
	void render(CDC* pDC);
	void read(CArchive& ar);
	void write(CArchive& ar);

	std::string ToString();
	bool IsInside(int x, int y);
	void paintShape(float r, float g, float b);
private:
	int x0, x1, y0, y1;
};

