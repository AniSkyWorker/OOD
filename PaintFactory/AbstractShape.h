#pragma once
#include "IShape.h"

class CAbstractShape : public IShape
{
public:
    sf::Color GetColor() const override;
    void SetColor(sf::Color color) override;

private:
    sf::Color m_color = sf::Color::White;
};

