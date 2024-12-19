#include "pch.h"
#include "CRGB.h"

CRGB::CRGB()
{
	this->red = 255;
	this->green = 255;
	this->blue = 255;

	this->color = RGB(red, green, blue);
}

CRGB::CRGB(COLORREF color)
{
	this->color = color;
	this->red = GetRValue(color);
	this->green = GetGValue(color);
	this->blue = GetBValue(color);
}

CRGB::CRGB(int red, int green, int blue)
{
	this->red = red;
	this->green = green;
	this->blue = blue;

	this->color = RGB(red, green, blue);
}

int CRGB::getRed()
{
	return this->red;
}

int CRGB::getGreen()
{
	return this->green;
}

int CRGB::getBlue()
{
	return this->blue;
}

COLORREF CRGB::getColor()
{
	return this->color;
}

bool CRGB::operator==(CRGB* color)
{
	return (this->red == color->getRed()) && (this->green == color->getGreen()) && (this->blue == color->getBlue());
}
