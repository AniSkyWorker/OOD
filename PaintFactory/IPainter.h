#pragma once
#include "IShape.h"
#include "IPictureDraft.h"
#include "ICanvas.h"

class IPainter
{
public:
	virtual void DrawPicture(ICanvas & canvas, const IPictureDraft & draft) const = 0;

	virtual ~IPainter() = default;
};