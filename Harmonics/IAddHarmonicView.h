#pragma once
#include "Signals.h"
#include "FunctionType.h"

class IAddHarmonicView
{
public:
	typedef sig::signal<void(float, FunctionType, float, float)> AddHarmonicSignal;

	virtual ~IAddHarmonicView() = default;
	virtual sig::connection DoOnAddHarmonic(AddHarmonicSignal::slot_type const& handler) = 0;
};
