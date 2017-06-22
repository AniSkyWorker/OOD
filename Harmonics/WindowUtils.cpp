#include "stdafx.h"
#include "WindowUtils.h"

namespace window_utils
{
float GetEditValue(const CWnd& edit)
{
	try
	{
		CString str;
		edit.GetWindowTextW(str);
		if (str.IsEmpty() || str == L"-")
		{
			return 0;
		}
		return boost::lexical_cast<float>(str.GetBuffer());
	}
	catch (...)
	{
		return 0;
	}

}

std::wstring GetControlText(const CWnd & edit)
{
    CString str;
    edit.GetWindowTextW(str);
    return str.GetString();
}
CRect GetWindowRect(const CWnd & parent, const CWnd & control)
{
    CRect rect;
    control.GetWindowRect(&rect);
    parent.ScreenToClient(rect);

    return rect;
}
}
