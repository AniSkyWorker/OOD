#pragma once
#include "IShapeFactory.h"
#include "ShapeType.h"

class CShapeFactory : public IShapeFactory
{
using ShapeCreationActionMap = std::map<ShapeType, std::function<std::unique_ptr<IShape>(std::istream & args)>>;

public:
	CShapeFactory();
	std::unique_ptr<IShape> CreateShape(const std::string & args) const override;

private:
	std::unique_ptr<IShape> AddPolygon(std::istream & strm);
	std::unique_ptr<IShape> AddEllipse(std::istream & strm);
	std::unique_ptr<IShape> AddRectangle(std::istream & strm);
	std::unique_ptr<IShape> AddTriangle(std::istream & strm);

	const ShapeCreationActionMap m_actionMap;
};
