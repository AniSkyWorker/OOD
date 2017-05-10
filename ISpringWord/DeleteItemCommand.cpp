#include "stdafx.h"
#include "DeleteItemCommand.h"
#include "PositionErrors.h"

using namespace std;

DeleteItemCommand::DeleteItemCommand(deque<DocumentItemPtr>& items, size_t index)
	: m_items(items)
	, m_index(index)
{
}

void DeleteItemCommand::DoExecute()
{
	if (m_index >= m_items.size())
	{
        throw InvalidPositionError(m_index);
	}
	auto eraseItemIt = next(m_items.begin(), m_index);
    m_deletedItem = *eraseItemIt;
	m_items.erase(eraseItemIt);
}

void DeleteItemCommand::DoUnexecute()
{
	if (m_index > m_items.size())
	{
        throw InvalidPositionError(m_index);
	}
	m_items.insert(next(m_items.begin(), m_index), m_deletedItem);
}
