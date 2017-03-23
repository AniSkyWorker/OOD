#pragma once
#include "IShape.h"

class IPictureDraft
{
public:
    virtual size_t GetShapesCount() const = 0;
    virtual IShape & GetShape(size_t index) const = 0;
    virtual void InsertShape(std::unique_ptr<IShape> && shape) = 0;

    virtual ~IPictureDraft() = default;
};
