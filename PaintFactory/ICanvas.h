#pragma once
#include "Colors.h"
#include "Point.h"

class ICanvas
{
public:
	virtual void SetColor(sf::Color backgroundColor) = 0;
	virtual void DrawLine(const SPoint & from, const SPoint & to, sf::Color color) = 0;
    virtual void DrawEllipse(const SPoint & center, float width, float height, sf::Color color) = 0;

    virtual void Show() = 0;
    virtual void WaitingForClose() = 0;

    virtual ~ICanvas() = default;
};