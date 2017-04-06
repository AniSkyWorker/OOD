#include "stdafx.h"
#include "Canvas.h"

using namespace color;

const unsigned ELLIPSE_QUALITY = 70;

void CCanvas::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    for (auto const& drawableObj : m_displayList)
    {
        target.draw(*drawableObj, states);
    }
}

void CCanvas::SetColor(sf::Color backgroundColor)
{
    m_color = backgroundColor;
}

void CCanvas::DrawLine(const SPoint & from, const SPoint & to)
{
    sf::Vertex points[] =
    {
        sf::Vertex({ from.x, from.y }, m_color),
        sf::Vertex({ to.x, to.y }, m_color)
    };

    sf::VertexArray line(sf::Lines, 2);
    std::for_each(std::begin(points), std::end(points), [&line](const sf::Vertex& vertex) {line.append(vertex); });
    m_displayList.push_back(std::make_unique<sf::VertexArray>(line));
}

void CCanvas::DrawEllipse(const SPoint & center, float width, float height)
{
    sf::ConvexShape ellipse;
    ellipse.setPointCount(ELLIPSE_QUALITY);

    for (unsigned i = 0; i < ELLIPSE_QUALITY; ++i)
    {
        float rad = (360 / ELLIPSE_QUALITY * i) / (360 / static_cast<float> (M_PI) / 2);
        float x = cos(rad) * width;
        float y = sin(rad) * height;

        ellipse.setPoint(i, sf::Vector2f(x, y));
    };

    ellipse.setPosition(center.x, center.y);
    ellipse.setFillColor(m_color);
    ellipse.setOutlineThickness(1.f);
    ellipse.setOutlineColor(m_color);

    m_displayList.push_back(std::make_unique<sf::ConvexShape>(ellipse));
}
