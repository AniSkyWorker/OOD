#include "stdafx.h"
#include "Canvas.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "Triangle.h"
#include "LineStyle.h"
#include "Style.h"
#include "Slide.h"
#include "Point.h"

using namespace std;

namespace
{
std::shared_ptr<ShapeGroup> BuildRobot()
{
    auto leftHand = make_shared<Rectangle>(Point{ 200, 200 }, Point{ 300, 50 });
    leftHand->SetFillStyle(make_shared<Style>(true, RGBAColor(0x94631e)));
    leftHand->SetOutlineStyle(make_shared<LineStyle>(true, RGBAColor(0)));

    auto rightHand = make_shared<Rectangle>(Point{ 700, 200 }, Point{ 300, 50 });
    rightHand->SetFillStyle(make_shared<Style>(true, RGBAColor(0x94631e)));
    rightHand->SetOutlineStyle(make_shared<LineStyle>(true, RGBAColor(0)));

    auto body = make_shared<Rectangle>(Point{ 500, 200 }, Point{ 200, 400 });
    body->SetFillStyle(make_shared<Style>(true, RGBAColor(0x94631e)));
    body->SetOutlineStyle(make_shared<LineStyle>(true, RGBAColor(0)));

    auto head = make_shared<Ellipse>(Point{ 600, 100 }, 100, 100);
    head->SetFillStyle(make_shared<Style>(true, RGBAColor(0xffd724)));
    head->SetOutlineStyle(make_shared<LineStyle>(true, RGBAColor(0xFF7924)));

    auto lEye = make_shared<Ellipse>(Point{ 550, 80 }, 30, 30);
    lEye->SetFillStyle(make_shared<Style>(true, RGBAColor(0x0)));
    lEye->SetOutlineStyle(make_shared<LineStyle>(true, RGBAColor(0xFF7924)));

    auto rEye = make_shared<Ellipse>(Point{ 650, 80 }, 30, 30);
    rEye->SetFillStyle(make_shared<Style>(true, RGBAColor(0xFA0900)));
    rEye->SetOutlineStyle(make_shared<LineStyle>(true, RGBAColor(0xFF7924)));

    auto nose = make_shared<Triangle>(Point{ 600, 100 }, Point{580,120}, Point{ 620, 120 });
    nose->SetFillStyle(make_shared<Style>(true, RGBAColor(0x0000FA)));
    nose->SetOutlineStyle(make_shared<LineStyle>(true, RGBAColor(0xFF7924)));

    auto mouth = make_shared<Ellipse>(Point{ 600, 160 }, 70, 20);
    mouth->SetFillStyle(make_shared<Style>(true, RGBAColor(0x329664)));
    mouth->SetOutlineStyle(make_shared<LineStyle>(true, RGBAColor(0xFF7924)));

    auto leftLeg = make_shared<Rectangle>(Point{ 500, 600 }, Point{ 50, 300 });
    leftLeg->SetFillStyle(make_shared<Style>(true, RGBAColor(0x94631e)));
    leftLeg->SetOutlineStyle(make_shared<LineStyle>(true, RGBAColor(0)));

    auto rightLeg = make_shared<Rectangle>(Point{ 650, 600 }, Point{ 50, 300 });
    rightLeg->SetFillStyle(make_shared<Style>(true, RGBAColor(0x94631e)));
    rightLeg->SetOutlineStyle(make_shared<LineStyle>(true, RGBAColor(0)));

    auto robot = make_shared<ShapeGroup>();
    robot->InsertShape(leftHand);
    robot->InsertShape(rightHand);
    robot->InsertShape(body);
    robot->InsertShape(head);
    robot->InsertShape(lEye);
    robot->InsertShape(rEye);
    robot->InsertShape(nose);
    robot->InsertShape(mouth);
    robot->InsertShape(leftLeg);
    robot->InsertShape(rightLeg);

    return robot;
}
}

int main()
{
	try
	{
		ofstream ifs("picture.svg");
		Slide slide;

		Canvas canvas(ifs);
		canvas.BeginDraw();

        auto robot = BuildRobot();
        slide.InsertShape(robot);

		slide.Draw(canvas);

        auto frame = Rect{ 50, 50, 400, 400 };
        robot->SetFrame(frame);
		slide.Draw(canvas);

        frame = Rect{ 800, 50, 400, 400 };
        robot->SetFrame(frame);
        slide.Draw(canvas);

        for(int i = 0; i < 300; i++)
        {
            frame = Rect{ float(rand() % 5000 + 1000), float(rand() % 2000),  float(rand() % 400 + 100), float(rand() % 400 + 100) };
            robot->SetFrame(frame);
            slide.Draw(canvas);
            i++;
        }

		canvas.EndDraw();
		ifs.close();
	}
	catch (exception & e)
	{
        std::cout << "Error: " << e.what() << endl;
	}
	return 0;
}

