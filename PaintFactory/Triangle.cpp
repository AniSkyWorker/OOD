#include "stdafx.h"
#include "Triangle.h"

CTriangle::CTriangle(const SPoint & first, const SPoint & second, const SPoint & third)
    : m_first(first)
    , m_second(second)
    , m_third(third)
{}

void CTriangle::Draw(ICanvas & canvas)
{
    canvas.SetColor(GetColor());
    canvas.DrawLine(m_first, m_second);
    canvas.DrawLine(m_first, m_third);
    canvas.DrawLine(m_second, m_third);
}

SPoint CTriangle::GetFirstVertex() const
{
    return m_first;
}

SPoint CTriangle::GetSecondVertex() const
{
    return m_second;
}

SPoint CTriangle::GetThirdVertex() const
{
    return m_third;
}
