#include "stdafx.h"
#include "Image.h"
#include "History.h"
#include "ResizeCommand.h"

using namespace std;
using namespace boost::filesystem;

CImage::CImage(const path & path, unsigned width, unsigned height, CHistory& history)
    : m_width(width)
    , m_height(height)
    , m_history(history)
{
    if (!exists(path))
    {
        throw runtime_error("Incorrect image path: " + path.generic_string());
    }
    char unique_name[FILENAME_MAX];
    tmpnam(unique_name);

    string pathPageStr(unique_name);
    pathPageStr += path.extension().generic_string();
    copy_file(path, pathPageStr);
    m_path = pathPageStr;
}

CImage::~CImage()
{
    remove(m_path);
}

string CImage::GetPath() const
{
    return m_path;
}

int CImage::GetWidth() const
{
    return m_width;
}

int CImage::GetHeight() const
{
    return m_height;
}

void CImage::Resize(int width, int height)
{
    m_history.AddAndExecuteCommand(make_unique<ResizeCommand>(m_width, m_height, width, height));
}
