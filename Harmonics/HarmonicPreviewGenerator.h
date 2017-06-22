#pragma once
#include "FunctionType.h"

namespace harmonic_preview
{
	std::wstring CreateHarmonicString(float amplitude, FunctionType function, float frequency, float phase);
};