#pragma once
#include "IDesigner.h"
#include "IShapeFactory.h"
#include "PictureDraft.h"

class CDesigner : public IDesigner
{
public:
    CDesigner(std::unique_ptr<IShapeFactory> && factory);

    const IPictureDraft & CreateDraft(std::istream & strm) override;

private:
    std::unique_ptr<IShapeFactory> m_shapesFactory;
    CPictureDraft m_draft;
};

