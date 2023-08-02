#pragma once

#include "Mob.h"

class SkeletonMelee : public Mob {
public:
	SkeletonMelee(const std::vector<sf::Sprite>& animation, float interval, const sf::Vector2f& position, float velocity, b2World* world);
	virtual void update(float delta) override;
	virtual void setVolume() override;

private:
	float m_hurtElapsedTime{};
	sf::Sound m_death;
	sf::Sound m_hurt;
	bool m_hurtPlayed = false;
	bool m_deathPlayed = false;
};