#include "stdafx.h"
#include "Canvas.h"
#include "RGBAColor.h"

using namespace std;

Canvas::Canvas(std::ostream & ostream)
	: m_ostream(ostream)
{
}

void Canvas::BeginDraw()
{
	m_ostream << "<svg xmlns = \"http://www.w3.org/2000/svg\">" << endl;
}

void Canvas::EndDraw()
{
	if (m_draw)
	{
		EndPath();
	}
	m_ostream << "</svg>" << endl;
}

void Canvas::MoveTo(float x, float y)
{
	if (!m_draw)
	{
		StartPath();
	}
	m_ostream << boost::format("M %1$.3f %2$.3f ") % x % y;
}

void Canvas::LineTo(float x, float y)
{
	if (!m_draw)
	{
		MoveTo(0, 0);
	}
	m_ostream << "L " << x << " " << y;
}

void Canvas::DrawEllipse(float x, float y, float hRadius, float vRadius)
{
	if (m_draw)
	{
		EndPath();
	}
	m_ostream << "\t<ellipse ";
	SetFillStyle();
	SetLineStyle();
	m_ostream << "cx=\"" << x << '"' << " cy=\"" << y << '"' << " rx=\"" << hRadius << '"' << " ry=\"" << vRadius << '"';
	m_ostream << " />" << endl;
}

void Canvas::SetLineWidth(int width)
{
    m_lineWidth = width;
	EndPath();
}

void Canvas::SetLineColor(RGBAColor color)
{
    m_lineColor = color;
	EndPath();
}

void Canvas::BeginFill(RGBAColor color)
{
    m_fillColor = color;
	EndPath();
}

void Canvas::EndFill()
{
    m_fillColor = boost::none;
	EndPath();
}

void Canvas::StartPath()
{
	if (!m_draw)
	{
		m_draw = true;
		m_ostream << "\t<path ";
		SetLineStyle();
		SetFillStyle();
		m_ostream << "d=\"";
	}
}

void Canvas::EndPath()
{
	if (m_draw)
	{
        m_draw = false;
		m_ostream << "\" />" << endl;
	}
}

void Canvas::SetLineStyle()
{
	m_ostream << boost::format(R"(stroke="#%1$06X" stroke-width="%2%" )") % m_lineColor.rgbColor % m_lineWidth;
}

void Canvas::SetFillStyle()
{
	if (m_fillColor)
	{
		m_ostream << boost::format(R"(fill="#%1$06X" fill-opacity="%2$.3f" )") % m_fillColor->rgbColor % m_fillColor->opacity;
	}
	else
	{
		m_ostream << "fill=\"none\" ";
	}
}
