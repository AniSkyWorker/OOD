#pragma once
#include "ICanvas.h"
#include "ModernGraphicsRenderer.h"

namespace app
{

class CModernCanvasRenderer : public graphics_lib::ICanvas, modern_graphics_lib::CModernGraphicsRenderer
{
public:
    CModernCanvasRenderer();

    void MoveTo(int x, int y) override;
    void LineTo(int x, int y) override;

private:
    modern_graphics_lib::CPoint m_point;
};

}
