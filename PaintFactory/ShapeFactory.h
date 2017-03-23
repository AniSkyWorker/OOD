#pragma once
#include "Triangle.h"
#include "Rectangle.h"
#include "RegularPolygon.h"
#include "Ellipse.h"
#include "IShapeFactory.h"

class CShapeFactory : public IShapeFactory
{
public:
	CShapeFactory();
	std::unique_ptr<IShape> CreateShape(std::istream & args) const override;
private:
	std::unique_ptr<IShape> AddPolygon(std::istream & strm);
	std::unique_ptr<IShape> AddEllipse(std::istream & strm);
	std::unique_ptr<IShape> AddRectangle(std::istream & strm);
	std::unique_ptr<IShape> AddTriangle(std::istream & strm);

private:
	const std::map<std::string, std::function<std::unique_ptr<IShape>(std::istream & args)>> m_actionMap;
};
