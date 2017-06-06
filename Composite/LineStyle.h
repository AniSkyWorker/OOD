#pragma once
#include "ILineStyle.h"

class LineStyle : public ILineStyle
{
public:
	LineStyle(bool isEnabled = false, const RGBAColor & color = RGBAColor(), int lineWidth = 1);
	
	bool IsEnabled()const final;
	void Enable(bool enable) final;

	RGBAColor GetColor()const final;
	void SetColor(const RGBAColor & color) final;

    int GetLineWidth()const final;
	void SetLineWidth(int width) final;

private:
	bool m_isEnabled;
	RGBAColor m_color;
    int m_lineWidth;
};

