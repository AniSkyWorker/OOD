#pragma once
#include "Point.h"

class IChartView
{
public:
	virtual void SetPointsInfo(const  std::vector<Point>& data) = 0;
	virtual ~IChartView() = default;
};

