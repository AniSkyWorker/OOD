#pragma once
#include "Resource.h"
#include "IChartView.h"

class TableDlg
    : public CDialogEx
    , public IChartView
{
public:
	TableDlg(CWnd* pParent = nullptr);

    DECLARE_DYNAMIC(TableDlg)
    enum { IDD = IDD_TABLE_VIEW_DIALOG };

	void SetPointsInfo(const std::vector<Point>& data) final;
    BOOL OnInitDialog() final;

protected:
	void DoDataExchange(CDataExchange* pDX) final;
	DECLARE_MESSAGE_MAP()

private:
	CListCtrl m_pointsList;
};
