#include "stdafx.h"
#include "Triangle.h"

namespace shape_drawing_lib
{

CTriangle::CTriangle(const Point & p1, const Point & p2, const Point & p3)
    : m_first(p1)
    , m_second(p2)
    , m_third(p3)
{
}

void CTriangle::Draw(graphics_lib::ICanvas & canvas)const
{
    canvas.MoveTo(m_first.x, m_first.y);
    canvas.LineTo(m_second.x, m_second.y);
    canvas.LineTo(m_third.x, m_third.y);

    canvas.MoveTo(m_second.x, m_second.y);
    canvas.LineTo(m_third.x, m_third.y);
}

}