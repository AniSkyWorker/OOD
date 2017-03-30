#pragma once
#include "IPainter.h"

class CPainter : public IPainter
{
public:
    void DrawPicture(ICanvas & canvas, const IPictureDraft & draft) const override;
};