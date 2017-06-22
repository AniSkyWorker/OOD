#pragma once
#include "Signals.h"
#include "FunctionType.h"

class IChartView;
class ITableView;

class IMainDlgView
{
public:
	typedef sig::signal<void(int, float)> ChangeHarmonicSignal;
	typedef sig::signal<void(int)> DeleteHarmonicSignal;
	typedef sig::signal<void(int)> ChangeSelectionSignal;

	virtual IChartView & GetChartView() = 0;
	virtual void SetListItems(std::vector<std::wstring> const& list) = 0;

	virtual sig::connection DoOnInit(const VoidSlot & handler) = 0;
	virtual sig::connection DoOnDeleteHarmonic(const DeleteHarmonicSignal::slot_type & handler) = 0;
	virtual sig::connection DoOnAddHarmonic(const VoidSlot& handler) = 0;
	virtual sig::connection DoOnChangeTab(const VoidSlot & handler) = 0;
	
	virtual ~IMainDlgView() = default;
};