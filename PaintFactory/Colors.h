#pragma once

namespace color
{
sf::Color StringToColor(const std::string & colors);

sf::Color GetColor(std::istream & strm);
}