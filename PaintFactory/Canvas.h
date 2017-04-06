#pragma once
#include "ICanvas.h"

class CCanvas final : public ICanvas, public sf::Drawable
{
public:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void SetColor(sf::Color backgroundColor) override;
    void DrawLine(const SPoint & from, const SPoint & to) override;
    void DrawEllipse(const SPoint & center, float width, float height) override;

private:
    sf::Color m_color;
    std::vector<std::unique_ptr<sf::Drawable>> m_displayList;
};
