#include "stdafx.h"
#include "ModernCanvasRenderer.h"

using namespace std;

namespace app
{

CModernCanvasRenderer::CModernCanvasRenderer()
    : CModernGraphicsRenderer(std::cout)
    , m_point(0, 0)
{
   BeginDraw();
}

void CModernCanvasRenderer::MoveTo(int x, int y)
{
    m_point = { x, y };
}

void CModernCanvasRenderer::LineTo(int x, int y)
{
    DrawLine(m_point, { x, y });
    MoveTo(x, y);
}

}