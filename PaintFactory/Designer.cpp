#include "stdafx.h"
#include "Designer.h"

CDesigner::CDesigner(std::unique_ptr<IShapeFactory>&& factory)
    : m_shapesFactory(std::move(factory))
{}

const IPictureDraft & CDesigner::CreateDraft(std::istream & strm)
{
    std::cout << "Enter shape and params:" << "\n";

    std::string shapeDescription;
    while (std::getline(strm, shapeDescription))
    {
        if (!shapeDescription.empty())
        {
            try
            {
                m_draft.InsertShape(std::move(m_shapesFactory->CreateShape(shapeDescription)));
            }
            catch (const std::exception & exp)
            {
                std::cout << exp.what() << "\n";
            }
        }
    }
    return m_draft;
}
