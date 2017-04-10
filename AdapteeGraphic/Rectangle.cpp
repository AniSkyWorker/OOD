#include "stdafx.h"
#include "Rectangle.h"

namespace shape_drawing_lib
{

CRectangle::CRectangle(const Point & leftTop, int width, int height)
    : m_leftTop(leftTop)
    , m_dimensions({width, height})
{
}

void CRectangle::Draw(graphics_lib::ICanvas & canvas)const
{
    canvas.MoveTo(m_leftTop.x, m_leftTop.y);

    canvas.LineTo(m_leftTop.x + m_dimensions.x, m_leftTop.y);
    canvas.LineTo(m_leftTop.x + m_dimensions.x, m_leftTop.y + m_dimensions.y);
    canvas.LineTo(m_leftTop.x, m_leftTop.y + m_dimensions.y);
    canvas.LineTo(m_leftTop.x, m_leftTop.y);
}

}