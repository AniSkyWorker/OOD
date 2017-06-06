#pragma once
#include "IShape.h"
#include "IShapeCollection.h"

class IShapeGroup 
    : public IShape
    , public IShapeCollection
{
public:
    virtual ~IShapeGroup() = default;
};