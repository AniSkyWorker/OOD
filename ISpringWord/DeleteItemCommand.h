#pragma once
#include "AbstractCommand.h"
#include "DocumentItem.h"

class DeleteItemCommand : public CAbstractCommand
{
public:
	DeleteItemCommand(std::deque<DocumentItemPtr>& items, size_t index);

protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	std::deque<DocumentItemPtr>& m_items;
	DocumentItemPtr m_deletedItem;
	size_t m_index;
};

