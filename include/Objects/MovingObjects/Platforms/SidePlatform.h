#pragma once

#include "MovingPlatform.h"

class SidePlatform : public MovingPlatform {
public:
	SidePlatform(const sf::Texture& texture, const sf::Vector2f& position, float interval, float velocity, const Direction& direction, b2World* world);
};