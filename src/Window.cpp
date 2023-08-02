#include "Window.h"

Window::Window()
	:	m_renderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Abys Ascender")
{
	m_renderWindow.setFramerateLimit(60);
}

sf::RenderWindow& Window::getRenderedWindow()
{
	return m_renderWindow;
}
