#include "stdafx.h"
#include "HTMLEditor.h"
#include "IDocument.h"

using namespace std;
using namespace boost::filesystem;

namespace
{
constexpr char IMAGES[] = "images";
const map<char, string> HTML_ENCODE_MAP = {
    { '<', "&lt;" },
    { '>', "&gt;" },
    { '&', "&amp;" },
    { '"', "&quot;" },
    { '\'', "&quot;" },
};

string EncodeHtmlStr(const string & str)
{
    string encodedStr;
    for (size_t i = 0; i < str.size(); i++)
    {
        auto encodeCharIt = HTML_ENCODE_MAP.find(str[i]);
        if (encodeCharIt != HTML_ENCODE_MAP.end())
        {
            encodedStr += encodeCharIt->second;
            continue;
        }
        encodedStr += str[i];
    }
    return encodedStr;
}
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

    std::ofstream file(path.generic_string());

    if (!file.is_open())
    {
        throw runtime_error("Invalid path specified" + path.generic_string());
    }

    file << "<!DOCTYPE html>\n<html>\n<head>\n\t<title>" << EncodeHtmlStr(m_document.GetTitle()) << "</title>\n</head>\n"
        << "<body>\n" << CreateBody(path) << "</body>\n</html>";
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
    return "\t<p>" + EncodeHtmlStr(paragraph->GetText()) + "</p>\n";
}

string HTMLEditor::CreateImage(const IImageCPtr & image, const path & imgPath)
{
    auto imgDirPath = path(IMAGES);
    auto relativePath = imgDirPath / path(image->GetPath()).filename();
    create_directories(imgPath.parent_path() / imgDirPath);
    copy_file(image->GetPath(), imgPath.parent_path() / relativePath, copy_option::overwrite_if_exists);
    return "\t<img src='" + EncodeHtmlStr(relativePath.generic_string()) + "' height=" + to_string(image->GetHeight())+ " width=" + to_string(image->GetWidth()) + ">\n";
}
