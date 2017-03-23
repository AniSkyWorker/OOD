#pragma once
#include "IShape.h"

class IShapeFactory
{
public:
	virtual std::unique_ptr<IShape> CreateShape(std::istream & args) const = 0;

	virtual ~IShapeFactory() = default;
};