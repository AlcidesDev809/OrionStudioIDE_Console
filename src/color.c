#include "color.h"

int getRValue(Color color)
{
    return (color >> 16) & 0xFF;
}

int getGValue(Color color)
{
    return (color >> 8) & 0xFF;
}

int getBValue(Color color)
{
    return color & 0xFF;
}
