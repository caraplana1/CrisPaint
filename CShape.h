#pragma once
#include "pch.h"
#include "CRGB.h"
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
	CRGB currentColor;
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
	// Check if a point is inside a shape
	virtual bool IsInside(int x, int y) = 0;
	virtual void paintShape(float r, float g, float b) = 0;
	bool IsReady();
	void SetColor(int r, int g, int b);
	void SetColor(COLORREF color);
};

