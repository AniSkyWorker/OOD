#include "stdafx.h"
#include "MainDlgPresenter.h"
#include "IHarmonicCollection.h"
#include "IMainDlgView.h"
#include "HarmonicPreviewGenerator.h"
#include "IChartView.h"

using namespace std;
namespace pl = std::placeholders;

CMainDlgPresenter::CMainDlgPresenter(IHarmonicCollection & harmonics, IMainDlgView & view, AddHarmonicDlg& addHarmonic)
	: m_harmonics(harmonics)
	, m_view(view)
	, m_addHarmonic(addHarmonic)
{
	m_connectionsStorage += m_view.DoOnAddHarmonic(std::bind(&CMainDlgPresenter::OpenAddDialog, this));
	m_connectionsStorage += m_view.DoOnDeleteHarmonic(std::bind(&CMainDlgPresenter::DeleteHarmonic, this, pl::_1));
	m_connectionsStorage += m_view.DoOnInit([&] { Update();});
	m_connectionsStorage += m_view.DoOnChangeTab([&] { UpdateChart(); });
	m_connectionsStorage += m_addHarmonic.DoOnAddHarmonic(std::bind(&CMainDlgPresenter::AddHarmonic, this, pl::_1, pl::_2, pl::_3, pl::_4));
	m_connectionsStorage += m_harmonics.DoOnChangeHarmonics(std::bind(&CMainDlgPresenter::Update, this));
}

void CMainDlgPresenter::ChangeFrequency(int index, float frequency)
{
	auto harmonic = m_harmonics.GetHarmonic(index);
	harmonic->SetFrequency(frequency);
}

void CMainDlgPresenter::ChangePhase(int index, float phase)
{
	auto harmonic = m_harmonics.GetHarmonic(index);
	harmonic->SetPhase(phase);
}

void CMainDlgPresenter::ChangeAmplitude(int index, float amplitude)
{
	auto harmonic = m_harmonics.GetHarmonic(index);
	harmonic->SetAmplitude(amplitude);
}

void CMainDlgPresenter::ChangeFunctionType(int index, FunctionType functionType)
{
	auto harmonic = m_harmonics.GetHarmonic(index);
	harmonic->SetFunctionType(functionType);
}

void CMainDlgPresenter::OpenAddDialog()
{
	 m_addHarmonic.DoModal();
}

void CMainDlgPresenter::AddHarmonic(FunctionType type, float aplitude, float frequency, float phase)
{
	m_harmonics.AddHarmonic(aplitude, type, frequency, phase);
	auto pHarmonic = m_harmonics.GetHarmonic(m_harmonics.GetSize() - 1);
	pHarmonic->DoOnChangeHarmonic(std::bind(&CMainDlgPresenter::Update, this));
}

void CMainDlgPresenter::DeleteHarmonic(int index)
{
	m_harmonics.DeleteHarmonic(index);
	Update();
}

void CMainDlgPresenter::Update()
{
	UpdateListView();
	UpdateChart();
}

void CMainDlgPresenter::UpdateChart()
{
	std::vector<Point> points;
	for (float x = 0; x <= 8; x += 0.1f)
	{
		points.emplace_back(x, m_harmonics.CalculateValueAt(x));
	}
	m_view.GetChartView().SetPointsInfo(points);
}

void CMainDlgPresenter::UpdateListView()
{
	std::vector<std::wstring> harmonicsStr;
	for (size_t i = 0; i < m_harmonics.GetSize(); ++i)
	{
		auto pHarmonic = m_harmonics.GetHarmonic(i);
		auto harmonicString = harmonic_preview::CreateHarmonicString(pHarmonic->GetAmplitude(), 
			pHarmonic->GetFucntionType(), 
			pHarmonic->GetFrequency(), 
			pHarmonic->GetPhase());
		harmonicsStr.push_back(harmonicString);
	}
	m_view.SetListItems(harmonicsStr);
}
