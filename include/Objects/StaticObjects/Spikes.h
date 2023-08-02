#pragma once

#include "StaticObject.h"
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

class Spikes : public StaticObject {
public:
	Spikes(const sf::Sprite& texture, const sf::Vector2f& position, b2World* world);
	size_t getDamage() const;

private:
	size_t m_damage = SPIKE_DAMAGE;
};