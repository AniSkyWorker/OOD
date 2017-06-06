#pragma once
#include "IShape.h"
#include <memory>

class IShapeCollection
{
public:
	virtual size_t GetShapesCount()const = 0;
	virtual void InsertShape(const std::shared_ptr<IShape> & shape) = 0;
	virtual std::shared_ptr<IShape> GetShapeAtIndex(size_t index) = 0;
	virtual void RemoveShapeAtIndex(size_t index) = 0;

	virtual ~IShapeCollection() = default;
};