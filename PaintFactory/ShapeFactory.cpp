#include "stdafx.h"
#include "ShapeFactory.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "RegularPolygon.h"
#include "Ellipse.h"

namespace
{

bool IsUnknownSymbol(const char & symbol)
{
	return (!isalpha(symbol) && !isspace(symbol) && !isalnum(symbol));
}

std::string GetExampleByType(ShapeType type)
{
    switch(type)
    {
    case ShapeType::Rectangle:
        return "rectangle x1 y1 x2 y2 color";
    case ShapeType::Triangle:
        return "triangle x1 y1 x2 y2 x3 y3 color";
    case ShapeType::Ellipse:
        return "ellipse x1 y1 r1 r2 color";
    case ShapeType::Polygon:
        return "polygon x1 y1 r1 pointCount color";
    default:
        return "";
    }
}

ShapeType GetShapeTypeByStr(const std::string & type)
{
    if (type == "rectangle")
    {
        return ShapeType::Rectangle;
    }
    else if (type == "triangle")
    {
        return ShapeType::Triangle;
    }
    else if (type == "ellipse")
    {
        return ShapeType::Ellipse;
    }
    else if (type == "polygon")
    {
        return ShapeType::Polygon;
    }
    throw std::runtime_error("Cant find shape by " + type + " type");
}

}

CShapeFactory::CShapeFactory()
	: m_actionMap ({
		{ ShapeType::Polygon, bind(&CShapeFactory::AddPolygon, this, std::placeholders::_1) },
		{ ShapeType::Ellipse, bind(&CShapeFactory::AddEllipse, this, std::placeholders::_1) },
		{ ShapeType::Rectangle, bind(&CShapeFactory::AddRectangle, this, std::placeholders::_1) },
		{ ShapeType::Triangle, bind(&CShapeFactory::AddTriangle, this, std::placeholders::_1) }
    })
{
}

std::unique_ptr<IShape> CShapeFactory::CreateShape(const std::string & args) const
{
	std::stringstream strm(args);
    strm.exceptions(std::ios::failbit);

    std::string typeStr;
    strm >> typeStr;

    auto type = GetShapeTypeByStr(typeStr);

	auto it = m_actionMap.find(type);
	if (it != m_actionMap.end())
	{
        try
        {
            return it->second(strm);
        }
        catch (const std::ios::failure&)
        {
            throw std::runtime_error("Cant create shape from " + strm.str() + ". \nExample: " + GetExampleByType(type));
        }
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
