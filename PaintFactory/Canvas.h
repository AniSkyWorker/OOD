#pragma once
#include "ICanvas.h"

class CCanvas final : public ICanvas, public sf::RenderWindow
{
public:
    CCanvas();
    void SetColor(sf::Color backgroundColor) override;
    void DrawLine(const SPoint & from, const SPoint & to, sf::Color color) override;
    void DrawEllipse(const SPoint & center, float width, float height, sf::Color color) override;

private:
    sf::Color m_color;
};
