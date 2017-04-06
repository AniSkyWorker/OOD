#pragma once
#include "ICanvasDrawable.h"

namespace shape_drawing_lib
{

class CTriangle : public ICanvasDrawable
{
public:
    CTriangle(const Point & p1, const Point & p2, const Point & p3);
    void Draw(graphics_lib::ICanvas & canvas)const override;

private:
    Point m_first;
    Point m_second;
    Point m_third;
};

}