#include "pch.h"
#include "CShape.h"


std::vector<BYTE> CShape::ClampColor(float r, float g, float b)
{
    BYTE R, G, B;

    // Clamp red
    if (r > 1)
        R = 255;
    else if (r < 0)
        R = 0;
    else
        R = r * 255;

    // Clamp green
    if (g > 1)
        G = 255;
    else if (g < 0)
        G = 0;
    else
        G = g * 255;
    
    // Clamp blue
    if (b > 1)
        B = 255;
    else if (b < 0)
        B = 0;
    else
        B = b * 255;

    std::vector<BYTE> result = {R, G, B};

    return result;
}

CShape::CShape()
{
}

CShape::~CShape()
{

}

bool CShape::IsReady()
{
    return this->isReady;
}
