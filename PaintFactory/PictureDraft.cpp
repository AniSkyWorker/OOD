#include "stdafx.h"
#include "PictureDraft.h"

size_t CPictureDraft::GetShapesCount() const
{
    return m_shapes.size();
}

IShape & CPictureDraft::GetShape(size_t index) const
{
    return *m_shapes[index];
}

void CPictureDraft::InsertShape(std::unique_ptr<IShape> && shape)
{
    if (shape)
    {
        m_shapes.push_back(std::move(shape));
    }
}
