#include "stdafx.h"
#include "Ellipse.h"

CEllipse::CEllipse(const SPoint & center, float radius, float radius1)
    : m_fRadius(radius)
    , m_sRadius(radius1)
    , m_center(center)
{}

void CEllipse::Draw(ICanvas & canvas)
{
    canvas.DrawEllipse(m_center, m_fRadius, m_sRadius, GetColor());
}

SPoint CEllipse::GetCenter() const
{
    return m_center;
}

float CEllipse::GetVerticalRadius() const
{
    return m_fRadius;
}

float CEllipse::GetHorizontalRadius() const
{
    return m_sRadius;
}

