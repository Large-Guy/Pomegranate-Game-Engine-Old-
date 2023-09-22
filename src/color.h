#pragma once

#include <stdlib.h>

//TODO: Color needs rework.
struct Color
{
public:
    float* data;
    Color(float r, float g, float b, float a = 1.0f);
    Color();
};