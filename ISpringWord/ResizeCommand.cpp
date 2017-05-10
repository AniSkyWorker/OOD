#include "stdafx.h"
#include "ResizeCommand.h"

using namespace std;

ResizeCommand::ResizeCommand(unsigned & width, unsigned & height, unsigned newWidth, unsigned newHeight)
	: m_width(width)
	, m_height(height)
	, m_newWidth(newWidth)
	, m_newHeight(newHeight)
{
}

void ResizeCommand::DoExecute()
{
    SwapValues();
}

void ResizeCommand::DoUnexecute()
{
    SwapValues();
}

void ResizeCommand::SwapValues()
{
    swap(m_width, m_newWidth);
    swap(m_height, m_newHeight);
}


