#pragma once
#include "AbstractCommand.h"
#include "IParagraph.h"
#include "DocumentItem.h"

class InsertDocumentItemCommand : public CAbstractCommand
{
public:
    InsertDocumentItemCommand(std::deque<DocumentItemPtr> & items, DocumentItemPtr item, const boost::optional<size_t> & position);

protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	std::deque<DocumentItemPtr> & m_items;
	DocumentItemPtr m_item;
	boost::optional<size_t> m_position;
};

