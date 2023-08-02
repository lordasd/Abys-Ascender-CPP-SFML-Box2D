#pragma once

#include "StaticObject.h"
#include <SFML/Graphics.hpp>

class Decoration : public StaticObject {
public:
	Decoration(const sf::Sprite& texture, const sf::Vector2f& position);
};