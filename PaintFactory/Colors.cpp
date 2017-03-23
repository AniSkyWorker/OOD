#include "stdafx.h"
#include "Colors.h"

namespace color
{

sf::Color StringToColor(const std::string & colors)
{
    sf::Color color;

    if (colors == "blue")
    {
        color = sf::Color::Blue;
    }
    else if (colors == "red")
    {
        color = sf::Color::Red;
    }
    else if (colors == "black")
    {
        color = sf::Color::Black;
    }
    else if (colors == "white")
    {
        color = sf::Color::White;
    }
    else if (colors == "yellow")
    {
        color = sf::Color::Yellow;
    }
    else
    {
        throw std::runtime_error("Incorrect color!");
    }

    return color;
}

sf::Color GetColor(std::istream & strm)
{
    std::string color;
    strm >> color;

    return StringToColor(color);
}

}