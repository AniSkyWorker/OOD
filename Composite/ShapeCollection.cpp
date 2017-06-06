#include "stdafx.h"
#include "ShapeCollection.h"

using namespace std;

ShapeCollection::ShapeCollection(const std::vector<std::shared_ptr<IShape>>& shapes)
    :m_shapes(shapes)
{
}

size_t ShapeCollection::GetShapesCount() const
{
    return m_shapes.size();
}

void ShapeCollection::InsertShape(const shared_ptr<IShape> & shape)
{
    m_shapes.push_back(shape);
}

shared_ptr<IShape> ShapeCollection::GetShapeAtIndex(size_t index)
{
    if (index >= m_shapes.size())
    {
        throw logic_error("Index is out of range");
    }
    return m_shapes.at(index);
}

void ShapeCollection::RemoveShapeAtIndex(size_t index)
{
    m_shapes.erase(m_shapes.begin() + index);
}

const std::vector<std::shared_ptr<IShape>>& ShapeCollection::GetShapes() const
{
    return m_shapes;
}

std::vector<std::shared_ptr<IShape>>& ShapeCollection::GetShapes()
{
    return m_shapes;
}
