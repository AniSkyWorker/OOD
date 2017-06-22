#include "stdafx.h"
#include "AddHarmonicDlg.h"
#include "afxdialogex.h"
#include "HarmonicPreviewGenerator.h"
#include "WindowUtils.h"

using namespace window_utils;

namespace
{
const std::map<std::wstring, FunctionType> COMBO_TEXT_MAP =
{
    { L"sin", FunctionType::Sin },
    { L"cos", FunctionType::Cos }
};
}

IMPLEMENT_DYNAMIC(AddHarmonicDlg, CDialogEx)

BEGIN_MESSAGE_MAP(AddHarmonicDlg, CDialogEx)
    ON_CBN_SELCHANGE(IDC_FUNC_COMBO, &AddHarmonicDlg::OnFuncComboUpdated)
    ON_EN_UPDATE(IDC_EDIT_AMPLITUDE, &AddHarmonicDlg::OnAmplitudeEditUpdated)
    ON_EN_UPDATE(IDC_EDIT_FREQUENCY, &AddHarmonicDlg::OnFrequencyEditUpdated)
    ON_EN_UPDATE(IDC_EDIT_PHASE, &AddHarmonicDlg::OnPhaseEditUpdated)
END_MESSAGE_MAP()

AddHarmonicDlg::AddHarmonicDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADD_HARMONIC_DIALOG, pParent)
	, m_functionType(FunctionType::Sin)
{
}

sig::connection AddHarmonicDlg::DoOnAddHarmonic(const AddHarmonicSlot& handler)
{
	return m_addHarmonicSignal.connect(handler);
}

sig::connection AddHarmonicDlg::DoOnDataChanged(const VoidSlot & handler)
{
    return m_onDataChanged.connect(handler);
}

void AddHarmonicDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_AMPLITUDE, m_amplitudeEdit);
	DDX_Control(pDX, IDC_EDIT_FREQUENCY, m_frequencyEdit);
	DDX_Control(pDX, IDC_EDIT_PHASE, m_phaseEdit);
    DDX_Control(pDX, IDC_FUNC_COMBO, m_funcTypeCombo);
	DDX_Control(pDX, IDC_STATIC_PREVIEW_HARMONIC, m_harmonicPreview);
}

void AddHarmonicDlg::UpdatePreview()
{
    const auto amplitude = GetEditValue(m_amplitudeEdit);
    const auto phase = GetEditValue(m_phaseEdit);
    const auto frequency = GetEditValue(m_frequencyEdit);

	auto previewString = harmonic_preview::CreateHarmonicString(amplitude, m_functionType, frequency, phase);
	m_harmonicPreview.SetWindowTextW(previewString.c_str());
}

BOOL AddHarmonicDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_phaseEdit.SetWindowTextW(L"0");
	m_amplitudeEdit.SetWindowTextW(L"1");
	m_frequencyEdit.SetWindowTextW(L"1");

    m_funcTypeCombo.AddString(L"sin");
    m_funcTypeCombo.AddString(L"cos");

	CheckRadioButton(IDC_SIN_RADIO, IDC_COS_RADIO, IDC_SIN_RADIO);

    auto onDataChanged = [this]() {
        UpdatePreview();
    };

    DoOnDataChanged(onDataChanged);

	UpdatePreview();
	return TRUE;
}

void AddHarmonicDlg::OnFuncComboUpdated()
{
    m_functionType = COMBO_TEXT_MAP.at(GetControlText(m_funcTypeCombo));
    m_onDataChanged();
}

void AddHarmonicDlg::OnAmplitudeEditUpdated()
{
    m_onDataChanged();
}

void AddHarmonicDlg::OnFrequencyEditUpdated()
{
    m_onDataChanged();
}

void AddHarmonicDlg::OnPhaseEditUpdated()
{
    m_onDataChanged();
}

void AddHarmonicDlg::OnOK()
{
	const auto amplitude = GetEditValue(m_amplitudeEdit);
	const auto phase = GetEditValue(m_phaseEdit);
    const auto frequency = GetEditValue(m_frequencyEdit);

	m_addHarmonicSignal(m_functionType, amplitude, frequency, phase);
	CDialogEx::OnOK();
}
