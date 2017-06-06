#include "stdafx.h"
#include "GroupShape.h"
#include "Rect.h"

using namespace std;

namespace
{
template<typename StylePtr>
StylePtr CalculateStyle(const ShapeCollection& collection)
{
	if (collection.GetShapesCount() == 0)
	{
		throw runtime_error("Coollection empty!");
	}

    auto& shapes = collection.GetShapes();
    StylePtr firstStyle = shapes.front()->GetOutlineStyle();
    const bool isSameStyle = std::any_of(shapes.begin() + 1, shapes.end()
        , [&firstStyle](auto const& shape) { return shape->GetOutlineStyle() == firstStyle; });

    return isSameStyle ? firstStyle : nullptr;
}

constexpr Rect INF_RECT = { 
    numeric_limits<float>::infinity()
    , numeric_limits<float>::infinity()
    , -numeric_limits<float>::infinity()
    , -numeric_limits<float>::infinity()
};

}

std::shared_ptr<IShapeGroup> ShapeGroup::GetGroup()
{
	return shared_from_this();
}

size_t ShapeGroup::GetShapesCount() const
{
    return m_shapeCollection.GetShapesCount();
}

void ShapeGroup::InsertShape(const std::shared_ptr<IShape>& shape)
{
    m_shapeCollection.InsertShape(shape);
}

std::shared_ptr<IShape> ShapeGroup::GetShapeAtIndex(size_t index)
{
    return m_shapeCollection.GetShapeAtIndex(index);
}

void ShapeGroup::RemoveShapeAtIndex(size_t index)
{
    m_shapeCollection.RemoveShapeAtIndex(index);
}

void ShapeGroup::Draw(ICanvas & canvas) const
{
	for (auto& shape : m_shapeCollection.GetShapes())
	{
		shape->Draw(canvas);
	}
}

Rect ShapeGroup::GetFrame() const
{
	if (GetShapesCount() == 0)
	{
        return Rect();
	}

    auto maxFrame = INF_RECT;
	for (auto const& shape : m_shapeCollection.GetShapes())
	{
		auto const& frame = shape->GetFrame();
        maxFrame.left = min(maxFrame.left, frame.left);
        maxFrame.top = min(maxFrame.top, frame.top);
        maxFrame.width = max(maxFrame.width, frame.left + frame.width);
        maxFrame.height = max(maxFrame.height, frame.top + frame.height);
	}

    maxFrame.width -= maxFrame.left;
    maxFrame.height -=  maxFrame.top;

	return maxFrame;
}

void ShapeGroup::SetFrame(const Rect& rect)
{
	auto oldFrame = GetFrame();

	for (auto & shape : m_shapeCollection.GetShapes())
	{
		auto shapeFrame = shape->GetFrame();
        shape->SetFrame({ rect.left + (shapeFrame.left - oldFrame.left) / oldFrame.width * rect.width
            , rect.top + (shapeFrame.top - oldFrame.top) / oldFrame.height * rect.height
            , shapeFrame.width * rect.width / oldFrame.width
            , shapeFrame.height * rect.height / oldFrame.height });
	}
}

void ShapeGroup::SetOutlineStyle(const std::shared_ptr<ILineStyle> & style)
{
	for (auto & shape : m_shapeCollection.GetShapes())
	{
		shape->SetOutlineStyle(style);
	}
}

std::shared_ptr<ILineStyle> ShapeGroup::GetOutlineStyle() const
{
    return CalculateStyle<std::shared_ptr<ILineStyle>>(m_shapeCollection);
}

void ShapeGroup::SetFillStyle(const std::shared_ptr<IStyle> & style)
{
    for (auto & shape : m_shapeCollection.GetShapes())
    {
        shape->SetFillStyle(style);
    }
}

std::shared_ptr<IStyle> ShapeGroup::GetFillStyle() const
{
	return CalculateStyle<std::shared_ptr<IStyle>>(m_shapeCollection);
}
