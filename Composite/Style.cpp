#include "stdafx.h"
#include "Style.h"

Style::Style(bool isEnabled, const RGBAColor & color)
	: m_isEnabled(isEnabled)
	, m_color(color)
{
}

bool Style::IsEnabled() const
{
	return m_isEnabled;
}

void Style::Enable(bool enable)
{
	m_isEnabled = enable;
}

RGBAColor Style::GetColor() const
{
	return m_color;
}

void Style::SetColor(const RGBAColor & color)
{
	m_color = color;
}
