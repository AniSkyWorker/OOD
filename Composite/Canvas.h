#pragma once
#include "ICanvas.h"
#include "RGBAColor.h"

class Canvas : public ICanvas
{
public:
	Canvas(std::ostream& ostream);
	void BeginDraw();
	void EndDraw();

	void MoveTo(float x, float y) final;
	void LineTo(float x, float y) final;
	void DrawEllipse(float x, float y, float hRadius, float vRadius) final;
    void SetLineWidth(int width) final;
    void SetLineColor(RGBAColor color) final;
    void BeginFill(RGBAColor color) final;
    void EndFill() final;

private:
	void StartPath();
	void EndPath();
	void SetLineStyle();
	void SetFillStyle();

	bool m_draw = false;
    int m_lineWidth = 1;
    RGBAColor m_lineColor;
    boost::optional<RGBAColor> m_fillColor;
    std::ostream & m_ostream;
};

