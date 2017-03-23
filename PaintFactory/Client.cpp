#include "stdafx.h"
#include "Client.h"
#include "Canvas.h"

using namespace color;

CClient::CClient(IDesigner & designer, const IPainter & painter)
    : m_designer(designer)
    , m_painter(painter)
{}

void CClient::CreatePicture()
{
    CCanvas canvas;

    std::cout << "Input canvas color:" << "\n";
    auto color = color::GetColor(std::cin);

    canvas.SetColor(color);
    m_painter.DrawPicture(canvas, m_designer.CreateDraft(std::cin));
}


