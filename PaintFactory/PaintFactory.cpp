// PaintFactory.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Client.h"
#include <memory>
#include "StreamHandler.h"

int main()
{
	auto designer = CDesigner(std::move(std::make_unique<CShapeFactory>()));
	auto painter = CPainter();
	CClient client(designer, painter);
	client.CreatePicture();

    return 0;
}

