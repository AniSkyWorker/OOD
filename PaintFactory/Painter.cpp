#include "stdafx.h"
#include "Painter.h"

void CPainter::DrawPicture(CCanvas & canvas, const IPictureDraft & draft) const
{
    for (size_t i = 0; i < draft.GetShapesCount();i++)
    {
        IShape & shape = draft.GetShape(i);
        shape.Draw(canvas);
    }

    canvas.display();

    while (canvas.isOpen())
    {
        sf::Event event;
        while (canvas.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                canvas.close();
        }
    }
}