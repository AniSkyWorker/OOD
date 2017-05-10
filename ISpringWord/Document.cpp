#include "stdafx.h"
#include "Document.h"
#include "ChangeStringCommand.h"
#include "InsertDocumentItemCommand.h"
#include "DeleteItemCommand.h"  
#include "HTMLEditor.h"
#include "Paragraph.h"
#include "Image.h"
#include "PositionErrors.h"

using namespace std;

void CDocument::SetTitle(const std::string & title)
{
	m_history.AddAndExecuteCommand(make_unique<CChangeStringCommand>(m_title, title));
}

std::string CDocument::GetTitle() const
{
	return m_title;
}

bool CDocument::CanUndo() const
{
	return m_history.CanUndo();
}

void CDocument::Undo()
{
	m_history.Undo();
}

bool CDocument::CanRedo() const
{
	return m_history.CanRedo();
}

void CDocument::Redo()
{
	m_history.Redo();
}

void CDocument::Save(const std::string& path) const
{
    HTMLEditor converter(*this);
    converter.Save(path);
}

IParagraphPtr CDocument::InsertParagraph(const std::string & text, const boost::optional<size_t> & position)
{
    auto paragraph = make_shared<CParagraph>(text, m_history);
    auto item = make_shared<CDocumentItem>(paragraph);
    m_history.AddAndExecuteCommand(make_unique<InsertDocumentItemCommand>(m_items, item, position));
    return paragraph;
}

IImagePtr CDocument::InsertImage(const std::string & path, int width, int height, const boost::optional<size_t>& position)
{
    auto image = make_shared<CImage>(path, width, height, m_history);
    auto item = make_shared<CDocumentItem>(image);
    m_history.AddAndExecuteCommand(make_unique<InsertDocumentItemCommand>(m_items, item, position));
    return image;
}

void CDocument::DeleteItem(size_t position)
{
    m_history.AddAndExecuteCommand(make_unique<DeleteItemCommand>(m_items, position));
}

size_t CDocument::GetItemsCount() const
{
    return m_items.size();
}

CConstDocumentItem CDocument::GetItem(size_t position) const
{
    return FindItem(position);
}

CDocumentItem CDocument::GetItem(size_t position)
{
    return FindItem(position);
}

CDocumentItem& CDocument::FindItem(size_t position)const
{
    if (position >= m_items.size())
    {
        throw InvalidPositionError(position);
    }
    return **next(m_items.begin(), position);
}

