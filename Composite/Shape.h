#pragma once
#include "IShape.h"
#include "Style.h"
#include "LineStyle.h"
#include "Rect.h"

class ICanvas;

class Shape : public IShape
{
public:
	Shape();

	void SetOutlineStyle(const std::shared_ptr<ILineStyle> & style) final;
	std::shared_ptr<ILineStyle> GetOutlineStyle()const final;

	void SetFillStyle(const std::shared_ptr<IStyle> & style) final;
	std::shared_ptr<IStyle> GetFillStyle()const final;

	std::shared_ptr<IShapeGroup> GetGroup() final;

    void Draw(ICanvas& canvas) const final;

protected:
    virtual void DrawBehavior(ICanvas & canvas) const = 0;
    Rect m_frame;

private:
	std::shared_ptr<ILineStyle> m_outlineStyle;
	std::shared_ptr<IStyle> m_fillStyle;
};

