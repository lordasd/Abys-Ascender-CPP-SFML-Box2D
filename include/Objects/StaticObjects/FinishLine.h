#pragma once

#include "StaticObject.h"
#include <SFML/Graphics.hpp>

class FinishLine : public StaticObject {
public:
	FinishLine(const sf::Vector2f& position, b2World* world);
	virtual void update(float) override {};
	virtual void render(sf::RenderWindow&) const override {};
};