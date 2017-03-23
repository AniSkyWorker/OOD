#include "stdafx.h"
#include "Client.h"
#include "Designer.h"
#include "Painter.h"
#include "ShapeFactory.h"

int main(int argc, char ** argv)
{
    try
    {
        CDesigner designer(std::move(std::make_unique<CShapeFactory>()));
        CPainter painter;
        CClient client(designer, painter);
        client.CreatePicture();
    }
    catch (const std::exception & exc)
    {
        std::cout << "Error! " <<exc.what() << std::endl;
    }
}