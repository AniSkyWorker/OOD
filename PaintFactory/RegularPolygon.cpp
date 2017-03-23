#include "stdafx.h"
#include "RegularPolygon.h"

CRegularPolygon::CRegularPolygon(const SPoint & center, float radius, unsigned vertexCount)
    : m_center(center)
    , m_radius(radius)
    , m_vertexCount(vertexCount)
{}

void CRegularPolygon::Draw(ICanvas & canvas)
{
    auto color = GetColor();
    float angle = static_cast<float>(M_PI) * 2 / m_vertexCount;

    SPoint firstPoint = GetPolygonPoint(0);

    for (unsigned i = 1; i <= m_vertexCount; i++)
    {
        SPoint secondPoint = GetPolygonPoint(i * angle);
        canvas.DrawLine(firstPoint, secondPoint, color);
        firstPoint = secondPoint;
    }
}

unsigned CRegularPolygon::GetVetexCount() const
{
    return m_vertexCount;
}

SPoint CRegularPolygon::GetCenter() const
{
    return m_center;
}

SPoint CRegularPolygon::GetPolygonPoint(float angle)
{
    return{ m_center.x + m_radius * cosf(angle), m_center.y + m_radius * sinf(angle) };
}
