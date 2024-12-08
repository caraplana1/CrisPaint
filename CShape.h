#pragma once
#include "pch.h"
#include "CShape.h"
#include <string>
#include <vector>

enum PRIMITIVE_ID
{
	LINE,
	CIRCLE,
	SQUARE,
	TRIANGLE,
	ELIPSE,
	CURVE
};

class CShape
{
protected:
	bool isReady;
	bool isFiled;
	CBrush brush;
	CPen pen;
	PRIMITIVE_ID type;
	std::vector<BYTE> ClampColor(float r, float g, float b);
public:
	CShape();
	~CShape();

	virtual void render(CDC* pDC) = 0;
	virtual void read(CArchive &ar) = 0;
	virtual void write(CArchive& ar) = 0;

	virtual std::string ToString() = 0;
	virtual bool IsInside(int x, int y) = 0;
	virtual void paintShape(float r, float g, float b) = 0;
	bool IsReady();

};

