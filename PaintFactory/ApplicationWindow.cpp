#include "stdafx.h"
#include "ApplicationWindow.h"

ApplicationWindow::ApplicationWindow()
    : m_window(sf::VideoMode(1024, 760), "AppWindow", sf::Style::Close)
{
}

void ApplicationWindow::Run(const RenderFunc& renderCallback)
{
    while (m_window.isOpen())
    {
        ProcessEvents();
        Render(renderCallback);
    }
}

void ApplicationWindow::ProcessEvents()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            m_window.close();
            break;
        }
    }
}

void ApplicationWindow::Render(const RenderFunc& renderCallback)
{
    m_window.clear();
    renderCallback(m_window);
    m_window.setView(m_window.getDefaultView());
    m_window.display();
}