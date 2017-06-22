// TableViewDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TableDlg.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(TableDlg, CDialogEx)

BEGIN_MESSAGE_MAP(TableDlg, CDialogEx)
END_MESSAGE_MAP()

TableDlg::TableDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TABLE_VIEW_DIALOG, pParent)
{
}

void TableDlg::SetPointsInfo(const std::vector<Point>& data)
{
	m_pointsList.DeleteAllItems();

	std::for_each(data.rbegin(), data.rend(), [&](auto & point) {
		auto index = m_pointsList.InsertItem(0, std::to_wstring(point.x).c_str());
		m_pointsList.SetItemText(index, 1, std::to_wstring(point.y).c_str());
	});
}

void TableDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_POINTS_LIST, m_pointsList);
}

BOOL TableDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_pointsList.DeleteAllItems();
	m_pointsList.InsertColumn(0, L"x", LVCFMT_LEFT, 150);
	m_pointsList.InsertColumn(1, L"y", LVCFMT_LEFT, 150);

	return TRUE;
}
