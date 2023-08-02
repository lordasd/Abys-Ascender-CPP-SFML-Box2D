#pragma once

#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include "MovingObject.h"
#include "Config.h"

enum class WeaponType { Sword, Arrow };

class Weapon : public MovingObject {
public:
	Weapon(const sf::Sprite& sprite, const sf::Vector2f& position, float velocity, float lifeTime);
	Weapon(const sf::Vector2f& position, float velocity, float lifeTime);
	virtual void update(float deltaTime) override;
	virtual void render(sf::RenderWindow& window) const override;
	bool isHit() const;
	void setHit();

private:
	float m_lifeTime;
	float m_elapsedTime{};
	bool m_hit = false;
};