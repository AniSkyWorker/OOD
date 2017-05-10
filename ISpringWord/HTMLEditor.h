#pragma once
#include "IParagraph.h"
#include "IImage.h"
class IDocument;

class HTMLEditor
{
public:
    HTMLEditor(const IDocument & document);

    void Save(const boost::filesystem::path & path);

private:
    std::string CreateBody(const boost::filesystem::path & path);
    std::string CreateParagraph(const IParagraphCPtr & paragraph);
    std::string CreateImage(const IImageCPtr & image, const boost::filesystem::path & path);

    const IDocument & m_document;
};

