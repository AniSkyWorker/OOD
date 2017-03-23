#pragma once
#include "AbstractShape.h"

class CRectangle : public CAbstractShape
{
public:
    CRectangle(const SPoint & topleft, float width, float height);

    void Draw(ICanvas & canvas) override;
    SPoint GetTopLeft() const;
    SPoint GetRightButtom() const;

private:
    SPoint m_topLeft;
    SPoint m_dimensions;
};
