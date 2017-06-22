#include "stdafx.h"
#include "ChartDlg.h"
#include "WindowUtils.h"

IMPLEMENT_DYNAMIC(ChartDlg, CDialog)
BEGIN_MESSAGE_MAP(ChartDlg, CDialog)
    ON_WM_PAINT()
END_MESSAGE_MAP()

ChartDlg::ChartDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_CHART_VIEW_DIALOG, pParent)
{
}

void ChartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BOOL ChartDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	return TRUE;
}

void ChartDlg::SetPointsInfo(const std::vector<Point>& data)
{
    m_points = data;
    UpdateBounds();
    RedrawWindow();
}

Point ChartDlg::GetScale()
{
    CRect dlgRect;
    GetClientRect(dlgRect);

    const int width = dlgRect.Width();
    const int heigth = dlgRect.Height();
    const float chartWidth = m_rightBottom.x - m_leftTop.x;
    const float chartHeight = m_rightBottom.y - m_leftTop.y;

    const float scaleX = (width - 5) / chartWidth;
    const float scaleY = (heigth - 5) / chartHeight;

    return Point(scaleX, scaleY);
}

Point ChartDlg::TranslatePoint(Point point, Point scale)
{
    return Point((point.x - m_leftTop.x) * scale.x, (point.y - m_leftTop.y) * scale.y);
}

void ChartDlg::OnPaint()
{
    CPaintDC dc(this);

    if (m_points.empty())
    {
        return;
    }

    auto scale = GetScale();

    CPen pen;
    pen.CreatePen(PS_SOLID, 2, RGB(255, 0, 255));
    auto oldPen = dc.SelectObject(&pen);

    auto firstPt = TranslatePoint(m_points.front(), scale);
    dc.MoveTo(static_cast<int>(firstPt.x), static_cast<int>(firstPt.y));
    for (size_t i = 1; i < m_points.size(); ++i)
    {
        auto pt = TranslatePoint(m_points[i], scale);
        dc.LineTo(static_cast<int>(pt.x), static_cast<int>(pt.y));
    }

    dc.SelectObject(oldPen);
}

void ChartDlg::UpdateBounds()
{
    m_leftTop = Point();
    m_rightBottom = Point();
    if (!m_points.empty())
    {
        m_leftTop = m_points.front();
        m_rightBottom = m_points.front();
        for (const auto & pt : m_points)
        {
            m_leftTop.x = min(m_leftTop.x, pt.x);
            m_rightBottom.x = max(m_rightBottom.x, pt.x);
            m_leftTop.y = min(m_leftTop.y, pt.y);
            m_rightBottom.y = max(m_rightBottom.y, pt.y);
        }
        if (m_leftTop.y == m_rightBottom.y)
        {
            m_leftTop.y -= 1;
            m_rightBottom.y += 1;
        }
        if (m_leftTop.x == m_rightBottom.x)
        {
            m_leftTop.x -= 1;
            m_rightBottom.x += 1;
        }
    }
}
