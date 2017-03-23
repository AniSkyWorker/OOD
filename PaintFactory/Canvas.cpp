#include "stdafx.h"
#include "Canvas.h"

using namespace color;

const unsigned ELLIPSE_QUALITY = 100;

CCanvas::CCanvas()
    : sf::RenderWindow(sf::VideoMode(800, 600), "Canvas")
{
}

void CCanvas::SetColor(sf::Color backgroundColor)
{
    m_color = backgroundColor;
    clear(backgroundColor);
}

void CCanvas::DrawLine(const SPoint & from, const SPoint & to, sf::Color color)
{
    sf::Vertex line[] =
    {
        sf::Vertex({ from.x, from.y }, color),
        sf::Vertex({ to.x, to.y }, color)
    };
    draw(line, 2, sf::Lines);
    //std::cout << "Draw " + color::ColorToString(color) + " line from " + from.ToString() + " to " + to.ToString() << "\n";
}

void CCanvas::DrawEllipse(const SPoint & center, float width, float height, sf::Color color)
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
    ellipse.setOutlineColor(color);

    draw(ellipse);

   // std::cout << "Draw " + color::ColorToString(color) + " ellipse with radiuses: " + std::to_string(width) + " and " + std::to_string(height) << "\n"
   //     << "with center in" << center.ToString() << "\n";
}