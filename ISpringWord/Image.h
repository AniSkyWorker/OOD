#pragma once
#include "IImage.h"

class CHistory;

class CImage : public IImage
{
public:
    CImage(const boost::filesystem::path & path, unsigned width, unsigned height, CHistory& history);
    ~CImage();

    std::string GetPath() const override;
    int GetWidth() const override;
    int GetHeight() const override;
    void Resize(int width, int height) override;

private:
    std::string m_path;
    unsigned m_width;
    unsigned m_height;
    CHistory& m_history;
};