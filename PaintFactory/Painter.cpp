#include "stdafx.h"
#include "Painter.h"

void CPainter::DrawPicture(ICanvas & canvas, const IPictureDraft & draft) const
{
    for (size_t i = 0; i < draft.GetShapesCount();i++)
    {
        IShape & shape = draft.GetShape(i);
        shape.Draw(canvas);
    }
}