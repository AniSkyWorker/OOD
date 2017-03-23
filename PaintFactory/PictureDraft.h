#pragma once
#include "IPictureDraft.h"

class CPictureDraft : public IPictureDraft
{
public:
    size_t GetShapesCount() const override;
    IShape & GetShape(size_t index) const override;
    void InsertShape(std::unique_ptr<IShape> && shape) override;

private:
    std::vector<std::unique_ptr<IShape>> m_shapes;
};
