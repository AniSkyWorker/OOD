#pragma once
#include "IDocument.h"
#include "History.h"

class CDocument: public IDocument
{
public:
	void SetTitle(const std::string & title) override;
	std::string GetTitle() const override;

	bool CanUndo() const override;	
	void Undo() override;
	bool CanRedo() const override;
	void Redo() override;
    void Save(const std::string& path) const;

    IParagraphPtr InsertParagraph(const std::string& text, 
        const boost::optional<size_t> & position) override;

    IImagePtr InsertImage(const std::string& path, int width, int height,
        const boost::optional<size_t> & position) override;

    void DeleteItem(size_t position) override;

    size_t GetItemsCount() const override;
    CConstDocumentItem GetItem(size_t position) const override;
    CDocumentItem GetItem(size_t position) override;

private:
    CDocumentItem & CDocument::FindItem(size_t position) const;

	std::string m_title;
	CHistory m_history;
    std::deque<DocumentItemPtr> m_items;
};