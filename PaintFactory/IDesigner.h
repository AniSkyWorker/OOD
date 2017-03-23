#pragma once
#include "IPictureDraft.h"

class IDesigner
{
public:
	virtual const IPictureDraft & CreateDraft(std::istream & strm) = 0;

	virtual ~IDesigner() = default;
};