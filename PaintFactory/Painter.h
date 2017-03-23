#pragma once
#include "IPainter.h"

class CPainter : public IPainter
{
public:
    void DrawPicture(CCanvas & canvas, const IPictureDraft & draft) const override;
};