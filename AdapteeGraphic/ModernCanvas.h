#pragma once
#include "ICanvas.h"
#include "ModernGraphicsRenderer.h"

namespace app 
{

class CModernCanvas : public graphics_lib::ICanvas
{
public:
    CModernCanvas();

    void MoveTo(int x, int y) override;
    void LineTo(int x, int y) override;

private:
    modern_graphics_lib::CModernGraphicsRenderer m_modernRenderer;
    modern_graphics_lib::CPoint m_point;
};

}

