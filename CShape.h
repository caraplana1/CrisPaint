#pragma once
#include "pch.h"
#include "CShape.h"

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
	PRIMITIVE_ID type;
public:
	CShape();
	~CShape();

	virtual void render(CDC* pDC) = 0;
	virtual void read(CArchive &ar) = 0;
	virtual void write(CArchive& ar) = 0;
	bool IsReady();

};

