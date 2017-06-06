#include "stdafx.h"
#include "Slide.h"
#include "ICanvas.h"

void Slide::Draw(ICanvas & canvas) const
{
    auto& shapes = m_shapeCollection.GetShapes();
    for (auto& shape : shapes)
    {
        shape->Draw(canvas);
    }
}

size_t Slide::GetShapesCount() const
{
    return  m_shapeCollection.GetShapesCount();;
}

void Slide::InsertShape(const std::shared_ptr<IShape>& shape)
{
    m_shapeCollection.InsertShape(shape);
}

std::shared_ptr<IShape> Slide::GetShapeAtIndex(size_t index)
{
    return m_shapeCollection.GetShapeAtIndex(index);
}

void Slide::RemoveShapeAtIndex(size_t index)
{
    return m_shapeCollection.RemoveShapeAtIndex(index);
}
