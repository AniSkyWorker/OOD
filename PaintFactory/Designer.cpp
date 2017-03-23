#include "stdafx.h"
#include "Designer.h"

CDesigner::CDesigner(std::unique_ptr<IShapeFactory>&& factory)
    : m_shapesFactory(std::move(factory))
{}

const IPictureDraft & CDesigner::CreateDraft(std::istream & strm)
{
    std::string shapeDescription;
    std::cout << "Enter shape and params:" << "\n";
    while (!strm.eof())
    {
        m_draft.InsertShape(std::move(m_shapesFactory->CreateShape(strm)));
    }
    return m_draft;
}
