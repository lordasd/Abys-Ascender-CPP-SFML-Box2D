#pragma once

#include "MovingPlatform.h"

class ElevatorPlatform : public MovingPlatform {
public:
	ElevatorPlatform(const sf::Texture& texture, const sf::Vector2f& position, const Direction& direction, float interval, float velocity, b2World* world);
};