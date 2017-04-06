#pragma once
#include "IDesigner.h"
#include "IPainter.h"
#include "Canvas.h"

class CClient
{
public:
    CClient(IDesigner & designer, const IPainter & painter);

    void CreatePicture(std::istream & strm);
    void ShowPicture(sf::RenderTarget & target);

private:
	IDesigner & m_designer;
	const IPainter & m_painter;
    std::unique_ptr<CCanvas> m_picture;
};