#pragma once
#include "ICanvas.h"

class IShape
{
public:
	virtual void Draw(ICanvas & canvas) = 0;
	virtual sf::Color GetColor() const = 0;
	virtual void SetColor(sf::Color color) = 0;

	virtual ~IShape() = default;
};