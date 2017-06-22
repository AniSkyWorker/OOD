#pragma once
#include <afxcmn.h>
#include <afxwin.h>
#include "IMainDlgView.h"
#include "ChartDlg.h"
#include "TableDlg.h"

class MainDlg
    : public CDialogEx
    , public IMainDlgView
{
public:
	MainDlg(CWnd* pParent = nullptr);

	enum { IDD = IDD_HARMONICS_DIALOG };

    void DoDataExchange(CDataExchange* pDX) final;
	void SetListItems(std::vector<std::wstring>const& list) final;

	IChartView & GetChartView() final;

	sig::connection DoOnInit(const VoidSlot & handler) final;
	sig::connection DoOnDeleteHarmonic(const DeleteHarmonicSignal::slot_type& handler) final;
	sig::connection DoOnAddHarmonic(const VoidSlot& handler) final;
	sig::connection DoOnChangeTab(const VoidSlot& handler) final;

protected:
    DECLARE_MESSAGE_MAP()

private:
    BOOL OnInitDialog() final;

    afx_msg void OnButtonAdd();
    afx_msg void OnButtonDelete();
    afx_msg void OnLbnSelchangeHarmonicsList();
    afx_msg void OnTcnSelchangeTabView(NMHDR *pNMHDR, LRESULT *pResult);

	VoidSignal m_initSignal;
	VoidSignal m_addHarmonicSignal;
	DeleteHarmonicSignal m_deleteHarmonicSignal;
	ChangeSelectionSignal m_changeSelection;
	VoidSignal m_changeTabSignal;

    HICON m_hIcon;

	std::shared_ptr<ChartDlg> m_chartDlg;
	std::shared_ptr<TableDlg> m_tableDlg;
	CTabCtrl m_tabs;
	CListBox m_harmonicsList;
};
