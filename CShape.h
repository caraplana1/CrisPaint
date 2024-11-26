#pragma once
#include "pch.h"
#include "CShape.h"

class CShape
{
public:
	CShape();
	~CShape();

	virtual void render(CDC* pDC) = 0;
	virtual void read(CArchive &ar) = 0;
	virtual void write(CArchive& ar) = 0;
	int m_type;

};

