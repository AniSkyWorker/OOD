#pragma once
#include "AbstractShape.h"

class CRegularPolygon : public CAbstractShape
{
public:
    CRegularPolygon(const SPoint & center, float radius, unsigned vertexCount);
    void Draw(ICanvas & canvas) override;

    unsigned GetVetexCount() const;
    SPoint GetCenter() const;

private:
    SPoint GetPolygonPoint(float angle);

    float m_radius;
    SPoint m_center;
    unsigned m_vertexCount;
};

