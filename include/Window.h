#pragma once

#include <SFML/Graphics.hpp>
#include "Config.h"

class Window {
public:
	Window();
	sf::RenderWindow& getRenderedWindow();

private:
	sf::RenderWindow m_renderWindow;
};