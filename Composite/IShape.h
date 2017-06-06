#pragma once
#include "IDrawable.h"

class IStyle;
class ILineStyle;
class IShapeGroup;
struct Rect;

class IShape : public IDrawable
{
public:
	virtual Rect GetFrame()const = 0;
	virtual void SetFrame(const Rect & rect) = 0;

	virtual void SetOutlineStyle(const std::shared_ptr<ILineStyle> & style) = 0;
	virtual std::shared_ptr<ILineStyle> GetOutlineStyle()const = 0;

	virtual void SetFillStyle(const std::shared_ptr<IStyle> & style) = 0;
	virtual std::shared_ptr<IStyle> GetFillStyle()const = 0;

	virtual std::shared_ptr<IShapeGroup> GetGroup() = 0;

	virtual ~IShape() = default;
};