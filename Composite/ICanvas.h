#pragma once
class RGBAColor;

class ICanvas
{
public:
	virtual void MoveTo(float x, float y) = 0;
	virtual void LineTo(float x, float y) = 0;
	virtual void DrawEllipse(float x, float y, float hRadius, float vRadius) = 0;
	virtual void SetLineWidth(int width) = 0;
	virtual void SetLineColor(RGBAColor color) = 0;
	virtual void BeginFill(RGBAColor color) = 0;
	virtual void EndFill() = 0;

	virtual ~ICanvas() = default;
};