#include "stdafx.h"
#include "Rectangle.h"
#include "ICanvas.h"

Rectangle::Rectangle(const Point & leftTop, const Point& dimensions)
	: m_leftTop(leftTop)
	, m_dimensions(dimensions)
{
    UpdateFrame();
}

Rect Rectangle::GetFrame() const
{
    return m_frame;
}

void Rectangle::SetFrame(const Rect & rect)
{
    m_leftTop = { rect.left, rect.top };
    m_dimensions.x = rect.width;
    m_dimensions.y = rect.height;
    UpdateFrame();
}

void Rectangle::DrawBehavior(ICanvas & canvas) const
{
	canvas.MoveTo(m_leftTop.x, m_leftTop.y);

	canvas.LineTo(m_leftTop.x + m_dimensions.x, m_leftTop.y);
	canvas.LineTo(m_leftTop.x + m_dimensions.x, m_leftTop.y + m_dimensions.y);
	canvas.LineTo(m_leftTop.x, m_leftTop.y + m_dimensions.y);
	canvas.LineTo(m_leftTop.x, m_leftTop.y);
}

void Rectangle::UpdateFrame()
{
    m_frame = { m_leftTop.x, m_leftTop.y, m_dimensions.x, m_dimensions.y };
}
