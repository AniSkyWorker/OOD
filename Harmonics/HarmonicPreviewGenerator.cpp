#include "stdafx.h"
#include "HarmonicPreviewGenerator.h"

namespace harmonic_preview
{
namespace
{
const std::map<FunctionType, std::wstring> FUNCTION_TYPE = {
    { FunctionType::Sin, L"sin" },
    { FunctionType::Cos, L"cos" },
};

std::wstring GetPhaseValue(float value)
{
    std::wostringstream strm;
    if (value != 0)
    {
        strm << std::abs(value);
        return ((value < 0) ? L" - " : L" + ") + strm.str();
    }

    return L"";
}
}

std::wstring CreateHarmonicString(float amplitude, FunctionType function, float frequency, float phase)
{
	std::wostringstream strm;
	strm << amplitude << L"*" << FUNCTION_TYPE.at(function) << L"(";

	if (frequency != 1)
	{
		strm << frequency << L"*x";
	}
	else
	{
		strm << L"x";
	}

	strm << GetPhaseValue(phase) << L")";
	return strm.str();
}
}
