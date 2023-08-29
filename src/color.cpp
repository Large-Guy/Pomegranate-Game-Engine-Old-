#include"color.h"

//Functions
Color::Color(float r, float g, float b, float a)
{
    data = (float*)malloc(sizeof(float)*4);
    data[0] = r;
    data[1] = g;
    data[2] = b;
    data[3] = a;
}
Color::Color()
{
    data = (float*)malloc(sizeof(float)*4);
    data[0] = 1.0;
    data[1] = 1.0;
    data[2] = 1.0;
    data[3] = 1.0;
}