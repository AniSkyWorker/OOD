#pragma once
#include "Shape.h"
#include "Point.h"

class Ellipse : public Shape
{
public:
	Ellipse(Point center, float hRadius, float vRadius);
    Rect GetFrame() const final;
    void SetFrame(const Rect& rect) final;

protected:
    void DrawBehavior(ICanvas& canvas) const final;

private:
    void UpdateFrame();

	Point m_center;
	float m_hRadius;
    float m_vRadius;
};

