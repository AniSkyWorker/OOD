#include "stdafx.h"
#include "Triangle.h"
#include "ICanvas.h"
#include "Rect.h"

using namespace std;

Triangle::Triangle(const Point& first, const Point& second, const Point& third)
    : m_first(first)
    , m_second(second)
    , m_third(third)
{
    UpdateFrame();
}

void Triangle::DrawBehavior(ICanvas & canvas) const
{
    auto frame = GetFrame();
    canvas.MoveTo(frame.left, frame.top + frame.height);
    canvas.LineTo(frame.left + (frame.width / 2.f), frame.top);
    canvas.LineTo(frame.left + frame.width, frame.top + frame.height);
    canvas.LineTo(frame.left, frame.top + frame.height);
}

void Triangle::UpdateFrame()
{
    float minX = numeric_limits<float>::infinity();
    float minY = numeric_limits<float>::infinity();
    float maxX = -numeric_limits<float>::infinity();
    float maxY = -numeric_limits<float>::infinity();

    auto updateFrame = [&](Point& point) {

        minX = min(minX, point.x);
        minY = min(minY, point.y);
        maxX = max(maxX, point.x);
        maxY = max(maxY, point.y);
    };

    updateFrame(m_first);
    updateFrame(m_second);
    updateFrame(m_third);

    m_frame = { minX, minY, maxX - minX, maxY - minY };
}

Rect Triangle::GetFrame() const
{
    return m_frame;
}

void Triangle::SetFrame(const Rect & rect)
{
    auto oldFrame = GetFrame();

    auto updatePointPos = [&](Point& point) {
        point.x = rect.left + (point.x - oldFrame.left) / oldFrame.width * rect.width;
        point.y = rect.top + (point.y - oldFrame.top) / oldFrame.height * rect.height;
    };

    updatePointPos(m_first);
    updatePointPos(m_second);
    updatePointPos(m_third);

    UpdateFrame();
}
