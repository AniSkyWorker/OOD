#pragma once
#include "FunctionType.h"
#include "AddHarmonicDlg.h"
#include "ScopedConnectionsStorage.h"

class IHarmonicCollection;
class IMainDlgView;

class CMainDlgPresenter
{
public:
	CMainDlgPresenter(IHarmonicCollection& harmonics, IMainDlgView& view, AddHarmonicDlg& addHarmonic);

private:
	void ChangeFrequency(int index, float frequency);
	void ChangePhase(int index, float phase);
	void ChangeAmplitude(int index, float amplitude);
	void ChangeFunctionType(int index, FunctionType functionType);
	void OpenAddDialog();
	void AddHarmonic(FunctionType type, float aplitude, float frequency, float phase);
	void DeleteHarmonic(int index);
	void Update();

	void UpdateChart();
	void UpdateListView();

	ScopedConnectionsStorage m_connectionsStorage;
    AddHarmonicDlg& m_addHarmonic;
	IHarmonicCollection& m_harmonics;
	IMainDlgView& m_view;
};

