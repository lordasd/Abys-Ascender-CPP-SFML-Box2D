#pragma once

#include "MovingObject.h"

class Drop : public MovingObject {
public:
	Drop(const sf::Sprite& texture, const sf::Vector2f& position, float interval, float velocity, b2World* world);
	virtual void update(float deltaTime) override;
	void remove();
	bool needRemove() const;

private:
	float m_elapsedTime{};
	float m_interval;
	bool m_remove = false;
};