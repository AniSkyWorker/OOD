#pragma once
#include <memory>
#include <string>
#include "IParagraph.h"
#include "IImage.h"

class CConstDocumentItem
{
public:
    CConstDocumentItem(const IParagraphPtr & paragraph);
    CConstDocumentItem(const IImagePtr & image);
    // Возвращает указатель на константное изображение, либо nullptr,
    // если элемент не является изображением
    std::shared_ptr<const IImage> GetImage() const;
    // Возвращает указатель на константный параграф, либо nullptr, если элемент не является параграфом
    std::shared_ptr<const IParagraph> GetParagraph() const;
    virtual ~CConstDocumentItem() = default;

protected:
    IParagraphPtr m_paragraph;
    IImagePtr m_image;
};