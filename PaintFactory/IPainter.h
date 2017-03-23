#pragma once
#include "IShape.h"
#include "IPictureDraft.h"
#include "Canvas.h"

class IPainter
{
public:
	virtual void DrawPicture(CCanvas & canvas, const IPictureDraft & draft) const = 0;

	virtual ~IPainter() = default;
};