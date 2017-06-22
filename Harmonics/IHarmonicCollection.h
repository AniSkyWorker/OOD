#pragma once
#include "IHarmonic.h"

using IHarmonicPtr = std::shared_ptr<IHarmonic>;

class IHarmonicCollection
{
public:
	virtual ~IHarmonicCollection() = default;
	
	virtual float CalculateValueAt(float x) const = 0;
	virtual IHarmonicPtr GetHarmonic(size_t index) const = 0;
	virtual void AddHarmonic(float aplitude, FunctionType type, float frequency, float phase) = 0;
	virtual void DeleteHarmonic(size_t index) = 0;

	virtual size_t GetSize() const = 0;

	virtual sig::connection DoOnChangeHarmonics(const VoidSlot& handler) = 0;
};