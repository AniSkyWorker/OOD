#pragma once
#include "IShapeGroup.h"
#include "LineStyle.h"
#include "Style.h"
#include "ShapeCollection.h"

struct Rect;

class ShapeGroup 
    : public IShapeGroup
    , public std::enable_shared_from_this<IShapeGroup>
{
public:
	Rect GetFrame()const final;
	void SetFrame(const Rect & rect) final;

	void SetOutlineStyle(const std::shared_ptr<ILineStyle> & style) final;
	std::shared_ptr<ILineStyle> GetOutlineStyle() const final;

    void SetFillStyle(const std::shared_ptr<IStyle> & style) final;
	std::shared_ptr<IStyle> GetFillStyle()const final;

    std::shared_ptr<IShapeGroup> GetGroup() final;

    size_t GetShapesCount()const final;
    void InsertShape(const std::shared_ptr<IShape> & shape) final;
    std::shared_ptr<IShape> GetShapeAtIndex(size_t index) final;
    void RemoveShapeAtIndex(size_t index)final;

	void Draw(ICanvas & canvas) const final;

private:
	ShapeCollection m_shapeCollection;
};

