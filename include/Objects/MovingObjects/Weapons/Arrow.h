#pragma once

#include "Weapon.h"
#include "Operation.h"

class Arrow : public Weapon {
public:
	Arrow(const sf::Sprite& sprite, const Direction& direction, const sf::Vector2f& position, b2World* world);
};