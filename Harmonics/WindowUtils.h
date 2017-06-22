#pragma once
#include <afxwin.h>

namespace window_utils
{
float GetEditValue(const CWnd& edit);
std::wstring GetControlText(const CWnd& edit);
CRect GetWindowRect(const CWnd& parent, const CWnd& control);
}