#include "Rectangle.h"

void Rectangle::setWidth(double w)
{
    if (w >= 0) width = w;
    else        throw NegativeWidth();
}

void Rectangle::setLength(double len)
{
    if (len >= 0) length = len;
    else          throw NegativeLength();
}
