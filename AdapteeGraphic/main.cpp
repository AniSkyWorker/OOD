#include "stdafx.h"
#include "CanvasPainter.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Canvas.h"
#include "ModernCanvas.h"
#include "ModernCanvasRenderer.h"

using namespace std;
// Пространство имен приложения (доступно для модификации)
namespace app
{

void PaintPicture(shape_drawing_lib::CCanvasPainter & painter)
{
    using namespace shape_drawing_lib;

    CTriangle triangle({ 10, 15 }, { 100, 200 }, { 150, 250 });
    CRectangle rectangle({ 30, 40 }, 18, 24);

    painter.Draw(triangle);
    painter.Draw(rectangle);
}

void PaintPictureOnCanvas(graphics_lib::ICanvas & canvas)
{
    shape_drawing_lib::CCanvasPainter painter(canvas);
    PaintPicture(painter);
}

std::unique_ptr<graphics_lib::ICanvas> GetCanvasByApi(bool isModernApi)
{
    if (isModernApi)
    {
        //uncomment code below to use object adapter
        //return std::make_unique<app::CModernCanvas>();
        return std::make_unique<app::CModernCanvasRenderer>();
    }
    else
    {
        return std::make_unique<graphics_lib::CCanvas>();
    }
}

}

int main()
{
    cout << "Should we use new API (y)?";
    string userInput;
    auto canvas = app::GetCanvasByApi(getline(cin, userInput) && (userInput == "y" || userInput == "Y"));
    app::PaintPictureOnCanvas(*canvas);
    return 0;
}
