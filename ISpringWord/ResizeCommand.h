#pragma once
#include "AbstractCommand.h"

class ResizeCommand
    : public CAbstractCommand
{
public:
	ResizeCommand(unsigned & width, unsigned & height, unsigned newWidth, unsigned newHeight);

protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
    void SwapValues();

	unsigned & m_width;
	unsigned & m_height;
	unsigned m_newWidth;
	unsigned m_newHeight;
};

