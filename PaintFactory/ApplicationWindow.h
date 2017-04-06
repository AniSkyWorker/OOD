#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

class ApplicationWindow
{
public:
    using RenderFunc = std::function<void(sf::RenderTarget &)>;
    ApplicationWindow();

    void Run(const RenderFunc& renderCallback);

private:
    void ProcessEvents();
    void Render(const RenderFunc& renderCallback);

    sf::RenderWindow m_window;
};