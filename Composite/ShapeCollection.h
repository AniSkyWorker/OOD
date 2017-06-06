#pragma once
#include "IShapeCollection.h"

class ShapeCollection
{
public:
    ShapeCollection() = default;
    ShapeCollection(const std::vector<std::shared_ptr<IShape>>& shapes);

    size_t GetShapesCount()const;
    void InsertShape(const std::shared_ptr<IShape> & shape);
    std::shared_ptr<IShape> GetShapeAtIndex(size_t index);
    void RemoveShapeAtIndex(size_t index);

    const std::vector<std::shared_ptr<IShape>>&  GetShapes() const;
    std::vector<std::shared_ptr<IShape>>& GetShapes();

private:
    std::vector<std::shared_ptr<IShape>> m_shapes;
};

