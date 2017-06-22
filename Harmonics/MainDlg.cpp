#include "stdafx.h"
#include "MainDlg.h"
#include "WindowUtils.h"

BEGIN_MESSAGE_MAP(MainDlg, CDialogEx)
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BUTTON2, &MainDlg::OnButtonAdd)
    ON_BN_CLICKED(IDC_BUTTON_DELETE, &MainDlg::OnButtonDelete)
    ON_LBN_SELCHANGE(IDC_HARMONICS_LIST, &MainDlg::OnLbnSelchangeHarmonicsList)
    ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_VIEW, &MainDlg::OnTcnSelchangeTabView)
END_MESSAGE_MAP()

MainDlg::MainDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HARMONICS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void MainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HARMONICS_LIST, m_harmonicsList);
	DDX_Control(pDX, IDC_TAB_VIEW, m_tabs);
}

void MainDlg::SetListItems(std::vector<std::wstring> const& list)
{
	m_harmonicsList.ResetContent();
	for (const auto & string : list)
	{
		m_harmonicsList.AddString(string.c_str());
	}
}

IChartView & MainDlg::GetChartView()
{
	int currentTab = m_tabs.GetCurSel();
    switch (currentTab)
    {
    case 0:
        return *m_chartDlg;
    case 1:
        return *m_tableDlg;
    }
    throw std::runtime_error("Incorrect selection");
}

sig::connection MainDlg::DoOnInit(const VoidSlot & handler)
{
	return m_initSignal.connect(handler);
}

sig::connection MainDlg::DoOnDeleteHarmonic(const DeleteHarmonicSignal::slot_type & handler)
{
	return m_deleteHarmonicSignal.connect(handler);
}

sig::connection MainDlg::DoOnAddHarmonic(const VoidSlot& handler)
{
	return m_addHarmonicSignal.connect(handler);
}

sig::connection MainDlg::DoOnChangeTab(const VoidSlot & handler)
{
	return m_changeTabSignal.connect(handler);
}

BOOL MainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	m_tabs.InsertItem(0, L"Chart");
	m_tabs.InsertItem(1, L"Table");

	m_chartDlg = std::make_shared<ChartDlg>(&m_tabs);
	m_chartDlg->Create(IDD_CHART_VIEW_DIALOG, &m_tabs);
	m_chartDlg->SubclassDlgItem(IDD_CHART_VIEW_DIALOG, this);

	m_tableDlg = std::make_shared<TableDlg>(&m_tabs);
	m_tableDlg->Create(IDD_TABLE_VIEW_DIALOG, &m_tabs);

	CRect rc;
	m_tabs.GetClientRect(rc);
	rc.top += 20;
	rc.bottom -= 10;
	rc.left += 10;
	rc.right -= 10;
	m_chartDlg->MoveWindow(&rc);
	m_tableDlg->MoveWindow(&rc);

	m_chartDlg->ShowWindow(TRUE);
	m_tableDlg->ShowWindow(FALSE);

	m_tabs.SetCurSel(0);

	m_initSignal();

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void MainDlg::OnButtonAdd()
{
	m_addHarmonicSignal();
}

void MainDlg::OnButtonDelete()
{
	int index = m_harmonicsList.GetCurSel();
	if (index >= 0)
	{
		m_deleteHarmonicSignal(index);
	}
}

void MainDlg::OnLbnSelchangeHarmonicsList()
{
	auto index = m_harmonicsList.GetCurSel();
	m_changeSelection(index);
}

void MainDlg::OnTcnSelchangeTabView(NMHDR *pNMHDR, LRESULT *pResult)
{
    int currentTab = m_tabs.GetCurSel();
    switch (currentTab)
    {
    case 0:
        m_chartDlg->ShowWindow(TRUE);
        m_tableDlg->ShowWindow(FALSE);
        break;
    case 1:
        m_chartDlg->ShowWindow(FALSE);
        m_tableDlg->ShowWindow(TRUE);
        break;
    }

	m_changeTabSignal();
	*pResult = 0;
}
