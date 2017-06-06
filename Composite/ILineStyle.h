#pragma once
#include "IStyle.h"

class ILineStyle : public IStyle
{
public:
	virtual int GetLineWidth()const = 0;
	virtual void SetLineWidth(int width) = 0;
};