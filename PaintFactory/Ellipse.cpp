#include "stdafx.h"
#include "Ellipse.h"

CEllipse::CEllipse(const SPoint & center, float horizontalRadius, float verticalRadius)
    : m_horizontalRadius(horizontalRadius)
    , m_verticalRadius(verticalRadius)
    , m_center(center)
{}

void CEllipse::Draw(ICanvas & canvas)
{
    canvas.DrawEllipse(m_center, m_verticalRadius, m_horizontalRadius, GetColor());
}

SPoint CEllipse::GetCenter() const
{
    return m_center;
}

float CEllipse::GetVerticalRadius() const
{
    return m_horizontalRadius;
}

float CEllipse::GetHorizontalRadius() const
{
    return m_verticalRadius;
}

