#pragma once
#include "AbstractShape.h"

class CEllipse : public CAbstractShape
{
public:
    CEllipse(const SPoint & center, float radius, float radius1);

    void Draw(ICanvas & canvas) override;

    SPoint GetCenter() const;
    float GetVerticalRadius() const;
    float GetHorizontalRadius() const;

private:
    SPoint m_center;
    float m_fRadius;
    float m_sRadius;
};
