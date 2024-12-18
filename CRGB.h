#pragma once

// Class to manage RGB colors
class CRGB
{
private: 
	int red;
	int green;
	int blue;

	public:
		CRGB();
		CRGB(int red, int green, int blue);
		int getRed();
		int getGreen();
		int getBlue();
		bool operator==(CRGB* color);
};

