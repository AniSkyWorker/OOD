#include "stdafx.h"
#include "Client.h"

using namespace color;

CClient::CClient(IDesigner & designer, const IPainter & painter)
    : m_designer(designer)
    , m_painter(painter)
    , m_picture(nullptr)
{}

void CClient::CreatePicture(std::istream & strm)
{
    CCanvas canvas;
    m_painter.DrawPicture(canvas, m_designer.CreateDraft(strm));

    m_picture = std::make_unique<CCanvas>(std::move(canvas));
}

void CClient::ShowPicture(sf::RenderTarget & target)
{
    m_picture->draw(target, sf::RenderStates::Default);
}
