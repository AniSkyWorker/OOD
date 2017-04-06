#pragma once
#include "stdafx.h"

using namespace std;

namespace graphics_lib_pro
{
    // ����� ��� ���������
    class ICanvas
    {
    public:
        // ��������� ����� � ������� 0xRRGGBB
        virtual void SetColor(uint32_t rgbColor) = 0;
        virtual void MoveTo(int x, int y) = 0;
        virtual void LineTo(int x, int y) = 0;
        virtual ~ICanvas() = default;
    };

    // ���������� ������ ��� ���������
    class CCanvas : public ICanvas
    {
    public:
        void SetColor(uint32_t rgbColor) override
        {
            // TODO: ������� � output ���� � ���� ������ SetColor (#RRGGBB)
        }
        void MoveTo(int x, int y) override
        {
            // ���������� �������� ��� ���������
        }
        void LineTo(int x, int y) override
        {
            // ���������� �������� ��� ���������
        }
    };
}

// ������������ ���� ����������� ����������� ����������� ���������� (���������� ��� ���������)
namespace modern_graphics_lib_pro
{
    class CPoint
    {
    public:

        CPoint(int x, int y) :x(x), y(y) {}

        int x;
        int y;
    };

    // ���� � ������� RGBA, ������ ��������� ��������� �������� �� 0.0f �� 1.0f
    class CRGBAColor
    {
    public:
        CRGBAColor(float r, float g, float b, float a) :r(r), g(g), b(b), a(a) {}
        float r, g, b, a;
    };

    // ����� ��� ������������ ��������� �������
    class CModernGraphicsRenderer
    {
    public:
        CModernGraphicsRenderer(ostream & strm) : m_out(strm)
        {
        }

        ~CModernGraphicsRenderer()
        {
            // ���������� �������� ��� ���������
        }

        // ���� ����� ������ ���� ������ � ������ ���������
        void BeginDraw()
        {
            // ���������� �������� ��� ���������
        }

        // ��������� ��������� �����
        void DrawLine(const CPoint & start, const CPoint & end, const CRGBAColor& color)
        {
            // TODO: ������� � output ���������� ��� ��������� ����� � ����
            // <line fromX="3" fromY="5" toX="5" toY="17">
            //   <color r="0.35" g="0.47" b="1.0" a="1.0" />
            // </line>
            // ����� �������� ������ ����� BeginDraw() � EndDraw()
        }

        // ���� ����� ������ ���� ������ � ����� ���������
        void EndDraw()
        {
            // ���������� �������� ��� ���������
        }
    private:
        ostream & m_out;
        bool m_drawing = false;
    };
}