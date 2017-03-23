#pragma once
#include "IDesigner.h"
#include "IPainter.h"

class CClient
{
public:
    CClient(IDesigner & designer, const IPainter & painter);

    void CreatePicture(); 

private:
	IDesigner & m_designer;
	const IPainter & m_painter;
};