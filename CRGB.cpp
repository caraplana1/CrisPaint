#include "pch.h"
#include "CRGB.h"

CRGB::CRGB()
{
	this->red = 0;
	this->green = 0;
	this->blue = 0;
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
