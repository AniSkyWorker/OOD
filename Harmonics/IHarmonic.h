#pragma once
#include "FunctionType.h"
#include "Signals.h"

class IHarmonic
{
public:
	virtual ~IHarmonic() = default;
	
	virtual FunctionType GetFucntionType() const = 0;
	virtual void SetFunctionType(FunctionType type) = 0;

	virtual float GetAmplitude() const = 0;
	virtual void SetAmplitude(float amplitude) = 0;
	
	virtual float GetFrequency() const = 0;
	virtual void SetFrequency(float frequency) = 0;

	virtual float GetPhase() const = 0;
	virtual void SetPhase(float phase) = 0;

	virtual sig::connection DoOnChangeHarmonic(const VoidSlot& handler) = 0;

	virtual float CalculateValueAt(float x) const = 0;
};


