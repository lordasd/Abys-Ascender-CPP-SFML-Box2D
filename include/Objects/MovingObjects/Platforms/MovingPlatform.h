#pragma once

#include "MovingObject.h"

class MovingPlatform : public MovingObject {
public:
	MovingPlatform(const sf::Texture& texture, const sf::Vector2f& position, float interval, float velocity);
	virtual void update(float deltaTime) override;

	const b2Vec2* getVertices() const;
	int32 getVerticesAmount() const;

protected:
	b2ChainShape m_chainShape;
	float m_elapsedTime{};
	float m_interval;
};