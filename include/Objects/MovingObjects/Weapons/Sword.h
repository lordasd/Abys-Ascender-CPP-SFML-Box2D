#pragma once

#include "Weapon.h"
#include "Operation.h"

class Sword : public Weapon {
public:
	Sword(const Direction& direction, const sf::Vector2f& position, b2World* world);

};