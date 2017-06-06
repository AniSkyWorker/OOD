#pragma once
#include "Shape.h"
#include "Point.h"

class Rectangle : public Shape
{
public:
	Rectangle(const Point& leftTop, const Point& dimensions);
    Rect GetFrame() const final;
    void SetFrame(const Rect& rect) final;

protected:
    void DrawBehavior(ICanvas & canvas) const final;

private:
    void UpdateFrame();

	Point m_leftTop;
    Point m_dimensions;
};

