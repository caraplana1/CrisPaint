#include "pch.h"
#include "CRGB.h"

CRGB::CRGB()
{
	this->red = 255;
	this->green = 255;
	this->blue = 255;
}

CRGB::CRGB(int red, int green, int blue)
{
	this->red = red;
	this->green = green;
	this->blue = blue;
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

bool CRGB::operator==(CRGB* color)
{
	return (this->red == color->getRed()) && (this->green == color->getGreen()) && (this->blue == color->getBlue());
}
