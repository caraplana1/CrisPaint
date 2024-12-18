#pragma once

// Class to manage RGB colors
class CRGB
{
private: 
	COLORREF color;
	int red;
	int green;
	int blue;

	public:
		CRGB();
		CRGB(COLORREF color);
		CRGB(int red, int green, int blue);
		int getRed();
		int getGreen();
		int getBlue();
		COLORREF getColor();
		bool operator==(CRGB* color);
};

