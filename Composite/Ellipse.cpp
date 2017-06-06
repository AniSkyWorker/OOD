#include "stdafx.h"
#include "Ellipse.h"
#include "ICanvas.h"

Ellipse::Ellipse(Point center, float hRadius, float vRadius)
	: m_center(center)
    , m_hRadius(hRadius)
    , m_vRadius(vRadius)
{
    UpdateFrame();
}

Rect Ellipse::GetFrame() const
{
    return m_frame;
}

void Ellipse::SetFrame(const Rect & rect)
{
    m_center.x = rect.left + rect.width / 2;
    m_center.y = rect.top + rect.height / 2;
    m_hRadius = rect.width / 2;
    m_vRadius = rect.height / 2;
    
    UpdateFrame();
}

void Ellipse::DrawBehavior(ICanvas & canvas) const
{
	canvas.DrawEllipse(m_center.x, m_center.y, m_hRadius, m_vRadius);
}

void Ellipse::UpdateFrame()
{
    m_frame = { m_center.x - m_hRadius, m_center.y - m_vRadius, 2 * m_hRadius, 2 * m_vRadius };
}
