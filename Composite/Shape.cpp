#include "stdafx.h"
#include "Shape.h"
#include "ICanvas.h"

using namespace std;

Shape::Shape()
{
	m_fillStyle = make_shared<Style>();
	m_outlineStyle = make_shared<LineStyle>(true, 0);
}

void Shape::SetOutlineStyle(const std::shared_ptr<ILineStyle> & style)
{
	m_outlineStyle = style;
}

std::shared_ptr<ILineStyle> Shape::GetOutlineStyle() const
{
	return m_outlineStyle;
}

void Shape::SetFillStyle(const std::shared_ptr<IStyle> & style)
{
	m_fillStyle = style;
}

std::shared_ptr<IStyle> Shape::GetFillStyle() const
{
	return m_fillStyle;
}

std::shared_ptr<IShapeGroup> Shape::GetGroup()
{
	return nullptr;
}

void Shape::Draw(ICanvas & canvas) const
{
    if (m_fillStyle->IsEnabled())
    {
        canvas.BeginFill(m_fillStyle->GetColor());
    }

    if (m_outlineStyle->IsEnabled())
    {
        canvas.SetLineColor(m_outlineStyle->GetColor());
    }

    DrawBehavior(canvas);

    if (m_fillStyle->IsEnabled())
    {
        canvas.EndFill();
    }
}
