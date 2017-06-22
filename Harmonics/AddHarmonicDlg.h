#pragma once
#include "resource.h"
#include "signals.h"

class AddHarmonicDlg : public CDialogEx
{
public:
    DECLARE_DYNAMIC(AddHarmonicDlg)
    enum { IDD = IDD_ADD_HARMONIC_DIALOG };

    AddHarmonicDlg(CWnd* pParent = nullptr);

    sig::connection DoOnAddHarmonic(const AddHarmonicSlot& handler);
    sig::connection DoOnDataChanged(const VoidSlot& handler);

	BOOL OnInitDialog() final;
    void OnOK() final;

protected:
	void DoDataExchange(CDataExchange* pDX) final;
	DECLARE_MESSAGE_MAP()

private:
    void UpdatePreview();

    afx_msg void OnFuncComboUpdated();
    afx_msg void OnAmplitudeEditUpdated();
    afx_msg void OnFrequencyEditUpdated();
    afx_msg void OnPhaseEditUpdated();

	CEdit m_amplitudeEdit;
	CEdit m_frequencyEdit;
	CEdit m_phaseEdit;
    CComboBox m_funcTypeCombo;
	CStatic m_harmonicPreview;

    FunctionType m_functionType;
    AddHarmonicSignal m_addHarmonicSignal;
    VoidSignal m_onDataChanged;
};
