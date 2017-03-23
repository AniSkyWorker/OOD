#pragma once
#include "AbstractShape.h"

class CTriangle : public CAbstractShape
{
public:
    CTriangle(const SPoint & first, const SPoint & second, const SPoint & third);

    void Draw(ICanvas & canvas) override;

    SPoint GetFirstVertex() const;
    SPoint GetSecondVertex() const;
    SPoint GetThirdVertex() const;

private:
    SPoint m_first;
    SPoint m_second;
    SPoint m_third;
};
