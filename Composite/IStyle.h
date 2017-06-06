#pragma once
#include "RGBAColor.h"

class IStyle
{
public:
	virtual bool IsEnabled()const = 0;
	virtual void Enable(bool enable) = 0;

	virtual RGBAColor GetColor()const = 0;
	virtual void SetColor(const RGBAColor & color) = 0;

	virtual ~IStyle() = default;
};