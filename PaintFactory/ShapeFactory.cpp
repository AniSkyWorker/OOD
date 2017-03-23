#include "stdafx.h"
#include "ShapeFactory.h"

namespace
{

bool IsUnknownSymbol(const char & symbol)
{
	return (!isalpha(symbol) && !isspace(symbol) && !isalnum(symbol));
}

}

CShapeFactory::CShapeFactory()
	: m_actionMap ({
		{ "polygon", bind(&CShapeFactory::AddPolygon, this, std::placeholders::_1) },
		{ "ellipse", bind(&CShapeFactory::AddEllipse, this, std::placeholders::_1) },
		{ "rectangle", bind(&CShapeFactory::AddRectangle, this, std::placeholders::_1) },
		{ "triangle", bind(&CShapeFactory::AddTriangle, this, std::placeholders::_1) }
})
{
}

std::unique_ptr<IShape> CShapeFactory::CreateShape(std::istream & args) const
{
	std::string action;
    args >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(args);
	}

    if (!action.empty())
    {
        std::cout << "Cant find shape by " + action + " type" << "\n";
    }

	return nullptr;
}

std::unique_ptr<IShape> CShapeFactory::AddPolygon(std::istream & strm)
{
	SPoint center;
	strm >> center.x;
	strm >> center.y;

	float radius;
	strm >> radius;

	unsigned count;
	strm >> count;

    std::unique_ptr<IShape> polygon = std::make_unique<CRegularPolygon>(center, radius, count);
	polygon->SetColor(color::GetColor(strm));

	return polygon;
}

std::unique_ptr<IShape> CShapeFactory::AddRectangle(std::istream & strm)
{
	SPoint leftTopPoint;
	strm >> leftTopPoint.x;
	strm >> leftTopPoint.y;

	SPoint dimensions;
	strm >> dimensions.x;
	strm >> dimensions.y;

    std::unique_ptr<IShape> rect = std::make_unique<CRectangle>(leftTopPoint, dimensions.x, dimensions.y);
	rect->SetColor(color::GetColor(strm));

	return rect;
}

std::unique_ptr<IShape> CShapeFactory::AddEllipse(std::istream & strm)
{
	SPoint center;
	strm >> center.x;
	strm >> center.y;

	float radius;
	strm >> radius;

    float sRadius;
	strm >> sRadius;

    std::unique_ptr<IShape> ellipse = std::make_unique<CEllipse>(center, radius, sRadius);
	ellipse->SetColor(color::GetColor(strm));

	return ellipse;
}

std::unique_ptr<IShape> CShapeFactory::AddTriangle(std::istream & strm)
{
	SPoint topVertexPos;
	strm >> topVertexPos.x;
	strm >> topVertexPos.y;

	SPoint leftVertexPos;
	strm >> leftVertexPos.x;
	strm >> leftVertexPos.y;

	SPoint rightVertexPos;
	strm >> rightVertexPos.x;
	strm >> rightVertexPos.y;

    std::unique_ptr<IShape> tringle = std::make_unique<CTriangle>(topVertexPos, leftVertexPos, rightVertexPos);
	tringle->SetColor(color::GetColor(strm));

	return tringle;
}
