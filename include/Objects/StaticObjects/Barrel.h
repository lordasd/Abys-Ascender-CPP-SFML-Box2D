#pragma once

#include "StaticObject.h"
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

class Barrel : public StaticObject {
public:
	Barrel(const sf::Sprite& texture, const sf::Vector2f& position, b2World* world);
};