#include "stdafx.h"
#include "Harmonic.h"

Harmonic::Harmonic(float amplitude, FunctionType function, float frequency, float phase)
	: m_amplitude (amplitude)
	, m_frequency(frequency)
	, m_functionType(function)
	, m_phase(phase)
{
}

FunctionType Harmonic::GetFucntionType() const
{
	return m_functionType;
}

void Harmonic::SetFunctionType(FunctionType type)
{
	m_functionType = type;
	m_harmonicChangeSignal();
}

float Harmonic::GetAmplitude() const
{
	return m_amplitude;
}

void Harmonic::SetAmplitude(float amplitude)
{
	m_amplitude = amplitude;
	m_harmonicChangeSignal();
}

float Harmonic::GetFrequency() const
{
	return m_frequency;
}

void Harmonic::SetFrequency(float frequency)
{
	m_frequency = frequency;
	m_harmonicChangeSignal();
}

float Harmonic::GetPhase() const
{
	return m_phase;
}

void Harmonic::SetPhase(float phase)
{
	m_phase = phase;
	m_harmonicChangeSignal();
}

float Harmonic::CalculateValueAt(float x) const
{
	std::map<FunctionType, std::function<float(float)>> functions = {
		{ FunctionType::Sin, &std::sinf },
		{ FunctionType::Cos, &std::cosf },
	};

	return m_amplitude * functions.at(m_functionType)(m_frequency * x + m_phase);
}

sig::connection Harmonic::DoOnChangeHarmonic(const VoidSlot& handler)
{
	return m_harmonicChangeSignal.connect(handler);
}
