#include "stdafx.h"
#include "ModernCanvas.h"

using namespace std;

namespace app
{

CModernCanvas::CModernCanvas()
    : m_modernRenderer(std::cout)
    , m_point(0, 0)
{
    m_modernRenderer.BeginDraw();
}

void CModernCanvas::MoveTo(int x, int y)
{
    m_point = { x, y };
}

void CModernCanvas::LineTo(int x, int y)
{
    m_modernRenderer.DrawLine(m_point, { x, y });
}

}