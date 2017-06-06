#pragma once
#include "IStyle.h"

class Style : public IStyle
{
public:
	Style(bool isEnabled = false, const RGBAColor & color = RGBAColor());

	bool IsEnabled()const final;
	void Enable(bool enable) final;

	RGBAColor GetColor()const final;
	void SetColor(const RGBAColor & color) final;

private:
	bool m_isEnabled;
	RGBAColor m_color;
};

