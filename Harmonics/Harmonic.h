#pragma once
#include "IHarmonic.h"

class Harmonic : public IHarmonic
{
public:
	Harmonic(float amplitude, FunctionType function, float frequency, float phase);

	FunctionType GetFucntionType() const final;
	void SetFunctionType(FunctionType type) final;

	float GetAmplitude() const final;
	void SetAmplitude(float amplitude) final;

	float GetFrequency() const final;
	void SetFrequency(float frequency) final;

	float GetPhase() const final;
	void SetPhase(float phase) final;

	float CalculateValueAt(float x) const final;
	sig::connection DoOnChangeHarmonic(const VoidSlot& handler) final;

private:
	float m_amplitude;
	float m_frequency;
	float m_phase;
    FunctionType m_functionType;

	VoidSignal m_harmonicChangeSignal;
};

