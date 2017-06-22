#pragma once

struct Point
{
    Point() = default;
    Point(float x, float y)
        :x(x), y(y)
    {}
    float x = 0;
    float y = 0;
};