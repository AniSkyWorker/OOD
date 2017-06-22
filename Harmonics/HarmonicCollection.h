#pragma once
#include "IHarmonicCollection.h"

class HarmonicCollection : public IHarmonicCollection
{
public:
	float CalculateValueAt(float x) const final;

	IHarmonicPtr GetHarmonic(size_t index) const final;

	void AddHarmonic(float amplitude, FunctionType type, float frequency, float phase) final;
	void DeleteHarmonic(size_t index) final;

	size_t GetSize() const final;
	sig::connection DoOnChangeHarmonics(const VoidSlot & handler) final;

private:
	std::vector<IHarmonicPtr> m_harmonics;
	VoidSignal m_harmonicsChangeSignal;
};

