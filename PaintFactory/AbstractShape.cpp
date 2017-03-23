#include "stdafx.h"
#include "AbstractShape.h"

sf::Color CAbstractShape::GetColor() const
{
    return m_color;
}

void CAbstractShape::SetColor(sf::Color color)
{
    m_color = color;
}
