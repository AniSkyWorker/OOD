#pragma once
#include "Shape.h"
#include "Point.h"

class Triangle : public Shape
{
public:
	Triangle(const Point& first, const Point& second, const Point& third);
    Rect GetFrame()const final;
    void SetFrame(const Rect& rect) final;

protected:
    void DrawBehavior(ICanvas & canvas) const final;

private:
    void UpdateFrame();

    Point m_first;
    Point m_second;
    Point m_third;
};

