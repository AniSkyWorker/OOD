#include "stdafx.h"
#include "HTMLEditor.h"
#include "IDocument.h"

using namespace std;
using namespace boost::filesystem;

namespace
{
constexpr char IMAGES[] = "images";
}

HTMLEditor::HTMLEditor(const IDocument & document)
    : m_document(document)
{
}

void HTMLEditor::Save(const path & path)
{
    if (path.empty())
    {
        throw runtime_error("Path cannot be empty!");
    }

    if (path.has_parent_path())
    {
        create_directories(path.parent_path());
    }

    std::ofstream file(path.string());

    if (!file.is_open())
    {
        throw runtime_error("Invalid path specified" + path.string());
    }

    file << "<!DOCTYPE html><html><head><title>" << m_document.GetTitle() << "</title></head>"
        << "<body>" << CreateBody(path) << "</body></html>";
    file.close();
}

string HTMLEditor::CreateBody(const path & path)
{
    string body;
    for (size_t i = 0; i < m_document.GetItemsCount(); i++)
    {
        const auto& item = m_document.GetItem(i);
        if (item.GetParagraph())
        {
            body += CreateParagraph(item.GetParagraph());
        }
        else if (item.GetImage())
        {
            body += CreateImage(item.GetImage(), path);
        }
    }
    return body;
}

string HTMLEditor::CreateParagraph(const IParagraphCPtr & paragraph)
{
    return "<p>" + paragraph->GetText() + "</p>";
}

string HTMLEditor::CreateImage(const IImageCPtr & image, const path & imgPath)
{
    auto imgDirPath = path(IMAGES);
    auto relativePath = imgDirPath / path(image->GetPath()).filename();
    create_directories(imgPath.parent_path() / imgDirPath);
    copy_file(image->GetPath(), imgPath.parent_path() / relativePath, copy_option::overwrite_if_exists);
    return "<img src='" + relativePath.string()+ "' height=" + to_string(image->GetHeight())+ " width=" + to_string(image->GetWidth()) + ">";
}
