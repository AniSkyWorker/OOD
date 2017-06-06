#include "stdafx.h"
#include "LineStyle.h"

LineStyle::LineStyle(bool isEnabled, const RGBAColor & color, int lineWidth)
	: m_isEnabled(isEnabled)
	, m_color(color)
	, m_lineWidth(lineWidth)
{
}

bool LineStyle::IsEnabled() const
{
	return m_isEnabled;
}

void LineStyle::Enable(bool enable)
{
	m_isEnabled = enable;
}

RGBAColor LineStyle::GetColor() const
{
	return m_color;
}

void LineStyle::SetColor(const RGBAColor & color)
{
	m_color = color;
}

int LineStyle::GetLineWidth() const
{
	return m_lineWidth;
}

void LineStyle::SetLineWidth(int width)
{
	m_lineWidth = width;
}
