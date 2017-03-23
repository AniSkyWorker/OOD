#include "stdafx.h"
#include "Point.h"

SPoint::SPoint(float x, float y)
    : x(x)
    , y(y)
{}

SPoint::SPoint()
{}

std::string SPoint::ToString() const
{
    return "(" + std::to_string(x) + ";" + std::to_string(y) + ")";
}
