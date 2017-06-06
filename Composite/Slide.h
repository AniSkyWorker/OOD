#pragma once
#include "GroupShape.h"

class Slide 
    : public IDrawable
    , public IShapeCollection
{
public:
	void Draw(ICanvas& canvas) const final;

    size_t GetShapesCount()const final;
    void InsertShape(const std::shared_ptr<IShape> & shape) final;
    std::shared_ptr<IShape> GetShapeAtIndex(size_t index) final;
    void RemoveShapeAtIndex(size_t index)final;

private:
	ShapeCollection m_shapeCollection;
};