#include "stdafx.h"
#include "InsertDocumentItemCommand.h"
#include "PositionErrors.h"

using namespace std;

InsertDocumentItemCommand::InsertDocumentItemCommand(deque<DocumentItemPtr> & items, DocumentItemPtr item, const boost::optional<size_t> & position)
	: m_items(items)
	, m_item(item)
	, m_position(position)
{
}

void InsertDocumentItemCommand::DoExecute()
{
    auto position = m_position.get_value_or(m_items.size());
	if (position > m_items.size())
	{
		throw InvalidPositionError(position);
	}
	m_items.insert(next(m_items.begin(), position), m_item);
}

void InsertDocumentItemCommand::DoUnexecute()
{
    assert(m_items.size() > 0);
    auto position = m_position.get_value_or(m_items.size() - 1);
	if (position >= m_items.size())
	{
        throw InvalidPositionError(position);
	}
	m_items.erase(next(m_items.begin(), position));
}
