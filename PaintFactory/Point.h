#pragma once

struct SPoint
{
    SPoint(float x, float y);

    SPoint();

    std::string ToString() const;

    float x = 0.f;
    float y = 0.f;
};