#include "stdafx.h"
#include "Rectangle.h"

CRectangle::CRectangle(const SPoint & topleft, float width, float height)
    : m_topLeft(topleft)
    , m_dimensions(width, height)
{}

void CRectangle::Draw(ICanvas & canvas)
{
    SPoint topRight(m_topLeft.x + m_dimensions.x, m_topLeft.y);
    SPoint buttomLeft(m_topLeft.x, m_topLeft.y + m_dimensions.y);
    SPoint buttomRight(m_topLeft.x + m_dimensions.x, m_topLeft.y + m_dimensions.y);
    auto color = GetColor();

    canvas.DrawLine(m_topLeft, topRight, color);
    canvas.DrawLine(m_topLeft, buttomLeft, color);
    canvas.DrawLine(buttomLeft, buttomRight, color);
    canvas.DrawLine(topRight, buttomRight, color);
}

SPoint CRectangle::GetTopLeft() const
{
    return m_topLeft;
}

SPoint CRectangle::GetRightButtom() const
{
    return SPoint(m_topLeft.x + m_dimensions.x, m_topLeft.y + m_dimensions.y);
}
