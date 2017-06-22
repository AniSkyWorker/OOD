#include "stdafx.h"
#include "HarmonicCollection.h"
#include "Harmonic.h"

float HarmonicCollection::CalculateValueAt(float x) const
{
	float result = 0;
	std::for_each(m_harmonics.cbegin(), m_harmonics.cend(), [&](auto & harmonic) {
		result += harmonic->CalculateValueAt(x);
	});
	return result;
}

IHarmonicPtr HarmonicCollection::GetHarmonic(size_t index) const
{
	if (index >= m_harmonics.size())
	{
		throw std::logic_error("Index more than harmonic count");
	}

	return m_harmonics[index];
}

void HarmonicCollection::AddHarmonic(float amplitude, FunctionType type, float frequency, float phase)
{
	auto pHarmonic = std::make_shared<Harmonic>(amplitude, type, frequency, phase);
	m_harmonics.push_back(pHarmonic);
	m_harmonicsChangeSignal();
}

void HarmonicCollection::DeleteHarmonic(size_t index)
{
	if (index >= m_harmonics.size())
	{
		throw std::out_of_range("Out of range");
	}

	m_harmonics.erase(m_harmonics.begin() + index);
	m_harmonicsChangeSignal();
}

size_t HarmonicCollection::GetSize() const
{
	return m_harmonics.size();
}

sig::connection HarmonicCollection::DoOnChangeHarmonics(const VoidSlot & handler)
{
	std::for_each(m_harmonics.begin(), m_harmonics.end(), [&](auto & harmonic) {
		harmonic->DoOnChangeHarmonic(handler);
	});

	return m_harmonicsChangeSignal.connect(handler);
}
