#pragma once
#include "stdafx.h"

using namespace std;

namespace graphics_lib_pro
{
    // Холст для рисования
    class ICanvas
    {
    public:
        // Установка цвета в формате 0xRRGGBB
        virtual void SetColor(uint32_t rgbColor) = 0;
        virtual void MoveTo(int x, int y) = 0;
        virtual void LineTo(int x, int y) = 0;
        virtual ~ICanvas() = default;
    };

    // Реализация холста для рисования
    class CCanvas : public ICanvas
    {
    public:
        void SetColor(uint32_t rgbColor) override
        {
            // TODO: вывести в output цвет в виде строки SetColor (#RRGGBB)
        }
        void MoveTo(int x, int y) override
        {
            // Реализация остается без изменения
        }
        void LineTo(int x, int y) override
        {
            // Реализация остается без изменения
        }
    };
}

// Пространство имен обновленной современной графической библиотеки (недоступно для изменения)
namespace modern_graphics_lib_pro
{
    class CPoint
    {
    public:

        CPoint(int x, int y) :x(x), y(y) {}

        int x;
        int y;
    };

    // Цвет в формате RGBA, каждый компонент принимает значения от 0.0f до 1.0f
    class CRGBAColor
    {
    public:
        CRGBAColor(float r, float g, float b, float a) :r(r), g(g), b(b), a(a) {}
        float r, g, b, a;
    };

    // Класс для современного рисования графики
    class CModernGraphicsRenderer
    {
    public:
        CModernGraphicsRenderer(ostream & strm) : m_out(strm)
        {
        }

        ~CModernGraphicsRenderer()
        {
            // Реализация остается без изменения
        }

        // Этот метод должен быть вызван в начале рисования
        void BeginDraw()
        {
            // Реализация остается без изменения
        }

        // Выполняет рисование линии
        void DrawLine(const CPoint & start, const CPoint & end, const CRGBAColor& color)
        {
            // TODO: выводит в output инструкцию для рисования линии в виде
            // <line fromX="3" fromY="5" toX="5" toY="17">
            //   <color r="0.35" g="0.47" b="1.0" a="1.0" />
            // </line>
            // Можно вызывать только между BeginDraw() и EndDraw()
        }

        // Этот метод должен быть вызван в конце рисования
        void EndDraw()
        {
            // Реализация остается без изменения
        }
    private:
        ostream & m_out;
        bool m_drawing = false;
    };
}