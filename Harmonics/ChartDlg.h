#pragma once
#include "IChartView.h"
#include "Resource.h"

class ChartDlg
    : public CDialog
    , public IChartView
{
public:
	ChartDlg(CWnd* pParent = NULL);
    DECLARE_DYNAMIC(ChartDlg)
	enum { IDD = IDD_CHART_VIEW_DIALOG };

    void SetPointsInfo(const std::vector<Point>& data) final;

protected:
    void DoDataExchange(CDataExchange* pDX) final;
	DECLARE_MESSAGE_MAP()

private:
    Point GetScale();
    Point TranslatePoint(Point point, Point scale);

    afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
    void UpdateBounds();

    std::vector<Point> m_points;
    Point m_leftTop;
    Point m_rightBottom;
};
